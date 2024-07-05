#
# Generated Makefile - do not edit!
#
# Edit the Makefile in the project folder instead (../Makefile). Each target
# has a -pre and a -post target defined where you can add customized code.
#
# This makefile implements configuration specific macros and targets.


# Include project Makefile
ifeq "${IGNORE_LOCAL}" "TRUE"
# do not include local makefile. User is passing all local related variables already
else
include Makefile
# Include makefile containing local settings
ifeq "$(wildcard nbproject/Makefile-local-default.mk)" "nbproject/Makefile-local-default.mk"
include nbproject/Makefile-local-default.mk
endif
endif

# Environment
MKDIR=gnumkdir -p
RM=rm -f 
MV=mv 
CP=cp 

# Macros
CND_CONF=default
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
IMAGE_TYPE=debug
OUTPUT_SUFFIX=elf
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/GwMasterCtrl_v5.0.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
else
IMAGE_TYPE=production
OUTPUT_SUFFIX=hex
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/GwMasterCtrl_v5.0.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
endif

ifeq ($(COMPARE_BUILD), true)
COMPARISON_BUILD=-mafrlcsj
else
COMPARISON_BUILD=
endif

ifdef SUB_IMAGE_ADDRESS

else
SUB_IMAGE_ADDRESS_COMMAND=
endif

# Object Directory
OBJECTDIR=build/${CND_CONF}/${IMAGE_TYPE}

# Distribution Directory
DISTDIR=dist/${CND_CONF}/${IMAGE_TYPE}

# Source Files Quoted if spaced
SOURCEFILES_QUOTED_IF_SPACED=src/app/logic/logic.c src/app/logic/state.c src/app/net/cellular.c src/app/net/serial.c src/app/net/radio.c src/app/out/power_ctrl.c src/app/sem/chronos.c src/app/sem/sem_objects.c src/app/sem/semaphore.c src/cfg/app_config.c src/cfg/hw_config.c src/drv/pcf2129t.c src/drv/rfm95.c src/hal/can/CANConfiguration.c src/hal/can/CANErrorFunctions.c src/hal/can/CANEventFunctions.c src/hal/can/CANFilterFunctions.c src/hal/can/CANInfoFunctions.c src/hal/can/CANReceiveFunctions.c src/hal/can/CANTransmitFunctions.c src/hal/pin32.c src/hal/uart32mx.c src/lib/aes.c src/lib/datetime.c src/lib/utils.c src/lib/shared_buff.c src/lib/jparsing.c src/lib/jsmn.c mcc_generated_files/spi3.c mcc_generated_files/uart3.c mcc_generated_files/interrupt_manager.c mcc_generated_files/mcc.c mcc_generated_files/uart1.c mcc_generated_files/pin_manager.c mcc_generated_files/uart2.c mcc_generated_files/tmr1.c mcc_generated_files/uart4.c mcc_generated_files/uart5.c mcc_generated_files/tmr2.c src/sal/buttons.c src/sal/pulse.c src/sal/timer.c src/sal/debug_std.c src/sas/canbus.c src/sas/atdrv.c src/sas/sim800c.c src/sas/storage.c src/sas/rmsg_blob.c src/sas/lora.c src/sas/slink.c src/sas/server.c src/sas/rtc.c src/sas/gps.c main.c src/app/edge/edge.c

# Object Files Quoted if spaced
OBJECTFILES_QUOTED_IF_SPACED=${OBJECTDIR}/src/app/logic/logic.o ${OBJECTDIR}/src/app/logic/state.o ${OBJECTDIR}/src/app/net/cellular.o ${OBJECTDIR}/src/app/net/serial.o ${OBJECTDIR}/src/app/net/radio.o ${OBJECTDIR}/src/app/out/power_ctrl.o ${OBJECTDIR}/src/app/sem/chronos.o ${OBJECTDIR}/src/app/sem/sem_objects.o ${OBJECTDIR}/src/app/sem/semaphore.o ${OBJECTDIR}/src/cfg/app_config.o ${OBJECTDIR}/src/cfg/hw_config.o ${OBJECTDIR}/src/drv/pcf2129t.o ${OBJECTDIR}/src/drv/rfm95.o ${OBJECTDIR}/src/hal/can/CANConfiguration.o ${OBJECTDIR}/src/hal/can/CANErrorFunctions.o ${OBJECTDIR}/src/hal/can/CANEventFunctions.o ${OBJECTDIR}/src/hal/can/CANFilterFunctions.o ${OBJECTDIR}/src/hal/can/CANInfoFunctions.o ${OBJECTDIR}/src/hal/can/CANReceiveFunctions.o ${OBJECTDIR}/src/hal/can/CANTransmitFunctions.o ${OBJECTDIR}/src/hal/pin32.o ${OBJECTDIR}/src/hal/uart32mx.o ${OBJECTDIR}/src/lib/aes.o ${OBJECTDIR}/src/lib/datetime.o ${OBJECTDIR}/src/lib/utils.o ${OBJECTDIR}/src/lib/shared_buff.o ${OBJECTDIR}/src/lib/jparsing.o ${OBJECTDIR}/src/lib/jsmn.o ${OBJECTDIR}/mcc_generated_files/spi3.o ${OBJECTDIR}/mcc_generated_files/uart3.o ${OBJECTDIR}/mcc_generated_files/interrupt_manager.o ${OBJECTDIR}/mcc_generated_files/mcc.o ${OBJECTDIR}/mcc_generated_files/uart1.o ${OBJECTDIR}/mcc_generated_files/pin_manager.o ${OBJECTDIR}/mcc_generated_files/uart2.o ${OBJECTDIR}/mcc_generated_files/tmr1.o ${OBJECTDIR}/mcc_generated_files/uart4.o ${OBJECTDIR}/mcc_generated_files/uart5.o ${OBJECTDIR}/mcc_generated_files/tmr2.o ${OBJECTDIR}/src/sal/buttons.o ${OBJECTDIR}/src/sal/pulse.o ${OBJECTDIR}/src/sal/timer.o ${OBJECTDIR}/src/sal/debug_std.o ${OBJECTDIR}/src/sas/canbus.o ${OBJECTDIR}/src/sas/atdrv.o ${OBJECTDIR}/src/sas/sim800c.o ${OBJECTDIR}/src/sas/storage.o ${OBJECTDIR}/src/sas/rmsg_blob.o ${OBJECTDIR}/src/sas/lora.o ${OBJECTDIR}/src/sas/slink.o ${OBJECTDIR}/src/sas/server.o ${OBJECTDIR}/src/sas/rtc.o ${OBJECTDIR}/src/sas/gps.o ${OBJECTDIR}/main.o ${OBJECTDIR}/src/app/edge/edge.o
POSSIBLE_DEPFILES=${OBJECTDIR}/src/app/logic/logic.o.d ${OBJECTDIR}/src/app/logic/state.o.d ${OBJECTDIR}/src/app/net/cellular.o.d ${OBJECTDIR}/src/app/net/serial.o.d ${OBJECTDIR}/src/app/net/radio.o.d ${OBJECTDIR}/src/app/out/power_ctrl.o.d ${OBJECTDIR}/src/app/sem/chronos.o.d ${OBJECTDIR}/src/app/sem/sem_objects.o.d ${OBJECTDIR}/src/app/sem/semaphore.o.d ${OBJECTDIR}/src/cfg/app_config.o.d ${OBJECTDIR}/src/cfg/hw_config.o.d ${OBJECTDIR}/src/drv/pcf2129t.o.d ${OBJECTDIR}/src/drv/rfm95.o.d ${OBJECTDIR}/src/hal/can/CANConfiguration.o.d ${OBJECTDIR}/src/hal/can/CANErrorFunctions.o.d ${OBJECTDIR}/src/hal/can/CANEventFunctions.o.d ${OBJECTDIR}/src/hal/can/CANFilterFunctions.o.d ${OBJECTDIR}/src/hal/can/CANInfoFunctions.o.d ${OBJECTDIR}/src/hal/can/CANReceiveFunctions.o.d ${OBJECTDIR}/src/hal/can/CANTransmitFunctions.o.d ${OBJECTDIR}/src/hal/pin32.o.d ${OBJECTDIR}/src/hal/uart32mx.o.d ${OBJECTDIR}/src/lib/aes.o.d ${OBJECTDIR}/src/lib/datetime.o.d ${OBJECTDIR}/src/lib/utils.o.d ${OBJECTDIR}/src/lib/shared_buff.o.d ${OBJECTDIR}/src/lib/jparsing.o.d ${OBJECTDIR}/src/lib/jsmn.o.d ${OBJECTDIR}/mcc_generated_files/spi3.o.d ${OBJECTDIR}/mcc_generated_files/uart3.o.d ${OBJECTDIR}/mcc_generated_files/interrupt_manager.o.d ${OBJECTDIR}/mcc_generated_files/mcc.o.d ${OBJECTDIR}/mcc_generated_files/uart1.o.d ${OBJECTDIR}/mcc_generated_files/pin_manager.o.d ${OBJECTDIR}/mcc_generated_files/uart2.o.d ${OBJECTDIR}/mcc_generated_files/tmr1.o.d ${OBJECTDIR}/mcc_generated_files/uart4.o.d ${OBJECTDIR}/mcc_generated_files/uart5.o.d ${OBJECTDIR}/mcc_generated_files/tmr2.o.d ${OBJECTDIR}/src/sal/buttons.o.d ${OBJECTDIR}/src/sal/pulse.o.d ${OBJECTDIR}/src/sal/timer.o.d ${OBJECTDIR}/src/sal/debug_std.o.d ${OBJECTDIR}/src/sas/canbus.o.d ${OBJECTDIR}/src/sas/atdrv.o.d ${OBJECTDIR}/src/sas/sim800c.o.d ${OBJECTDIR}/src/sas/storage.o.d ${OBJECTDIR}/src/sas/rmsg_blob.o.d ${OBJECTDIR}/src/sas/lora.o.d ${OBJECTDIR}/src/sas/slink.o.d ${OBJECTDIR}/src/sas/server.o.d ${OBJECTDIR}/src/sas/rtc.o.d ${OBJECTDIR}/src/sas/gps.o.d ${OBJECTDIR}/main.o.d ${OBJECTDIR}/src/app/edge/edge.o.d

# Object Files
OBJECTFILES=${OBJECTDIR}/src/app/logic/logic.o ${OBJECTDIR}/src/app/logic/state.o ${OBJECTDIR}/src/app/net/cellular.o ${OBJECTDIR}/src/app/net/serial.o ${OBJECTDIR}/src/app/net/radio.o ${OBJECTDIR}/src/app/out/power_ctrl.o ${OBJECTDIR}/src/app/sem/chronos.o ${OBJECTDIR}/src/app/sem/sem_objects.o ${OBJECTDIR}/src/app/sem/semaphore.o ${OBJECTDIR}/src/cfg/app_config.o ${OBJECTDIR}/src/cfg/hw_config.o ${OBJECTDIR}/src/drv/pcf2129t.o ${OBJECTDIR}/src/drv/rfm95.o ${OBJECTDIR}/src/hal/can/CANConfiguration.o ${OBJECTDIR}/src/hal/can/CANErrorFunctions.o ${OBJECTDIR}/src/hal/can/CANEventFunctions.o ${OBJECTDIR}/src/hal/can/CANFilterFunctions.o ${OBJECTDIR}/src/hal/can/CANInfoFunctions.o ${OBJECTDIR}/src/hal/can/CANReceiveFunctions.o ${OBJECTDIR}/src/hal/can/CANTransmitFunctions.o ${OBJECTDIR}/src/hal/pin32.o ${OBJECTDIR}/src/hal/uart32mx.o ${OBJECTDIR}/src/lib/aes.o ${OBJECTDIR}/src/lib/datetime.o ${OBJECTDIR}/src/lib/utils.o ${OBJECTDIR}/src/lib/shared_buff.o ${OBJECTDIR}/src/lib/jparsing.o ${OBJECTDIR}/src/lib/jsmn.o ${OBJECTDIR}/mcc_generated_files/spi3.o ${OBJECTDIR}/mcc_generated_files/uart3.o ${OBJECTDIR}/mcc_generated_files/interrupt_manager.o ${OBJECTDIR}/mcc_generated_files/mcc.o ${OBJECTDIR}/mcc_generated_files/uart1.o ${OBJECTDIR}/mcc_generated_files/pin_manager.o ${OBJECTDIR}/mcc_generated_files/uart2.o ${OBJECTDIR}/mcc_generated_files/tmr1.o ${OBJECTDIR}/mcc_generated_files/uart4.o ${OBJECTDIR}/mcc_generated_files/uart5.o ${OBJECTDIR}/mcc_generated_files/tmr2.o ${OBJECTDIR}/src/sal/buttons.o ${OBJECTDIR}/src/sal/pulse.o ${OBJECTDIR}/src/sal/timer.o ${OBJECTDIR}/src/sal/debug_std.o ${OBJECTDIR}/src/sas/canbus.o ${OBJECTDIR}/src/sas/atdrv.o ${OBJECTDIR}/src/sas/sim800c.o ${OBJECTDIR}/src/sas/storage.o ${OBJECTDIR}/src/sas/rmsg_blob.o ${OBJECTDIR}/src/sas/lora.o ${OBJECTDIR}/src/sas/slink.o ${OBJECTDIR}/src/sas/server.o ${OBJECTDIR}/src/sas/rtc.o ${OBJECTDIR}/src/sas/gps.o ${OBJECTDIR}/main.o ${OBJECTDIR}/src/app/edge/edge.o

