#include "bulbctrl.h"

#include "sas/timer.h"
#include "sas/debug.h"
#include "sas/pulse.h"

#include "cfg/hw_config.h"
#include "mcc_generated_files/adc1.h"

#include <stdio.h>

enum
{
   kBulbCtrlErrIncompleteADC = 1 << 0,
};


typedef struct
{
   uint32_t data[5];
   size_t index;
   size_t count;
} AvgList;


typedef struct
{
   size_t skip_phases;
   size_t priority;
   bool is_on;
   
   uint32_t power_sum;
   size_t power_sum_count;
   
   AvgList avg_power_on;
   AvgList avg_power_off;
   AvgList avg_switch_on;
   AvgList avg_switch_off;
   
} BulbMonitor;


typedef struct
{
   BulbConfig config;

   uint32_t output_map;
   uint32_t last_output_map;
   
   uint32_t last_port;
   size_t monitoring;
   
   bool isr_phase;
   bool have_phase;
   uint32_t time_last_phase;

   uint32_t main_power_timeout;
   uint32_t burnt_bulb_map;
   uint32_t burnt_triac_map;

   uint32_t errors;
   size_t bulb_index;
   size_t power_index;
   size_t mux_index;
   BulbMonitor mon[12];
   
   uint32_t power_sum;
   uint32_t power_sum_count;
   
   bool dbg_print_adc_values;
   uint32_t power_value[(20 - 1) * 8]; // not necessary 
   
   bool dbg_print_prio;
   
   uint32_t time_phase;
   uint32_t time_timer;
      
} BulbCtrlInt;


////////////////////////////////////////////////////////////////////////////////////////////////////


static BulbCtrlInt bc;
static void on_next_phase(void);
static void on_phase_start(void);
static void avg_add(AvgList * avg, uint32_t value);
static uint32_t avg_comp(AvgList * avg);
static uint32_t avg_sum(AvgList * avg);

static uint8_t print_buff[1024];
static size_t dbg_elected_ch;


////////////////////////////////////////////////////////////////////////////////////////////////////


void __ISR(_TIMER_1_VECTOR, IPL4AUTO) _T1Interrupt (void)
{
   IFS0CLR = 1 << _IFS0_T1IF_POSITION;
   on_next_phase();
}

void __ISR (_CHANGE_NOTICE_VECTOR, IPL4AUTO) _CHANGE_NOTICE ( void )
{
   if(IFS1bits.CNBIF)
   {
      uint32_t port = *bc.config.sig_port;
      uint32_t mod = bc.last_port ^ port;
      
      // If phase input is rising
      if(mod & bc.config.sig_port_mask && (port & bc.config.sig_port_mask))
      {
         on_phase_start();
      }     
     
      bc.last_port = port;
      IFS1CLR = 1 << _IFS1_CNBIF_POSITION;
   }
}

static void on_phase_start(void)
{
   uint32_t time_start = _CP0_GET_COUNT();
   
   if(!bc.monitoring)
      return;

   bc.isr_phase = true;
   
   // DBG
   TRISFCLR = 1 << 1;
   LATFCLR = 2;
   // LATFSET = 2;
   
   uint32_t map = bc.output_map;
   for(size_t i = 0; i < bc.config.pin_out_count; i++, map >>= 1)
   {
      bulb_ctrl_set(i, (map & 1) > 0);
   }
   
   BulbMonitor * mon = bc.mon;
   uint32_t change_map = bc.last_output_map ^ bc.output_map;
   
   size_t highest_prio = 0;
   bc.bulb_index = bc.config.pin_out_count;
   
   for(uint32_t i = 0, mask = 1; i < bc.config.pin_out_count; i++, mask <<= 1, mon++)
   {
      mon->power_sum = 0;
      mon->power_sum_count = 0;
      mon->priority++;
      
      if (mon->skip_phases)
         mon->skip_phases--;
      
      mon->is_on = (mask & bc.output_map) > 0;
      
      if(mask & change_map)
      {
         if (mask & bc.output_map)
         {
            mon->priority += bc.config.pin_out_count;
            mon->skip_phases = bc.config.skip_on_phases;
         }
         else
         {
            mon->skip_phases = bc.config.skip_off_phases;
         }
      }
      
      if (!mon->skip_phases && highest_prio < mon->priority)
      {
         highest_prio = mon->priority;
         bc.bulb_index = i;
      }
   }
   
   bc.last_output_map = bc.output_map;

   // All are in skip phases?
   if (bc.bulb_index >= bc.config.pin_out_count)
   {
      bulb_ctrl_mux(15);
      return;
   }
   
   bulb_ctrl_mux(bc.bulb_index);
   
   if (bc.bulb_index == 3)
   {
      LATFSET = 2;
   }

   // Testing
   // U1TXREG = '0' + bc.bulb_index;
   // if (bc.bulb_index == 8 && bc.mon[8].is_on)
   //   LATFSET = 1 << 1;
   
   // Timer Start
   TMR1 = 0;
   T1CONbits.ON = 1;
   
   // ADC Start
   AD1CON1bits.SAMP = 1;
   
   bc.power_index = 0;
   bc.power_sum = 0;
   bc.power_sum_count = 0;
   
   bc.time_phase = _CP0_GET_COUNT() - time_start;
}

