#ifndef POWER_CTRL_MSG
#define POWER_CTRL_MSG

enum PwrMsgAddr
{
   kPwrMsgAddrFirst      = 1,
   kPwrMsgAddrAny        = 0xFF,
};

enum PwrDevType
{
   kPwrMsgDevTypeCtrl    = 1,
   kPwrMsgDevTypePwrOutput,
   kPwrMsgDevTypePwrSplit,
};

/////////////////////////////////////////     Output    ///////////////////////////////////////

enum PwrMsgOutCmd
{
   kPwrMsgOutCmdInvalid     = 0,
   kPwrMsgOutCmdReset,
   kPwrMsgOutCmdStatus,
   kPwrMsgOutCmdConfig,
   kPwrMsgOutCmdSetFlags,
   kPwrMsgOutCmdClearFlags,
   kPwrMsgOutCmdSignal16,
   kPwrMsgOutCmdSet,
};

enum PwrMsgOutStatusFlags
{
   kPwrMsgOutFlagPowerDown    = 1 << 0,
   kPwrMsgOutFlagFailedOutput = 1 << 1,
   kPwrMsgOutFlagBurntBulb    = 1 << 2,
};

enum PwrMsgOutSig16Flags
{
   PwrMsgOutSig16FlagSecMark   = 1 << 0,
};

/////////////////////////////////////////     Split    ///////////////////////////////////////

enum PwrMsgSplitCmd
{
   kPwrMsgSplitCmdInvalid      = 0,
   kPwrMsgSplitCmdReset,
   kPwrMsgSplitCmdStatus,
   kPwrMsgSplitCmdConfig,
   kPwrMsgSplitCmdSetFlags,
   kPwrMsgSplitCmdClearFlags,
};

enum PwrMsgSplitStateFlags
{
   kPwrMsgSplitFlagInvalid      = 0 << 0,
   kPwrMsgSplitFlagActive       = 1 << 1,
   kPwrMsgSplitFlagPowerDown    = 1 << 2,
   kPwrMsgSplitFlagFailedRelay  = 1 << 3,
};


typedef struct
{
   union
   {
      struct
      {
         unsigned src_addr: 8;
         unsigned src_type: 3;
         unsigned dst_addr: 8;
         unsigned dst_type: 3;
         unsigned cmd: 7;
         unsigned : 3;
      };
      
      uint32_t id;
   };
   
   union
   {
      union
      {
         struct __attribute__ ((packed))
         {
            uint8_t burnt_timeout;
            uint8_t main_power_timeout;
         } cfg;

         struct __attribute__ ((packed))
         {
            uint8_t flags;
            uint8_t input;
            uint16_t burnt;
            uint16_t failed;
         } status;
         
         struct __attribute__ ((packed))
         {
            uint16_t value;
            uint8_t flags;
         } sig16;
         
      } po;
      
      union
      {
         struct __attribute__ ((packed))
         {
            uint16_t flags;
         } status;
         
      } ps;
      
      uint32_t data[2];
   };

} PwrMsg;







#endif