# Source Files
SOURCEFILES=src/app/logic/logic.c src/app/logic/state.c src/app/net/cellular.c src/app/net/serial.c src/app/net/radio.c src/app/out/power_ctrl.c src/app/sem/chronos.c src/app/sem/sem_objects.c src/app/sem/semaphore.c src/cfg/app_config.c src/cfg/hw_config.c src/drv/pcf2129t.c src/drv/rfm95.c src/hal/can/CANConfiguration.c src/hal/can/CANErrorFunctions.c src/hal/can/CANEventFunctions.c src/hal/can/CANFilterFunctions.c src/hal/can/CANInfoFunctions.c src/hal/can/CANReceiveFunctions.c src/hal/can/CANTransmitFunctions.c src/hal/pin32.c src/hal/uart32mx.c src/lib/aes.c src/lib/datetime.c src/lib/utils.c src/lib/shared_buff.c src/lib/jparsing.c src/lib/jsmn.c mcc_generated_files/spi3.c mcc_generated_files/uart3.c mcc_generated_files/interrupt_manager.c mcc_generated_files/mcc.c mcc_generated_files/uart1.c mcc_generated_files/pin_manager.c mcc_generated_files/uart2.c mcc_generated_files/tmr1.c mcc_generated_files/uart4.c mcc_generated_files/uart5.c mcc_generated_files/tmr2.c src/sal/buttons.c src/sal/pulse.c src/sal/timer.c src/sal/debug_std.c src/sas/canbus.c src/sas/atdrv.c src/sas/sim800c.c src/sas/storage.c src/sas/rmsg_blob.c src/sas/lora.c src/sas/slink.c src/sas/server.c src/sas/rtc.c src/sas/gps.c main.c src/app/edge/edge.c



CFLAGS=
ASFLAGS=
LDLIBSOPTIONS=

############# Tool locations ##########################################
# If you copy a project from one host to another, the path where the  #
# compiler is installed may be different.                             #
# If you open this project with MPLAB X in the new host, this         #
# makefile will be regenerated and the paths will be corrected.       #
#######################################################################
# fixDeps replaces a bunch of sed/cat/printf statements that slow down the build
FIXDEPS=fixDeps

.build-conf:  ${BUILD_SUBPROJECTS}
ifneq ($(INFORMATION_MESSAGE), )
	@echo $(INFORMATION_MESSAGE)
endif
	${MAKE}  -f nbproject/Makefile-default.mk dist/${CND_CONF}/${IMAGE_TYPE}/GwMasterCtrl_v5.0.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}

