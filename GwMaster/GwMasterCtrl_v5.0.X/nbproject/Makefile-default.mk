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
SOURCEFILES_QUOTED_IF_SPACED=src/app/logic/logic.c src/app/logic/state.c src/app/net/cellular.c src/app/net/serial.c src/app/net/radio.c src/app/out/power_ctrl.c src/app/sem/chronos.c src/app/sem/sem_objects.c src/app/sem/semaphore.c src/cfg/app_config.c src/cfg/hw_config.c src/drv/pcf2129t.c src/drv/rfm95.c src/hal/can/CANConfiguration.c src/hal/can/CANErrorFunctions.c src/hal/can/CANEventFunctions.c src/hal/can/CANFilterFunctions.c src/hal/can/CANInfoFunctions.c src/hal/can/CANReceiveFunctions.c src/hal/can/CANTransmitFunctions.c src/hal/pin32.c src/hal/uart32mx.c src/lib/aes.c src/lib/datetime.c src/lib/utils.c src/lib/shared_buff.c src/lib/jparsing.c src/lib/jsmn.c mcc_generated_files/spi3.c mcc_generated_files/uart3.c mcc_generated_files/interrupt_manager.c mcc_generated_files/mcc.c mcc_generated_files/uart1.c mcc_generated_files/pin_manager.c mcc_generated_files/uart2.c mcc_generated_files/tmr1.c mcc_generated_files/uart4.c mcc_generated_files/uart5.c mcc_generated_files/tmr2.c src/sal/buttons.c src/sal/pulse.c src/sal/timer.c src/sal/debug.c src/sas/canbus.c src/sas/atdrv.c src/sas/sim800c.c src/sas/storage.c src/sas/rmsg_blob.c src/sas/lora.c src/sas/slink.c src/sas/server.c src/sas/rtc.c src/sas/gps.c main.c

# Object Files Quoted if spaced
OBJECTFILES_QUOTED_IF_SPACED=${OBJECTDIR}/src/app/logic/logic.o ${OBJECTDIR}/src/app/logic/state.o ${OBJECTDIR}/src/app/net/cellular.o ${OBJECTDIR}/src/app/net/serial.o ${OBJECTDIR}/src/app/net/radio.o ${OBJECTDIR}/src/app/out/power_ctrl.o ${OBJECTDIR}/src/app/sem/chronos.o ${OBJECTDIR}/src/app/sem/sem_objects.o ${OBJECTDIR}/src/app/sem/semaphore.o ${OBJECTDIR}/src/cfg/app_config.o ${OBJECTDIR}/src/cfg/hw_config.o ${OBJECTDIR}/src/drv/pcf2129t.o ${OBJECTDIR}/src/drv/rfm95.o ${OBJECTDIR}/src/hal/can/CANConfiguration.o ${OBJECTDIR}/src/hal/can/CANErrorFunctions.o ${OBJECTDIR}/src/hal/can/CANEventFunctions.o ${OBJECTDIR}/src/hal/can/CANFilterFunctions.o ${OBJECTDIR}/src/hal/can/CANInfoFunctions.o ${OBJECTDIR}/src/hal/can/CANReceiveFunctions.o ${OBJECTDIR}/src/hal/can/CANTransmitFunctions.o ${OBJECTDIR}/src/hal/pin32.o ${OBJECTDIR}/src/hal/uart32mx.o ${OBJECTDIR}/src/lib/aes.o ${OBJECTDIR}/src/lib/datetime.o ${OBJECTDIR}/src/lib/utils.o ${OBJECTDIR}/src/lib/shared_buff.o ${OBJECTDIR}/src/lib/jparsing.o ${OBJECTDIR}/src/lib/jsmn.o ${OBJECTDIR}/mcc_generated_files/spi3.o ${OBJECTDIR}/mcc_generated_files/uart3.o ${OBJECTDIR}/mcc_generated_files/interrupt_manager.o ${OBJECTDIR}/mcc_generated_files/mcc.o ${OBJECTDIR}/mcc_generated_files/uart1.o ${OBJECTDIR}/mcc_generated_files/pin_manager.o ${OBJECTDIR}/mcc_generated_files/uart2.o ${OBJECTDIR}/mcc_generated_files/tmr1.o ${OBJECTDIR}/mcc_generated_files/uart4.o ${OBJECTDIR}/mcc_generated_files/uart5.o ${OBJECTDIR}/mcc_generated_files/tmr2.o ${OBJECTDIR}/src/sal/buttons.o ${OBJECTDIR}/src/sal/pulse.o ${OBJECTDIR}/src/sal/timer.o ${OBJECTDIR}/src/sal/debug.o ${OBJECTDIR}/src/sas/canbus.o ${OBJECTDIR}/src/sas/atdrv.o ${OBJECTDIR}/src/sas/sim800c.o ${OBJECTDIR}/src/sas/storage.o ${OBJECTDIR}/src/sas/rmsg_blob.o ${OBJECTDIR}/src/sas/lora.o ${OBJECTDIR}/src/sas/slink.o ${OBJECTDIR}/src/sas/server.o ${OBJECTDIR}/src/sas/rtc.o ${OBJECTDIR}/src/sas/gps.o ${OBJECTDIR}/main.o
POSSIBLE_DEPFILES=${OBJECTDIR}/src/app/logic/logic.o.d ${OBJECTDIR}/src/app/logic/state.o.d ${OBJECTDIR}/src/app/net/cellular.o.d ${OBJECTDIR}/src/app/net/serial.o.d ${OBJECTDIR}/src/app/net/radio.o.d ${OBJECTDIR}/src/app/out/power_ctrl.o.d ${OBJECTDIR}/src/app/sem/chronos.o.d ${OBJECTDIR}/src/app/sem/sem_objects.o.d ${OBJECTDIR}/src/app/sem/semaphore.o.d ${OBJECTDIR}/src/cfg/app_config.o.d ${OBJECTDIR}/src/cfg/hw_config.o.d ${OBJECTDIR}/src/drv/pcf2129t.o.d ${OBJECTDIR}/src/drv/rfm95.o.d ${OBJECTDIR}/src/hal/can/CANConfiguration.o.d ${OBJECTDIR}/src/hal/can/CANErrorFunctions.o.d ${OBJECTDIR}/src/hal/can/CANEventFunctions.o.d ${OBJECTDIR}/src/hal/can/CANFilterFunctions.o.d ${OBJECTDIR}/src/hal/can/CANInfoFunctions.o.d ${OBJECTDIR}/src/hal/can/CANReceiveFunctions.o.d ${OBJECTDIR}/src/hal/can/CANTransmitFunctions.o.d ${OBJECTDIR}/src/hal/pin32.o.d ${OBJECTDIR}/src/hal/uart32mx.o.d ${OBJECTDIR}/src/lib/aes.o.d ${OBJECTDIR}/src/lib/datetime.o.d ${OBJECTDIR}/src/lib/utils.o.d ${OBJECTDIR}/src/lib/shared_buff.o.d ${OBJECTDIR}/src/lib/jparsing.o.d ${OBJECTDIR}/src/lib/jsmn.o.d ${OBJECTDIR}/mcc_generated_files/spi3.o.d ${OBJECTDIR}/mcc_generated_files/uart3.o.d ${OBJECTDIR}/mcc_generated_files/interrupt_manager.o.d ${OBJECTDIR}/mcc_generated_files/mcc.o.d ${OBJECTDIR}/mcc_generated_files/uart1.o.d ${OBJECTDIR}/mcc_generated_files/pin_manager.o.d ${OBJECTDIR}/mcc_generated_files/uart2.o.d ${OBJECTDIR}/mcc_generated_files/tmr1.o.d ${OBJECTDIR}/mcc_generated_files/uart4.o.d ${OBJECTDIR}/mcc_generated_files/uart5.o.d ${OBJECTDIR}/mcc_generated_files/tmr2.o.d ${OBJECTDIR}/src/sal/buttons.o.d ${OBJECTDIR}/src/sal/pulse.o.d ${OBJECTDIR}/src/sal/timer.o.d ${OBJECTDIR}/src/sal/debug.o.d ${OBJECTDIR}/src/sas/canbus.o.d ${OBJECTDIR}/src/sas/atdrv.o.d ${OBJECTDIR}/src/sas/sim800c.o.d ${OBJECTDIR}/src/sas/storage.o.d ${OBJECTDIR}/src/sas/rmsg_blob.o.d ${OBJECTDIR}/src/sas/lora.o.d ${OBJECTDIR}/src/sas/slink.o.d ${OBJECTDIR}/src/sas/server.o.d ${OBJECTDIR}/src/sas/rtc.o.d ${OBJECTDIR}/src/sas/gps.o.d ${OBJECTDIR}/main.o.d

# Object Files
OBJECTFILES=${OBJECTDIR}/src/app/logic/logic.o ${OBJECTDIR}/src/app/logic/state.o ${OBJECTDIR}/src/app/net/cellular.o ${OBJECTDIR}/src/app/net/serial.o ${OBJECTDIR}/src/app/net/radio.o ${OBJECTDIR}/src/app/out/power_ctrl.o ${OBJECTDIR}/src/app/sem/chronos.o ${OBJECTDIR}/src/app/sem/sem_objects.o ${OBJECTDIR}/src/app/sem/semaphore.o ${OBJECTDIR}/src/cfg/app_config.o ${OBJECTDIR}/src/cfg/hw_config.o ${OBJECTDIR}/src/drv/pcf2129t.o ${OBJECTDIR}/src/drv/rfm95.o ${OBJECTDIR}/src/hal/can/CANConfiguration.o ${OBJECTDIR}/src/hal/can/CANErrorFunctions.o ${OBJECTDIR}/src/hal/can/CANEventFunctions.o ${OBJECTDIR}/src/hal/can/CANFilterFunctions.o ${OBJECTDIR}/src/hal/can/CANInfoFunctions.o ${OBJECTDIR}/src/hal/can/CANReceiveFunctions.o ${OBJECTDIR}/src/hal/can/CANTransmitFunctions.o ${OBJECTDIR}/src/hal/pin32.o ${OBJECTDIR}/src/hal/uart32mx.o ${OBJECTDIR}/src/lib/aes.o ${OBJECTDIR}/src/lib/datetime.o ${OBJECTDIR}/src/lib/utils.o ${OBJECTDIR}/src/lib/shared_buff.o ${OBJECTDIR}/src/lib/jparsing.o ${OBJECTDIR}/src/lib/jsmn.o ${OBJECTDIR}/mcc_generated_files/spi3.o ${OBJECTDIR}/mcc_generated_files/uart3.o ${OBJECTDIR}/mcc_generated_files/interrupt_manager.o ${OBJECTDIR}/mcc_generated_files/mcc.o ${OBJECTDIR}/mcc_generated_files/uart1.o ${OBJECTDIR}/mcc_generated_files/pin_manager.o ${OBJECTDIR}/mcc_generated_files/uart2.o ${OBJECTDIR}/mcc_generated_files/tmr1.o ${OBJECTDIR}/mcc_generated_files/uart4.o ${OBJECTDIR}/mcc_generated_files/uart5.o ${OBJECTDIR}/mcc_generated_files/tmr2.o ${OBJECTDIR}/src/sal/buttons.o ${OBJECTDIR}/src/sal/pulse.o ${OBJECTDIR}/src/sal/timer.o ${OBJECTDIR}/src/sal/debug.o ${OBJECTDIR}/src/sas/canbus.o ${OBJECTDIR}/src/sas/atdrv.o ${OBJECTDIR}/src/sas/sim800c.o ${OBJECTDIR}/src/sas/storage.o ${OBJECTDIR}/src/sas/rmsg_blob.o ${OBJECTDIR}/src/sas/lora.o ${OBJECTDIR}/src/sas/slink.o ${OBJECTDIR}/src/sas/server.o ${OBJECTDIR}/src/sas/rtc.o ${OBJECTDIR}/src/sas/gps.o ${OBJECTDIR}/main.o