static void on_next_phase(void)
{
   uint32_t time_start = _CP0_GET_COUNT();
   
   uint32_t adc_value = ADC1BUF0;
   
   if (AD1CON1bits.DONE)
   {
      bc.power_value[bc.power_index] = adc_value;
   }
   else 
   {
      bc.errors |= kBulbCtrlErrIncompleteADC;
      return;
   }

   if (adc_value >= bc.config.power_noise_floor)
   {
      bc.power_sum_count++;
      bc.power_sum += adc_value;
   }
   
   bc.power_index++;
   if(bc.power_index >= COUNT(bc.power_value))
   {
      T1CONbits.ON = 0;
      
      BulbMonitor * mon = &bc.mon[bc.bulb_index];
      if (!mon->skip_phases)
      {
         AvgList * avg = (mon->is_on ? &mon->avg_power_on : &mon->avg_power_off);
         //uint32_t avg_value = bc.power_sum_count > 0 ? bc.power_sum / bc.power_sum_count : 0;
         uint32_t avg_value = bc.power_sum / 1000;
         avg_add(avg, avg_value);
         mon->priority = 0;
      }
      
      if(bc.bulb_index == 3) // && mon->is_on)
      {
         //LATFCLR = 1 << 1;
         //bc.dbg_print_adc_values = true;
         //bc.power_sum_ready = true;
      }
   }
   else
   {
      AD1CON1bits.SAMP = 1;
   }
   
   if(bc.power_index == COUNT(bc.power_value) / 4)
   {
      BulbMonitor * mon = &bc.mon[bc.bulb_index];
      
      if (!mon->skip_phases)
      {
         bool switched = pin_read(&bc.config.pin_sig_sense) == 0;
         uint32_t avg_value = switched == mon->is_on ? 0 : 99;
         
         AvgList * avg = mon->is_on ? &mon->avg_switch_on : &mon->avg_switch_off;
         avg_add(avg, avg_value);
      }
   }
   
   bc.time_timer = _CP0_GET_COUNT() - time_start;
}

static void check_bulbs(void)
{
   uint32_t burnt_bulb_map = 0;
   uint32_t burnt_triac_map = 0;
   
   uint32_t mask = 1;
   BulbMonitor * mon = bc.mon;
   for(size_t i = 0; i < bc.config.pin_out_count; i++, mon++, mask <<= 1)
   {
      AvgList * avg = &mon->avg_power_on;
      if (avg->count == COUNT(avg->data))
      {
         uint32_t value = avg_comp(avg);
         if (value <= bc.config.power_on_burnt_thresh)
         {
            burnt_bulb_map |= mask;
         }
      }
      
      avg = &mon->avg_power_off;
      if (avg->count == COUNT(avg->data))
      {
         uint32_t value = avg_comp(avg);
         if (value >= bc.config.power_off_burnt_thresh)
         {
            burnt_triac_map |= mask;
         }
      }
      
      avg = &mon->avg_switch_on;
      if (avg->count == COUNT(avg->data))
      {
         uint32_t value = avg_comp(avg);
         if (value >= bc.config.switch_on_fail_thresh)
         {
            burnt_triac_map |= mask;
         }
      }
      
      avg = &mon->avg_switch_off;
      if (avg->count == COUNT(avg->data))
      {
         uint32_t value = avg_comp(avg);
         if (value >= bc.config.switch_off_fail_thresh)
         {
            burnt_triac_map |= mask;
         }
      }
   }
      
   static uint32_t last_print = 0;
   uint32_t now = timer_tick();
   
   if ((bc.burnt_bulb_map != burnt_bulb_map || bc.burnt_triac_map != burnt_triac_map) || (now - last_print >= 2000))
   {
      bc.burnt_bulb_map = burnt_bulb_map;
      bc.burnt_triac_map = burnt_triac_map;
      bulb_ctrl_print();
      last_print = now;
   }
}