MP_PROCESSOR_OPTION=32MX570F512L
MP_LINKER_FILE_OPTION=
# ------------------------------------------------------------------------------------
# Rules for buildStep: assemble
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: assembleWithPreprocess
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: compile
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${OBJECTDIR}/src/app/logic/logic.o: src/app/logic/logic.c  .generated_files/1bb128ffb50a8d1a6415719c6e8341198c24a498.flag .generated_files/8bac4a0766d39c6687560ebfeb650ad7e1a6910e.flag
	@${MKDIR} "${OBJECTDIR}/src/app/logic" 
	@${RM} ${OBJECTDIR}/src/app/logic/logic.o.d 
	@${RM} ${OBJECTDIR}/src/app/logic/logic.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"src" -I"." -D_SUPPRESS_PLIB_WARNING -I"C:/Program Files (x86)/Microchip/xc32/v2.15/pic32-libs" -MP -MMD -MF "${OBJECTDIR}/src/app/logic/logic.o.d" -o ${OBJECTDIR}/src/app/logic/logic.o src/app/logic/logic.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/src/app/logic/state.o: src/app/logic/state.c  .generated_files/b34bc05dab60f88fda8709f827df7a0aa082559e.flag .generated_files/8bac4a0766d39c6687560ebfeb650ad7e1a6910e.flag
	@${MKDIR} "${OBJECTDIR}/src/app/logic" 
	@${RM} ${OBJECTDIR}/src/app/logic/state.o.d 
	@${RM} ${OBJECTDIR}/src/app/logic/state.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"src" -I"." -D_SUPPRESS_PLIB_WARNING -I"C:/Program Files (x86)/Microchip/xc32/v2.15/pic32-libs" -MP -MMD -MF "${OBJECTDIR}/src/app/logic/state.o.d" -o ${OBJECTDIR}/src/app/logic/state.o src/app/logic/state.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/src/app/net/cellular.o: src/app/net/cellular.c  .generated_files/cbd2c0a286a0f95fec08218a14e2177896d3765a.flag .generated_files/8bac4a0766d39c6687560ebfeb650ad7e1a6910e.flag
	@${MKDIR} "${OBJECTDIR}/src/app/net" 
	@${RM} ${OBJECTDIR}/src/app/net/cellular.o.d 
	@${RM} ${OBJECTDIR}/src/app/net/cellular.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"src" -I"." -D_SUPPRESS_PLIB_WARNING -I"C:/Program Files (x86)/Microchip/xc32/v2.15/pic32-libs" -MP -MMD -MF "${OBJECTDIR}/src/app/net/cellular.o.d" -o ${OBJECTDIR}/src/app/net/cellular.o src/app/net/cellular.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/src/app/net/serial.o: src/app/net/serial.c  .generated_files/c4ad9729502927eac575d0d4139c432c7843b703.flag .generated_files/8bac4a0766d39c6687560ebfeb650ad7e1a6910e.flag
	@${MKDIR} "${OBJECTDIR}/src/app/net" 
	@${RM} ${OBJECTDIR}/src/app/net/serial.o.d 
	@${RM} ${OBJECTDIR}/src/app/net/serial.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"src" -I"." -D_SUPPRESS_PLIB_WARNING -I"C:/Program Files (x86)/Microchip/xc32/v2.15/pic32-libs" -MP -MMD -MF "${OBJECTDIR}/src/app/net/serial.o.d" -o ${OBJECTDIR}/src/app/net/serial.o src/app/net/serial.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/src/app/net/radio.o: src/app/net/radio.c  .generated_files/7563c4185ad2bd32aaa0cd077c5e6911a104c4bd.flag .generated_files/8bac4a0766d39c6687560ebfeb650ad7e1a6910e.flag
	@${MKDIR} "${OBJECTDIR}/src/app/net" 
	@${RM} ${OBJECTDIR}/src/app/net/radio.o.d 
	@${RM} ${OBJECTDIR}/src/app/net/radio.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"src" -I"." -D_SUPPRESS_PLIB_WARNING -I"C:/Program Files (x86)/Microchip/xc32/v2.15/pic32-libs" -MP -MMD -MF "${OBJECTDIR}/src/app/net/radio.o.d" -o ${OBJECTDIR}/src/app/net/radio.o src/app/net/radio.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/src/app/out/power_ctrl.o: src/app/out/power_ctrl.c  .generated_files/4fff60be216b6c5b80355e8f7789918e8a681cdf.flag .generated_files/8bac4a0766d39c6687560ebfeb650ad7e1a6910e.flag
	@${MKDIR} "${OBJECTDIR}/src/app/out" 
	@${RM} ${OBJECTDIR}/src/app/out/power_ctrl.o.d 
	@${RM} ${OBJECTDIR}/src/app/out/power_ctrl.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"src" -I"." -D_SUPPRESS_PLIB_WARNING -I"C:/Program Files (x86)/Microchip/xc32/v2.15/pic32-libs" -MP -MMD -MF "${OBJECTDIR}/src/app/out/power_ctrl.o.d" -o ${OBJECTDIR}/src/app/out/power_ctrl.o src/app/out/power_ctrl.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/src/app/sem/chronos.o: src/app/sem/chronos.c  .generated_files/c6cbb6c1c19e12436ed8c9cc1af0c062cab9f878.flag .generated_files/8bac4a0766d39c6687560ebfeb650ad7e1a6910e.flag
	@${MKDIR} "${OBJECTDIR}/src/app/sem" 
	@${RM} ${OBJECTDIR}/src/app/sem/chronos.o.d 
	@${RM} ${OBJECTDIR}/src/app/sem/chronos.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"src" -I"." -D_SUPPRESS_PLIB_WARNING -I"C:/Program Files (x86)/Microchip/xc32/v2.15/pic32-libs" -MP -MMD -MF "${OBJECTDIR}/src/app/sem/chronos.o.d" -o ${OBJECTDIR}/src/app/sem/chronos.o src/app/sem/chronos.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/src/app/sem/sem_objects.o: src/app/sem/sem_objects.c  .generated_files/2a1f5ed453834e4e2e5062e3d59482a6d41509a6.flag .generated_files/8bac4a0766d39c6687560ebfeb650ad7e1a6910e.flag
	@${MKDIR} "${OBJECTDIR}/src/app/sem" 
	@${RM} ${OBJECTDIR}/src/app/sem/sem_objects.o.d 
	@${RM} ${OBJECTDIR}/src/app/sem/sem_objects.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"src" -I"." -D_SUPPRESS_PLIB_WARNING -I"C:/Program Files (x86)/Microchip/xc32/v2.15/pic32-libs" -MP -MMD -MF "${OBJECTDIR}/src/app/sem/sem_objects.o.d" -o ${OBJECTDIR}/src/app/sem/sem_objects.o src/app/sem/sem_objects.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/src/app/sem/semaphore.o: src/app/sem/semaphore.c  .generated_files/8a7f4433ee23c062c552d4971fd0ef6df6bbf2f4.flag .generated_files/8bac4a0766d39c6687560ebfeb650ad7e1a6910e.flag
	@${MKDIR} "${OBJECTDIR}/src/app/sem" 
	@${RM} ${OBJECTDIR}/src/app/sem/semaphore.o.d 
	@${RM} ${OBJECTDIR}/src/app/sem/semaphore.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"src" -I"." -D_SUPPRESS_PLIB_WARNING -I"C:/Program Files (x86)/Microchip/xc32/v2.15/pic32-libs" -MP -MMD -MF "${OBJECTDIR}/src/app/sem/semaphore.o.d" -o ${OBJECTDIR}/src/app/sem/semaphore.o src/app/sem/semaphore.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/src/cfg/app_config.o: src/cfg/app_config.c  .generated_files/27f444400d3fd96e1b50af918dfd54734bca54fb.flag .generated_files/8bac4a0766d39c6687560ebfeb650ad7e1a6910e.flag
	@${MKDIR} "${OBJECTDIR}/src/cfg" 
	@${RM} ${OBJECTDIR}/src/cfg/app_config.o.d 
	@${RM} ${OBJECTDIR}/src/cfg/app_config.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"src" -I"." -D_SUPPRESS_PLIB_WARNING -I"C:/Program Files (x86)/Microchip/xc32/v2.15/pic32-libs" -MP -MMD -MF "${OBJECTDIR}/src/cfg/app_config.o.d" -o ${OBJECTDIR}/src/cfg/app_config.o src/cfg/app_config.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/src/cfg/hw_config.o: src/cfg/hw_config.c  .generated_files/72e2044fdbd6c336184b56b63dd9944d9fd75889.flag .generated_files/8bac4a0766d39c6687560ebfeb650ad7e1a6910e.flag
	@${MKDIR} "${OBJECTDIR}/src/cfg" 
	@${RM} ${OBJECTDIR}/src/cfg/hw_config.o.d 
	@${RM} ${OBJECTDIR}/src/cfg/hw_config.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"src" -I"." -D_SUPPRESS_PLIB_WARNING -I"C:/Program Files (x86)/Microchip/xc32/v2.15/pic32-libs" -MP -MMD -MF "${OBJECTDIR}/src/cfg/hw_config.o.d" -o ${OBJECTDIR}/src/cfg/hw_config.o src/cfg/hw_config.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/src/drv/pcf2129t.o: src/drv/pcf2129t.c  .generated_files/776917a74178518e836998845cc435bf84f80339.flag .generated_files/8bac4a0766d39c6687560ebfeb650ad7e1a6910e.flag
	@${MKDIR} "${OBJECTDIR}/src/drv" 
	@${RM} ${OBJECTDIR}/src/drv/pcf2129t.o.d 
	@${RM} ${OBJECTDIR}/src/drv/pcf2129t.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"src" -I"." -D_SUPPRESS_PLIB_WARNING -I"C:/Program Files (x86)/Microchip/xc32/v2.15/pic32-libs" -MP -MMD -MF "${OBJECTDIR}/src/drv/pcf2129t.o.d" -o ${OBJECTDIR}/src/drv/pcf2129t.o src/drv/pcf2129t.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/src/drv/rfm95.o: src/drv/rfm95.c  .generated_files/bebca9eb084dbf0f2dd16614be48b9b37b69e993.flag .generated_files/8bac4a0766d39c6687560ebfeb650ad7e1a6910e.flag
	@${MKDIR} "${OBJECTDIR}/src/drv" 
	@${RM} ${OBJECTDIR}/src/drv/rfm95.o.d 
	@${RM} ${OBJECTDIR}/src/drv/rfm95.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"src" -I"." -D_SUPPRESS_PLIB_WARNING -I"C:/Program Files (x86)/Microchip/xc32/v2.15/pic32-libs" -MP -MMD -MF "${OBJECTDIR}/src/drv/rfm95.o.d" -o ${OBJECTDIR}/src/drv/rfm95.o src/drv/rfm95.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/src/hal/can/CANConfiguration.o: src/hal/can/CANConfiguration.c  .generated_files/328768b6c2bc0cecebfd9924aaf3f6b5ff2dfce8.flag .generated_files/8bac4a0766d39c6687560ebfeb650ad7e1a6910e.flag
	@${MKDIR} "${OBJECTDIR}/src/hal/can" 
	@${RM} ${OBJECTDIR}/src/hal/can/CANConfiguration.o.d 
	@${RM} ${OBJECTDIR}/src/hal/can/CANConfiguration.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"src" -I"." -D_SUPPRESS_PLIB_WARNING -I"C:/Program Files (x86)/Microchip/xc32/v2.15/pic32-libs" -MP -MMD -MF "${OBJECTDIR}/src/hal/can/CANConfiguration.o.d" -o ${OBJECTDIR}/src/hal/can/CANConfiguration.o src/hal/can/CANConfiguration.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/src/hal/can/CANErrorFunctions.o: src/hal/can/CANErrorFunctions.c  .generated_files/e347f4cbcfe94115c7f53e31d216b9b2030e9d2a.flag .generated_files/8bac4a0766d39c6687560ebfeb650ad7e1a6910e.flag
	@${MKDIR} "${OBJECTDIR}/src/hal/can" 
	@${RM} ${OBJECTDIR}/src/hal/can/CANErrorFunctions.o.d 
	@${RM} ${OBJECTDIR}/src/hal/can/CANErrorFunctions.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"src" -I"." -D_SUPPRESS_PLIB_WARNING -I"C:/Program Files (x86)/Microchip/xc32/v2.15/pic32-libs" -MP -MMD -MF "${OBJECTDIR}/src/hal/can/CANErrorFunctions.o.d" -o ${OBJECTDIR}/src/hal/can/CANErrorFunctions.o src/hal/can/CANErrorFunctions.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/src/hal/can/CANEventFunctions.o: src/hal/can/CANEventFunctions.c  .generated_files/27bf611881c0afca862197c8d0eb23796b0b2e55.flag .generated_files/8bac4a0766d39c6687560ebfeb650ad7e1a6910e.flag
	@${MKDIR} "${OBJECTDIR}/src/hal/can" 
	@${RM} ${OBJECTDIR}/src/hal/can/CANEventFunctions.o.d 
	@${RM} ${OBJECTDIR}/src/hal/can/CANEventFunctions.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"src" -I"." -D_SUPPRESS_PLIB_WARNING -I"C:/Program Files (x86)/Microchip/xc32/v2.15/pic32-libs" -MP -MMD -MF "${OBJECTDIR}/src/hal/can/CANEventFunctions.o.d" -o ${OBJECTDIR}/src/hal/can/CANEventFunctions.o src/hal/can/CANEventFunctions.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/src/hal/can/CANFilterFunctions.o: src/hal/can/CANFilterFunctions.c  .generated_files/de3505b99374c6cfedcc5d102a0190000e3fd67.flag .generated_files/8bac4a0766d39c6687560ebfeb650ad7e1a6910e.flag
	@${MKDIR} "${OBJECTDIR}/src/hal/can" 
	@${RM} ${OBJECTDIR}/src/hal/can/CANFilterFunctions.o.d 
	@${RM} ${OBJECTDIR}/src/hal/can/CANFilterFunctions.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"src" -I"." -D_SUPPRESS_PLIB_WARNING -I"C:/Program Files (x86)/Microchip/xc32/v2.15/pic32-libs" -MP -MMD -MF "${OBJECTDIR}/src/hal/can/CANFilterFunctions.o.d" -o ${OBJECTDIR}/src/hal/can/CANFilterFunctions.o src/hal/can/CANFilterFunctions.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/src/hal/can/CANInfoFunctions.o: src/hal/can/CANInfoFunctions.c  .generated_files/3d35ff3ccbf15dc8da44ce2ca2974e671036b611.flag .generated_files/8bac4a0766d39c6687560ebfeb650ad7e1a6910e.flag
	@${MKDIR} "${OBJECTDIR}/src/hal/can" 
	@${RM} ${OBJECTDIR}/src/hal/can/CANInfoFunctions.o.d 
	@${RM} ${OBJECTDIR}/src/hal/can/CANInfoFunctions.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"src" -I"." -D_SUPPRESS_PLIB_WARNING -I"C:/Program Files (x86)/Microchip/xc32/v2.15/pic32-libs" -MP -MMD -MF "${OBJECTDIR}/src/hal/can/CANInfoFunctions.o.d" -o ${OBJECTDIR}/src/hal/can/CANInfoFunctions.o src/hal/can/CANInfoFunctions.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/src/hal/can/CANReceiveFunctions.o: src/hal/can/CANReceiveFunctions.c  .generated_files/5844739b7ed6a47033fc269b18772135a8309b32.flag .generated_files/8bac4a0766d39c6687560ebfeb650ad7e1a6910e.flag
	@${MKDIR} "${OBJECTDIR}/src/hal/can" 
	@${RM} ${OBJECTDIR}/src/hal/can/CANReceiveFunctions.o.d 
	@${RM} ${OBJECTDIR}/src/hal/can/CANReceiveFunctions.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"src" -I"." -D_SUPPRESS_PLIB_WARNING -I"C:/Program Files (x86)/Microchip/xc32/v2.15/pic32-libs" -MP -MMD -MF "${OBJECTDIR}/src/hal/can/CANReceiveFunctions.o.d" -o ${OBJECTDIR}/src/hal/can/CANReceiveFunctions.o src/hal/can/CANReceiveFunctions.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/src/hal/can/CANTransmitFunctions.o: src/hal/can/CANTransmitFunctions.c  .generated_files/55abeabaf3c30b987cbd5c072df2f928039427c7.flag .generated_files/8bac4a0766d39c6687560ebfeb650ad7e1a6910e.flag
	@${MKDIR} "${OBJECTDIR}/src/hal/can" 
	@${RM} ${OBJECTDIR}/src/hal/can/CANTransmitFunctions.o.d 
	@${RM} ${OBJECTDIR}/src/hal/can/CANTransmitFunctions.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"src" -I"." -D_SUPPRESS_PLIB_WARNING -I"C:/Program Files (x86)/Microchip/xc32/v2.15/pic32-libs" -MP -MMD -MF "${OBJECTDIR}/src/hal/can/CANTransmitFunctions.o.d" -o ${OBJECTDIR}/src/hal/can/CANTransmitFunctions.o src/hal/can/CANTransmitFunctions.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/src/hal/pin32.o: src/hal/pin32.c  .generated_files/c3101fd863f3999db8ff6db9c086a7efc6fe9a54.flag .generated_files/8bac4a0766d39c6687560ebfeb650ad7e1a6910e.flag
	@${MKDIR} "${OBJECTDIR}/src/hal" 
	@${RM} ${OBJECTDIR}/src/hal/pin32.o.d 
	@${RM} ${OBJECTDIR}/src/hal/pin32.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"src" -I"." -D_SUPPRESS_PLIB_WARNING -I"C:/Program Files (x86)/Microchip/xc32/v2.15/pic32-libs" -MP -MMD -MF "${OBJECTDIR}/src/hal/pin32.o.d" -o ${OBJECTDIR}/src/hal/pin32.o src/hal/pin32.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/src/hal/uart32mx.o: src/hal/uart32mx.c  .generated_files/dbd1165a661332f6bead5484c5ea564f993a1fb6.flag .generated_files/8bac4a0766d39c6687560ebfeb650ad7e1a6910e.flag
	@${MKDIR} "${OBJECTDIR}/src/hal" 
	@${RM} ${OBJECTDIR}/src/hal/uart32mx.o.d 
	@${RM} ${OBJECTDIR}/src/hal/uart32mx.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"src" -I"." -D_SUPPRESS_PLIB_WARNING -I"C:/Program Files (x86)/Microchip/xc32/v2.15/pic32-libs" -MP -MMD -MF "${OBJECTDIR}/src/hal/uart32mx.o.d" -o ${OBJECTDIR}/src/hal/uart32mx.o src/hal/uart32mx.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/src/lib/aes.o: src/lib/aes.c  .generated_files/eb5f7f93fb200be4672ec1117bd0120aa3050d4.flag .generated_files/8bac4a0766d39c6687560ebfeb650ad7e1a6910e.flag
	@${MKDIR} "${OBJECTDIR}/src/lib" 
	@${RM} ${OBJECTDIR}/src/lib/aes.o.d 
	@${RM} ${OBJECTDIR}/src/lib/aes.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"src" -I"." -D_SUPPRESS_PLIB_WARNING -I"C:/Program Files (x86)/Microchip/xc32/v2.15/pic32-libs" -MP -MMD -MF "${OBJECTDIR}/src/lib/aes.o.d" -o ${OBJECTDIR}/src/lib/aes.o src/lib/aes.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/src/lib/datetime.o: src/lib/datetime.c  .generated_files/890d734c78f18a77b6f56acec976a514c920896d.flag .generated_files/8bac4a0766d39c6687560ebfeb650ad7e1a6910e.flag
	@${MKDIR} "${OBJECTDIR}/src/lib" 
	@${RM} ${OBJECTDIR}/src/lib/datetime.o.d 
	@${RM} ${OBJECTDIR}/src/lib/datetime.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"src" -I"." -D_SUPPRESS_PLIB_WARNING -I"C:/Program Files (x86)/Microchip/xc32/v2.15/pic32-libs" -MP -MMD -MF "${OBJECTDIR}/src/lib/datetime.o.d" -o ${OBJECTDIR}/src/lib/datetime.o src/lib/datetime.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/src/lib/utils.o: src/lib/utils.c  .generated_files/36561c29babb66a39aacf72e6818b3490ebff07b.flag .generated_files/8bac4a0766d39c6687560ebfeb650ad7e1a6910e.flag
	@${MKDIR} "${OBJECTDIR}/src/lib" 
	@${RM} ${OBJECTDIR}/src/lib/utils.o.d 
	@${RM} ${OBJECTDIR}/src/lib/utils.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"src" -I"." -D_SUPPRESS_PLIB_WARNING -I"C:/Program Files (x86)/Microchip/xc32/v2.15/pic32-libs" -MP -MMD -MF "${OBJECTDIR}/src/lib/utils.o.d" -o ${OBJECTDIR}/src/lib/utils.o src/lib/utils.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/src/lib/shared_buff.o: src/lib/shared_buff.c  .generated_files/2cb3ee4c08f4307c54af161bf79c3947ce22a951.flag .generated_files/8bac4a0766d39c6687560ebfeb650ad7e1a6910e.flag
	@${MKDIR} "${OBJECTDIR}/src/lib" 
	@${RM} ${OBJECTDIR}/src/lib/shared_buff.o.d 
	@${RM} ${OBJECTDIR}/src/lib/shared_buff.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"src" -I"." -D_SUPPRESS_PLIB_WARNING -I"C:/Program Files (x86)/Microchip/xc32/v2.15/pic32-libs" -MP -MMD -MF "${OBJECTDIR}/src/lib/shared_buff.o.d" -o ${OBJECTDIR}/src/lib/shared_buff.o src/lib/shared_buff.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/src/lib/jparsing.o: src/lib/jparsing.c  .generated_files/fe35b02ba74e45e00e4cd0b28ad4c205973ed9b2.flag .generated_files/8bac4a0766d39c6687560ebfeb650ad7e1a6910e.flag
	@${MKDIR} "${OBJECTDIR}/src/lib" 
	@${RM} ${OBJECTDIR}/src/lib/jparsing.o.d 
	@${RM} ${OBJECTDIR}/src/lib/jparsing.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"src" -I"." -D_SUPPRESS_PLIB_WARNING -I"C:/Program Files (x86)/Microchip/xc32/v2.15/pic32-libs" -MP -MMD -MF "${OBJECTDIR}/src/lib/jparsing.o.d" -o ${OBJECTDIR}/src/lib/jparsing.o src/lib/jparsing.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/src/lib/jsmn.o: src/lib/jsmn.c  .generated_files/5306cfe2e6e2e49ad0aa52dc4d939437ebc6f796.flag .generated_files/8bac4a0766d39c6687560ebfeb650ad7e1a6910e.flag
	@${MKDIR} "${OBJECTDIR}/src/lib" 
	@${RM} ${OBJECTDIR}/src/lib/jsmn.o.d 
	@${RM} ${OBJECTDIR}/src/lib/jsmn.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"src" -I"." -D_SUPPRESS_PLIB_WARNING -I"C:/Program Files (x86)/Microchip/xc32/v2.15/pic32-libs" -MP -MMD -MF "${OBJECTDIR}/src/lib/jsmn.o.d" -o ${OBJECTDIR}/src/lib/jsmn.o src/lib/jsmn.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/mcc_generated_files/spi3.o: mcc_generated_files/spi3.c  .generated_files/b8ecb360e199cf840d6e13e79ca1a26bb02ab839.flag .generated_files/8bac4a0766d39c6687560ebfeb650ad7e1a6910e.flag
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/spi3.o.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/spi3.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"src" -I"." -D_SUPPRESS_PLIB_WARNING -I"C:/Program Files (x86)/Microchip/xc32/v2.15/pic32-libs" -MP -MMD -MF "${OBJECTDIR}/mcc_generated_files/spi3.o.d" -o ${OBJECTDIR}/mcc_generated_files/spi3.o mcc_generated_files/spi3.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/mcc_generated_files/uart3.o: mcc_generated_files/uart3.c  .generated_files/aaa493baf776510745a634468f3b46cf484dc9e0.flag .generated_files/8bac4a0766d39c6687560ebfeb650ad7e1a6910e.flag
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/uart3.o.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/uart3.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"src" -I"." -D_SUPPRESS_PLIB_WARNING -I"C:/Program Files (x86)/Microchip/xc32/v2.15/pic32-libs" -MP -MMD -MF "${OBJECTDIR}/mcc_generated_files/uart3.o.d" -o ${OBJECTDIR}/mcc_generated_files/uart3.o mcc_generated_files/uart3.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/mcc_generated_files/interrupt_manager.o: mcc_generated_files/interrupt_manager.c  .generated_files/da623cb1c31639de0f5a79270a1b25ac37724ff7.flag .generated_files/8bac4a0766d39c6687560ebfeb650ad7e1a6910e.flag
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/interrupt_manager.o.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/interrupt_manager.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"src" -I"." -D_SUPPRESS_PLIB_WARNING -I"C:/Program Files (x86)/Microchip/xc32/v2.15/pic32-libs" -MP -MMD -MF "${OBJECTDIR}/mcc_generated_files/interrupt_manager.o.d" -o ${OBJECTDIR}/mcc_generated_files/interrupt_manager.o mcc_generated_files/interrupt_manager.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/mcc_generated_files/mcc.o: mcc_generated_files/mcc.c  .generated_files/1eed88594d34a948070740c64df829c8b4c839f2.flag .generated_files/8bac4a0766d39c6687560ebfeb650ad7e1a6910e.flag
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/mcc.o.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/mcc.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"src" -I"." -D_SUPPRESS_PLIB_WARNING -I"C:/Program Files (x86)/Microchip/xc32/v2.15/pic32-libs" -MP -MMD -MF "${OBJECTDIR}/mcc_generated_files/mcc.o.d" -o ${OBJECTDIR}/mcc_generated_files/mcc.o mcc_generated_files/mcc.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/mcc_generated_files/uart1.o: mcc_generated_files/uart1.c  .generated_files/1210ff4f5e241ccc412fc00150b81489a78a0a18.flag .generated_files/8bac4a0766d39c6687560ebfeb650ad7e1a6910e.flag
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/uart1.o.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/uart1.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"src" -I"." -D_SUPPRESS_PLIB_WARNING -I"C:/Program Files (x86)/Microchip/xc32/v2.15/pic32-libs" -MP -MMD -MF "${OBJECTDIR}/mcc_generated_files/uart1.o.d" -o ${OBJECTDIR}/mcc_generated_files/uart1.o mcc_generated_files/uart1.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/mcc_generated_files/pin_manager.o: mcc_generated_files/pin_manager.c  .generated_files/3011fcd632a32378193b861a3dd001e2e718caa9.flag .generated_files/8bac4a0766d39c6687560ebfeb650ad7e1a6910e.flag
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/pin_manager.o.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/pin_manager.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"src" -I"." -D_SUPPRESS_PLIB_WARNING -I"C:/Program Files (x86)/Microchip/xc32/v2.15/pic32-libs" -MP -MMD -MF "${OBJECTDIR}/mcc_generated_files/pin_manager.o.d" -o ${OBJECTDIR}/mcc_generated_files/pin_manager.o mcc_generated_files/pin_manager.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/mcc_generated_files/uart2.o: mcc_generated_files/uart2.c  .generated_files/3f079427653d75c0154b40832bcb7ad6d0b4c264.flag .generated_files/8bac4a0766d39c6687560ebfeb650ad7e1a6910e.flag
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/uart2.o.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/uart2.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"src" -I"." -D_SUPPRESS_PLIB_WARNING -I"C:/Program Files (x86)/Microchip/xc32/v2.15/pic32-libs" -MP -MMD -MF "${OBJECTDIR}/mcc_generated_files/uart2.o.d" -o ${OBJECTDIR}/mcc_generated_files/uart2.o mcc_generated_files/uart2.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/mcc_generated_files/tmr1.o: mcc_generated_files/tmr1.c  .generated_files/ac4e4d6529e008ac4d484a8b10358d2ca60223a1.flag .generated_files/8bac4a0766d39c6687560ebfeb650ad7e1a6910e.flag
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/tmr1.o.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/tmr1.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"src" -I"." -D_SUPPRESS_PLIB_WARNING -I"C:/Program Files (x86)/Microchip/xc32/v2.15/pic32-libs" -MP -MMD -MF "${OBJECTDIR}/mcc_generated_files/tmr1.o.d" -o ${OBJECTDIR}/mcc_generated_files/tmr1.o mcc_generated_files/tmr1.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/mcc_generated_files/uart4.o: mcc_generated_files/uart4.c  .generated_files/c416177a81712edf8fe1a5b2cf5dafadc15fe3b0.flag .generated_files/8bac4a0766d39c6687560ebfeb650ad7e1a6910e.flag
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/uart4.o.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/uart4.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"src" -I"." -D_SUPPRESS_PLIB_WARNING -I"C:/Program Files (x86)/Microchip/xc32/v2.15/pic32-libs" -MP -MMD -MF "${OBJECTDIR}/mcc_generated_files/uart4.o.d" -o ${OBJECTDIR}/mcc_generated_files/uart4.o mcc_generated_files/uart4.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/mcc_generated_files/uart5.o: mcc_generated_files/uart5.c  .generated_files/c2f1333b5092192305ec6646e7f3f4a850f8d808.flag .generated_files/8bac4a0766d39c6687560ebfeb650ad7e1a6910e.flag
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/uart5.o.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/uart5.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"src" -I"." -D_SUPPRESS_PLIB_WARNING -I"C:/Program Files (x86)/Microchip/xc32/v2.15/pic32-libs" -MP -MMD -MF "${OBJECTDIR}/mcc_generated_files/uart5.o.d" -o ${OBJECTDIR}/mcc_generated_files/uart5.o mcc_generated_files/uart5.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/mcc_generated_files/tmr2.o: mcc_generated_files/tmr2.c  .generated_files/36efb0192e707e8aa6d341d8dc7781f4c98fae63.flag .generated_files/8bac4a0766d39c6687560ebfeb650ad7e1a6910e.flag
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/tmr2.o.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/tmr2.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"src" -I"." -D_SUPPRESS_PLIB_WARNING -I"C:/Program Files (x86)/Microchip/xc32/v2.15/pic32-libs" -MP -MMD -MF "${OBJECTDIR}/mcc_generated_files/tmr2.o.d" -o ${OBJECTDIR}/mcc_generated_files/tmr2.o mcc_generated_files/tmr2.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/src/sal/buttons.o: src/sal/buttons.c  .generated_files/10c5927c1070a96de8f8be1e6fb584b7913839f6.flag .generated_files/8bac4a0766d39c6687560ebfeb650ad7e1a6910e.flag
	@${MKDIR} "${OBJECTDIR}/src/sal" 
	@${RM} ${OBJECTDIR}/src/sal/buttons.o.d 
	@${RM} ${OBJECTDIR}/src/sal/buttons.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"src" -I"." -D_SUPPRESS_PLIB_WARNING -I"C:/Program Files (x86)/Microchip/xc32/v2.15/pic32-libs" -MP -MMD -MF "${OBJECTDIR}/src/sal/buttons.o.d" -o ${OBJECTDIR}/src/sal/buttons.o src/sal/buttons.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/src/sal/pulse.o: src/sal/pulse.c  .generated_files/2e40a29c1f2086b1bb16c4fb60613f97134159b0.flag .generated_files/8bac4a0766d39c6687560ebfeb650ad7e1a6910e.flag
	@${MKDIR} "${OBJECTDIR}/src/sal" 
	@${RM} ${OBJECTDIR}/src/sal/pulse.o.d 
	@${RM} ${OBJECTDIR}/src/sal/pulse.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"src" -I"." -D_SUPPRESS_PLIB_WARNING -I"C:/Program Files (x86)/Microchip/xc32/v2.15/pic32-libs" -MP -MMD -MF "${OBJECTDIR}/src/sal/pulse.o.d" -o ${OBJECTDIR}/src/sal/pulse.o src/sal/pulse.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/src/sal/timer.o: src/sal/timer.c  .generated_files/2894b7903cd183f0bde437f8d03c42c5f02bf0dc.flag .generated_files/8bac4a0766d39c6687560ebfeb650ad7e1a6910e.flag
	@${MKDIR} "${OBJECTDIR}/src/sal" 
	@${RM} ${OBJECTDIR}/src/sal/timer.o.d 
	@${RM} ${OBJECTDIR}/src/sal/timer.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"src" -I"." -D_SUPPRESS_PLIB_WARNING -I"C:/Program Files (x86)/Microchip/xc32/v2.15/pic32-libs" -MP -MMD -MF "${OBJECTDIR}/src/sal/timer.o.d" -o ${OBJECTDIR}/src/sal/timer.o src/sal/timer.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/src/sal/debug_std.o: src/sal/debug_std.c  .generated_files/a7758a7421d501cdf9aae2756005d06753f6fdf3.flag .generated_files/8bac4a0766d39c6687560ebfeb650ad7e1a6910e.flag
	@${MKDIR} "${OBJECTDIR}/src/sal" 
	@${RM} ${OBJECTDIR}/src/sal/debug_std.o.d 
	@${RM} ${OBJECTDIR}/src/sal/debug_std.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"src" -I"." -D_SUPPRESS_PLIB_WARNING -I"C:/Program Files (x86)/Microchip/xc32/v2.15/pic32-libs" -MP -MMD -MF "${OBJECTDIR}/src/sal/debug_std.o.d" -o ${OBJECTDIR}/src/sal/debug_std.o src/sal/debug_std.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/src/sas/canbus.o: src/sas/canbus.c  .generated_files/4c778766489ce4e5de2fbabc0fab8f43afc8dbbc.flag .generated_files/8bac4a0766d39c6687560ebfeb650ad7e1a6910e.flag
	@${MKDIR} "${OBJECTDIR}/src/sas" 
	@${RM} ${OBJECTDIR}/src/sas/canbus.o.d 
	@${RM} ${OBJECTDIR}/src/sas/canbus.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"src" -I"." -D_SUPPRESS_PLIB_WARNING -I"C:/Program Files (x86)/Microchip/xc32/v2.15/pic32-libs" -MP -MMD -MF "${OBJECTDIR}/src/sas/canbus.o.d" -o ${OBJECTDIR}/src/sas/canbus.o src/sas/canbus.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/src/sas/atdrv.o: src/sas/atdrv.c  .generated_files/2b29bd8b59c6471ecb5713cbfd89d9b7e5fd9ca1.flag .generated_files/8bac4a0766d39c6687560ebfeb650ad7e1a6910e.flag
	@${MKDIR} "${OBJECTDIR}/src/sas" 
	@${RM} ${OBJECTDIR}/src/sas/atdrv.o.d 
	@${RM} ${OBJECTDIR}/src/sas/atdrv.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"src" -I"." -D_SUPPRESS_PLIB_WARNING -I"C:/Program Files (x86)/Microchip/xc32/v2.15/pic32-libs" -MP -MMD -MF "${OBJECTDIR}/src/sas/atdrv.o.d" -o ${OBJECTDIR}/src/sas/atdrv.o src/sas/atdrv.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/src/sas/sim800c.o: src/sas/sim800c.c  .generated_files/aefbd250899272980a7fa8f8ea894b03827b74a6.flag .generated_files/8bac4a0766d39c6687560ebfeb650ad7e1a6910e.flag
	@${MKDIR} "${OBJECTDIR}/src/sas" 
	@${RM} ${OBJECTDIR}/src/sas/sim800c.o.d 
	@${RM} ${OBJECTDIR}/src/sas/sim800c.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"src" -I"." -D_SUPPRESS_PLIB_WARNING -I"C:/Program Files (x86)/Microchip/xc32/v2.15/pic32-libs" -MP -MMD -MF "${OBJECTDIR}/src/sas/sim800c.o.d" -o ${OBJECTDIR}/src/sas/sim800c.o src/sas/sim800c.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/src/sas/storage.o: src/sas/storage.c  .generated_files/4bd45d9ec690b200363e8a087b1c6a444960ab14.flag .generated_files/8bac4a0766d39c6687560ebfeb650ad7e1a6910e.flag
	@${MKDIR} "${OBJECTDIR}/src/sas" 
	@${RM} ${OBJECTDIR}/src/sas/storage.o.d 
	@${RM} ${OBJECTDIR}/src/sas/storage.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"src" -I"." -D_SUPPRESS_PLIB_WARNING -I"C:/Program Files (x86)/Microchip/xc32/v2.15/pic32-libs" -MP -MMD -MF "${OBJECTDIR}/src/sas/storage.o.d" -o ${OBJECTDIR}/src/sas/storage.o src/sas/storage.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/src/sas/rmsg_blob.o: src/sas/rmsg_blob.c  .generated_files/2fa71dec00bb4164191b60d4d09c526ea2b4803b.flag .generated_files/8bac4a0766d39c6687560ebfeb650ad7e1a6910e.flag
	@${MKDIR} "${OBJECTDIR}/src/sas" 
	@${RM} ${OBJECTDIR}/src/sas/rmsg_blob.o.d 
	@${RM} ${OBJECTDIR}/src/sas/rmsg_blob.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"src" -I"." -D_SUPPRESS_PLIB_WARNING -I"C:/Program Files (x86)/Microchip/xc32/v2.15/pic32-libs" -MP -MMD -MF "${OBJECTDIR}/src/sas/rmsg_blob.o.d" -o ${OBJECTDIR}/src/sas/rmsg_blob.o src/sas/rmsg_blob.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/src/sas/lora.o: src/sas/lora.c  .generated_files/e5f8e107df938d852a626e5da02f536f2ddb839f.flag .generated_files/8bac4a0766d39c6687560ebfeb650ad7e1a6910e.flag
	@${MKDIR} "${OBJECTDIR}/src/sas" 
	@${RM} ${OBJECTDIR}/src/sas/lora.o.d 
	@${RM} ${OBJECTDIR}/src/sas/lora.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"src" -I"." -D_SUPPRESS_PLIB_WARNING -I"C:/Program Files (x86)/Microchip/xc32/v2.15/pic32-libs" -MP -MMD -MF "${OBJECTDIR}/src/sas/lora.o.d" -o ${OBJECTDIR}/src/sas/lora.o src/sas/lora.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/src/sas/slink.o: src/sas/slink.c  .generated_files/8745087ec86f18e726d560892605e3750ece3bda.flag .generated_files/8bac4a0766d39c6687560ebfeb650ad7e1a6910e.flag
	@${MKDIR} "${OBJECTDIR}/src/sas" 
	@${RM} ${OBJECTDIR}/src/sas/slink.o.d 
	@${RM} ${OBJECTDIR}/src/sas/slink.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"src" -I"." -D_SUPPRESS_PLIB_WARNING -I"C:/Program Files (x86)/Microchip/xc32/v2.15/pic32-libs" -MP -MMD -MF "${OBJECTDIR}/src/sas/slink.o.d" -o ${OBJECTDIR}/src/sas/slink.o src/sas/slink.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/src/sas/server.o: src/sas/server.c  .generated_files/f9a14a5b87fbef4856fefe08fabd395b72f71d9d.flag .generated_files/8bac4a0766d39c6687560ebfeb650ad7e1a6910e.flag
	@${MKDIR} "${OBJECTDIR}/src/sas" 
	@${RM} ${OBJECTDIR}/src/sas/server.o.d 
	@${RM} ${OBJECTDIR}/src/sas/server.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"src" -I"." -D_SUPPRESS_PLIB_WARNING -I"C:/Program Files (x86)/Microchip/xc32/v2.15/pic32-libs" -MP -MMD -MF "${OBJECTDIR}/src/sas/server.o.d" -o ${OBJECTDIR}/src/sas/server.o src/sas/server.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/src/sas/rtc.o: src/sas/rtc.c  .generated_files/7ba8b41f263dd5c10b686c9d0543b372c103e26b.flag .generated_files/8bac4a0766d39c6687560ebfeb650ad7e1a6910e.flag
	@${MKDIR} "${OBJECTDIR}/src/sas" 
	@${RM} ${OBJECTDIR}/src/sas/rtc.o.d 
	@${RM} ${OBJECTDIR}/src/sas/rtc.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"src" -I"." -D_SUPPRESS_PLIB_WARNING -I"C:/Program Files (x86)/Microchip/xc32/v2.15/pic32-libs" -MP -MMD -MF "${OBJECTDIR}/src/sas/rtc.o.d" -o ${OBJECTDIR}/src/sas/rtc.o src/sas/rtc.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/src/sas/gps.o: src/sas/gps.c  .generated_files/46ac47e6a9f6408865167b23fd850017b0dd72c6.flag .generated_files/8bac4a0766d39c6687560ebfeb650ad7e1a6910e.flag
	@${MKDIR} "${OBJECTDIR}/src/sas" 
	@${RM} ${OBJECTDIR}/src/sas/gps.o.d 
	@${RM} ${OBJECTDIR}/src/sas/gps.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"src" -I"." -D_SUPPRESS_PLIB_WARNING -I"C:/Program Files (x86)/Microchip/xc32/v2.15/pic32-libs" -MP -MMD -MF "${OBJECTDIR}/src/sas/gps.o.d" -o ${OBJECTDIR}/src/sas/gps.o src/sas/gps.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/main.o: main.c  .generated_files/669f1ec6cb9681003dde3e487da3f6c1a695c6e8.flag .generated_files/8bac4a0766d39c6687560ebfeb650ad7e1a6910e.flag
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/main.o.d 
	@${RM} ${OBJECTDIR}/main.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"src" -I"." -D_SUPPRESS_PLIB_WARNING -I"C:/Program Files (x86)/Microchip/xc32/v2.15/pic32-libs" -MP -MMD -MF "${OBJECTDIR}/main.o.d" -o ${OBJECTDIR}/main.o main.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/src/app/edge/edge.o: src/app/edge/edge.c  .generated_files/2936659d4f075b8fd43a4077d9f29a551ce4b327.flag .generated_files/8bac4a0766d39c6687560ebfeb650ad7e1a6910e.flag
	@${MKDIR} "${OBJECTDIR}/src/app/edge" 
	@${RM} ${OBJECTDIR}/src/app/edge/edge.o.d 
	@${RM} ${OBJECTDIR}/src/app/edge/edge.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"src" -I"." -D_SUPPRESS_PLIB_WARNING -I"C:/Program Files (x86)/Microchip/xc32/v2.15/pic32-libs" -MP -MMD -MF "${OBJECTDIR}/src/app/edge/edge.o.d" -o ${OBJECTDIR}/src/app/edge/edge.o src/app/edge/edge.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	