# Source Files
SOURCEFILES=src/app/logic/logic.c src/app/logic/state.c src/app/net/cellular.c src/app/net/serial.c src/app/net/radio.c src/app/out/power_ctrl.c src/app/sem/chronos.c src/app/sem/sem_objects.c src/app/sem/semaphore.c src/cfg/app_config.c src/cfg/hw_config.c src/drv/pcf2129t.c src/drv/rfm95.c src/hal/can/CANConfiguration.c src/hal/can/CANErrorFunctions.c src/hal/can/CANEventFunctions.c src/hal/can/CANFilterFunctions.c src/hal/can/CANInfoFunctions.c src/hal/can/CANReceiveFunctions.c src/hal/can/CANTransmitFunctions.c src/hal/pin32.c src/hal/uart32mx.c src/lib/aes.c src/lib/datetime.c src/lib/utils.c src/lib/shared_buff.c src/lib/jparsing.c src/lib/jsmn.c mcc_generated_files/spi3.c mcc_generated_files/uart3.c mcc_generated_files/interrupt_manager.c mcc_generated_files/mcc.c mcc_generated_files/uart1.c mcc_generated_files/pin_manager.c mcc_generated_files/uart2.c mcc_generated_files/tmr1.c mcc_generated_files/uart4.c mcc_generated_files/uart5.c mcc_generated_files/tmr2.c src/sal/buttons.c src/sal/pulse.c src/sal/timer.c src/sal/debug.c src/sas/canbus.c src/sas/atdrv.c src/sas/sim800c.c src/sas/storage.c src/sas/rmsg_blob.c src/sas/lora.c src/sas/slink.c src/sas/server.c src/sas/rtc.c src/sas/gps.c main.c



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
${OBJECTDIR}/src/app/logic/logic.o: src/app/logic/logic.c  .generated_files/c4ea5ba6a0b5ba0385923528a791c736d864b94c.flag .generated_files/8bac4a0766d39c6687560ebfeb650ad7e1a6910e.flag
	@${MKDIR} "${OBJECTDIR}/src/app/logic" 
	@${RM} ${OBJECTDIR}/src/app/logic/logic.o.d 
	@${RM} ${OBJECTDIR}/src/app/logic/logic.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"src" -I"." -O2 -D_SUPPRESS_PLIB_WARNING -I"C:/Program Files (x86)/Microchip/xc32/v2.15/pic32-libs" -MP -MMD -MF "${OBJECTDIR}/src/app/logic/logic.o.d" -o ${OBJECTDIR}/src/app/logic/logic.o src/app/logic/logic.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/src/app/logic/state.o: src/app/logic/state.c  .generated_files/6a131df50cae7ee7e2ca197014f416a174309421.flag .generated_files/8bac4a0766d39c6687560ebfeb650ad7e1a6910e.flag
	@${MKDIR} "${OBJECTDIR}/src/app/logic" 
	@${RM} ${OBJECTDIR}/src/app/logic/state.o.d 
	@${RM} ${OBJECTDIR}/src/app/logic/state.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"src" -I"." -O2 -D_SUPPRESS_PLIB_WARNING -I"C:/Program Files (x86)/Microchip/xc32/v2.15/pic32-libs" -MP -MMD -MF "${OBJECTDIR}/src/app/logic/state.o.d" -o ${OBJECTDIR}/src/app/logic/state.o src/app/logic/state.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/src/app/net/cellular.o: src/app/net/cellular.c  .generated_files/544b6930f8577577344a8c0ff5b0db159095a352.flag .generated_files/8bac4a0766d39c6687560ebfeb650ad7e1a6910e.flag
	@${MKDIR} "${OBJECTDIR}/src/app/net" 
	@${RM} ${OBJECTDIR}/src/app/net/cellular.o.d 
	@${RM} ${OBJECTDIR}/src/app/net/cellular.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"src" -I"." -O2 -D_SUPPRESS_PLIB_WARNING -I"C:/Program Files (x86)/Microchip/xc32/v2.15/pic32-libs" -MP -MMD -MF "${OBJECTDIR}/src/app/net/cellular.o.d" -o ${OBJECTDIR}/src/app/net/cellular.o src/app/net/cellular.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/src/app/net/serial.o: src/app/net/serial.c  .generated_files/bfc3f94045840c09631c856befe28e672c86c9c7.flag .generated_files/8bac4a0766d39c6687560ebfeb650ad7e1a6910e.flag
	@${MKDIR} "${OBJECTDIR}/src/app/net" 
	@${RM} ${OBJECTDIR}/src/app/net/serial.o.d 
	@${RM} ${OBJECTDIR}/src/app/net/serial.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"src" -I"." -O2 -D_SUPPRESS_PLIB_WARNING -I"C:/Program Files (x86)/Microchip/xc32/v2.15/pic32-libs" -MP -MMD -MF "${OBJECTDIR}/src/app/net/serial.o.d" -o ${OBJECTDIR}/src/app/net/serial.o src/app/net/serial.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/src/app/net/radio.o: src/app/net/radio.c  .generated_files/ef1137a9f7708a1180d96deda596b82fddead3b9.flag .generated_files/8bac4a0766d39c6687560ebfeb650ad7e1a6910e.flag
	@${MKDIR} "${OBJECTDIR}/src/app/net" 
	@${RM} ${OBJECTDIR}/src/app/net/radio.o.d 
	@${RM} ${OBJECTDIR}/src/app/net/radio.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"src" -I"." -O2 -D_SUPPRESS_PLIB_WARNING -I"C:/Program Files (x86)/Microchip/xc32/v2.15/pic32-libs" -MP -MMD -MF "${OBJECTDIR}/src/app/net/radio.o.d" -o ${OBJECTDIR}/src/app/net/radio.o src/app/net/radio.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/src/app/out/power_ctrl.o: src/app/out/power_ctrl.c  .generated_files/8f5a670490ea92d8ea174899c48ea9119aec6d68.flag .generated_files/8bac4a0766d39c6687560ebfeb650ad7e1a6910e.flag
	@${MKDIR} "${OBJECTDIR}/src/app/out" 
	@${RM} ${OBJECTDIR}/src/app/out/power_ctrl.o.d 
	@${RM} ${OBJECTDIR}/src/app/out/power_ctrl.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"src" -I"." -O2 -D_SUPPRESS_PLIB_WARNING -I"C:/Program Files (x86)/Microchip/xc32/v2.15/pic32-libs" -MP -MMD -MF "${OBJECTDIR}/src/app/out/power_ctrl.o.d" -o ${OBJECTDIR}/src/app/out/power_ctrl.o src/app/out/power_ctrl.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/src/app/sem/chronos.o: src/app/sem/chronos.c  .generated_files/7d215c10b2a3ea2155498fc744d19abeff54b4f.flag .generated_files/8bac4a0766d39c6687560ebfeb650ad7e1a6910e.flag
	@${MKDIR} "${OBJECTDIR}/src/app/sem" 
	@${RM} ${OBJECTDIR}/src/app/sem/chronos.o.d 
	@${RM} ${OBJECTDIR}/src/app/sem/chronos.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"src" -I"." -O2 -D_SUPPRESS_PLIB_WARNING -I"C:/Program Files (x86)/Microchip/xc32/v2.15/pic32-libs" -MP -MMD -MF "${OBJECTDIR}/src/app/sem/chronos.o.d" -o ${OBJECTDIR}/src/app/sem/chronos.o src/app/sem/chronos.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/src/app/sem/sem_objects.o: src/app/sem/sem_objects.c  .generated_files/2b9def84fc5aae3c8f0889c020a96db619757a33.flag .generated_files/8bac4a0766d39c6687560ebfeb650ad7e1a6910e.flag
	@${MKDIR} "${OBJECTDIR}/src/app/sem" 
	@${RM} ${OBJECTDIR}/src/app/sem/sem_objects.o.d 
	@${RM} ${OBJECTDIR}/src/app/sem/sem_objects.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"src" -I"." -O2 -D_SUPPRESS_PLIB_WARNING -I"C:/Program Files (x86)/Microchip/xc32/v2.15/pic32-libs" -MP -MMD -MF "${OBJECTDIR}/src/app/sem/sem_objects.o.d" -o ${OBJECTDIR}/src/app/sem/sem_objects.o src/app/sem/sem_objects.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/src/app/sem/semaphore.o: src/app/sem/semaphore.c  .generated_files/ef5f37dde56ddeca7665d26e49056e76cf6d0c99.flag .generated_files/8bac4a0766d39c6687560ebfeb650ad7e1a6910e.flag
	@${MKDIR} "${OBJECTDIR}/src/app/sem" 
	@${RM} ${OBJECTDIR}/src/app/sem/semaphore.o.d 
	@${RM} ${OBJECTDIR}/src/app/sem/semaphore.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"src" -I"." -O2 -D_SUPPRESS_PLIB_WARNING -I"C:/Program Files (x86)/Microchip/xc32/v2.15/pic32-libs" -MP -MMD -MF "${OBJECTDIR}/src/app/sem/semaphore.o.d" -o ${OBJECTDIR}/src/app/sem/semaphore.o src/app/sem/semaphore.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/src/cfg/app_config.o: src/cfg/app_config.c  .generated_files/bcccd6cb02abe85ef9235b09bd8d27232c042585.flag .generated_files/8bac4a0766d39c6687560ebfeb650ad7e1a6910e.flag
	@${MKDIR} "${OBJECTDIR}/src/cfg" 
	@${RM} ${OBJECTDIR}/src/cfg/app_config.o.d 
	@${RM} ${OBJECTDIR}/src/cfg/app_config.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"src" -I"." -O2 -D_SUPPRESS_PLIB_WARNING -I"C:/Program Files (x86)/Microchip/xc32/v2.15/pic32-libs" -MP -MMD -MF "${OBJECTDIR}/src/cfg/app_config.o.d" -o ${OBJECTDIR}/src/cfg/app_config.o src/cfg/app_config.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/src/cfg/hw_config.o: src/cfg/hw_config.c  .generated_files/9994b96ce4ef70875d3885c58c41e992b5625590.flag .generated_files/8bac4a0766d39c6687560ebfeb650ad7e1a6910e.flag
	@${MKDIR} "${OBJECTDIR}/src/cfg" 
	@${RM} ${OBJECTDIR}/src/cfg/hw_config.o.d 
	@${RM} ${OBJECTDIR}/src/cfg/hw_config.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"src" -I"." -O2 -D_SUPPRESS_PLIB_WARNING -I"C:/Program Files (x86)/Microchip/xc32/v2.15/pic32-libs" -MP -MMD -MF "${OBJECTDIR}/src/cfg/hw_config.o.d" -o ${OBJECTDIR}/src/cfg/hw_config.o src/cfg/hw_config.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/src/drv/pcf2129t.o: src/drv/pcf2129t.c  .generated_files/b81b8516d74e5a712a650689554c7fd11e6a3794.flag .generated_files/8bac4a0766d39c6687560ebfeb650ad7e1a6910e.flag
	@${MKDIR} "${OBJECTDIR}/src/drv" 
	@${RM} ${OBJECTDIR}/src/drv/pcf2129t.o.d 
	@${RM} ${OBJECTDIR}/src/drv/pcf2129t.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"src" -I"." -O2 -D_SUPPRESS_PLIB_WARNING -I"C:/Program Files (x86)/Microchip/xc32/v2.15/pic32-libs" -MP -MMD -MF "${OBJECTDIR}/src/drv/pcf2129t.o.d" -o ${OBJECTDIR}/src/drv/pcf2129t.o src/drv/pcf2129t.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/src/drv/rfm95.o: src/drv/rfm95.c  .generated_files/1fce4b337d2ee89c2ed18ce28fa95b0524bd58b2.flag .generated_files/8bac4a0766d39c6687560ebfeb650ad7e1a6910e.flag
	@${MKDIR} "${OBJECTDIR}/src/drv" 
	@${RM} ${OBJECTDIR}/src/drv/rfm95.o.d 
	@${RM} ${OBJECTDIR}/src/drv/rfm95.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"src" -I"." -O2 -D_SUPPRESS_PLIB_WARNING -I"C:/Program Files (x86)/Microchip/xc32/v2.15/pic32-libs" -MP -MMD -MF "${OBJECTDIR}/src/drv/rfm95.o.d" -o ${OBJECTDIR}/src/drv/rfm95.o src/drv/rfm95.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/src/hal/can/CANConfiguration.o: src/hal/can/CANConfiguration.c  .generated_files/4aeade204643de4a5bb20058037f2b30cc7caac5.flag .generated_files/8bac4a0766d39c6687560ebfeb650ad7e1a6910e.flag
	@${MKDIR} "${OBJECTDIR}/src/hal/can" 
	@${RM} ${OBJECTDIR}/src/hal/can/CANConfiguration.o.d 
	@${RM} ${OBJECTDIR}/src/hal/can/CANConfiguration.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"src" -I"." -O2 -D_SUPPRESS_PLIB_WARNING -I"C:/Program Files (x86)/Microchip/xc32/v2.15/pic32-libs" -MP -MMD -MF "${OBJECTDIR}/src/hal/can/CANConfiguration.o.d" -o ${OBJECTDIR}/src/hal/can/CANConfiguration.o src/hal/can/CANConfiguration.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/src/hal/can/CANErrorFunctions.o: src/hal/can/CANErrorFunctions.c  .generated_files/7f2b3c5bd291c92cc88b6ebda6a2e30883c2b4fd.flag .generated_files/8bac4a0766d39c6687560ebfeb650ad7e1a6910e.flag
	@${MKDIR} "${OBJECTDIR}/src/hal/can" 
	@${RM} ${OBJECTDIR}/src/hal/can/CANErrorFunctions.o.d 
	@${RM} ${OBJECTDIR}/src/hal/can/CANErrorFunctions.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"src" -I"." -O2 -D_SUPPRESS_PLIB_WARNING -I"C:/Program Files (x86)/Microchip/xc32/v2.15/pic32-libs" -MP -MMD -MF "${OBJECTDIR}/src/hal/can/CANErrorFunctions.o.d" -o ${OBJECTDIR}/src/hal/can/CANErrorFunctions.o src/hal/can/CANErrorFunctions.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/src/hal/can/CANEventFunctions.o: src/hal/can/CANEventFunctions.c  .generated_files/718280c1b5638494f15a437ad30c56f14fa42ffc.flag .generated_files/8bac4a0766d39c6687560ebfeb650ad7e1a6910e.flag
	@${MKDIR} "${OBJECTDIR}/src/hal/can" 
	@${RM} ${OBJECTDIR}/src/hal/can/CANEventFunctions.o.d 
	@${RM} ${OBJECTDIR}/src/hal/can/CANEventFunctions.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"src" -I"." -O2 -D_SUPPRESS_PLIB_WARNING -I"C:/Program Files (x86)/Microchip/xc32/v2.15/pic32-libs" -MP -MMD -MF "${OBJECTDIR}/src/hal/can/CANEventFunctions.o.d" -o ${OBJECTDIR}/src/hal/can/CANEventFunctions.o src/hal/can/CANEventFunctions.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/src/hal/can/CANFilterFunctions.o: src/hal/can/CANFilterFunctions.c  .generated_files/7c177c1b3f50f969ce736bb7019af97981f4bb37.flag .generated_files/8bac4a0766d39c6687560ebfeb650ad7e1a6910e.flag
	@${MKDIR} "${OBJECTDIR}/src/hal/can" 
	@${RM} ${OBJECTDIR}/src/hal/can/CANFilterFunctions.o.d 
	@${RM} ${OBJECTDIR}/src/hal/can/CANFilterFunctions.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"src" -I"." -O2 -D_SUPPRESS_PLIB_WARNING -I"C:/Program Files (x86)/Microchip/xc32/v2.15/pic32-libs" -MP -MMD -MF "${OBJECTDIR}/src/hal/can/CANFilterFunctions.o.d" -o ${OBJECTDIR}/src/hal/can/CANFilterFunctions.o src/hal/can/CANFilterFunctions.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/src/hal/can/CANInfoFunctions.o: src/hal/can/CANInfoFunctions.c  .generated_files/8ad72c807ddf0e73a75ac42fe60ae92804e5cfdb.flag .generated_files/8bac4a0766d39c6687560ebfeb650ad7e1a6910e.flag
	@${MKDIR} "${OBJECTDIR}/src/hal/can" 
	@${RM} ${OBJECTDIR}/src/hal/can/CANInfoFunctions.o.d 
	@${RM} ${OBJECTDIR}/src/hal/can/CANInfoFunctions.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"src" -I"." -O2 -D_SUPPRESS_PLIB_WARNING -I"C:/Program Files (x86)/Microchip/xc32/v2.15/pic32-libs" -MP -MMD -MF "${OBJECTDIR}/src/hal/can/CANInfoFunctions.o.d" -o ${OBJECTDIR}/src/hal/can/CANInfoFunctions.o src/hal/can/CANInfoFunctions.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/src/hal/can/CANReceiveFunctions.o: src/hal/can/CANReceiveFunctions.c  .generated_files/fa5fe78ce405252e251deb9be73813988b492a37.flag .generated_files/8bac4a0766d39c6687560ebfeb650ad7e1a6910e.flag
	@${MKDIR} "${OBJECTDIR}/src/hal/can" 
	@${RM} ${OBJECTDIR}/src/hal/can/CANReceiveFunctions.o.d 
	@${RM} ${OBJECTDIR}/src/hal/can/CANReceiveFunctions.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"src" -I"." -O2 -D_SUPPRESS_PLIB_WARNING -I"C:/Program Files (x86)/Microchip/xc32/v2.15/pic32-libs" -MP -MMD -MF "${OBJECTDIR}/src/hal/can/CANReceiveFunctions.o.d" -o ${OBJECTDIR}/src/hal/can/CANReceiveFunctions.o src/hal/can/CANReceiveFunctions.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/src/hal/can/CANTransmitFunctions.o: src/hal/can/CANTransmitFunctions.c  .generated_files/7e8c93d55b5506164dd79add2279eafcd3d9bd.flag .generated_files/8bac4a0766d39c6687560ebfeb650ad7e1a6910e.flag
	@${MKDIR} "${OBJECTDIR}/src/hal/can" 
	@${RM} ${OBJECTDIR}/src/hal/can/CANTransmitFunctions.o.d 
	@${RM} ${OBJECTDIR}/src/hal/can/CANTransmitFunctions.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"src" -I"." -O2 -D_SUPPRESS_PLIB_WARNING -I"C:/Program Files (x86)/Microchip/xc32/v2.15/pic32-libs" -MP -MMD -MF "${OBJECTDIR}/src/hal/can/CANTransmitFunctions.o.d" -o ${OBJECTDIR}/src/hal/can/CANTransmitFunctions.o src/hal/can/CANTransmitFunctions.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/src/hal/pin32.o: src/hal/pin32.c  .generated_files/789be1e40a877564ff12afe332df81c7d3fe4866.flag .generated_files/8bac4a0766d39c6687560ebfeb650ad7e1a6910e.flag
	@${MKDIR} "${OBJECTDIR}/src/hal" 
	@${RM} ${OBJECTDIR}/src/hal/pin32.o.d 
	@${RM} ${OBJECTDIR}/src/hal/pin32.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"src" -I"." -O2 -D_SUPPRESS_PLIB_WARNING -I"C:/Program Files (x86)/Microchip/xc32/v2.15/pic32-libs" -MP -MMD -MF "${OBJECTDIR}/src/hal/pin32.o.d" -o ${OBJECTDIR}/src/hal/pin32.o src/hal/pin32.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/src/hal/uart32mx.o: src/hal/uart32mx.c  .generated_files/d6f6deeeaaa50854e74d68305139d463ed108472.flag .generated_files/8bac4a0766d39c6687560ebfeb650ad7e1a6910e.flag
	@${MKDIR} "${OBJECTDIR}/src/hal" 
	@${RM} ${OBJECTDIR}/src/hal/uart32mx.o.d 
	@${RM} ${OBJECTDIR}/src/hal/uart32mx.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"src" -I"." -O2 -D_SUPPRESS_PLIB_WARNING -I"C:/Program Files (x86)/Microchip/xc32/v2.15/pic32-libs" -MP -MMD -MF "${OBJECTDIR}/src/hal/uart32mx.o.d" -o ${OBJECTDIR}/src/hal/uart32mx.o src/hal/uart32mx.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/src/lib/aes.o: src/lib/aes.c  .generated_files/754dbdcd19bc97c86b1e4f4dba740ed7be7f2e05.flag .generated_files/8bac4a0766d39c6687560ebfeb650ad7e1a6910e.flag
	@${MKDIR} "${OBJECTDIR}/src/lib" 
	@${RM} ${OBJECTDIR}/src/lib/aes.o.d 
	@${RM} ${OBJECTDIR}/src/lib/aes.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"src" -I"." -O2 -D_SUPPRESS_PLIB_WARNING -I"C:/Program Files (x86)/Microchip/xc32/v2.15/pic32-libs" -MP -MMD -MF "${OBJECTDIR}/src/lib/aes.o.d" -o ${OBJECTDIR}/src/lib/aes.o src/lib/aes.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/src/lib/datetime.o: src/lib/datetime.c  .generated_files/5140a57a308c2480530b8eeabc2d14cd7668fb41.flag .generated_files/8bac4a0766d39c6687560ebfeb650ad7e1a6910e.flag
	@${MKDIR} "${OBJECTDIR}/src/lib" 
	@${RM} ${OBJECTDIR}/src/lib/datetime.o.d 
	@${RM} ${OBJECTDIR}/src/lib/datetime.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"src" -I"." -O2 -D_SUPPRESS_PLIB_WARNING -I"C:/Program Files (x86)/Microchip/xc32/v2.15/pic32-libs" -MP -MMD -MF "${OBJECTDIR}/src/lib/datetime.o.d" -o ${OBJECTDIR}/src/lib/datetime.o src/lib/datetime.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/src/lib/utils.o: src/lib/utils.c  .generated_files/6f90de24ebc376424c373546cb56dd2ed104afc1.flag .generated_files/8bac4a0766d39c6687560ebfeb650ad7e1a6910e.flag
	@${MKDIR} "${OBJECTDIR}/src/lib" 
	@${RM} ${OBJECTDIR}/src/lib/utils.o.d 
	@${RM} ${OBJECTDIR}/src/lib/utils.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"src" -I"." -O2 -D_SUPPRESS_PLIB_WARNING -I"C:/Program Files (x86)/Microchip/xc32/v2.15/pic32-libs" -MP -MMD -MF "${OBJECTDIR}/src/lib/utils.o.d" -o ${OBJECTDIR}/src/lib/utils.o src/lib/utils.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/src/lib/shared_buff.o: src/lib/shared_buff.c  .generated_files/8fe18c775753d9ac13aafe68bdb1df78f044a12e.flag .generated_files/8bac4a0766d39c6687560ebfeb650ad7e1a6910e.flag
	@${MKDIR} "${OBJECTDIR}/src/lib" 
	@${RM} ${OBJECTDIR}/src/lib/shared_buff.o.d 
	@${RM} ${OBJECTDIR}/src/lib/shared_buff.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"src" -I"." -O2 -D_SUPPRESS_PLIB_WARNING -I"C:/Program Files (x86)/Microchip/xc32/v2.15/pic32-libs" -MP -MMD -MF "${OBJECTDIR}/src/lib/shared_buff.o.d" -o ${OBJECTDIR}/src/lib/shared_buff.o src/lib/shared_buff.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/src/lib/jparsing.o: src/lib/jparsing.c  .generated_files/64c1c697958101c8cb54d012aa2671884ca461fe.flag .generated_files/8bac4a0766d39c6687560ebfeb650ad7e1a6910e.flag
	@${MKDIR} "${OBJECTDIR}/src/lib" 
	@${RM} ${OBJECTDIR}/src/lib/jparsing.o.d 
	@${RM} ${OBJECTDIR}/src/lib/jparsing.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"src" -I"." -O2 -D_SUPPRESS_PLIB_WARNING -I"C:/Program Files (x86)/Microchip/xc32/v2.15/pic32-libs" -MP -MMD -MF "${OBJECTDIR}/src/lib/jparsing.o.d" -o ${OBJECTDIR}/src/lib/jparsing.o src/lib/jparsing.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/src/lib/jsmn.o: src/lib/jsmn.c  .generated_files/b609195240375196e3fdc6f84f18a711d66ba63f.flag .generated_files/8bac4a0766d39c6687560ebfeb650ad7e1a6910e.flag
	@${MKDIR} "${OBJECTDIR}/src/lib" 
	@${RM} ${OBJECTDIR}/src/lib/jsmn.o.d 
	@${RM} ${OBJECTDIR}/src/lib/jsmn.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"src" -I"." -O2 -D_SUPPRESS_PLIB_WARNING -I"C:/Program Files (x86)/Microchip/xc32/v2.15/pic32-libs" -MP -MMD -MF "${OBJECTDIR}/src/lib/jsmn.o.d" -o ${OBJECTDIR}/src/lib/jsmn.o src/lib/jsmn.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/mcc_generated_files/spi3.o: mcc_generated_files/spi3.c  .generated_files/45d4496be3cdbba6e15a4ba8161dd4cc535a6a32.flag .generated_files/8bac4a0766d39c6687560ebfeb650ad7e1a6910e.flag
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/spi3.o.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/spi3.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"src" -I"." -O2 -D_SUPPRESS_PLIB_WARNING -I"C:/Program Files (x86)/Microchip/xc32/v2.15/pic32-libs" -MP -MMD -MF "${OBJECTDIR}/mcc_generated_files/spi3.o.d" -o ${OBJECTDIR}/mcc_generated_files/spi3.o mcc_generated_files/spi3.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/mcc_generated_files/uart3.o: mcc_generated_files/uart3.c  .generated_files/83029e496b807477c6be4206742fc502adeec11b.flag .generated_files/8bac4a0766d39c6687560ebfeb650ad7e1a6910e.flag
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/uart3.o.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/uart3.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"src" -I"." -O2 -D_SUPPRESS_PLIB_WARNING -I"C:/Program Files (x86)/Microchip/xc32/v2.15/pic32-libs" -MP -MMD -MF "${OBJECTDIR}/mcc_generated_files/uart3.o.d" -o ${OBJECTDIR}/mcc_generated_files/uart3.o mcc_generated_files/uart3.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/mcc_generated_files/interrupt_manager.o: mcc_generated_files/interrupt_manager.c  .generated_files/c3082424c7e4c90e1c6a7e04e2edbcd65798e809.flag .generated_files/8bac4a0766d39c6687560ebfeb650ad7e1a6910e.flag
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/interrupt_manager.o.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/interrupt_manager.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"src" -I"." -O2 -D_SUPPRESS_PLIB_WARNING -I"C:/Program Files (x86)/Microchip/xc32/v2.15/pic32-libs" -MP -MMD -MF "${OBJECTDIR}/mcc_generated_files/interrupt_manager.o.d" -o ${OBJECTDIR}/mcc_generated_files/interrupt_manager.o mcc_generated_files/interrupt_manager.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/mcc_generated_files/mcc.o: mcc_generated_files/mcc.c  .generated_files/aa78509eccf0ab15c9bb061c99ed5f53cd2c474a.flag .generated_files/8bac4a0766d39c6687560ebfeb650ad7e1a6910e.flag
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/mcc.o.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/mcc.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"src" -I"." -O2 -D_SUPPRESS_PLIB_WARNING -I"C:/Program Files (x86)/Microchip/xc32/v2.15/pic32-libs" -MP -MMD -MF "${OBJECTDIR}/mcc_generated_files/mcc.o.d" -o ${OBJECTDIR}/mcc_generated_files/mcc.o mcc_generated_files/mcc.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/mcc_generated_files/uart1.o: mcc_generated_files/uart1.c  .generated_files/d731ad7fd011a12b2b4153a2fd90f28e04122a86.flag .generated_files/8bac4a0766d39c6687560ebfeb650ad7e1a6910e.flag
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/uart1.o.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/uart1.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"src" -I"." -O2 -D_SUPPRESS_PLIB_WARNING -I"C:/Program Files (x86)/Microchip/xc32/v2.15/pic32-libs" -MP -MMD -MF "${OBJECTDIR}/mcc_generated_files/uart1.o.d" -o ${OBJECTDIR}/mcc_generated_files/uart1.o mcc_generated_files/uart1.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/mcc_generated_files/pin_manager.o: mcc_generated_files/pin_manager.c  .generated_files/2a4870961b7b853f70feb104e6e2511622f05e2b.flag .generated_files/8bac4a0766d39c6687560ebfeb650ad7e1a6910e.flag
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/pin_manager.o.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/pin_manager.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"src" -I"." -O2 -D_SUPPRESS_PLIB_WARNING -I"C:/Program Files (x86)/Microchip/xc32/v2.15/pic32-libs" -MP -MMD -MF "${OBJECTDIR}/mcc_generated_files/pin_manager.o.d" -o ${OBJECTDIR}/mcc_generated_files/pin_manager.o mcc_generated_files/pin_manager.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/mcc_generated_files/uart2.o: mcc_generated_files/uart2.c  .generated_files/612b335e26e61a63f83897022a5bf21b7552c461.flag .generated_files/8bac4a0766d39c6687560ebfeb650ad7e1a6910e.flag
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/uart2.o.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/uart2.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"src" -I"." -O2 -D_SUPPRESS_PLIB_WARNING -I"C:/Program Files (x86)/Microchip/xc32/v2.15/pic32-libs" -MP -MMD -MF "${OBJECTDIR}/mcc_generated_files/uart2.o.d" -o ${OBJECTDIR}/mcc_generated_files/uart2.o mcc_generated_files/uart2.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/mcc_generated_files/tmr1.o: mcc_generated_files/tmr1.c  .generated_files/e0618b8c7e251041acdf7448eaf127dbaf5117df.flag .generated_files/8bac4a0766d39c6687560ebfeb650ad7e1a6910e.flag
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/tmr1.o.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/tmr1.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"src" -I"." -O2 -D_SUPPRESS_PLIB_WARNING -I"C:/Program Files (x86)/Microchip/xc32/v2.15/pic32-libs" -MP -MMD -MF "${OBJECTDIR}/mcc_generated_files/tmr1.o.d" -o ${OBJECTDIR}/mcc_generated_files/tmr1.o mcc_generated_files/tmr1.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/mcc_generated_files/uart4.o: mcc_generated_files/uart4.c  .generated_files/d54624877fc044a040892a4dbb8d31f3ef671eaa.flag .generated_files/8bac4a0766d39c6687560ebfeb650ad7e1a6910e.flag
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/uart4.o.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/uart4.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"src" -I"." -O2 -D_SUPPRESS_PLIB_WARNING -I"C:/Program Files (x86)/Microchip/xc32/v2.15/pic32-libs" -MP -MMD -MF "${OBJECTDIR}/mcc_generated_files/uart4.o.d" -o ${OBJECTDIR}/mcc_generated_files/uart4.o mcc_generated_files/uart4.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/mcc_generated_files/uart5.o: mcc_generated_files/uart5.c  .generated_files/30f4801620a04320f099f6663dfb404189feb9b6.flag .generated_files/8bac4a0766d39c6687560ebfeb650ad7e1a6910e.flag
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/uart5.o.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/uart5.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"src" -I"." -O2 -D_SUPPRESS_PLIB_WARNING -I"C:/Program Files (x86)/Microchip/xc32/v2.15/pic32-libs" -MP -MMD -MF "${OBJECTDIR}/mcc_generated_files/uart5.o.d" -o ${OBJECTDIR}/mcc_generated_files/uart5.o mcc_generated_files/uart5.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/mcc_generated_files/tmr2.o: mcc_generated_files/tmr2.c  .generated_files/1c319098c4e539ef8b6354451021c96167e12081.flag .generated_files/8bac4a0766d39c6687560ebfeb650ad7e1a6910e.flag
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/tmr2.o.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/tmr2.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"src" -I"." -O2 -D_SUPPRESS_PLIB_WARNING -I"C:/Program Files (x86)/Microchip/xc32/v2.15/pic32-libs" -MP -MMD -MF "${OBJECTDIR}/mcc_generated_files/tmr2.o.d" -o ${OBJECTDIR}/mcc_generated_files/tmr2.o mcc_generated_files/tmr2.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/src/sal/buttons.o: src/sal/buttons.c  .generated_files/b672fb821c5a44dbfaa1e7b696e4f3df5328a6f5.flag .generated_files/8bac4a0766d39c6687560ebfeb650ad7e1a6910e.flag
	@${MKDIR} "${OBJECTDIR}/src/sal" 
	@${RM} ${OBJECTDIR}/src/sal/buttons.o.d 
	@${RM} ${OBJECTDIR}/src/sal/buttons.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"src" -I"." -O2 -D_SUPPRESS_PLIB_WARNING -I"C:/Program Files (x86)/Microchip/xc32/v2.15/pic32-libs" -MP -MMD -MF "${OBJECTDIR}/src/sal/buttons.o.d" -o ${OBJECTDIR}/src/sal/buttons.o src/sal/buttons.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/src/sal/pulse.o: src/sal/pulse.c  .generated_files/febd4282906ad85becb7a4522e8ebc330acb1ed9.flag .generated_files/8bac4a0766d39c6687560ebfeb650ad7e1a6910e.flag
	@${MKDIR} "${OBJECTDIR}/src/sal" 
	@${RM} ${OBJECTDIR}/src/sal/pulse.o.d 
	@${RM} ${OBJECTDIR}/src/sal/pulse.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"src" -I"." -O2 -D_SUPPRESS_PLIB_WARNING -I"C:/Program Files (x86)/Microchip/xc32/v2.15/pic32-libs" -MP -MMD -MF "${OBJECTDIR}/src/sal/pulse.o.d" -o ${OBJECTDIR}/src/sal/pulse.o src/sal/pulse.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/src/sal/timer.o: src/sal/timer.c  .generated_files/1953c7ab653cbc8eab235f5c57d4ad5e0815a627.flag .generated_files/8bac4a0766d39c6687560ebfeb650ad7e1a6910e.flag
	@${MKDIR} "${OBJECTDIR}/src/sal" 
	@${RM} ${OBJECTDIR}/src/sal/timer.o.d 
	@${RM} ${OBJECTDIR}/src/sal/timer.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"src" -I"." -O2 -D_SUPPRESS_PLIB_WARNING -I"C:/Program Files (x86)/Microchip/xc32/v2.15/pic32-libs" -MP -MMD -MF "${OBJECTDIR}/src/sal/timer.o.d" -o ${OBJECTDIR}/src/sal/timer.o src/sal/timer.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/src/sal/debug.o: src/sal/debug.c  .generated_files/9628cb4b8a05b6e385b0d0b9cea8f116f5c40e80.flag .generated_files/8bac4a0766d39c6687560ebfeb650ad7e1a6910e.flag
	@${MKDIR} "${OBJECTDIR}/src/sal" 
	@${RM} ${OBJECTDIR}/src/sal/debug.o.d 
	@${RM} ${OBJECTDIR}/src/sal/debug.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"src" -I"." -O2 -D_SUPPRESS_PLIB_WARNING -I"C:/Program Files (x86)/Microchip/xc32/v2.15/pic32-libs" -MP -MMD -MF "${OBJECTDIR}/src/sal/debug.o.d" -o ${OBJECTDIR}/src/sal/debug.o src/sal/debug.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/src/sas/canbus.o: src/sas/canbus.c  .generated_files/677f54fc480a19e3b35f2910ca61e5558b26e74a.flag .generated_files/8bac4a0766d39c6687560ebfeb650ad7e1a6910e.flag
	@${MKDIR} "${OBJECTDIR}/src/sas" 
	@${RM} ${OBJECTDIR}/src/sas/canbus.o.d 
	@${RM} ${OBJECTDIR}/src/sas/canbus.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"src" -I"." -O2 -D_SUPPRESS_PLIB_WARNING -I"C:/Program Files (x86)/Microchip/xc32/v2.15/pic32-libs" -MP -MMD -MF "${OBJECTDIR}/src/sas/canbus.o.d" -o ${OBJECTDIR}/src/sas/canbus.o src/sas/canbus.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/src/sas/atdrv.o: src/sas/atdrv.c  .generated_files/8d98717b377f73822d3f5864552992b3e68f9d83.flag .generated_files/8bac4a0766d39c6687560ebfeb650ad7e1a6910e.flag
	@${MKDIR} "${OBJECTDIR}/src/sas" 
	@${RM} ${OBJECTDIR}/src/sas/atdrv.o.d 
	@${RM} ${OBJECTDIR}/src/sas/atdrv.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"src" -I"." -O2 -D_SUPPRESS_PLIB_WARNING -I"C:/Program Files (x86)/Microchip/xc32/v2.15/pic32-libs" -MP -MMD -MF "${OBJECTDIR}/src/sas/atdrv.o.d" -o ${OBJECTDIR}/src/sas/atdrv.o src/sas/atdrv.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/src/sas/sim800c.o: src/sas/sim800c.c  .generated_files/fdb8c2f1521a734d98ca49930b6f8701ecad14fd.flag .generated_files/8bac4a0766d39c6687560ebfeb650ad7e1a6910e.flag
	@${MKDIR} "${OBJECTDIR}/src/sas" 
	@${RM} ${OBJECTDIR}/src/sas/sim800c.o.d 
	@${RM} ${OBJECTDIR}/src/sas/sim800c.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"src" -I"." -O2 -D_SUPPRESS_PLIB_WARNING -I"C:/Program Files (x86)/Microchip/xc32/v2.15/pic32-libs" -MP -MMD -MF "${OBJECTDIR}/src/sas/sim800c.o.d" -o ${OBJECTDIR}/src/sas/sim800c.o src/sas/sim800c.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/src/sas/storage.o: src/sas/storage.c  .generated_files/342dfec160eed2019aab1bd6dd6af4b9b0105556.flag .generated_files/8bac4a0766d39c6687560ebfeb650ad7e1a6910e.flag
	@${MKDIR} "${OBJECTDIR}/src/sas" 
	@${RM} ${OBJECTDIR}/src/sas/storage.o.d 
	@${RM} ${OBJECTDIR}/src/sas/storage.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"src" -I"." -O2 -D_SUPPRESS_PLIB_WARNING -I"C:/Program Files (x86)/Microchip/xc32/v2.15/pic32-libs" -MP -MMD -MF "${OBJECTDIR}/src/sas/storage.o.d" -o ${OBJECTDIR}/src/sas/storage.o src/sas/storage.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/src/sas/rmsg_blob.o: src/sas/rmsg_blob.c  .generated_files/cd581e6e8ed198025f5b193d591d8a939ba53f0b.flag .generated_files/8bac4a0766d39c6687560ebfeb650ad7e1a6910e.flag
	@${MKDIR} "${OBJECTDIR}/src/sas" 
	@${RM} ${OBJECTDIR}/src/sas/rmsg_blob.o.d 
	@${RM} ${OBJECTDIR}/src/sas/rmsg_blob.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"src" -I"." -O2 -D_SUPPRESS_PLIB_WARNING -I"C:/Program Files (x86)/Microchip/xc32/v2.15/pic32-libs" -MP -MMD -MF "${OBJECTDIR}/src/sas/rmsg_blob.o.d" -o ${OBJECTDIR}/src/sas/rmsg_blob.o src/sas/rmsg_blob.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/src/sas/lora.o: src/sas/lora.c  .generated_files/afa93f58d2e33b2c32512b3f860c46bca5e587e6.flag .generated_files/8bac4a0766d39c6687560ebfeb650ad7e1a6910e.flag
	@${MKDIR} "${OBJECTDIR}/src/sas" 
	@${RM} ${OBJECTDIR}/src/sas/lora.o.d 
	@${RM} ${OBJECTDIR}/src/sas/lora.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"src" -I"." -O2 -D_SUPPRESS_PLIB_WARNING -I"C:/Program Files (x86)/Microchip/xc32/v2.15/pic32-libs" -MP -MMD -MF "${OBJECTDIR}/src/sas/lora.o.d" -o ${OBJECTDIR}/src/sas/lora.o src/sas/lora.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/src/sas/slink.o: src/sas/slink.c  .generated_files/2451099fb0361a109164b30c64886817515adaf6.flag .generated_files/8bac4a0766d39c6687560ebfeb650ad7e1a6910e.flag
	@${MKDIR} "${OBJECTDIR}/src/sas" 
	@${RM} ${OBJECTDIR}/src/sas/slink.o.d 
	@${RM} ${OBJECTDIR}/src/sas/slink.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"src" -I"." -O2 -D_SUPPRESS_PLIB_WARNING -I"C:/Program Files (x86)/Microchip/xc32/v2.15/pic32-libs" -MP -MMD -MF "${OBJECTDIR}/src/sas/slink.o.d" -o ${OBJECTDIR}/src/sas/slink.o src/sas/slink.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/src/sas/server.o: src/sas/server.c  .generated_files/2051cad6f91002fb269ab1e315fafd331e1e6ffc.flag .generated_files/8bac4a0766d39c6687560ebfeb650ad7e1a6910e.flag
	@${MKDIR} "${OBJECTDIR}/src/sas" 
	@${RM} ${OBJECTDIR}/src/sas/server.o.d 
	@${RM} ${OBJECTDIR}/src/sas/server.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"src" -I"." -O2 -D_SUPPRESS_PLIB_WARNING -I"C:/Program Files (x86)/Microchip/xc32/v2.15/pic32-libs" -MP -MMD -MF "${OBJECTDIR}/src/sas/server.o.d" -o ${OBJECTDIR}/src/sas/server.o src/sas/server.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/src/sas/rtc.o: src/sas/rtc.c  .generated_files/cc38f6b09c03e3a7eadfd53e6238cbadf3153ca8.flag .generated_files/8bac4a0766d39c6687560ebfeb650ad7e1a6910e.flag
	@${MKDIR} "${OBJECTDIR}/src/sas" 
	@${RM} ${OBJECTDIR}/src/sas/rtc.o.d 
	@${RM} ${OBJECTDIR}/src/sas/rtc.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"src" -I"." -O2 -D_SUPPRESS_PLIB_WARNING -I"C:/Program Files (x86)/Microchip/xc32/v2.15/pic32-libs" -MP -MMD -MF "${OBJECTDIR}/src/sas/rtc.o.d" -o ${OBJECTDIR}/src/sas/rtc.o src/sas/rtc.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/src/sas/gps.o: src/sas/gps.c  .generated_files/2285eca3b0fdbd3ce8850fd4f76a3022d4c9e8f7.flag .generated_files/8bac4a0766d39c6687560ebfeb650ad7e1a6910e.flag
	@${MKDIR} "${OBJECTDIR}/src/sas" 
	@${RM} ${OBJECTDIR}/src/sas/gps.o.d 
	@${RM} ${OBJECTDIR}/src/sas/gps.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"src" -I"." -O2 -D_SUPPRESS_PLIB_WARNING -I"C:/Program Files (x86)/Microchip/xc32/v2.15/pic32-libs" -MP -MMD -MF "${OBJECTDIR}/src/sas/gps.o.d" -o ${OBJECTDIR}/src/sas/gps.o src/sas/gps.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/main.o: main.c  .generated_files/68b487aa56025b86821a0800079b9c336c409476.flag .generated_files/8bac4a0766d39c6687560ebfeb650ad7e1a6910e.flag
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/main.o.d 
	@${RM} ${OBJECTDIR}/main.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"src" -I"." -O2 -D_SUPPRESS_PLIB_WARNING -I"C:/Program Files (x86)/Microchip/xc32/v2.15/pic32-libs" -MP -MMD -MF "${OBJECTDIR}/main.o.d" -o ${OBJECTDIR}/main.o main.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	