static void avg_add(AvgList * avg, uint32_t value)
{
   if(avg->count < COUNT(avg->data))
   {
      avg->data[avg->count++] = value;
   }
   else
   {
      avg->data[avg->index++] = value;
      if(avg->index >= COUNT(avg->data))
         avg->index = 0;
   }
}

static uint32_t avg_comp(AvgList * avg)
{
   uint32_t sum = 0;
   
   if(!avg->count)
      return sum;
   
   for(size_t j = 0; j < avg->count; j++)
   {
      sum += avg->data[j];
   }
   sum /= avg->count;
   
   return sum;
}

static uint32_t avg_sum(AvgList * avg)
{
   uint32_t sum = 0;
   
   for(size_t j = 0; j < avg->count; j++)
   {
      sum += avg->data[j];
   }
   
   return sum;
}

static void on_main_power_changed(bool on)
{
   if(on)
   {
      if(!bc.have_phase)
      {
         DBG(kLvlWarn, "main power ON");
      }
      
      bc.have_phase = true;
      bc.time_last_phase = timer_tick();
      pulse_enable(kPulseMainsPowerError, false);
   }
   else
   {
      bc.have_phase = false;
      DBG(kLvlWarn, "main power OFF");
      pulse_enable(kPulseMainsPowerError, true);
   }
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////


void bulb_ctrl_init(const BulbConfig * config)
{
   bc = (BulbCtrlInt){
      .config = *config,
   };
   
   bc.have_phase = true;
   bc.main_power_timeout = bc.config.main_power_timeout;
   
   pin_input(&bc.config.pin_sig_sense);
   
   for(size_t i = 0; i < bc.config.pin_out_count; i++)
   {
      pin_write(&bc.config.pin_out[i], bc.config.out_pol_invert);
      pin_output(&bc.config.pin_out[i]);
   }
   
   for(size_t i = 0; i < bc.config.pin_mux_count; i++)
   {
      pin_write(&bc.config.pin_mux[i], false);
      pin_output(&bc.config.pin_mux[i]);
   }
   
   bulb_ctrl_clear();
   
	CNCONBbits.ON = 1;
	CNENBbits.CNIEB2 = 1; // Pin : RB2

   // 0x7D0 // 0xFA0; //0x1F40; //0x3E80; // Period = 0.001 s; Frequency = 32000000 Hz; PR1 32000;    
   T1CONbits.ON = 0;
   TMR1 = 0;    
   PR1 = 0x7D00 / 8;
   T1CON = 0x0000;
   
   IPC8bits.CNIP = 4;
   IPC8bits.CNIS = 0;
   IPC1bits.T1IP = 4;
   IPC1bits.T1IS = 0;
   
   IFS1bits.CNBIF = 0;
   IEC1bits.CNBIE = 1;
   IFS0bits.T1IF = 0;
   IEC0bits.T1IE = 1;
   
   AD1CON1bits.ON = 0;
   AD1CHSbits.CH0NA = 0; // Channel 0 negative input is VR-
   AD1CHSbits.CH0SA = 1; // Channel 0 positive input is AN0
   AD1CON1bits.FORM = 0; // Integer 16-bit output
   AD1CON1bits.SSRC = 7; // Internal counter ends sampling and starts conversion
   AD1CSSL = 0; // No scanning required
   AD1CON2bits.VCFG = 0; // Internal voltage references
   AD1CON2bits.CSCNA = 0; // Do not scan inputs
   AD1CON2bits.BUFM = 0; // Buffer configured as one 16-word buffer
   AD1CON2bits.ALTS = 0; // Always use MUX A input multiplexer settings
   AD1CON3bits.ADRC = 0; // Clock derived from PBclock
   
   // WTF?!
   //AD1CON3bits.ADCS = 0b00111111; // TAD  
   //AD1CON3bits.SAMC = 0b11111; // 31 TAD auto-sample time
   AD1CON3 = 0xF;
   AD1CON3bits.SAMC = 0b111; 
   AD1CON1bits.ON = 1;
}

void bulb_ctrl_start(void)
{
   IFS1bits.CNBIF = 0;
   IEC1bits.CNBIE = 1;
   IFS0bits.T1IF = 0;
   IEC0bits.T1IE = 1;
   bulb_ctrl_monitor(true);
}

void bulb_ctrl_clear(void)
{
   bool monitor = bc.monitoring;
   bulb_ctrl_monitor(false);
   
   bc.output_map = 0;
   bc.burnt_triac_map = 0;
   bc.burnt_bulb_map = 0;
   
   BulbMonitor * mon = bc.mon;
   for(size_t i = 0; i < bc.config.pin_out_count; i++, mon++)
   {
      pin_write(&bc.config.pin_out[i], bc.config.out_pol_invert);
      mon->avg_power_on.count = 0;
      mon->avg_power_off.count = 0;
      mon->avg_switch_on.count = 0;
      mon->avg_switch_off.count = 0;
   }
   
   bulb_ctrl_monitor(monitor);
}

void bulb_ctrl_set(size_t index, bool en)
{
   if(index >= bc.config.pin_out_count)
      return;
   
   if (bc.config.out_pol_invert)
      en = !en;

   pin_write(&bc.config.pin_out[index], en);
}

void bulb_ctrl_set_map(uint32_t map)
{
   bc.output_map = map;
}

void bulb_ctrl_set_cfg(uint32_t burnt_timeout, uint32_t main_power_timeout)
{
   bc.main_power_timeout = main_power_timeout;
}

void bulb_ctrl_monitor(bool en)
{   
   bc.monitoring = en;
}

void bulb_ctrl_mux(size_t index)
{
   bc.mux_index = index;
   
   index = bc.config.map_triac_sense[index];
   
   for(size_t i = 0; i < bc.config.pin_mux_count; i++, index >>= 1)
   {
      pin_write(&bc.config.pin_mux[i], (index & 1) > 0);
   }
}

size_t bulb_ctrl_get_index()
{
   return bc.mux_index;
}

uint32_t bulb_ctrl_burnt_bulb_map(void)
{
   return bc.burnt_bulb_map;
}

uint32_t bulb_ctrl_burnt_triac_map(void)
{
   return bc.burnt_triac_map;
}

bool bulb_ctrl_have_power(void)
{
   return bc.have_phase;
}

void bulb_ctrl_print(void)
{
   size_t pos = 0;
   static bool first = true;
   
   for(size_t k = 0; k < 4; k++)
   {
      BulbMonitor * mon = bc.mon;
      
      for(size_t i = 0; i < bc.config.pin_out_count; i++, mon++)
      {
         AvgList * avg;
         switch(k)
         {
            case 0: avg = &mon->avg_power_on; break;
            case 1: avg = &mon->avg_power_off; break;
            case 2: avg = &mon->avg_switch_on; break;
            case 3: avg = &mon->avg_switch_off; break;
         }

         if (avg->count > 0)
         {
            uint32_t sum = avg_comp(avg);
            
            // if (i == 3 && k == 0)
            // {
            //   DBG(kLvlWarn, "%u %u %u %u %u %u %u", avg->count, avg->data[0], avg->data[1], avg->data[2], avg->data[3], avg->data[4], sum);
            // }
            
            pos += sprintf(&print_buff[pos], "%3u ", sum);
         }
         else
         {
            pos += sprintf(&print_buff[pos], "  . ");
         }
      }
      
      pos += sprintf(&print_buff[pos], "|  ");
   }
   
   pos += sprintf(&print_buff[pos], "%3X, %3X ", bc.burnt_bulb_map, bc.burnt_triac_map);

   if (first)
   {
      first = false;
      DBG(kLvlVerb, " ON power consumption                           |  Off power consumption                           |  ON switch detection                             |  OFF switch detection                            |");
   }
      
   DBG(kLvlVerb, "%s", print_buff);
   
   /*BulbMonitor * mon = &bc.mon[8];
   DBG(kLvlVerb, "%u %u %u %u %u", mon->avg_power_on.data[0], mon->avg_power_on.data[1], mon->avg_power_on.data[2], mon->avg_power_on.data[3], mon->avg_power_on.data[4]);
   DBG(kLvlVerb, "%u %u %u %u %u", mon->avg_power_off.data[0], mon->avg_power_off.data[1], mon->avg_power_off.data[2], mon->avg_power_off.data[3], mon->avg_power_off.data[4]);
   */
   
}

static void bulb_ctrl_print_adcvals(void)
{
   static uint32_t power_sum[COUNT(bc.power_value)];
   memcpy(power_sum, bc.power_value, sizeof(power_sum));
   
   size_t pos = 0;
   uint32_t sum = 0;

   for(size_t i = 0; i < COUNT(bc.power_value); i++)
   {
      sum += power_sum[i];
   }

   uint32_t avg = sum / COUNT(bc.power_value);

   pos = 0;
   if (avg > 0)
   {
      for(size_t i = 0; i < COUNT(bc.power_value); i++)
      {
         pos += sprintf(&print_buff[pos], "%u ", power_sum[i]);
      }

      DBG(kLvlVerb, "%s \r\n------------ %u %u", print_buff, sum, avg);
   }
}

static void bulb_ctrl_print_prio(void)
{
   BulbMonitor * mon = bc.mon;
 
   size_t pos = 0;
   for(size_t i = 0; i < bc.config.pin_out_count; i++, mon++)
   {
      pos += sprintf(&print_buff[pos], "%3u ", mon->priority);
   }
   
   mon = bc.mon;
   pos += sprintf(&print_buff[pos], "\r\n");
   
   
   bool found_skip = false;
   
   for(size_t i = 0; i < bc.config.pin_out_count; i++, mon++)
   {
      pos += sprintf(&print_buff[pos], "%3u ", mon->skip_phases);
      
      if(mon->skip_phases > 0)
         found_skip = true;
   }
   
   //if (found_skip)
   {
      DBG(kLvlVerb, "\r\n%s  %u \r\n", print_buff, bulb_ctrl_get_index());
   }
}

void bulb_ctrl_service(void)
{
   if(bc.isr_phase)
   {
      bc.isr_phase = false;
      on_main_power_changed(true);
      check_bulbs();
   }
   
   if(bc.have_phase)
   {
      if(timer_tick() - bc.time_last_phase >= bc.main_power_timeout)
      {
         bc.have_phase = false;
         on_main_power_changed(false);
      }
   }
   
   if (bc.dbg_print_adc_values)
   {
      bc.dbg_print_adc_values = false;
      bulb_ctrl_print_adcvals();
   }
   
   if (bc.dbg_print_prio)
   {
      bc.dbg_print_prio = false;
      bulb_ctrl_print_prio();
   }
   
   if (bc.errors)
   {
      if (bc.errors & kBulbCtrlErrIncompleteADC)
      {
         bc.errors -= kBulbCtrlErrIncompleteADC;
         DBG(kLvlError, "bulb, ADC sampling not complete");
      }
   }
   
   /*static uint32_t time_phase = 0;
   if (time_phase < bc.time_phase)
   {
      time_phase = bc.time_phase;
      DBG(kLvlVerb, "f %u %u", bc.time_phase, bc.time_phase / 16);
   }
   
   static uint32_t timer_max = 0;
   if (timer_max < bc.time_timer)
   {
      timer_max = bc.time_timer;
      DBG(kLvlVerb, "t %u %u", timer_max, bc.time_timer / 16);
   }*/
}