else
${OBJECTDIR}/src/app/logic/logic.o: src/app/logic/logic.c  .generated_files/98f9588652f8fb1074e915203bb1b5b05dbd4958.flag .generated_files/8bac4a0766d39c6687560ebfeb650ad7e1a6910e.flag
	@${MKDIR} "${OBJECTDIR}/src/app/logic" 
	@${RM} ${OBJECTDIR}/src/app/logic/logic.o.d 
	@${RM} ${OBJECTDIR}/src/app/logic/logic.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"src" -I"." -D_SUPPRESS_PLIB_WARNING -I"C:/Program Files (x86)/Microchip/xc32/v2.15/pic32-libs" -MP -MMD -MF "${OBJECTDIR}/src/app/logic/logic.o.d" -o ${OBJECTDIR}/src/app/logic/logic.o src/app/logic/logic.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/src/app/logic/state.o: src/app/logic/state.c  .generated_files/d154f5709b756846c62f908bb56a366dc43d8423.flag .generated_files/8bac4a0766d39c6687560ebfeb650ad7e1a6910e.flag
	@${MKDIR} "${OBJECTDIR}/src/app/logic" 
	@${RM} ${OBJECTDIR}/src/app/logic/state.o.d 
	@${RM} ${OBJECTDIR}/src/app/logic/state.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"src" -I"." -D_SUPPRESS_PLIB_WARNING -I"C:/Program Files (x86)/Microchip/xc32/v2.15/pic32-libs" -MP -MMD -MF "${OBJECTDIR}/src/app/logic/state.o.d" -o ${OBJECTDIR}/src/app/logic/state.o src/app/logic/state.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/src/app/net/cellular.o: src/app/net/cellular.c  .generated_files/dc30c22ba12e0ec83b3e0891c7dadf93c0dc804a.flag .generated_files/8bac4a0766d39c6687560ebfeb650ad7e1a6910e.flag
	@${MKDIR} "${OBJECTDIR}/src/app/net" 
	@${RM} ${OBJECTDIR}/src/app/net/cellular.o.d 
	@${RM} ${OBJECTDIR}/src/app/net/cellular.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"src" -I"." -D_SUPPRESS_PLIB_WARNING -I"C:/Program Files (x86)/Microchip/xc32/v2.15/pic32-libs" -MP -MMD -MF "${OBJECTDIR}/src/app/net/cellular.o.d" -o ${OBJECTDIR}/src/app/net/cellular.o src/app/net/cellular.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/src/app/net/serial.o: src/app/net/serial.c  .generated_files/ec88b2718535429e4fe1d63469ed9f1974ba1983.flag .generated_files/8bac4a0766d39c6687560ebfeb650ad7e1a6910e.flag
	@${MKDIR} "${OBJECTDIR}/src/app/net" 
	@${RM} ${OBJECTDIR}/src/app/net/serial.o.d 
	@${RM} ${OBJECTDIR}/src/app/net/serial.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"src" -I"." -D_SUPPRESS_PLIB_WARNING -I"C:/Program Files (x86)/Microchip/xc32/v2.15/pic32-libs" -MP -MMD -MF "${OBJECTDIR}/src/app/net/serial.o.d" -o ${OBJECTDIR}/src/app/net/serial.o src/app/net/serial.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/src/app/net/radio.o: src/app/net/radio.c  .generated_files/e7a3552bb562ab797d036e667f2aad7a47a74a24.flag .generated_files/8bac4a0766d39c6687560ebfeb650ad7e1a6910e.flag
	@${MKDIR} "${OBJECTDIR}/src/app/net" 
	@${RM} ${OBJECTDIR}/src/app/net/radio.o.d 
	@${RM} ${OBJECTDIR}/src/app/net/radio.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"src" -I"." -D_SUPPRESS_PLIB_WARNING -I"C:/Program Files (x86)/Microchip/xc32/v2.15/pic32-libs" -MP -MMD -MF "${OBJECTDIR}/src/app/net/radio.o.d" -o ${OBJECTDIR}/src/app/net/radio.o src/app/net/radio.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/src/app/out/power_ctrl.o: src/app/out/power_ctrl.c  .generated_files/e4900d9bc1e1347a13b708e59d52b02b463ba8d1.flag .generated_files/8bac4a0766d39c6687560ebfeb650ad7e1a6910e.flag
	@${MKDIR} "${OBJECTDIR}/src/app/out" 
	@${RM} ${OBJECTDIR}/src/app/out/power_ctrl.o.d 
	@${RM} ${OBJECTDIR}/src/app/out/power_ctrl.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"src" -I"." -D_SUPPRESS_PLIB_WARNING -I"C:/Program Files (x86)/Microchip/xc32/v2.15/pic32-libs" -MP -MMD -MF "${OBJECTDIR}/src/app/out/power_ctrl.o.d" -o ${OBJECTDIR}/src/app/out/power_ctrl.o src/app/out/power_ctrl.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/src/app/sem/chronos.o: src/app/sem/chronos.c  .generated_files/69099e5cd187d61a587d65d846470bb49f75d6d6.flag .generated_files/8bac4a0766d39c6687560ebfeb650ad7e1a6910e.flag
	@${MKDIR} "${OBJECTDIR}/src/app/sem" 
	@${RM} ${OBJECTDIR}/src/app/sem/chronos.o.d 
	@${RM} ${OBJECTDIR}/src/app/sem/chronos.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"src" -I"." -D_SUPPRESS_PLIB_WARNING -I"C:/Program Files (x86)/Microchip/xc32/v2.15/pic32-libs" -MP -MMD -MF "${OBJECTDIR}/src/app/sem/chronos.o.d" -o ${OBJECTDIR}/src/app/sem/chronos.o src/app/sem/chronos.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/src/app/sem/sem_objects.o: src/app/sem/sem_objects.c  .generated_files/914ed294fb437ac72fd89012030cd1d61d6d3a13.flag .generated_files/8bac4a0766d39c6687560ebfeb650ad7e1a6910e.flag
	@${MKDIR} "${OBJECTDIR}/src/app/sem" 
	@${RM} ${OBJECTDIR}/src/app/sem/sem_objects.o.d 
	@${RM} ${OBJECTDIR}/src/app/sem/sem_objects.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"src" -I"." -D_SUPPRESS_PLIB_WARNING -I"C:/Program Files (x86)/Microchip/xc32/v2.15/pic32-libs" -MP -MMD -MF "${OBJECTDIR}/src/app/sem/sem_objects.o.d" -o ${OBJECTDIR}/src/app/sem/sem_objects.o src/app/sem/sem_objects.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/src/app/sem/semaphore.o: src/app/sem/semaphore.c  .generated_files/b11ed45fe707af029ed93ec81494e12436e492d6.flag .generated_files/8bac4a0766d39c6687560ebfeb650ad7e1a6910e.flag
	@${MKDIR} "${OBJECTDIR}/src/app/sem" 
	@${RM} ${OBJECTDIR}/src/app/sem/semaphore.o.d 
	@${RM} ${OBJECTDIR}/src/app/sem/semaphore.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"src" -I"." -D_SUPPRESS_PLIB_WARNING -I"C:/Program Files (x86)/Microchip/xc32/v2.15/pic32-libs" -MP -MMD -MF "${OBJECTDIR}/src/app/sem/semaphore.o.d" -o ${OBJECTDIR}/src/app/sem/semaphore.o src/app/sem/semaphore.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/src/cfg/app_config.o: src/cfg/app_config.c  .generated_files/f9ddd7778134c4531d1c35286b4741b7633a73f9.flag .generated_files/8bac4a0766d39c6687560ebfeb650ad7e1a6910e.flag
	@${MKDIR} "${OBJECTDIR}/src/cfg" 
	@${RM} ${OBJECTDIR}/src/cfg/app_config.o.d 
	@${RM} ${OBJECTDIR}/src/cfg/app_config.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"src" -I"." -D_SUPPRESS_PLIB_WARNING -I"C:/Program Files (x86)/Microchip/xc32/v2.15/pic32-libs" -MP -MMD -MF "${OBJECTDIR}/src/cfg/app_config.o.d" -o ${OBJECTDIR}/src/cfg/app_config.o src/cfg/app_config.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/src/cfg/hw_config.o: src/cfg/hw_config.c  .generated_files/48456e0cb9d1ebea6b459a5adfd23887254f792b.flag .generated_files/8bac4a0766d39c6687560ebfeb650ad7e1a6910e.flag
	@${MKDIR} "${OBJECTDIR}/src/cfg" 
	@${RM} ${OBJECTDIR}/src/cfg/hw_config.o.d 
	@${RM} ${OBJECTDIR}/src/cfg/hw_config.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"src" -I"." -D_SUPPRESS_PLIB_WARNING -I"C:/Program Files (x86)/Microchip/xc32/v2.15/pic32-libs" -MP -MMD -MF "${OBJECTDIR}/src/cfg/hw_config.o.d" -o ${OBJECTDIR}/src/cfg/hw_config.o src/cfg/hw_config.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/src/drv/pcf2129t.o: src/drv/pcf2129t.c  .generated_files/2028ddb2da7033519beba1ec9902ec03d2fa5cf3.flag .generated_files/8bac4a0766d39c6687560ebfeb650ad7e1a6910e.flag
	@${MKDIR} "${OBJECTDIR}/src/drv" 
	@${RM} ${OBJECTDIR}/src/drv/pcf2129t.o.d 
	@${RM} ${OBJECTDIR}/src/drv/pcf2129t.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"src" -I"." -D_SUPPRESS_PLIB_WARNING -I"C:/Program Files (x86)/Microchip/xc32/v2.15/pic32-libs" -MP -MMD -MF "${OBJECTDIR}/src/drv/pcf2129t.o.d" -o ${OBJECTDIR}/src/drv/pcf2129t.o src/drv/pcf2129t.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/src/drv/rfm95.o: src/drv/rfm95.c  .generated_files/c80641ed8c39496bc674578120a20986990fa9e5.flag .generated_files/8bac4a0766d39c6687560ebfeb650ad7e1a6910e.flag
	@${MKDIR} "${OBJECTDIR}/src/drv" 
	@${RM} ${OBJECTDIR}/src/drv/rfm95.o.d 
	@${RM} ${OBJECTDIR}/src/drv/rfm95.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"src" -I"." -D_SUPPRESS_PLIB_WARNING -I"C:/Program Files (x86)/Microchip/xc32/v2.15/pic32-libs" -MP -MMD -MF "${OBJECTDIR}/src/drv/rfm95.o.d" -o ${OBJECTDIR}/src/drv/rfm95.o src/drv/rfm95.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/src/hal/can/CANConfiguration.o: src/hal/can/CANConfiguration.c  .generated_files/db3cf47b69ffc6291386cf2ab9a78f47f96a9de8.flag .generated_files/8bac4a0766d39c6687560ebfeb650ad7e1a6910e.flag
	@${MKDIR} "${OBJECTDIR}/src/hal/can" 
	@${RM} ${OBJECTDIR}/src/hal/can/CANConfiguration.o.d 
	@${RM} ${OBJECTDIR}/src/hal/can/CANConfiguration.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"src" -I"." -D_SUPPRESS_PLIB_WARNING -I"C:/Program Files (x86)/Microchip/xc32/v2.15/pic32-libs" -MP -MMD -MF "${OBJECTDIR}/src/hal/can/CANConfiguration.o.d" -o ${OBJECTDIR}/src/hal/can/CANConfiguration.o src/hal/can/CANConfiguration.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/src/hal/can/CANErrorFunctions.o: src/hal/can/CANErrorFunctions.c  .generated_files/9fddedf8047a3f061c9ece810edaaec9948332b4.flag .generated_files/8bac4a0766d39c6687560ebfeb650ad7e1a6910e.flag
	@${MKDIR} "${OBJECTDIR}/src/hal/can" 
	@${RM} ${OBJECTDIR}/src/hal/can/CANErrorFunctions.o.d 
	@${RM} ${OBJECTDIR}/src/hal/can/CANErrorFunctions.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"src" -I"." -D_SUPPRESS_PLIB_WARNING -I"C:/Program Files (x86)/Microchip/xc32/v2.15/pic32-libs" -MP -MMD -MF "${OBJECTDIR}/src/hal/can/CANErrorFunctions.o.d" -o ${OBJECTDIR}/src/hal/can/CANErrorFunctions.o src/hal/can/CANErrorFunctions.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/src/hal/can/CANEventFunctions.o: src/hal/can/CANEventFunctions.c  .generated_files/72fe6595fe0284e2fcc87dde045229b6c395ae5.flag .generated_files/8bac4a0766d39c6687560ebfeb650ad7e1a6910e.flag
	@${MKDIR} "${OBJECTDIR}/src/hal/can" 
	@${RM} ${OBJECTDIR}/src/hal/can/CANEventFunctions.o.d 
	@${RM} ${OBJECTDIR}/src/hal/can/CANEventFunctions.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"src" -I"." -D_SUPPRESS_PLIB_WARNING -I"C:/Program Files (x86)/Microchip/xc32/v2.15/pic32-libs" -MP -MMD -MF "${OBJECTDIR}/src/hal/can/CANEventFunctions.o.d" -o ${OBJECTDIR}/src/hal/can/CANEventFunctions.o src/hal/can/CANEventFunctions.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/src/hal/can/CANFilterFunctions.o: src/hal/can/CANFilterFunctions.c  .generated_files/15018451538d4a720a01b499776efa8d5e25428b.flag .generated_files/8bac4a0766d39c6687560ebfeb650ad7e1a6910e.flag
	@${MKDIR} "${OBJECTDIR}/src/hal/can" 
	@${RM} ${OBJECTDIR}/src/hal/can/CANFilterFunctions.o.d 
	@${RM} ${OBJECTDIR}/src/hal/can/CANFilterFunctions.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"src" -I"." -D_SUPPRESS_PLIB_WARNING -I"C:/Program Files (x86)/Microchip/xc32/v2.15/pic32-libs" -MP -MMD -MF "${OBJECTDIR}/src/hal/can/CANFilterFunctions.o.d" -o ${OBJECTDIR}/src/hal/can/CANFilterFunctions.o src/hal/can/CANFilterFunctions.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/src/hal/can/CANInfoFunctions.o: src/hal/can/CANInfoFunctions.c  .generated_files/63e36881716f4a3f2fad85fd3b5e3b21fa0ac4b3.flag .generated_files/8bac4a0766d39c6687560ebfeb650ad7e1a6910e.flag
	@${MKDIR} "${OBJECTDIR}/src/hal/can" 
	@${RM} ${OBJECTDIR}/src/hal/can/CANInfoFunctions.o.d 
	@${RM} ${OBJECTDIR}/src/hal/can/CANInfoFunctions.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"src" -I"." -D_SUPPRESS_PLIB_WARNING -I"C:/Program Files (x86)/Microchip/xc32/v2.15/pic32-libs" -MP -MMD -MF "${OBJECTDIR}/src/hal/can/CANInfoFunctions.o.d" -o ${OBJECTDIR}/src/hal/can/CANInfoFunctions.o src/hal/can/CANInfoFunctions.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/src/hal/can/CANReceiveFunctions.o: src/hal/can/CANReceiveFunctions.c  .generated_files/f88a3868ca64fe8439ee918024bb637c121cacc6.flag .generated_files/8bac4a0766d39c6687560ebfeb650ad7e1a6910e.flag
	@${MKDIR} "${OBJECTDIR}/src/hal/can" 
	@${RM} ${OBJECTDIR}/src/hal/can/CANReceiveFunctions.o.d 
	@${RM} ${OBJECTDIR}/src/hal/can/CANReceiveFunctions.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"src" -I"." -D_SUPPRESS_PLIB_WARNING -I"C:/Program Files (x86)/Microchip/xc32/v2.15/pic32-libs" -MP -MMD -MF "${OBJECTDIR}/src/hal/can/CANReceiveFunctions.o.d" -o ${OBJECTDIR}/src/hal/can/CANReceiveFunctions.o src/hal/can/CANReceiveFunctions.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/src/hal/can/CANTransmitFunctions.o: src/hal/can/CANTransmitFunctions.c  .generated_files/144e601fe42f7ff52f7ae6c2a1ba9f6f41726879.flag .generated_files/8bac4a0766d39c6687560ebfeb650ad7e1a6910e.flag
	@${MKDIR} "${OBJECTDIR}/src/hal/can" 
	@${RM} ${OBJECTDIR}/src/hal/can/CANTransmitFunctions.o.d 
	@${RM} ${OBJECTDIR}/src/hal/can/CANTransmitFunctions.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"src" -I"." -D_SUPPRESS_PLIB_WARNING -I"C:/Program Files (x86)/Microchip/xc32/v2.15/pic32-libs" -MP -MMD -MF "${OBJECTDIR}/src/hal/can/CANTransmitFunctions.o.d" -o ${OBJECTDIR}/src/hal/can/CANTransmitFunctions.o src/hal/can/CANTransmitFunctions.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/src/hal/pin32.o: src/hal/pin32.c  .generated_files/4f21a48632fe7aa3a646da1e26a6fb164c567e95.flag .generated_files/8bac4a0766d39c6687560ebfeb650ad7e1a6910e.flag
	@${MKDIR} "${OBJECTDIR}/src/hal" 
	@${RM} ${OBJECTDIR}/src/hal/pin32.o.d 
	@${RM} ${OBJECTDIR}/src/hal/pin32.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"src" -I"." -D_SUPPRESS_PLIB_WARNING -I"C:/Program Files (x86)/Microchip/xc32/v2.15/pic32-libs" -MP -MMD -MF "${OBJECTDIR}/src/hal/pin32.o.d" -o ${OBJECTDIR}/src/hal/pin32.o src/hal/pin32.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/src/hal/uart32mx.o: src/hal/uart32mx.c  .generated_files/f4118646c29f975c0070d07f061c5394576f0d00.flag .generated_files/8bac4a0766d39c6687560ebfeb650ad7e1a6910e.flag
	@${MKDIR} "${OBJECTDIR}/src/hal" 
	@${RM} ${OBJECTDIR}/src/hal/uart32mx.o.d 
	@${RM} ${OBJECTDIR}/src/hal/uart32mx.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"src" -I"." -D_SUPPRESS_PLIB_WARNING -I"C:/Program Files (x86)/Microchip/xc32/v2.15/pic32-libs" -MP -MMD -MF "${OBJECTDIR}/src/hal/uart32mx.o.d" -o ${OBJECTDIR}/src/hal/uart32mx.o src/hal/uart32mx.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/src/lib/aes.o: src/lib/aes.c  .generated_files/f61e1166a0dbb71bd4fffd7d96e7f21d84ae635f.flag .generated_files/8bac4a0766d39c6687560ebfeb650ad7e1a6910e.flag
	@${MKDIR} "${OBJECTDIR}/src/lib" 
	@${RM} ${OBJECTDIR}/src/lib/aes.o.d 
	@${RM} ${OBJECTDIR}/src/lib/aes.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"src" -I"." -D_SUPPRESS_PLIB_WARNING -I"C:/Program Files (x86)/Microchip/xc32/v2.15/pic32-libs" -MP -MMD -MF "${OBJECTDIR}/src/lib/aes.o.d" -o ${OBJECTDIR}/src/lib/aes.o src/lib/aes.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/src/lib/datetime.o: src/lib/datetime.c  .generated_files/172c3b9e4e7d3d05bc65e16f3c5af54ae9da3ffb.flag .generated_files/8bac4a0766d39c6687560ebfeb650ad7e1a6910e.flag
	@${MKDIR} "${OBJECTDIR}/src/lib" 
	@${RM} ${OBJECTDIR}/src/lib/datetime.o.d 
	@${RM} ${OBJECTDIR}/src/lib/datetime.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"src" -I"." -D_SUPPRESS_PLIB_WARNING -I"C:/Program Files (x86)/Microchip/xc32/v2.15/pic32-libs" -MP -MMD -MF "${OBJECTDIR}/src/lib/datetime.o.d" -o ${OBJECTDIR}/src/lib/datetime.o src/lib/datetime.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/src/lib/utils.o: src/lib/utils.c  .generated_files/b30c76b817605e06cfaaeaabc9183c15888de3f0.flag .generated_files/8bac4a0766d39c6687560ebfeb650ad7e1a6910e.flag
	@${MKDIR} "${OBJECTDIR}/src/lib" 
	@${RM} ${OBJECTDIR}/src/lib/utils.o.d 
	@${RM} ${OBJECTDIR}/src/lib/utils.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"src" -I"." -D_SUPPRESS_PLIB_WARNING -I"C:/Program Files (x86)/Microchip/xc32/v2.15/pic32-libs" -MP -MMD -MF "${OBJECTDIR}/src/lib/utils.o.d" -o ${OBJECTDIR}/src/lib/utils.o src/lib/utils.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/src/lib/shared_buff.o: src/lib/shared_buff.c  .generated_files/bba5fc67a04094aff72af135b45655456825a012.flag .generated_files/8bac4a0766d39c6687560ebfeb650ad7e1a6910e.flag
	@${MKDIR} "${OBJECTDIR}/src/lib" 
	@${RM} ${OBJECTDIR}/src/lib/shared_buff.o.d 
	@${RM} ${OBJECTDIR}/src/lib/shared_buff.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"src" -I"." -D_SUPPRESS_PLIB_WARNING -I"C:/Program Files (x86)/Microchip/xc32/v2.15/pic32-libs" -MP -MMD -MF "${OBJECTDIR}/src/lib/shared_buff.o.d" -o ${OBJECTDIR}/src/lib/shared_buff.o src/lib/shared_buff.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/src/lib/jparsing.o: src/lib/jparsing.c  .generated_files/35ee01d1b109105da59a79b4e7a9fb41b95bd526.flag .generated_files/8bac4a0766d39c6687560ebfeb650ad7e1a6910e.flag
	@${MKDIR} "${OBJECTDIR}/src/lib" 
	@${RM} ${OBJECTDIR}/src/lib/jparsing.o.d 
	@${RM} ${OBJECTDIR}/src/lib/jparsing.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"src" -I"." -D_SUPPRESS_PLIB_WARNING -I"C:/Program Files (x86)/Microchip/xc32/v2.15/pic32-libs" -MP -MMD -MF "${OBJECTDIR}/src/lib/jparsing.o.d" -o ${OBJECTDIR}/src/lib/jparsing.o src/lib/jparsing.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/src/lib/jsmn.o: src/lib/jsmn.c  .generated_files/54096542dab4c3b098af4212f64389c49f361a1c.flag .generated_files/8bac4a0766d39c6687560ebfeb650ad7e1a6910e.flag
	@${MKDIR} "${OBJECTDIR}/src/lib" 
	@${RM} ${OBJECTDIR}/src/lib/jsmn.o.d 
	@${RM} ${OBJECTDIR}/src/lib/jsmn.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"src" -I"." -D_SUPPRESS_PLIB_WARNING -I"C:/Program Files (x86)/Microchip/xc32/v2.15/pic32-libs" -MP -MMD -MF "${OBJECTDIR}/src/lib/jsmn.o.d" -o ${OBJECTDIR}/src/lib/jsmn.o src/lib/jsmn.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/mcc_generated_files/spi3.o: mcc_generated_files/spi3.c  .generated_files/121f7de767bf744069f2af4f9a699546940d55d6.flag .generated_files/8bac4a0766d39c6687560ebfeb650ad7e1a6910e.flag
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/spi3.o.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/spi3.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"src" -I"." -D_SUPPRESS_PLIB_WARNING -I"C:/Program Files (x86)/Microchip/xc32/v2.15/pic32-libs" -MP -MMD -MF "${OBJECTDIR}/mcc_generated_files/spi3.o.d" -o ${OBJECTDIR}/mcc_generated_files/spi3.o mcc_generated_files/spi3.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/mcc_generated_files/uart3.o: mcc_generated_files/uart3.c  .generated_files/c978f3bff9a8532290597d7e4b9b8245776bd036.flag .generated_files/8bac4a0766d39c6687560ebfeb650ad7e1a6910e.flag
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/uart3.o.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/uart3.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"src" -I"." -D_SUPPRESS_PLIB_WARNING -I"C:/Program Files (x86)/Microchip/xc32/v2.15/pic32-libs" -MP -MMD -MF "${OBJECTDIR}/mcc_generated_files/uart3.o.d" -o ${OBJECTDIR}/mcc_generated_files/uart3.o mcc_generated_files/uart3.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/mcc_generated_files/interrupt_manager.o: mcc_generated_files/interrupt_manager.c  .generated_files/56353c8d98f18beb61b7673b001ae34af7a4cff8.flag .generated_files/8bac4a0766d39c6687560ebfeb650ad7e1a6910e.flag
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/interrupt_manager.o.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/interrupt_manager.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"src" -I"." -D_SUPPRESS_PLIB_WARNING -I"C:/Program Files (x86)/Microchip/xc32/v2.15/pic32-libs" -MP -MMD -MF "${OBJECTDIR}/mcc_generated_files/interrupt_manager.o.d" -o ${OBJECTDIR}/mcc_generated_files/interrupt_manager.o mcc_generated_files/interrupt_manager.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/mcc_generated_files/mcc.o: mcc_generated_files/mcc.c  .generated_files/6654044de1e02e7441df09e9ff61bc2b06e0c415.flag .generated_files/8bac4a0766d39c6687560ebfeb650ad7e1a6910e.flag
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/mcc.o.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/mcc.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"src" -I"." -D_SUPPRESS_PLIB_WARNING -I"C:/Program Files (x86)/Microchip/xc32/v2.15/pic32-libs" -MP -MMD -MF "${OBJECTDIR}/mcc_generated_files/mcc.o.d" -o ${OBJECTDIR}/mcc_generated_files/mcc.o mcc_generated_files/mcc.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/mcc_generated_files/uart1.o: mcc_generated_files/uart1.c  .generated_files/26a1b8d39ed08bb871c93659c30a1661afb95d5b.flag .generated_files/8bac4a0766d39c6687560ebfeb650ad7e1a6910e.flag
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/uart1.o.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/uart1.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"src" -I"." -D_SUPPRESS_PLIB_WARNING -I"C:/Program Files (x86)/Microchip/xc32/v2.15/pic32-libs" -MP -MMD -MF "${OBJECTDIR}/mcc_generated_files/uart1.o.d" -o ${OBJECTDIR}/mcc_generated_files/uart1.o mcc_generated_files/uart1.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/mcc_generated_files/pin_manager.o: mcc_generated_files/pin_manager.c  .generated_files/88184b2f1c3ac0f7d93f4402f9cfce98338abca4.flag .generated_files/8bac4a0766d39c6687560ebfeb650ad7e1a6910e.flag
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/pin_manager.o.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/pin_manager.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"src" -I"." -D_SUPPRESS_PLIB_WARNING -I"C:/Program Files (x86)/Microchip/xc32/v2.15/pic32-libs" -MP -MMD -MF "${OBJECTDIR}/mcc_generated_files/pin_manager.o.d" -o ${OBJECTDIR}/mcc_generated_files/pin_manager.o mcc_generated_files/pin_manager.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/mcc_generated_files/uart2.o: mcc_generated_files/uart2.c  .generated_files/25a5412ad0d3e0bcda8474e1ac8a846914e92fe1.flag .generated_files/8bac4a0766d39c6687560ebfeb650ad7e1a6910e.flag
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/uart2.o.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/uart2.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"src" -I"." -D_SUPPRESS_PLIB_WARNING -I"C:/Program Files (x86)/Microchip/xc32/v2.15/pic32-libs" -MP -MMD -MF "${OBJECTDIR}/mcc_generated_files/uart2.o.d" -o ${OBJECTDIR}/mcc_generated_files/uart2.o mcc_generated_files/uart2.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/mcc_generated_files/tmr1.o: mcc_generated_files/tmr1.c  .generated_files/9e56c9e8fd5215a6d47c232e39318ca62b7fe048.flag .generated_files/8bac4a0766d39c6687560ebfeb650ad7e1a6910e.flag
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/tmr1.o.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/tmr1.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"src" -I"." -D_SUPPRESS_PLIB_WARNING -I"C:/Program Files (x86)/Microchip/xc32/v2.15/pic32-libs" -MP -MMD -MF "${OBJECTDIR}/mcc_generated_files/tmr1.o.d" -o ${OBJECTDIR}/mcc_generated_files/tmr1.o mcc_generated_files/tmr1.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/mcc_generated_files/uart4.o: mcc_generated_files/uart4.c  .generated_files/79421049b3be5a3cb45c7bafd99913faccecdd96.flag .generated_files/8bac4a0766d39c6687560ebfeb650ad7e1a6910e.flag
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/uart4.o.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/uart4.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"src" -I"." -D_SUPPRESS_PLIB_WARNING -I"C:/Program Files (x86)/Microchip/xc32/v2.15/pic32-libs" -MP -MMD -MF "${OBJECTDIR}/mcc_generated_files/uart4.o.d" -o ${OBJECTDIR}/mcc_generated_files/uart4.o mcc_generated_files/uart4.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/mcc_generated_files/uart5.o: mcc_generated_files/uart5.c  .generated_files/c21ff5678bb4276084251af1e47c61ac6b88668.flag .generated_files/8bac4a0766d39c6687560ebfeb650ad7e1a6910e.flag
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/uart5.o.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/uart5.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"src" -I"." -D_SUPPRESS_PLIB_WARNING -I"C:/Program Files (x86)/Microchip/xc32/v2.15/pic32-libs" -MP -MMD -MF "${OBJECTDIR}/mcc_generated_files/uart5.o.d" -o ${OBJECTDIR}/mcc_generated_files/uart5.o mcc_generated_files/uart5.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/mcc_generated_files/tmr2.o: mcc_generated_files/tmr2.c  .generated_files/140093657f1526f273f6ba8d37d4f4b69625b290.flag .generated_files/8bac4a0766d39c6687560ebfeb650ad7e1a6910e.flag
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/tmr2.o.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/tmr2.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"src" -I"." -D_SUPPRESS_PLIB_WARNING -I"C:/Program Files (x86)/Microchip/xc32/v2.15/pic32-libs" -MP -MMD -MF "${OBJECTDIR}/mcc_generated_files/tmr2.o.d" -o ${OBJECTDIR}/mcc_generated_files/tmr2.o mcc_generated_files/tmr2.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/src/sal/buttons.o: src/sal/buttons.c  .generated_files/c640fa84432b10a89a68a20d97f20181da53cf35.flag .generated_files/8bac4a0766d39c6687560ebfeb650ad7e1a6910e.flag
	@${MKDIR} "${OBJECTDIR}/src/sal" 
	@${RM} ${OBJECTDIR}/src/sal/buttons.o.d 
	@${RM} ${OBJECTDIR}/src/sal/buttons.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"src" -I"." -D_SUPPRESS_PLIB_WARNING -I"C:/Program Files (x86)/Microchip/xc32/v2.15/pic32-libs" -MP -MMD -MF "${OBJECTDIR}/src/sal/buttons.o.d" -o ${OBJECTDIR}/src/sal/buttons.o src/sal/buttons.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/src/sal/pulse.o: src/sal/pulse.c  .generated_files/f908f1906402bcc1fc14167698aa585f1e7e198.flag .generated_files/8bac4a0766d39c6687560ebfeb650ad7e1a6910e.flag
	@${MKDIR} "${OBJECTDIR}/src/sal" 
	@${RM} ${OBJECTDIR}/src/sal/pulse.o.d 
	@${RM} ${OBJECTDIR}/src/sal/pulse.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"src" -I"." -D_SUPPRESS_PLIB_WARNING -I"C:/Program Files (x86)/Microchip/xc32/v2.15/pic32-libs" -MP -MMD -MF "${OBJECTDIR}/src/sal/pulse.o.d" -o ${OBJECTDIR}/src/sal/pulse.o src/sal/pulse.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/src/sal/timer.o: src/sal/timer.c  .generated_files/148b5ec6efffc1ccea31f9206607ea1907e31c5b.flag .generated_files/8bac4a0766d39c6687560ebfeb650ad7e1a6910e.flag
	@${MKDIR} "${OBJECTDIR}/src/sal" 
	@${RM} ${OBJECTDIR}/src/sal/timer.o.d 
	@${RM} ${OBJECTDIR}/src/sal/timer.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"src" -I"." -D_SUPPRESS_PLIB_WARNING -I"C:/Program Files (x86)/Microchip/xc32/v2.15/pic32-libs" -MP -MMD -MF "${OBJECTDIR}/src/sal/timer.o.d" -o ${OBJECTDIR}/src/sal/timer.o src/sal/timer.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/src/sal/debug_std.o: src/sal/debug_std.c  .generated_files/2456e1c2720a755040ad22955a5715424efd41e6.flag .generated_files/8bac4a0766d39c6687560ebfeb650ad7e1a6910e.flag
	@${MKDIR} "${OBJECTDIR}/src/sal" 
	@${RM} ${OBJECTDIR}/src/sal/debug_std.o.d 
	@${RM} ${OBJECTDIR}/src/sal/debug_std.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"src" -I"." -D_SUPPRESS_PLIB_WARNING -I"C:/Program Files (x86)/Microchip/xc32/v2.15/pic32-libs" -MP -MMD -MF "${OBJECTDIR}/src/sal/debug_std.o.d" -o ${OBJECTDIR}/src/sal/debug_std.o src/sal/debug_std.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/src/sas/canbus.o: src/sas/canbus.c  .generated_files/f867368de270f817adf86daa854a4aa527febae0.flag .generated_files/8bac4a0766d39c6687560ebfeb650ad7e1a6910e.flag
	@${MKDIR} "${OBJECTDIR}/src/sas" 
	@${RM} ${OBJECTDIR}/src/sas/canbus.o.d 
	@${RM} ${OBJECTDIR}/src/sas/canbus.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"src" -I"." -D_SUPPRESS_PLIB_WARNING -I"C:/Program Files (x86)/Microchip/xc32/v2.15/pic32-libs" -MP -MMD -MF "${OBJECTDIR}/src/sas/canbus.o.d" -o ${OBJECTDIR}/src/sas/canbus.o src/sas/canbus.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/src/sas/atdrv.o: src/sas/atdrv.c  .generated_files/460b8fae2e434fda926fbeea7460c818a57c8858.flag .generated_files/8bac4a0766d39c6687560ebfeb650ad7e1a6910e.flag
	@${MKDIR} "${OBJECTDIR}/src/sas" 
	@${RM} ${OBJECTDIR}/src/sas/atdrv.o.d 
	@${RM} ${OBJECTDIR}/src/sas/atdrv.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"src" -I"." -D_SUPPRESS_PLIB_WARNING -I"C:/Program Files (x86)/Microchip/xc32/v2.15/pic32-libs" -MP -MMD -MF "${OBJECTDIR}/src/sas/atdrv.o.d" -o ${OBJECTDIR}/src/sas/atdrv.o src/sas/atdrv.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/src/sas/sim800c.o: src/sas/sim800c.c  .generated_files/675bb0fbd7706e76804d6d55c7258d13fdb654cb.flag .generated_files/8bac4a0766d39c6687560ebfeb650ad7e1a6910e.flag
	@${MKDIR} "${OBJECTDIR}/src/sas" 
	@${RM} ${OBJECTDIR}/src/sas/sim800c.o.d 
	@${RM} ${OBJECTDIR}/src/sas/sim800c.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"src" -I"." -D_SUPPRESS_PLIB_WARNING -I"C:/Program Files (x86)/Microchip/xc32/v2.15/pic32-libs" -MP -MMD -MF "${OBJECTDIR}/src/sas/sim800c.o.d" -o ${OBJECTDIR}/src/sas/sim800c.o src/sas/sim800c.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/src/sas/storage.o: src/sas/storage.c  .generated_files/9bc7c9d72e8c472c7b764666451cd35b1e7457eb.flag .generated_files/8bac4a0766d39c6687560ebfeb650ad7e1a6910e.flag
	@${MKDIR} "${OBJECTDIR}/src/sas" 
	@${RM} ${OBJECTDIR}/src/sas/storage.o.d 
	@${RM} ${OBJECTDIR}/src/sas/storage.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"src" -I"." -D_SUPPRESS_PLIB_WARNING -I"C:/Program Files (x86)/Microchip/xc32/v2.15/pic32-libs" -MP -MMD -MF "${OBJECTDIR}/src/sas/storage.o.d" -o ${OBJECTDIR}/src/sas/storage.o src/sas/storage.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/src/sas/rmsg_blob.o: src/sas/rmsg_blob.c  .generated_files/db0caac88926014cddb8eb3c6379d319cdfa3f90.flag .generated_files/8bac4a0766d39c6687560ebfeb650ad7e1a6910e.flag
	@${MKDIR} "${OBJECTDIR}/src/sas" 
	@${RM} ${OBJECTDIR}/src/sas/rmsg_blob.o.d 
	@${RM} ${OBJECTDIR}/src/sas/rmsg_blob.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"src" -I"." -D_SUPPRESS_PLIB_WARNING -I"C:/Program Files (x86)/Microchip/xc32/v2.15/pic32-libs" -MP -MMD -MF "${OBJECTDIR}/src/sas/rmsg_blob.o.d" -o ${OBJECTDIR}/src/sas/rmsg_blob.o src/sas/rmsg_blob.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/src/sas/lora.o: src/sas/lora.c  .generated_files/ba280bb11f2040a3a66b41f1828778334bcbb135.flag .generated_files/8bac4a0766d39c6687560ebfeb650ad7e1a6910e.flag
	@${MKDIR} "${OBJECTDIR}/src/sas" 
	@${RM} ${OBJECTDIR}/src/sas/lora.o.d 
	@${RM} ${OBJECTDIR}/src/sas/lora.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"src" -I"." -D_SUPPRESS_PLIB_WARNING -I"C:/Program Files (x86)/Microchip/xc32/v2.15/pic32-libs" -MP -MMD -MF "${OBJECTDIR}/src/sas/lora.o.d" -o ${OBJECTDIR}/src/sas/lora.o src/sas/lora.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/src/sas/slink.o: src/sas/slink.c  .generated_files/fc5908078dcfdc02b488e88b328c5e919654540c.flag .generated_files/8bac4a0766d39c6687560ebfeb650ad7e1a6910e.flag
	@${MKDIR} "${OBJECTDIR}/src/sas" 
	@${RM} ${OBJECTDIR}/src/sas/slink.o.d 
	@${RM} ${OBJECTDIR}/src/sas/slink.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"src" -I"." -D_SUPPRESS_PLIB_WARNING -I"C:/Program Files (x86)/Microchip/xc32/v2.15/pic32-libs" -MP -MMD -MF "${OBJECTDIR}/src/sas/slink.o.d" -o ${OBJECTDIR}/src/sas/slink.o src/sas/slink.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/src/sas/server.o: src/sas/server.c  .generated_files/8e953fd9afcdcf3b9388ee2de192ade20e1e7014.flag .generated_files/8bac4a0766d39c6687560ebfeb650ad7e1a6910e.flag
	@${MKDIR} "${OBJECTDIR}/src/sas" 
	@${RM} ${OBJECTDIR}/src/sas/server.o.d 
	@${RM} ${OBJECTDIR}/src/sas/server.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"src" -I"." -D_SUPPRESS_PLIB_WARNING -I"C:/Program Files (x86)/Microchip/xc32/v2.15/pic32-libs" -MP -MMD -MF "${OBJECTDIR}/src/sas/server.o.d" -o ${OBJECTDIR}/src/sas/server.o src/sas/server.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/src/sas/rtc.o: src/sas/rtc.c  .generated_files/79bab8e294f50a6316b79414e99faac461499a0e.flag .generated_files/8bac4a0766d39c6687560ebfeb650ad7e1a6910e.flag
	@${MKDIR} "${OBJECTDIR}/src/sas" 
	@${RM} ${OBJECTDIR}/src/sas/rtc.o.d 
	@${RM} ${OBJECTDIR}/src/sas/rtc.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"src" -I"." -D_SUPPRESS_PLIB_WARNING -I"C:/Program Files (x86)/Microchip/xc32/v2.15/pic32-libs" -MP -MMD -MF "${OBJECTDIR}/src/sas/rtc.o.d" -o ${OBJECTDIR}/src/sas/rtc.o src/sas/rtc.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/src/sas/gps.o: src/sas/gps.c  .generated_files/c59feae2f8cd832b9a92bc4cb70002beb586fd22.flag .generated_files/8bac4a0766d39c6687560ebfeb650ad7e1a6910e.flag
	@${MKDIR} "${OBJECTDIR}/src/sas" 
	@${RM} ${OBJECTDIR}/src/sas/gps.o.d 
	@${RM} ${OBJECTDIR}/src/sas/gps.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"src" -I"." -D_SUPPRESS_PLIB_WARNING -I"C:/Program Files (x86)/Microchip/xc32/v2.15/pic32-libs" -MP -MMD -MF "${OBJECTDIR}/src/sas/gps.o.d" -o ${OBJECTDIR}/src/sas/gps.o src/sas/gps.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/main.o: main.c  .generated_files/5ddef3ade575b1c7f1b3d84f0d98581a522560dc.flag .generated_files/8bac4a0766d39c6687560ebfeb650ad7e1a6910e.flag
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/main.o.d 
	@${RM} ${OBJECTDIR}/main.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"src" -I"." -D_SUPPRESS_PLIB_WARNING -I"C:/Program Files (x86)/Microchip/xc32/v2.15/pic32-libs" -MP -MMD -MF "${OBJECTDIR}/main.o.d" -o ${OBJECTDIR}/main.o main.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/src/app/edge/edge.o: src/app/edge/edge.c  .generated_files/29cd72e38b142581bbdc34a3ad7357c5415a9265.flag .generated_files/8bac4a0766d39c6687560ebfeb650ad7e1a6910e.flag
	@${MKDIR} "${OBJECTDIR}/src/app/edge" 
	@${RM} ${OBJECTDIR}/src/app/edge/edge.o.d 
	@${RM} ${OBJECTDIR}/src/app/edge/edge.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"src" -I"." -D_SUPPRESS_PLIB_WARNING -I"C:/Program Files (x86)/Microchip/xc32/v2.15/pic32-libs" -MP -MMD -MF "${OBJECTDIR}/src/app/edge/edge.o.d" -o ${OBJECTDIR}/src/app/edge/edge.o src/app/edge/edge.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: compileCPP
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: link
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
dist/${CND_CONF}/${IMAGE_TYPE}/GwMasterCtrl_v5.0.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk    
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE) -g   -mprocessor=$(MP_PROCESSOR_OPTION)  -o dist/${CND_CONF}/${IMAGE_TYPE}/GwMasterCtrl_v5.0.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX} ${OBJECTFILES_QUOTED_IF_SPACED}          -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  -std=gnu99 $(COMPARISON_BUILD)   -mreserve=data@0x0:0x1FC -mreserve=boot@0x1FC00490:0x1FC00BEF  -Wl,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_LD_POST)$(MP_LINKER_FILE_OPTION),--defsym=__MPLAB_DEBUG=1,--defsym=__DEBUG=1,-D=__DEBUG_D,--defsym=_min_heap_size=32,--gc-sections,--no-code-in-dinit,--no-dinit-in-serial-mem,-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map",--report-mem,--cref,--memorysummary,dist/${CND_CONF}/${IMAGE_TYPE}/memoryfile.xml,--defsym=_ebase_address=0x9D001000 -mdfp="${DFP_DIR}"
	