else
${OBJECTDIR}/src/app/logic/logic.o: src/app/logic/logic.c  .generated_files/ad3f499695ee949ac4274250c830812071b3d69.flag .generated_files/8bac4a0766d39c6687560ebfeb650ad7e1a6910e.flag
	@${MKDIR} "${OBJECTDIR}/src/app/logic" 
	@${RM} ${OBJECTDIR}/src/app/logic/logic.o.d 
	@${RM} ${OBJECTDIR}/src/app/logic/logic.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"src" -I"." -O2 -D_SUPPRESS_PLIB_WARNING -I"C:/Program Files (x86)/Microchip/xc32/v2.15/pic32-libs" -MP -MMD -MF "${OBJECTDIR}/src/app/logic/logic.o.d" -o ${OBJECTDIR}/src/app/logic/logic.o src/app/logic/logic.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/src/app/logic/state.o: src/app/logic/state.c  .generated_files/34700c857bc4d2a1ddb79d236ce4e03738452549.flag .generated_files/8bac4a0766d39c6687560ebfeb650ad7e1a6910e.flag
	@${MKDIR} "${OBJECTDIR}/src/app/logic" 
	@${RM} ${OBJECTDIR}/src/app/logic/state.o.d 
	@${RM} ${OBJECTDIR}/src/app/logic/state.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"src" -I"." -O2 -D_SUPPRESS_PLIB_WARNING -I"C:/Program Files (x86)/Microchip/xc32/v2.15/pic32-libs" -MP -MMD -MF "${OBJECTDIR}/src/app/logic/state.o.d" -o ${OBJECTDIR}/src/app/logic/state.o src/app/logic/state.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/src/app/net/cellular.o: src/app/net/cellular.c  .generated_files/545b4218e68a18412977912d3b390e4c55fed4f3.flag .generated_files/8bac4a0766d39c6687560ebfeb650ad7e1a6910e.flag
	@${MKDIR} "${OBJECTDIR}/src/app/net" 
	@${RM} ${OBJECTDIR}/src/app/net/cellular.o.d 
	@${RM} ${OBJECTDIR}/src/app/net/cellular.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"src" -I"." -O2 -D_SUPPRESS_PLIB_WARNING -I"C:/Program Files (x86)/Microchip/xc32/v2.15/pic32-libs" -MP -MMD -MF "${OBJECTDIR}/src/app/net/cellular.o.d" -o ${OBJECTDIR}/src/app/net/cellular.o src/app/net/cellular.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/src/app/net/serial.o: src/app/net/serial.c  .generated_files/33211cd2f93a1a5712d7df8544cb095f38595bcc.flag .generated_files/8bac4a0766d39c6687560ebfeb650ad7e1a6910e.flag
	@${MKDIR} "${OBJECTDIR}/src/app/net" 
	@${RM} ${OBJECTDIR}/src/app/net/serial.o.d 
	@${RM} ${OBJECTDIR}/src/app/net/serial.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"src" -I"." -O2 -D_SUPPRESS_PLIB_WARNING -I"C:/Program Files (x86)/Microchip/xc32/v2.15/pic32-libs" -MP -MMD -MF "${OBJECTDIR}/src/app/net/serial.o.d" -o ${OBJECTDIR}/src/app/net/serial.o src/app/net/serial.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/src/app/net/radio.o: src/app/net/radio.c  .generated_files/2d84c68acbf275fa351e7630f9f2ffad341e311d.flag .generated_files/8bac4a0766d39c6687560ebfeb650ad7e1a6910e.flag
	@${MKDIR} "${OBJECTDIR}/src/app/net" 
	@${RM} ${OBJECTDIR}/src/app/net/radio.o.d 
	@${RM} ${OBJECTDIR}/src/app/net/radio.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"src" -I"." -O2 -D_SUPPRESS_PLIB_WARNING -I"C:/Program Files (x86)/Microchip/xc32/v2.15/pic32-libs" -MP -MMD -MF "${OBJECTDIR}/src/app/net/radio.o.d" -o ${OBJECTDIR}/src/app/net/radio.o src/app/net/radio.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/src/app/out/power_ctrl.o: src/app/out/power_ctrl.c  .generated_files/d713c4299173947357b96ba932cd2b37d91c4f0c.flag .generated_files/8bac4a0766d39c6687560ebfeb650ad7e1a6910e.flag
	@${MKDIR} "${OBJECTDIR}/src/app/out" 
	@${RM} ${OBJECTDIR}/src/app/out/power_ctrl.o.d 
	@${RM} ${OBJECTDIR}/src/app/out/power_ctrl.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"src" -I"." -O2 -D_SUPPRESS_PLIB_WARNING -I"C:/Program Files (x86)/Microchip/xc32/v2.15/pic32-libs" -MP -MMD -MF "${OBJECTDIR}/src/app/out/power_ctrl.o.d" -o ${OBJECTDIR}/src/app/out/power_ctrl.o src/app/out/power_ctrl.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/src/app/sem/chronos.o: src/app/sem/chronos.c  .generated_files/551066d79fd31fc88ebfccd5e92cbb50bf159908.flag .generated_files/8bac4a0766d39c6687560ebfeb650ad7e1a6910e.flag
	@${MKDIR} "${OBJECTDIR}/src/app/sem" 
	@${RM} ${OBJECTDIR}/src/app/sem/chronos.o.d 
	@${RM} ${OBJECTDIR}/src/app/sem/chronos.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"src" -I"." -O2 -D_SUPPRESS_PLIB_WARNING -I"C:/Program Files (x86)/Microchip/xc32/v2.15/pic32-libs" -MP -MMD -MF "${OBJECTDIR}/src/app/sem/chronos.o.d" -o ${OBJECTDIR}/src/app/sem/chronos.o src/app/sem/chronos.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/src/app/sem/sem_objects.o: src/app/sem/sem_objects.c  .generated_files/c23490dc0228051af1d98496b3e3823866fb5aa7.flag .generated_files/8bac4a0766d39c6687560ebfeb650ad7e1a6910e.flag
	@${MKDIR} "${OBJECTDIR}/src/app/sem" 
	@${RM} ${OBJECTDIR}/src/app/sem/sem_objects.o.d 
	@${RM} ${OBJECTDIR}/src/app/sem/sem_objects.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"src" -I"." -O2 -D_SUPPRESS_PLIB_WARNING -I"C:/Program Files (x86)/Microchip/xc32/v2.15/pic32-libs" -MP -MMD -MF "${OBJECTDIR}/src/app/sem/sem_objects.o.d" -o ${OBJECTDIR}/src/app/sem/sem_objects.o src/app/sem/sem_objects.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/src/app/sem/semaphore.o: src/app/sem/semaphore.c  .generated_files/578d5fb2fb75eb0721468e04ed12fa3dbf934f3a.flag .generated_files/8bac4a0766d39c6687560ebfeb650ad7e1a6910e.flag
	@${MKDIR} "${OBJECTDIR}/src/app/sem" 
	@${RM} ${OBJECTDIR}/src/app/sem/semaphore.o.d 
	@${RM} ${OBJECTDIR}/src/app/sem/semaphore.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"src" -I"." -O2 -D_SUPPRESS_PLIB_WARNING -I"C:/Program Files (x86)/Microchip/xc32/v2.15/pic32-libs" -MP -MMD -MF "${OBJECTDIR}/src/app/sem/semaphore.o.d" -o ${OBJECTDIR}/src/app/sem/semaphore.o src/app/sem/semaphore.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/src/cfg/app_config.o: src/cfg/app_config.c  .generated_files/e405cd1eb9efc2e6b81d2c96b16d924cdcbb6119.flag .generated_files/8bac4a0766d39c6687560ebfeb650ad7e1a6910e.flag
	@${MKDIR} "${OBJECTDIR}/src/cfg" 
	@${RM} ${OBJECTDIR}/src/cfg/app_config.o.d 
	@${RM} ${OBJECTDIR}/src/cfg/app_config.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"src" -I"." -O2 -D_SUPPRESS_PLIB_WARNING -I"C:/Program Files (x86)/Microchip/xc32/v2.15/pic32-libs" -MP -MMD -MF "${OBJECTDIR}/src/cfg/app_config.o.d" -o ${OBJECTDIR}/src/cfg/app_config.o src/cfg/app_config.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/src/cfg/hw_config.o: src/cfg/hw_config.c  .generated_files/1019daf711c6434b3912b1bff93a56ff4cdd3caf.flag .generated_files/8bac4a0766d39c6687560ebfeb650ad7e1a6910e.flag
	@${MKDIR} "${OBJECTDIR}/src/cfg" 
	@${RM} ${OBJECTDIR}/src/cfg/hw_config.o.d 
	@${RM} ${OBJECTDIR}/src/cfg/hw_config.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"src" -I"." -O2 -D_SUPPRESS_PLIB_WARNING -I"C:/Program Files (x86)/Microchip/xc32/v2.15/pic32-libs" -MP -MMD -MF "${OBJECTDIR}/src/cfg/hw_config.o.d" -o ${OBJECTDIR}/src/cfg/hw_config.o src/cfg/hw_config.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/src/drv/pcf2129t.o: src/drv/pcf2129t.c  .generated_files/d71114a04db190ee8c7396208fc1017cf2db9ad0.flag .generated_files/8bac4a0766d39c6687560ebfeb650ad7e1a6910e.flag
	@${MKDIR} "${OBJECTDIR}/src/drv" 
	@${RM} ${OBJECTDIR}/src/drv/pcf2129t.o.d 
	@${RM} ${OBJECTDIR}/src/drv/pcf2129t.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"src" -I"." -O2 -D_SUPPRESS_PLIB_WARNING -I"C:/Program Files (x86)/Microchip/xc32/v2.15/pic32-libs" -MP -MMD -MF "${OBJECTDIR}/src/drv/pcf2129t.o.d" -o ${OBJECTDIR}/src/drv/pcf2129t.o src/drv/pcf2129t.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/src/drv/rfm95.o: src/drv/rfm95.c  .generated_files/52e3ca5d4196ba89921768b768227e03e866065f.flag .generated_files/8bac4a0766d39c6687560ebfeb650ad7e1a6910e.flag
	@${MKDIR} "${OBJECTDIR}/src/drv" 
	@${RM} ${OBJECTDIR}/src/drv/rfm95.o.d 
	@${RM} ${OBJECTDIR}/src/drv/rfm95.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"src" -I"." -O2 -D_SUPPRESS_PLIB_WARNING -I"C:/Program Files (x86)/Microchip/xc32/v2.15/pic32-libs" -MP -MMD -MF "${OBJECTDIR}/src/drv/rfm95.o.d" -o ${OBJECTDIR}/src/drv/rfm95.o src/drv/rfm95.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/src/hal/can/CANConfiguration.o: src/hal/can/CANConfiguration.c  .generated_files/db4d4c76d0f41d62af137f18c56e3bf71588f495.flag .generated_files/8bac4a0766d39c6687560ebfeb650ad7e1a6910e.flag
	@${MKDIR} "${OBJECTDIR}/src/hal/can" 
	@${RM} ${OBJECTDIR}/src/hal/can/CANConfiguration.o.d 
	@${RM} ${OBJECTDIR}/src/hal/can/CANConfiguration.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"src" -I"." -O2 -D_SUPPRESS_PLIB_WARNING -I"C:/Program Files (x86)/Microchip/xc32/v2.15/pic32-libs" -MP -MMD -MF "${OBJECTDIR}/src/hal/can/CANConfiguration.o.d" -o ${OBJECTDIR}/src/hal/can/CANConfiguration.o src/hal/can/CANConfiguration.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/src/hal/can/CANErrorFunctions.o: src/hal/can/CANErrorFunctions.c  .generated_files/a69c5ab16ac1c4af196dd1bca74184eff1063ef9.flag .generated_files/8bac4a0766d39c6687560ebfeb650ad7e1a6910e.flag
	@${MKDIR} "${OBJECTDIR}/src/hal/can" 
	@${RM} ${OBJECTDIR}/src/hal/can/CANErrorFunctions.o.d 
	@${RM} ${OBJECTDIR}/src/hal/can/CANErrorFunctions.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"src" -I"." -O2 -D_SUPPRESS_PLIB_WARNING -I"C:/Program Files (x86)/Microchip/xc32/v2.15/pic32-libs" -MP -MMD -MF "${OBJECTDIR}/src/hal/can/CANErrorFunctions.o.d" -o ${OBJECTDIR}/src/hal/can/CANErrorFunctions.o src/hal/can/CANErrorFunctions.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/src/hal/can/CANEventFunctions.o: src/hal/can/CANEventFunctions.c  .generated_files/3b65ae7c43d407332e724e85f5100016be5e6ed9.flag .generated_files/8bac4a0766d39c6687560ebfeb650ad7e1a6910e.flag
	@${MKDIR} "${OBJECTDIR}/src/hal/can" 
	@${RM} ${OBJECTDIR}/src/hal/can/CANEventFunctions.o.d 
	@${RM} ${OBJECTDIR}/src/hal/can/CANEventFunctions.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"src" -I"." -O2 -D_SUPPRESS_PLIB_WARNING -I"C:/Program Files (x86)/Microchip/xc32/v2.15/pic32-libs" -MP -MMD -MF "${OBJECTDIR}/src/hal/can/CANEventFunctions.o.d" -o ${OBJECTDIR}/src/hal/can/CANEventFunctions.o src/hal/can/CANEventFunctions.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/src/hal/can/CANFilterFunctions.o: src/hal/can/CANFilterFunctions.c  .generated_files/faea175d9c1dc3a4ff902055ec65e510fd5a7eab.flag .generated_files/8bac4a0766d39c6687560ebfeb650ad7e1a6910e.flag
	@${MKDIR} "${OBJECTDIR}/src/hal/can" 
	@${RM} ${OBJECTDIR}/src/hal/can/CANFilterFunctions.o.d 
	@${RM} ${OBJECTDIR}/src/hal/can/CANFilterFunctions.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"src" -I"." -O2 -D_SUPPRESS_PLIB_WARNING -I"C:/Program Files (x86)/Microchip/xc32/v2.15/pic32-libs" -MP -MMD -MF "${OBJECTDIR}/src/hal/can/CANFilterFunctions.o.d" -o ${OBJECTDIR}/src/hal/can/CANFilterFunctions.o src/hal/can/CANFilterFunctions.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/src/hal/can/CANInfoFunctions.o: src/hal/can/CANInfoFunctions.c  .generated_files/4ef474b821055eca9b7757b018e3f512225ee4e6.flag .generated_files/8bac4a0766d39c6687560ebfeb650ad7e1a6910e.flag
	@${MKDIR} "${OBJECTDIR}/src/hal/can" 
	@${RM} ${OBJECTDIR}/src/hal/can/CANInfoFunctions.o.d 
	@${RM} ${OBJECTDIR}/src/hal/can/CANInfoFunctions.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"src" -I"." -O2 -D_SUPPRESS_PLIB_WARNING -I"C:/Program Files (x86)/Microchip/xc32/v2.15/pic32-libs" -MP -MMD -MF "${OBJECTDIR}/src/hal/can/CANInfoFunctions.o.d" -o ${OBJECTDIR}/src/hal/can/CANInfoFunctions.o src/hal/can/CANInfoFunctions.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/src/hal/can/CANReceiveFunctions.o: src/hal/can/CANReceiveFunctions.c  .generated_files/147627ee06be1fc6a29895aa6c52597c6353f9de.flag .generated_files/8bac4a0766d39c6687560ebfeb650ad7e1a6910e.flag
	@${MKDIR} "${OBJECTDIR}/src/hal/can" 
	@${RM} ${OBJECTDIR}/src/hal/can/CANReceiveFunctions.o.d 
	@${RM} ${OBJECTDIR}/src/hal/can/CANReceiveFunctions.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"src" -I"." -O2 -D_SUPPRESS_PLIB_WARNING -I"C:/Program Files (x86)/Microchip/xc32/v2.15/pic32-libs" -MP -MMD -MF "${OBJECTDIR}/src/hal/can/CANReceiveFunctions.o.d" -o ${OBJECTDIR}/src/hal/can/CANReceiveFunctions.o src/hal/can/CANReceiveFunctions.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/src/hal/can/CANTransmitFunctions.o: src/hal/can/CANTransmitFunctions.c  .generated_files/6087b22b8d1e037df3d18b7062e60b4e5f792255.flag .generated_files/8bac4a0766d39c6687560ebfeb650ad7e1a6910e.flag
	@${MKDIR} "${OBJECTDIR}/src/hal/can" 
	@${RM} ${OBJECTDIR}/src/hal/can/CANTransmitFunctions.o.d 
	@${RM} ${OBJECTDIR}/src/hal/can/CANTransmitFunctions.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"src" -I"." -O2 -D_SUPPRESS_PLIB_WARNING -I"C:/Program Files (x86)/Microchip/xc32/v2.15/pic32-libs" -MP -MMD -MF "${OBJECTDIR}/src/hal/can/CANTransmitFunctions.o.d" -o ${OBJECTDIR}/src/hal/can/CANTransmitFunctions.o src/hal/can/CANTransmitFunctions.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/src/hal/pin32.o: src/hal/pin32.c  .generated_files/449290b72c6b9128cd4e7347143c749ba6b829b8.flag .generated_files/8bac4a0766d39c6687560ebfeb650ad7e1a6910e.flag
	@${MKDIR} "${OBJECTDIR}/src/hal" 
	@${RM} ${OBJECTDIR}/src/hal/pin32.o.d 
	@${RM} ${OBJECTDIR}/src/hal/pin32.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"src" -I"." -O2 -D_SUPPRESS_PLIB_WARNING -I"C:/Program Files (x86)/Microchip/xc32/v2.15/pic32-libs" -MP -MMD -MF "${OBJECTDIR}/src/hal/pin32.o.d" -o ${OBJECTDIR}/src/hal/pin32.o src/hal/pin32.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/src/hal/uart32mx.o: src/hal/uart32mx.c  .generated_files/f2c75587b0748c8e7cee3465290611a6b9d7b4cf.flag .generated_files/8bac4a0766d39c6687560ebfeb650ad7e1a6910e.flag
	@${MKDIR} "${OBJECTDIR}/src/hal" 
	@${RM} ${OBJECTDIR}/src/hal/uart32mx.o.d 
	@${RM} ${OBJECTDIR}/src/hal/uart32mx.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"src" -I"." -O2 -D_SUPPRESS_PLIB_WARNING -I"C:/Program Files (x86)/Microchip/xc32/v2.15/pic32-libs" -MP -MMD -MF "${OBJECTDIR}/src/hal/uart32mx.o.d" -o ${OBJECTDIR}/src/hal/uart32mx.o src/hal/uart32mx.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/src/lib/aes.o: src/lib/aes.c  .generated_files/153270abdd9e9829a1b890463429e5fdf98e86fc.flag .generated_files/8bac4a0766d39c6687560ebfeb650ad7e1a6910e.flag
	@${MKDIR} "${OBJECTDIR}/src/lib" 
	@${RM} ${OBJECTDIR}/src/lib/aes.o.d 
	@${RM} ${OBJECTDIR}/src/lib/aes.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"src" -I"." -O2 -D_SUPPRESS_PLIB_WARNING -I"C:/Program Files (x86)/Microchip/xc32/v2.15/pic32-libs" -MP -MMD -MF "${OBJECTDIR}/src/lib/aes.o.d" -o ${OBJECTDIR}/src/lib/aes.o src/lib/aes.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/src/lib/datetime.o: src/lib/datetime.c  .generated_files/5bc472e4cab81704641acd628b13e9e2bf22c69f.flag .generated_files/8bac4a0766d39c6687560ebfeb650ad7e1a6910e.flag
	@${MKDIR} "${OBJECTDIR}/src/lib" 
	@${RM} ${OBJECTDIR}/src/lib/datetime.o.d 
	@${RM} ${OBJECTDIR}/src/lib/datetime.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"src" -I"." -O2 -D_SUPPRESS_PLIB_WARNING -I"C:/Program Files (x86)/Microchip/xc32/v2.15/pic32-libs" -MP -MMD -MF "${OBJECTDIR}/src/lib/datetime.o.d" -o ${OBJECTDIR}/src/lib/datetime.o src/lib/datetime.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/src/lib/utils.o: src/lib/utils.c  .generated_files/690eb095238ee9dc1a72c197c9f8f6e0f3f1b87c.flag .generated_files/8bac4a0766d39c6687560ebfeb650ad7e1a6910e.flag
	@${MKDIR} "${OBJECTDIR}/src/lib" 
	@${RM} ${OBJECTDIR}/src/lib/utils.o.d 
	@${RM} ${OBJECTDIR}/src/lib/utils.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"src" -I"." -O2 -D_SUPPRESS_PLIB_WARNING -I"C:/Program Files (x86)/Microchip/xc32/v2.15/pic32-libs" -MP -MMD -MF "${OBJECTDIR}/src/lib/utils.o.d" -o ${OBJECTDIR}/src/lib/utils.o src/lib/utils.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/src/lib/shared_buff.o: src/lib/shared_buff.c  .generated_files/6f599a251f30bad8ce06dc7f76841144960aa582.flag .generated_files/8bac4a0766d39c6687560ebfeb650ad7e1a6910e.flag
	@${MKDIR} "${OBJECTDIR}/src/lib" 
	@${RM} ${OBJECTDIR}/src/lib/shared_buff.o.d 
	@${RM} ${OBJECTDIR}/src/lib/shared_buff.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"src" -I"." -O2 -D_SUPPRESS_PLIB_WARNING -I"C:/Program Files (x86)/Microchip/xc32/v2.15/pic32-libs" -MP -MMD -MF "${OBJECTDIR}/src/lib/shared_buff.o.d" -o ${OBJECTDIR}/src/lib/shared_buff.o src/lib/shared_buff.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/src/lib/jparsing.o: src/lib/jparsing.c  .generated_files/30cacd8b607fbad7b91d4806c5997d66d7d0fa34.flag .generated_files/8bac4a0766d39c6687560ebfeb650ad7e1a6910e.flag
	@${MKDIR} "${OBJECTDIR}/src/lib" 
	@${RM} ${OBJECTDIR}/src/lib/jparsing.o.d 
	@${RM} ${OBJECTDIR}/src/lib/jparsing.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"src" -I"." -O2 -D_SUPPRESS_PLIB_WARNING -I"C:/Program Files (x86)/Microchip/xc32/v2.15/pic32-libs" -MP -MMD -MF "${OBJECTDIR}/src/lib/jparsing.o.d" -o ${OBJECTDIR}/src/lib/jparsing.o src/lib/jparsing.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/src/lib/jsmn.o: src/lib/jsmn.c  .generated_files/2ad0e180a426a4160bb1da411b47ce188ec4d913.flag .generated_files/8bac4a0766d39c6687560ebfeb650ad7e1a6910e.flag
	@${MKDIR} "${OBJECTDIR}/src/lib" 
	@${RM} ${OBJECTDIR}/src/lib/jsmn.o.d 
	@${RM} ${OBJECTDIR}/src/lib/jsmn.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"src" -I"." -O2 -D_SUPPRESS_PLIB_WARNING -I"C:/Program Files (x86)/Microchip/xc32/v2.15/pic32-libs" -MP -MMD -MF "${OBJECTDIR}/src/lib/jsmn.o.d" -o ${OBJECTDIR}/src/lib/jsmn.o src/lib/jsmn.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/mcc_generated_files/spi3.o: mcc_generated_files/spi3.c  .generated_files/c22ea398fd6073e3062e5377938814c2d7d292e2.flag .generated_files/8bac4a0766d39c6687560ebfeb650ad7e1a6910e.flag
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/spi3.o.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/spi3.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"src" -I"." -O2 -D_SUPPRESS_PLIB_WARNING -I"C:/Program Files (x86)/Microchip/xc32/v2.15/pic32-libs" -MP -MMD -MF "${OBJECTDIR}/mcc_generated_files/spi3.o.d" -o ${OBJECTDIR}/mcc_generated_files/spi3.o mcc_generated_files/spi3.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/mcc_generated_files/uart3.o: mcc_generated_files/uart3.c  .generated_files/7ec2ed7976a9b77fd3096edeb15c2aa25120ddc3.flag .generated_files/8bac4a0766d39c6687560ebfeb650ad7e1a6910e.flag
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/uart3.o.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/uart3.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"src" -I"." -O2 -D_SUPPRESS_PLIB_WARNING -I"C:/Program Files (x86)/Microchip/xc32/v2.15/pic32-libs" -MP -MMD -MF "${OBJECTDIR}/mcc_generated_files/uart3.o.d" -o ${OBJECTDIR}/mcc_generated_files/uart3.o mcc_generated_files/uart3.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/mcc_generated_files/interrupt_manager.o: mcc_generated_files/interrupt_manager.c  .generated_files/3f545782353ae94b1db6528fbdc438901f912c79.flag .generated_files/8bac4a0766d39c6687560ebfeb650ad7e1a6910e.flag
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/interrupt_manager.o.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/interrupt_manager.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"src" -I"." -O2 -D_SUPPRESS_PLIB_WARNING -I"C:/Program Files (x86)/Microchip/xc32/v2.15/pic32-libs" -MP -MMD -MF "${OBJECTDIR}/mcc_generated_files/interrupt_manager.o.d" -o ${OBJECTDIR}/mcc_generated_files/interrupt_manager.o mcc_generated_files/interrupt_manager.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/mcc_generated_files/mcc.o: mcc_generated_files/mcc.c  .generated_files/9afb8531684f791f7dc602cdc9868f53c575cc0e.flag .generated_files/8bac4a0766d39c6687560ebfeb650ad7e1a6910e.flag
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/mcc.o.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/mcc.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"src" -I"." -O2 -D_SUPPRESS_PLIB_WARNING -I"C:/Program Files (x86)/Microchip/xc32/v2.15/pic32-libs" -MP -MMD -MF "${OBJECTDIR}/mcc_generated_files/mcc.o.d" -o ${OBJECTDIR}/mcc_generated_files/mcc.o mcc_generated_files/mcc.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/mcc_generated_files/uart1.o: mcc_generated_files/uart1.c  .generated_files/ada028c30677cda00056fe727dce8496088308f4.flag .generated_files/8bac4a0766d39c6687560ebfeb650ad7e1a6910e.flag
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/uart1.o.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/uart1.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"src" -I"." -O2 -D_SUPPRESS_PLIB_WARNING -I"C:/Program Files (x86)/Microchip/xc32/v2.15/pic32-libs" -MP -MMD -MF "${OBJECTDIR}/mcc_generated_files/uart1.o.d" -o ${OBJECTDIR}/mcc_generated_files/uart1.o mcc_generated_files/uart1.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/mcc_generated_files/pin_manager.o: mcc_generated_files/pin_manager.c  .generated_files/74b27e9e1298b6e4c1b378c2001afec9e59fc703.flag .generated_files/8bac4a0766d39c6687560ebfeb650ad7e1a6910e.flag
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/pin_manager.o.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/pin_manager.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"src" -I"." -O2 -D_SUPPRESS_PLIB_WARNING -I"C:/Program Files (x86)/Microchip/xc32/v2.15/pic32-libs" -MP -MMD -MF "${OBJECTDIR}/mcc_generated_files/pin_manager.o.d" -o ${OBJECTDIR}/mcc_generated_files/pin_manager.o mcc_generated_files/pin_manager.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/mcc_generated_files/uart2.o: mcc_generated_files/uart2.c  .generated_files/196c4a7a7288816497d98c364c5524081f7e00dc.flag .generated_files/8bac4a0766d39c6687560ebfeb650ad7e1a6910e.flag
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/uart2.o.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/uart2.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"src" -I"." -O2 -D_SUPPRESS_PLIB_WARNING -I"C:/Program Files (x86)/Microchip/xc32/v2.15/pic32-libs" -MP -MMD -MF "${OBJECTDIR}/mcc_generated_files/uart2.o.d" -o ${OBJECTDIR}/mcc_generated_files/uart2.o mcc_generated_files/uart2.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/mcc_generated_files/tmr1.o: mcc_generated_files/tmr1.c  .generated_files/a3c5df9a44bad3a71c7315337ed59571190b9fc7.flag .generated_files/8bac4a0766d39c6687560ebfeb650ad7e1a6910e.flag
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/tmr1.o.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/tmr1.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"src" -I"." -O2 -D_SUPPRESS_PLIB_WARNING -I"C:/Program Files (x86)/Microchip/xc32/v2.15/pic32-libs" -MP -MMD -MF "${OBJECTDIR}/mcc_generated_files/tmr1.o.d" -o ${OBJECTDIR}/mcc_generated_files/tmr1.o mcc_generated_files/tmr1.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/mcc_generated_files/uart4.o: mcc_generated_files/uart4.c  .generated_files/6461086bd05538842b1dcdabac0279d370639821.flag .generated_files/8bac4a0766d39c6687560ebfeb650ad7e1a6910e.flag
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/uart4.o.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/uart4.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"src" -I"." -O2 -D_SUPPRESS_PLIB_WARNING -I"C:/Program Files (x86)/Microchip/xc32/v2.15/pic32-libs" -MP -MMD -MF "${OBJECTDIR}/mcc_generated_files/uart4.o.d" -o ${OBJECTDIR}/mcc_generated_files/uart4.o mcc_generated_files/uart4.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/mcc_generated_files/uart5.o: mcc_generated_files/uart5.c  .generated_files/6800f11d0c2e2de61d8aef9d61d687f4c124d1ea.flag .generated_files/8bac4a0766d39c6687560ebfeb650ad7e1a6910e.flag
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/uart5.o.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/uart5.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"src" -I"." -O2 -D_SUPPRESS_PLIB_WARNING -I"C:/Program Files (x86)/Microchip/xc32/v2.15/pic32-libs" -MP -MMD -MF "${OBJECTDIR}/mcc_generated_files/uart5.o.d" -o ${OBJECTDIR}/mcc_generated_files/uart5.o mcc_generated_files/uart5.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/mcc_generated_files/tmr2.o: mcc_generated_files/tmr2.c  .generated_files/5203e2597c60e0f80881f9dc70a6b3985dfc6d74.flag .generated_files/8bac4a0766d39c6687560ebfeb650ad7e1a6910e.flag
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/tmr2.o.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/tmr2.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"src" -I"." -O2 -D_SUPPRESS_PLIB_WARNING -I"C:/Program Files (x86)/Microchip/xc32/v2.15/pic32-libs" -MP -MMD -MF "${OBJECTDIR}/mcc_generated_files/tmr2.o.d" -o ${OBJECTDIR}/mcc_generated_files/tmr2.o mcc_generated_files/tmr2.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/src/sal/buttons.o: src/sal/buttons.c  .generated_files/7daf40f53b8499b2933b0956846c6f90f0b57b33.flag .generated_files/8bac4a0766d39c6687560ebfeb650ad7e1a6910e.flag
	@${MKDIR} "${OBJECTDIR}/src/sal" 
	@${RM} ${OBJECTDIR}/src/sal/buttons.o.d 
	@${RM} ${OBJECTDIR}/src/sal/buttons.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"src" -I"." -O2 -D_SUPPRESS_PLIB_WARNING -I"C:/Program Files (x86)/Microchip/xc32/v2.15/pic32-libs" -MP -MMD -MF "${OBJECTDIR}/src/sal/buttons.o.d" -o ${OBJECTDIR}/src/sal/buttons.o src/sal/buttons.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/src/sal/pulse.o: src/sal/pulse.c  .generated_files/fc81d9f2947e064c05cc1a34c33f11f8de976521.flag .generated_files/8bac4a0766d39c6687560ebfeb650ad7e1a6910e.flag
	@${MKDIR} "${OBJECTDIR}/src/sal" 
	@${RM} ${OBJECTDIR}/src/sal/pulse.o.d 
	@${RM} ${OBJECTDIR}/src/sal/pulse.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"src" -I"." -O2 -D_SUPPRESS_PLIB_WARNING -I"C:/Program Files (x86)/Microchip/xc32/v2.15/pic32-libs" -MP -MMD -MF "${OBJECTDIR}/src/sal/pulse.o.d" -o ${OBJECTDIR}/src/sal/pulse.o src/sal/pulse.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/src/sal/timer.o: src/sal/timer.c  .generated_files/18cd5419149c2223173e9435e503aa2d997579.flag .generated_files/8bac4a0766d39c6687560ebfeb650ad7e1a6910e.flag
	@${MKDIR} "${OBJECTDIR}/src/sal" 
	@${RM} ${OBJECTDIR}/src/sal/timer.o.d 
	@${RM} ${OBJECTDIR}/src/sal/timer.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"src" -I"." -O2 -D_SUPPRESS_PLIB_WARNING -I"C:/Program Files (x86)/Microchip/xc32/v2.15/pic32-libs" -MP -MMD -MF "${OBJECTDIR}/src/sal/timer.o.d" -o ${OBJECTDIR}/src/sal/timer.o src/sal/timer.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/src/sal/debug.o: src/sal/debug.c  .generated_files/8c1e9b4ea1fe08c1f3065be1bb22a74a52ac5b63.flag .generated_files/8bac4a0766d39c6687560ebfeb650ad7e1a6910e.flag
	@${MKDIR} "${OBJECTDIR}/src/sal" 
	@${RM} ${OBJECTDIR}/src/sal/debug.o.d 
	@${RM} ${OBJECTDIR}/src/sal/debug.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"src" -I"." -O2 -D_SUPPRESS_PLIB_WARNING -I"C:/Program Files (x86)/Microchip/xc32/v2.15/pic32-libs" -MP -MMD -MF "${OBJECTDIR}/src/sal/debug.o.d" -o ${OBJECTDIR}/src/sal/debug.o src/sal/debug.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/src/sas/canbus.o: src/sas/canbus.c  .generated_files/3b2548fae2a76fe0d4ebb6a5b18646a7132a4f58.flag .generated_files/8bac4a0766d39c6687560ebfeb650ad7e1a6910e.flag
	@${MKDIR} "${OBJECTDIR}/src/sas" 
	@${RM} ${OBJECTDIR}/src/sas/canbus.o.d 
	@${RM} ${OBJECTDIR}/src/sas/canbus.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"src" -I"." -O2 -D_SUPPRESS_PLIB_WARNING -I"C:/Program Files (x86)/Microchip/xc32/v2.15/pic32-libs" -MP -MMD -MF "${OBJECTDIR}/src/sas/canbus.o.d" -o ${OBJECTDIR}/src/sas/canbus.o src/sas/canbus.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/src/sas/atdrv.o: src/sas/atdrv.c  .generated_files/ac3e6da52e0a2c2834ae0bdac8bd1d1bfe44a10f.flag .generated_files/8bac4a0766d39c6687560ebfeb650ad7e1a6910e.flag
	@${MKDIR} "${OBJECTDIR}/src/sas" 
	@${RM} ${OBJECTDIR}/src/sas/atdrv.o.d 
	@${RM} ${OBJECTDIR}/src/sas/atdrv.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"src" -I"." -O2 -D_SUPPRESS_PLIB_WARNING -I"C:/Program Files (x86)/Microchip/xc32/v2.15/pic32-libs" -MP -MMD -MF "${OBJECTDIR}/src/sas/atdrv.o.d" -o ${OBJECTDIR}/src/sas/atdrv.o src/sas/atdrv.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/src/sas/sim800c.o: src/sas/sim800c.c  .generated_files/e2a9e053586fa81b6374b03584a74371b80bb1bb.flag .generated_files/8bac4a0766d39c6687560ebfeb650ad7e1a6910e.flag
	@${MKDIR} "${OBJECTDIR}/src/sas" 
	@${RM} ${OBJECTDIR}/src/sas/sim800c.o.d 
	@${RM} ${OBJECTDIR}/src/sas/sim800c.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"src" -I"." -O2 -D_SUPPRESS_PLIB_WARNING -I"C:/Program Files (x86)/Microchip/xc32/v2.15/pic32-libs" -MP -MMD -MF "${OBJECTDIR}/src/sas/sim800c.o.d" -o ${OBJECTDIR}/src/sas/sim800c.o src/sas/sim800c.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/src/sas/storage.o: src/sas/storage.c  .generated_files/e8021ae9653e886508d87146a2f89508cd86843d.flag .generated_files/8bac4a0766d39c6687560ebfeb650ad7e1a6910e.flag
	@${MKDIR} "${OBJECTDIR}/src/sas" 
	@${RM} ${OBJECTDIR}/src/sas/storage.o.d 
	@${RM} ${OBJECTDIR}/src/sas/storage.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"src" -I"." -O2 -D_SUPPRESS_PLIB_WARNING -I"C:/Program Files (x86)/Microchip/xc32/v2.15/pic32-libs" -MP -MMD -MF "${OBJECTDIR}/src/sas/storage.o.d" -o ${OBJECTDIR}/src/sas/storage.o src/sas/storage.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/src/sas/rmsg_blob.o: src/sas/rmsg_blob.c  .generated_files/e845d3cbcc3d656c094e857d56db84258d81f61a.flag .generated_files/8bac4a0766d39c6687560ebfeb650ad7e1a6910e.flag
	@${MKDIR} "${OBJECTDIR}/src/sas" 
	@${RM} ${OBJECTDIR}/src/sas/rmsg_blob.o.d 
	@${RM} ${OBJECTDIR}/src/sas/rmsg_blob.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"src" -I"." -O2 -D_SUPPRESS_PLIB_WARNING -I"C:/Program Files (x86)/Microchip/xc32/v2.15/pic32-libs" -MP -MMD -MF "${OBJECTDIR}/src/sas/rmsg_blob.o.d" -o ${OBJECTDIR}/src/sas/rmsg_blob.o src/sas/rmsg_blob.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/src/sas/lora.o: src/sas/lora.c  .generated_files/d8608315eb58d5ce1ee4cbde31c4f0d6cc8b1558.flag .generated_files/8bac4a0766d39c6687560ebfeb650ad7e1a6910e.flag
	@${MKDIR} "${OBJECTDIR}/src/sas" 
	@${RM} ${OBJECTDIR}/src/sas/lora.o.d 
	@${RM} ${OBJECTDIR}/src/sas/lora.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"src" -I"." -O2 -D_SUPPRESS_PLIB_WARNING -I"C:/Program Files (x86)/Microchip/xc32/v2.15/pic32-libs" -MP -MMD -MF "${OBJECTDIR}/src/sas/lora.o.d" -o ${OBJECTDIR}/src/sas/lora.o src/sas/lora.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/src/sas/slink.o: src/sas/slink.c  .generated_files/339f8d50e7e49baed7eae8e4a9b7466c39f2785a.flag .generated_files/8bac4a0766d39c6687560ebfeb650ad7e1a6910e.flag
	@${MKDIR} "${OBJECTDIR}/src/sas" 
	@${RM} ${OBJECTDIR}/src/sas/slink.o.d 
	@${RM} ${OBJECTDIR}/src/sas/slink.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"src" -I"." -O2 -D_SUPPRESS_PLIB_WARNING -I"C:/Program Files (x86)/Microchip/xc32/v2.15/pic32-libs" -MP -MMD -MF "${OBJECTDIR}/src/sas/slink.o.d" -o ${OBJECTDIR}/src/sas/slink.o src/sas/slink.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/src/sas/server.o: src/sas/server.c  .generated_files/1895903964f40baa0d792677e887d385b0042b52.flag .generated_files/8bac4a0766d39c6687560ebfeb650ad7e1a6910e.flag
	@${MKDIR} "${OBJECTDIR}/src/sas" 
	@${RM} ${OBJECTDIR}/src/sas/server.o.d 
	@${RM} ${OBJECTDIR}/src/sas/server.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"src" -I"." -O2 -D_SUPPRESS_PLIB_WARNING -I"C:/Program Files (x86)/Microchip/xc32/v2.15/pic32-libs" -MP -MMD -MF "${OBJECTDIR}/src/sas/server.o.d" -o ${OBJECTDIR}/src/sas/server.o src/sas/server.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/src/sas/rtc.o: src/sas/rtc.c  .generated_files/5f736766f33b66cbd71e57a0560ab14a91730dfd.flag .generated_files/8bac4a0766d39c6687560ebfeb650ad7e1a6910e.flag
	@${MKDIR} "${OBJECTDIR}/src/sas" 
	@${RM} ${OBJECTDIR}/src/sas/rtc.o.d 
	@${RM} ${OBJECTDIR}/src/sas/rtc.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"src" -I"." -O2 -D_SUPPRESS_PLIB_WARNING -I"C:/Program Files (x86)/Microchip/xc32/v2.15/pic32-libs" -MP -MMD -MF "${OBJECTDIR}/src/sas/rtc.o.d" -o ${OBJECTDIR}/src/sas/rtc.o src/sas/rtc.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/src/sas/gps.o: src/sas/gps.c  .generated_files/f8b739d4c225d8965f82f7fbb685793fd5fcf26.flag .generated_files/8bac4a0766d39c6687560ebfeb650ad7e1a6910e.flag
	@${MKDIR} "${OBJECTDIR}/src/sas" 
	@${RM} ${OBJECTDIR}/src/sas/gps.o.d 
	@${RM} ${OBJECTDIR}/src/sas/gps.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"src" -I"." -O2 -D_SUPPRESS_PLIB_WARNING -I"C:/Program Files (x86)/Microchip/xc32/v2.15/pic32-libs" -MP -MMD -MF "${OBJECTDIR}/src/sas/gps.o.d" -o ${OBJECTDIR}/src/sas/gps.o src/sas/gps.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/main.o: main.c  .generated_files/cc7ec1c968e63e715d902893388bfe8cc28690c4.flag .generated_files/8bac4a0766d39c6687560ebfeb650ad7e1a6910e.flag
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/main.o.d 
	@${RM} ${OBJECTDIR}/main.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"src" -I"." -O2 -D_SUPPRESS_PLIB_WARNING -I"C:/Program Files (x86)/Microchip/xc32/v2.15/pic32-libs" -MP -MMD -MF "${OBJECTDIR}/main.o.d" -o ${OBJECTDIR}/main.o main.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	
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
	${MP_CC} $(MP_EXTRA_LD_PRE) -g   -mprocessor=$(MP_PROCESSOR_OPTION)  -o dist/${CND_CONF}/${IMAGE_TYPE}/GwMasterCtrl_v5.0.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX} ${OBJECTFILES_QUOTED_IF_SPACED}          -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  -std=gnu99 $(COMPARISON_BUILD)      -Wl,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_LD_POST)$(MP_LINKER_FILE_OPTION),--defsym=__MPLAB_DEBUG=1,--defsym=__DEBUG=1,-D=__DEBUG_D,--gc-sections,--no-code-in-dinit,--no-dinit-in-serial-mem,-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map",--memorysummary,dist/${CND_CONF}/${IMAGE_TYPE}/memoryfile.xml,--defsym=_ebase_address=0x9D001000 -mdfp="${DFP_DIR}"
	
else
dist/${CND_CONF}/${IMAGE_TYPE}/GwMasterCtrl_v5.0.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk   
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE)  -mprocessor=$(MP_PROCESSOR_OPTION)  -o dist/${CND_CONF}/${IMAGE_TYPE}/GwMasterCtrl_v5.0.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} ${OBJECTFILES_QUOTED_IF_SPACED}          -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  -std=gnu99 $(COMPARISON_BUILD)  -Wl,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_LD_POST)$(MP_LINKER_FILE_OPTION),--gc-sections,--no-code-in-dinit,--no-dinit-in-serial-mem,-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map",--memorysummary,dist/${CND_CONF}/${IMAGE_TYPE}/memoryfile.xml,--defsym=_ebase_address=0x9D001000 -mdfp="${DFP_DIR}"
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