else
dist/${CND_CONF}/${IMAGE_TYPE}/GwMasterCtrl_v5.0.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk   
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE)  -mprocessor=$(MP_PROCESSOR_OPTION)  -o dist/${CND_CONF}/${IMAGE_TYPE}/GwMasterCtrl_v5.0.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} ${OBJECTFILES_QUOTED_IF_SPACED}          -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  -std=gnu99 $(COMPARISON_BUILD)  -Wl,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_LD_POST)$(MP_LINKER_FILE_OPTION),--defsym=_min_heap_size=32,--gc-sections,--no-code-in-dinit,--no-dinit-in-serial-mem,-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map",--report-mem,--cref,--memorysummary,dist/${CND_CONF}/${IMAGE_TYPE}/memoryfile.xml,--defsym=_ebase_address=0x9D001000 -mdfp="${DFP_DIR}"
	${MP_CC_DIR}\\xc32-bin2hex dist/${CND_CONF}/${IMAGE_TYPE}/GwMasterCtrl_v5.0.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} 
endif


# Subprojects
.build-subprojects:


# Subprojects
.clean-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r build/default
	${RM} -r dist/default

# Enable dependency checking
.dep.inc: .depcheck-impl

DEPFILES=$(shell mplabwildcard ${POSSIBLE_DEPFILES})
ifneq (${DEPFILES},)
include ${DEPFILES}
endif
