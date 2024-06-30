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
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/GwOutputCard_v5.0.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
else
IMAGE_TYPE=production
OUTPUT_SUFFIX=hex
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/GwOutputCard_v5.0.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
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
SOURCEFILES_QUOTED_IF_SPACED=src/app/hostctrl.c src/app/logic.c src/cfg/app_config.c src/cfg/hw_config.c src/hal/can/CANConfiguration.c src/hal/can/CANErrorFunctions.c src/hal/can/CANEventFunctions.c src/hal/can/CANFilterFunctions.c src/hal/can/CANInfoFunctions.c src/hal/can/CANReceiveFunctions.c src/hal/can/CANTransmitFunctions.c src/hal/pin32.c src/hal/uart32mx.c mcc_generated_files/interrupt_manager.c mcc_generated_files/mcc.c mcc_generated_files/pin_manager.c mcc_generated_files/tmr2.c mcc_generated_files/uart1.c mcc_generated_files/adc1.c mcc_generated_files/tmr1.c src/sas/debug.c src/sas/pulse.c src/sas/timer.c src/ssl/bulbctrl.c src/ssl/canbus.c main.c

# Object Files Quoted if spaced
OBJECTFILES_QUOTED_IF_SPACED=${OBJECTDIR}/src/app/hostctrl.o ${OBJECTDIR}/src/app/logic.o ${OBJECTDIR}/src/cfg/app_config.o ${OBJECTDIR}/src/cfg/hw_config.o ${OBJECTDIR}/src/hal/can/CANConfiguration.o ${OBJECTDIR}/src/hal/can/CANErrorFunctions.o ${OBJECTDIR}/src/hal/can/CANEventFunctions.o ${OBJECTDIR}/src/hal/can/CANFilterFunctions.o ${OBJECTDIR}/src/hal/can/CANInfoFunctions.o ${OBJECTDIR}/src/hal/can/CANReceiveFunctions.o ${OBJECTDIR}/src/hal/can/CANTransmitFunctions.o ${OBJECTDIR}/src/hal/pin32.o ${OBJECTDIR}/src/hal/uart32mx.o ${OBJECTDIR}/mcc_generated_files/interrupt_manager.o ${OBJECTDIR}/mcc_generated_files/mcc.o ${OBJECTDIR}/mcc_generated_files/pin_manager.o ${OBJECTDIR}/mcc_generated_files/tmr2.o ${OBJECTDIR}/mcc_generated_files/uart1.o ${OBJECTDIR}/mcc_generated_files/adc1.o ${OBJECTDIR}/mcc_generated_files/tmr1.o ${OBJECTDIR}/src/sas/debug.o ${OBJECTDIR}/src/sas/pulse.o ${OBJECTDIR}/src/sas/timer.o ${OBJECTDIR}/src/ssl/bulbctrl.o ${OBJECTDIR}/src/ssl/canbus.o ${OBJECTDIR}/main.o
POSSIBLE_DEPFILES=${OBJECTDIR}/src/app/hostctrl.o.d ${OBJECTDIR}/src/app/logic.o.d ${OBJECTDIR}/src/cfg/app_config.o.d ${OBJECTDIR}/src/cfg/hw_config.o.d ${OBJECTDIR}/src/hal/can/CANConfiguration.o.d ${OBJECTDIR}/src/hal/can/CANErrorFunctions.o.d ${OBJECTDIR}/src/hal/can/CANEventFunctions.o.d ${OBJECTDIR}/src/hal/can/CANFilterFunctions.o.d ${OBJECTDIR}/src/hal/can/CANInfoFunctions.o.d ${OBJECTDIR}/src/hal/can/CANReceiveFunctions.o.d ${OBJECTDIR}/src/hal/can/CANTransmitFunctions.o.d ${OBJECTDIR}/src/hal/pin32.o.d ${OBJECTDIR}/src/hal/uart32mx.o.d ${OBJECTDIR}/mcc_generated_files/interrupt_manager.o.d ${OBJECTDIR}/mcc_generated_files/mcc.o.d ${OBJECTDIR}/mcc_generated_files/pin_manager.o.d ${OBJECTDIR}/mcc_generated_files/tmr2.o.d ${OBJECTDIR}/mcc_generated_files/uart1.o.d ${OBJECTDIR}/mcc_generated_files/adc1.o.d ${OBJECTDIR}/mcc_generated_files/tmr1.o.d ${OBJECTDIR}/src/sas/debug.o.d ${OBJECTDIR}/src/sas/pulse.o.d ${OBJECTDIR}/src/sas/timer.o.d ${OBJECTDIR}/src/ssl/bulbctrl.o.d ${OBJECTDIR}/src/ssl/canbus.o.d ${OBJECTDIR}/main.o.d

# Object Files
OBJECTFILES=${OBJECTDIR}/src/app/hostctrl.o ${OBJECTDIR}/src/app/logic.o ${OBJECTDIR}/src/cfg/app_config.o ${OBJECTDIR}/src/cfg/hw_config.o ${OBJECTDIR}/src/hal/can/CANConfiguration.o ${OBJECTDIR}/src/hal/can/CANErrorFunctions.o ${OBJECTDIR}/src/hal/can/CANEventFunctions.o ${OBJECTDIR}/src/hal/can/CANFilterFunctions.o ${OBJECTDIR}/src/hal/can/CANInfoFunctions.o ${OBJECTDIR}/src/hal/can/CANReceiveFunctions.o ${OBJECTDIR}/src/hal/can/CANTransmitFunctions.o ${OBJECTDIR}/src/hal/pin32.o ${OBJECTDIR}/src/hal/uart32mx.o ${OBJECTDIR}/mcc_generated_files/interrupt_manager.o ${OBJECTDIR}/mcc_generated_files/mcc.o ${OBJECTDIR}/mcc_generated_files/pin_manager.o ${OBJECTDIR}/mcc_generated_files/tmr2.o ${OBJECTDIR}/mcc_generated_files/uart1.o ${OBJECTDIR}/mcc_generated_files/adc1.o ${OBJECTDIR}/mcc_generated_files/tmr1.o ${OBJECTDIR}/src/sas/debug.o ${OBJECTDIR}/src/sas/pulse.o ${OBJECTDIR}/src/sas/timer.o ${OBJECTDIR}/src/ssl/bulbctrl.o ${OBJECTDIR}/src/ssl/canbus.o ${OBJECTDIR}/main.o

# Source Files
SOURCEFILES=src/app/hostctrl.c src/app/logic.c src/cfg/app_config.c src/cfg/hw_config.c src/hal/can/CANConfiguration.c src/hal/can/CANErrorFunctions.c src/hal/can/CANEventFunctions.c src/hal/can/CANFilterFunctions.c src/hal/can/CANInfoFunctions.c src/hal/can/CANReceiveFunctions.c src/hal/can/CANTransmitFunctions.c src/hal/pin32.c src/hal/uart32mx.c mcc_generated_files/interrupt_manager.c mcc_generated_files/mcc.c mcc_generated_files/pin_manager.c mcc_generated_files/tmr2.c mcc_generated_files/uart1.c mcc_generated_files/adc1.c mcc_generated_files/tmr1.c src/sas/debug.c src/sas/pulse.c src/sas/timer.c src/ssl/bulbctrl.c src/ssl/canbus.c main.c



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
	${MAKE}  -f nbproject/Makefile-default.mk dist/${CND_CONF}/${IMAGE_TYPE}/GwOutputCard_v5.0.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}

MP_PROCESSOR_OPTION=32MX530F128H
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
${OBJECTDIR}/src/app/hostctrl.o: src/app/hostctrl.c  .generated_files/844f6f39777dea02f8e7894962089863528de6f7.flag .generated_files/8bac4a0766d39c6687560ebfeb650ad7e1a6910e.flag
	@${MKDIR} "${OBJECTDIR}/src/app" 
	@${RM} ${OBJECTDIR}/src/app/hostctrl.o.d 
	@${RM} ${OBJECTDIR}/src/app/hostctrl.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"." -I"src" -MP -MMD -MF "${OBJECTDIR}/src/app/hostctrl.o.d" -o ${OBJECTDIR}/src/app/hostctrl.o src/app/hostctrl.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/src/app/logic.o: src/app/logic.c  .generated_files/8f38e51afa009e38e669abbb9111eb442fbd1a9f.flag .generated_files/8bac4a0766d39c6687560ebfeb650ad7e1a6910e.flag
	@${MKDIR} "${OBJECTDIR}/src/app" 
	@${RM} ${OBJECTDIR}/src/app/logic.o.d 
	@${RM} ${OBJECTDIR}/src/app/logic.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"." -I"src" -MP -MMD -MF "${OBJECTDIR}/src/app/logic.o.d" -o ${OBJECTDIR}/src/app/logic.o src/app/logic.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/src/cfg/app_config.o: src/cfg/app_config.c  .generated_files/674590741e97d4f964340906e3deac8b688bee0d.flag .generated_files/8bac4a0766d39c6687560ebfeb650ad7e1a6910e.flag
	@${MKDIR} "${OBJECTDIR}/src/cfg" 
	@${RM} ${OBJECTDIR}/src/cfg/app_config.o.d 
	@${RM} ${OBJECTDIR}/src/cfg/app_config.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"." -I"src" -MP -MMD -MF "${OBJECTDIR}/src/cfg/app_config.o.d" -o ${OBJECTDIR}/src/cfg/app_config.o src/cfg/app_config.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/src/cfg/hw_config.o: src/cfg/hw_config.c  .generated_files/c1ec44a29ca36d0b837236151f3b35998910868.flag .generated_files/8bac4a0766d39c6687560ebfeb650ad7e1a6910e.flag
	@${MKDIR} "${OBJECTDIR}/src/cfg" 
	@${RM} ${OBJECTDIR}/src/cfg/hw_config.o.d 
	@${RM} ${OBJECTDIR}/src/cfg/hw_config.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"." -I"src" -MP -MMD -MF "${OBJECTDIR}/src/cfg/hw_config.o.d" -o ${OBJECTDIR}/src/cfg/hw_config.o src/cfg/hw_config.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/src/hal/can/CANConfiguration.o: src/hal/can/CANConfiguration.c  .generated_files/7ac80f0d5c3ee0d32d0ba089c86aafeb57515e43.flag .generated_files/8bac4a0766d39c6687560ebfeb650ad7e1a6910e.flag
	@${MKDIR} "${OBJECTDIR}/src/hal/can" 
	@${RM} ${OBJECTDIR}/src/hal/can/CANConfiguration.o.d 
	@${RM} ${OBJECTDIR}/src/hal/can/CANConfiguration.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"." -I"src" -MP -MMD -MF "${OBJECTDIR}/src/hal/can/CANConfiguration.o.d" -o ${OBJECTDIR}/src/hal/can/CANConfiguration.o src/hal/can/CANConfiguration.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/src/hal/can/CANErrorFunctions.o: src/hal/can/CANErrorFunctions.c  .generated_files/6a5641c2236a044b1505dba786a0179a74d70ea3.flag .generated_files/8bac4a0766d39c6687560ebfeb650ad7e1a6910e.flag
	@${MKDIR} "${OBJECTDIR}/src/hal/can" 
	@${RM} ${OBJECTDIR}/src/hal/can/CANErrorFunctions.o.d 
	@${RM} ${OBJECTDIR}/src/hal/can/CANErrorFunctions.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"." -I"src" -MP -MMD -MF "${OBJECTDIR}/src/hal/can/CANErrorFunctions.o.d" -o ${OBJECTDIR}/src/hal/can/CANErrorFunctions.o src/hal/can/CANErrorFunctions.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/src/hal/can/CANEventFunctions.o: src/hal/can/CANEventFunctions.c  .generated_files/951ea53eab268a90e9a75d59d976bcada5bff45c.flag .generated_files/8bac4a0766d39c6687560ebfeb650ad7e1a6910e.flag
	@${MKDIR} "${OBJECTDIR}/src/hal/can" 
	@${RM} ${OBJECTDIR}/src/hal/can/CANEventFunctions.o.d 
	@${RM} ${OBJECTDIR}/src/hal/can/CANEventFunctions.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"." -I"src" -MP -MMD -MF "${OBJECTDIR}/src/hal/can/CANEventFunctions.o.d" -o ${OBJECTDIR}/src/hal/can/CANEventFunctions.o src/hal/can/CANEventFunctions.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/src/hal/can/CANFilterFunctions.o: src/hal/can/CANFilterFunctions.c  .generated_files/f685a71da8fba15c606fef62d0e65b663e694af3.flag .generated_files/8bac4a0766d39c6687560ebfeb650ad7e1a6910e.flag
	@${MKDIR} "${OBJECTDIR}/src/hal/can" 
	@${RM} ${OBJECTDIR}/src/hal/can/CANFilterFunctions.o.d 
	@${RM} ${OBJECTDIR}/src/hal/can/CANFilterFunctions.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"." -I"src" -MP -MMD -MF "${OBJECTDIR}/src/hal/can/CANFilterFunctions.o.d" -o ${OBJECTDIR}/src/hal/can/CANFilterFunctions.o src/hal/can/CANFilterFunctions.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/src/hal/can/CANInfoFunctions.o: src/hal/can/CANInfoFunctions.c  .generated_files/bf738592bb22cde32f40f73f6256ed88a83b346d.flag .generated_files/8bac4a0766d39c6687560ebfeb650ad7e1a6910e.flag
	@${MKDIR} "${OBJECTDIR}/src/hal/can" 
	@${RM} ${OBJECTDIR}/src/hal/can/CANInfoFunctions.o.d 
	@${RM} ${OBJECTDIR}/src/hal/can/CANInfoFunctions.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"." -I"src" -MP -MMD -MF "${OBJECTDIR}/src/hal/can/CANInfoFunctions.o.d" -o ${OBJECTDIR}/src/hal/can/CANInfoFunctions.o src/hal/can/CANInfoFunctions.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/src/hal/can/CANReceiveFunctions.o: src/hal/can/CANReceiveFunctions.c  .generated_files/c43d12ac3b40f42576b3223450ccd41bbeb60f4c.flag .generated_files/8bac4a0766d39c6687560ebfeb650ad7e1a6910e.flag
	@${MKDIR} "${OBJECTDIR}/src/hal/can" 
	@${RM} ${OBJECTDIR}/src/hal/can/CANReceiveFunctions.o.d 
	@${RM} ${OBJECTDIR}/src/hal/can/CANReceiveFunctions.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"." -I"src" -MP -MMD -MF "${OBJECTDIR}/src/hal/can/CANReceiveFunctions.o.d" -o ${OBJECTDIR}/src/hal/can/CANReceiveFunctions.o src/hal/can/CANReceiveFunctions.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/src/hal/can/CANTransmitFunctions.o: src/hal/can/CANTransmitFunctions.c  .generated_files/14e1457c8d28fbb2b30aab24d892e3d1f27113b3.flag .generated_files/8bac4a0766d39c6687560ebfeb650ad7e1a6910e.flag
	@${MKDIR} "${OBJECTDIR}/src/hal/can" 
	@${RM} ${OBJECTDIR}/src/hal/can/CANTransmitFunctions.o.d 
	@${RM} ${OBJECTDIR}/src/hal/can/CANTransmitFunctions.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"." -I"src" -MP -MMD -MF "${OBJECTDIR}/src/hal/can/CANTransmitFunctions.o.d" -o ${OBJECTDIR}/src/hal/can/CANTransmitFunctions.o src/hal/can/CANTransmitFunctions.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/src/hal/pin32.o: src/hal/pin32.c  .generated_files/f25d0fe71b3666a3243fb02483ce99f85ec0c5ba.flag .generated_files/8bac4a0766d39c6687560ebfeb650ad7e1a6910e.flag
	@${MKDIR} "${OBJECTDIR}/src/hal" 
	@${RM} ${OBJECTDIR}/src/hal/pin32.o.d 
	@${RM} ${OBJECTDIR}/src/hal/pin32.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"." -I"src" -MP -MMD -MF "${OBJECTDIR}/src/hal/pin32.o.d" -o ${OBJECTDIR}/src/hal/pin32.o src/hal/pin32.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/src/hal/uart32mx.o: src/hal/uart32mx.c  .generated_files/d574928cf9a06c04ba8024ba5238767826880c1.flag .generated_files/8bac4a0766d39c6687560ebfeb650ad7e1a6910e.flag
	@${MKDIR} "${OBJECTDIR}/src/hal" 
	@${RM} ${OBJECTDIR}/src/hal/uart32mx.o.d 
	@${RM} ${OBJECTDIR}/src/hal/uart32mx.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"." -I"src" -MP -MMD -MF "${OBJECTDIR}/src/hal/uart32mx.o.d" -o ${OBJECTDIR}/src/hal/uart32mx.o src/hal/uart32mx.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/mcc_generated_files/interrupt_manager.o: mcc_generated_files/interrupt_manager.c  .generated_files/f6d5542fea6ca8ee403b4bb2e30e6f4585934abf.flag .generated_files/8bac4a0766d39c6687560ebfeb650ad7e1a6910e.flag
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/interrupt_manager.o.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/interrupt_manager.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"." -I"src" -MP -MMD -MF "${OBJECTDIR}/mcc_generated_files/interrupt_manager.o.d" -o ${OBJECTDIR}/mcc_generated_files/interrupt_manager.o mcc_generated_files/interrupt_manager.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/mcc_generated_files/mcc.o: mcc_generated_files/mcc.c  .generated_files/d102c746eadb5661b60a3de0ba3794933fe6fcac.flag .generated_files/8bac4a0766d39c6687560ebfeb650ad7e1a6910e.flag
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/mcc.o.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/mcc.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"." -I"src" -MP -MMD -MF "${OBJECTDIR}/mcc_generated_files/mcc.o.d" -o ${OBJECTDIR}/mcc_generated_files/mcc.o mcc_generated_files/mcc.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/mcc_generated_files/pin_manager.o: mcc_generated_files/pin_manager.c  .generated_files/eaffd0a80fcfe667f9a59bcbe3243829898c328b.flag .generated_files/8bac4a0766d39c6687560ebfeb650ad7e1a6910e.flag
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/pin_manager.o.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/pin_manager.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"." -I"src" -MP -MMD -MF "${OBJECTDIR}/mcc_generated_files/pin_manager.o.d" -o ${OBJECTDIR}/mcc_generated_files/pin_manager.o mcc_generated_files/pin_manager.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/mcc_generated_files/tmr2.o: mcc_generated_files/tmr2.c  .generated_files/c08aec1bf58bcbe01ed6800e789c49b42df76d6b.flag .generated_files/8bac4a0766d39c6687560ebfeb650ad7e1a6910e.flag
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/tmr2.o.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/tmr2.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"." -I"src" -MP -MMD -MF "${OBJECTDIR}/mcc_generated_files/tmr2.o.d" -o ${OBJECTDIR}/mcc_generated_files/tmr2.o mcc_generated_files/tmr2.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/mcc_generated_files/uart1.o: mcc_generated_files/uart1.c  .generated_files/843cbd287024c42ef56676ac7aca9e17abc5a004.flag .generated_files/8bac4a0766d39c6687560ebfeb650ad7e1a6910e.flag
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/uart1.o.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/uart1.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"." -I"src" -MP -MMD -MF "${OBJECTDIR}/mcc_generated_files/uart1.o.d" -o ${OBJECTDIR}/mcc_generated_files/uart1.o mcc_generated_files/uart1.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/mcc_generated_files/adc1.o: mcc_generated_files/adc1.c  .generated_files/b98a9b0be4ebf48f748f4920f29a75c4ddf0e1ef.flag .generated_files/8bac4a0766d39c6687560ebfeb650ad7e1a6910e.flag
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/adc1.o.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/adc1.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"." -I"src" -MP -MMD -MF "${OBJECTDIR}/mcc_generated_files/adc1.o.d" -o ${OBJECTDIR}/mcc_generated_files/adc1.o mcc_generated_files/adc1.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/mcc_generated_files/tmr1.o: mcc_generated_files/tmr1.c  .generated_files/97adf1ab4824f64a742d101dcd4b86132b200257.flag .generated_files/8bac4a0766d39c6687560ebfeb650ad7e1a6910e.flag
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/tmr1.o.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/tmr1.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"." -I"src" -MP -MMD -MF "${OBJECTDIR}/mcc_generated_files/tmr1.o.d" -o ${OBJECTDIR}/mcc_generated_files/tmr1.o mcc_generated_files/tmr1.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/src/sas/debug.o: src/sas/debug.c  .generated_files/2fbbbf1a2d994e91ad100613e42e356f8d4b79cb.flag .generated_files/8bac4a0766d39c6687560ebfeb650ad7e1a6910e.flag
	@${MKDIR} "${OBJECTDIR}/src/sas" 
	@${RM} ${OBJECTDIR}/src/sas/debug.o.d 
	@${RM} ${OBJECTDIR}/src/sas/debug.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"." -I"src" -MP -MMD -MF "${OBJECTDIR}/src/sas/debug.o.d" -o ${OBJECTDIR}/src/sas/debug.o src/sas/debug.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/src/sas/pulse.o: src/sas/pulse.c  .generated_files/48324c610c2ae231dbf8ffa98565011bf658c7b4.flag .generated_files/8bac4a0766d39c6687560ebfeb650ad7e1a6910e.flag
	@${MKDIR} "${OBJECTDIR}/src/sas" 
	@${RM} ${OBJECTDIR}/src/sas/pulse.o.d 
	@${RM} ${OBJECTDIR}/src/sas/pulse.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"." -I"src" -MP -MMD -MF "${OBJECTDIR}/src/sas/pulse.o.d" -o ${OBJECTDIR}/src/sas/pulse.o src/sas/pulse.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/src/sas/timer.o: src/sas/timer.c  .generated_files/fdb1acde8b91c7ad7f1255af41f3e8c3e7ceb884.flag .generated_files/8bac4a0766d39c6687560ebfeb650ad7e1a6910e.flag
	@${MKDIR} "${OBJECTDIR}/src/sas" 
	@${RM} ${OBJECTDIR}/src/sas/timer.o.d 
	@${RM} ${OBJECTDIR}/src/sas/timer.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"." -I"src" -MP -MMD -MF "${OBJECTDIR}/src/sas/timer.o.d" -o ${OBJECTDIR}/src/sas/timer.o src/sas/timer.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/src/ssl/bulbctrl.o: src/ssl/bulbctrl.c  .generated_files/f8a1682dc14ed1cc248802dffe8d9f11088046f0.flag .generated_files/8bac4a0766d39c6687560ebfeb650ad7e1a6910e.flag
	@${MKDIR} "${OBJECTDIR}/src/ssl" 
	@${RM} ${OBJECTDIR}/src/ssl/bulbctrl.o.d 
	@${RM} ${OBJECTDIR}/src/ssl/bulbctrl.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"." -I"src" -MP -MMD -MF "${OBJECTDIR}/src/ssl/bulbctrl.o.d" -o ${OBJECTDIR}/src/ssl/bulbctrl.o src/ssl/bulbctrl.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/src/ssl/canbus.o: src/ssl/canbus.c  .generated_files/cc4efd4b5dc23656d169ab0b2afb3f83d97c1e7e.flag .generated_files/8bac4a0766d39c6687560ebfeb650ad7e1a6910e.flag
	@${MKDIR} "${OBJECTDIR}/src/ssl" 
	@${RM} ${OBJECTDIR}/src/ssl/canbus.o.d 
	@${RM} ${OBJECTDIR}/src/ssl/canbus.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"." -I"src" -MP -MMD -MF "${OBJECTDIR}/src/ssl/canbus.o.d" -o ${OBJECTDIR}/src/ssl/canbus.o src/ssl/canbus.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/main.o: main.c  .generated_files/4fb5e451339de3f886dbbdb02938d75cfc06cbea.flag .generated_files/8bac4a0766d39c6687560ebfeb650ad7e1a6910e.flag
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/main.o.d 
	@${RM} ${OBJECTDIR}/main.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"." -I"src" -MP -MMD -MF "${OBJECTDIR}/main.o.d" -o ${OBJECTDIR}/main.o main.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	
else
${OBJECTDIR}/src/app/hostctrl.o: src/app/hostctrl.c  .generated_files/5b02a3c6613cd23eb8a9db604a5fc5ef2df9377.flag .generated_files/8bac4a0766d39c6687560ebfeb650ad7e1a6910e.flag
	@${MKDIR} "${OBJECTDIR}/src/app" 
	@${RM} ${OBJECTDIR}/src/app/hostctrl.o.d 
	@${RM} ${OBJECTDIR}/src/app/hostctrl.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"." -I"src" -MP -MMD -MF "${OBJECTDIR}/src/app/hostctrl.o.d" -o ${OBJECTDIR}/src/app/hostctrl.o src/app/hostctrl.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/src/app/logic.o: src/app/logic.c  .generated_files/76b45b813175e91c7c6c3c6ba7887b98227f8944.flag .generated_files/8bac4a0766d39c6687560ebfeb650ad7e1a6910e.flag
	@${MKDIR} "${OBJECTDIR}/src/app" 
	@${RM} ${OBJECTDIR}/src/app/logic.o.d 
	@${RM} ${OBJECTDIR}/src/app/logic.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"." -I"src" -MP -MMD -MF "${OBJECTDIR}/src/app/logic.o.d" -o ${OBJECTDIR}/src/app/logic.o src/app/logic.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/src/cfg/app_config.o: src/cfg/app_config.c  .generated_files/fd01f6197b7992aeb29723afeef9dec3f6ba5c25.flag .generated_files/8bac4a0766d39c6687560ebfeb650ad7e1a6910e.flag
	@${MKDIR} "${OBJECTDIR}/src/cfg" 
	@${RM} ${OBJECTDIR}/src/cfg/app_config.o.d 
	@${RM} ${OBJECTDIR}/src/cfg/app_config.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"." -I"src" -MP -MMD -MF "${OBJECTDIR}/src/cfg/app_config.o.d" -o ${OBJECTDIR}/src/cfg/app_config.o src/cfg/app_config.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/src/cfg/hw_config.o: src/cfg/hw_config.c  .generated_files/c1e11c9e6a60daf92638a1183d8eab7635c8d7da.flag .generated_files/8bac4a0766d39c6687560ebfeb650ad7e1a6910e.flag
	@${MKDIR} "${OBJECTDIR}/src/cfg" 
	@${RM} ${OBJECTDIR}/src/cfg/hw_config.o.d 
	@${RM} ${OBJECTDIR}/src/cfg/hw_config.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"." -I"src" -MP -MMD -MF "${OBJECTDIR}/src/cfg/hw_config.o.d" -o ${OBJECTDIR}/src/cfg/hw_config.o src/cfg/hw_config.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/src/hal/can/CANConfiguration.o: src/hal/can/CANConfiguration.c  .generated_files/d8855b9470c8062805cf9de02a66762a5121a7bc.flag .generated_files/8bac4a0766d39c6687560ebfeb650ad7e1a6910e.flag
	@${MKDIR} "${OBJECTDIR}/src/hal/can" 
	@${RM} ${OBJECTDIR}/src/hal/can/CANConfiguration.o.d 
	@${RM} ${OBJECTDIR}/src/hal/can/CANConfiguration.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"." -I"src" -MP -MMD -MF "${OBJECTDIR}/src/hal/can/CANConfiguration.o.d" -o ${OBJECTDIR}/src/hal/can/CANConfiguration.o src/hal/can/CANConfiguration.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/src/hal/can/CANErrorFunctions.o: src/hal/can/CANErrorFunctions.c  .generated_files/ede67ca0c7f420dc46dc8328a9bf812f532eb91c.flag .generated_files/8bac4a0766d39c6687560ebfeb650ad7e1a6910e.flag
	@${MKDIR} "${OBJECTDIR}/src/hal/can" 
	@${RM} ${OBJECTDIR}/src/hal/can/CANErrorFunctions.o.d 
	@${RM} ${OBJECTDIR}/src/hal/can/CANErrorFunctions.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"." -I"src" -MP -MMD -MF "${OBJECTDIR}/src/hal/can/CANErrorFunctions.o.d" -o ${OBJECTDIR}/src/hal/can/CANErrorFunctions.o src/hal/can/CANErrorFunctions.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/src/hal/can/CANEventFunctions.o: src/hal/can/CANEventFunctions.c  .generated_files/edf212ea010e93d66b8c7b85dceb389237a44ff1.flag .generated_files/8bac4a0766d39c6687560ebfeb650ad7e1a6910e.flag
	@${MKDIR} "${OBJECTDIR}/src/hal/can" 
	@${RM} ${OBJECTDIR}/src/hal/can/CANEventFunctions.o.d 
	@${RM} ${OBJECTDIR}/src/hal/can/CANEventFunctions.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"." -I"src" -MP -MMD -MF "${OBJECTDIR}/src/hal/can/CANEventFunctions.o.d" -o ${OBJECTDIR}/src/hal/can/CANEventFunctions.o src/hal/can/CANEventFunctions.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/src/hal/can/CANFilterFunctions.o: src/hal/can/CANFilterFunctions.c  .generated_files/518937c89f0eb2fbf428d2d0401d2c1372bed82d.flag .generated_files/8bac4a0766d39c6687560ebfeb650ad7e1a6910e.flag
	@${MKDIR} "${OBJECTDIR}/src/hal/can" 
	@${RM} ${OBJECTDIR}/src/hal/can/CANFilterFunctions.o.d 
	@${RM} ${OBJECTDIR}/src/hal/can/CANFilterFunctions.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"." -I"src" -MP -MMD -MF "${OBJECTDIR}/src/hal/can/CANFilterFunctions.o.d" -o ${OBJECTDIR}/src/hal/can/CANFilterFunctions.o src/hal/can/CANFilterFunctions.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/src/hal/can/CANInfoFunctions.o: src/hal/can/CANInfoFunctions.c  .generated_files/59a651baf975f3290092184aa81bfbfc97fd1f74.flag .generated_files/8bac4a0766d39c6687560ebfeb650ad7e1a6910e.flag
	@${MKDIR} "${OBJECTDIR}/src/hal/can" 
	@${RM} ${OBJECTDIR}/src/hal/can/CANInfoFunctions.o.d 
	@${RM} ${OBJECTDIR}/src/hal/can/CANInfoFunctions.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"." -I"src" -MP -MMD -MF "${OBJECTDIR}/src/hal/can/CANInfoFunctions.o.d" -o ${OBJECTDIR}/src/hal/can/CANInfoFunctions.o src/hal/can/CANInfoFunctions.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/src/hal/can/CANReceiveFunctions.o: src/hal/can/CANReceiveFunctions.c  .generated_files/50e36f8acad2d3a885b2a0b29bc249fca1c2de99.flag .generated_files/8bac4a0766d39c6687560ebfeb650ad7e1a6910e.flag
	@${MKDIR} "${OBJECTDIR}/src/hal/can" 
	@${RM} ${OBJECTDIR}/src/hal/can/CANReceiveFunctions.o.d 
	@${RM} ${OBJECTDIR}/src/hal/can/CANReceiveFunctions.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"." -I"src" -MP -MMD -MF "${OBJECTDIR}/src/hal/can/CANReceiveFunctions.o.d" -o ${OBJECTDIR}/src/hal/can/CANReceiveFunctions.o src/hal/can/CANReceiveFunctions.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/src/hal/can/CANTransmitFunctions.o: src/hal/can/CANTransmitFunctions.c  .generated_files/d9b33676d71e222c719189658aa7516fe55e299d.flag .generated_files/8bac4a0766d39c6687560ebfeb650ad7e1a6910e.flag
	@${MKDIR} "${OBJECTDIR}/src/hal/can" 
	@${RM} ${OBJECTDIR}/src/hal/can/CANTransmitFunctions.o.d 
	@${RM} ${OBJECTDIR}/src/hal/can/CANTransmitFunctions.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"." -I"src" -MP -MMD -MF "${OBJECTDIR}/src/hal/can/CANTransmitFunctions.o.d" -o ${OBJECTDIR}/src/hal/can/CANTransmitFunctions.o src/hal/can/CANTransmitFunctions.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/src/hal/pin32.o: src/hal/pin32.c  .generated_files/478eb749dafc27d861021a2e4235471f37360ef3.flag .generated_files/8bac4a0766d39c6687560ebfeb650ad7e1a6910e.flag
	@${MKDIR} "${OBJECTDIR}/src/hal" 
	@${RM} ${OBJECTDIR}/src/hal/pin32.o.d 
	@${RM} ${OBJECTDIR}/src/hal/pin32.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"." -I"src" -MP -MMD -MF "${OBJECTDIR}/src/hal/pin32.o.d" -o ${OBJECTDIR}/src/hal/pin32.o src/hal/pin32.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/src/hal/uart32mx.o: src/hal/uart32mx.c  .generated_files/425c84e22ad1ba35a86c3ddad0d3adfb47c94837.flag .generated_files/8bac4a0766d39c6687560ebfeb650ad7e1a6910e.flag
	@${MKDIR} "${OBJECTDIR}/src/hal" 
	@${RM} ${OBJECTDIR}/src/hal/uart32mx.o.d 
	@${RM} ${OBJECTDIR}/src/hal/uart32mx.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"." -I"src" -MP -MMD -MF "${OBJECTDIR}/src/hal/uart32mx.o.d" -o ${OBJECTDIR}/src/hal/uart32mx.o src/hal/uart32mx.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/mcc_generated_files/interrupt_manager.o: mcc_generated_files/interrupt_manager.c  .generated_files/7e2ec6fd488caa2bd64a1615b6b82e18ed234b43.flag .generated_files/8bac4a0766d39c6687560ebfeb650ad7e1a6910e.flag
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/interrupt_manager.o.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/interrupt_manager.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"." -I"src" -MP -MMD -MF "${OBJECTDIR}/mcc_generated_files/interrupt_manager.o.d" -o ${OBJECTDIR}/mcc_generated_files/interrupt_manager.o mcc_generated_files/interrupt_manager.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/mcc_generated_files/mcc.o: mcc_generated_files/mcc.c  .generated_files/5564aed3ab405f759b4b46eac8a4ab863faf6aa0.flag .generated_files/8bac4a0766d39c6687560ebfeb650ad7e1a6910e.flag
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/mcc.o.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/mcc.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"." -I"src" -MP -MMD -MF "${OBJECTDIR}/mcc_generated_files/mcc.o.d" -o ${OBJECTDIR}/mcc_generated_files/mcc.o mcc_generated_files/mcc.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/mcc_generated_files/pin_manager.o: mcc_generated_files/pin_manager.c  .generated_files/b5dbee45ebd8ab0dc2bc5c2fa0faf2fe85b812ad.flag .generated_files/8bac4a0766d39c6687560ebfeb650ad7e1a6910e.flag
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/pin_manager.o.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/pin_manager.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"." -I"src" -MP -MMD -MF "${OBJECTDIR}/mcc_generated_files/pin_manager.o.d" -o ${OBJECTDIR}/mcc_generated_files/pin_manager.o mcc_generated_files/pin_manager.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/mcc_generated_files/tmr2.o: mcc_generated_files/tmr2.c  .generated_files/cd49acb3be29c2e2f98cb908d724f97a2a8ec259.flag .generated_files/8bac4a0766d39c6687560ebfeb650ad7e1a6910e.flag
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/tmr2.o.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/tmr2.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"." -I"src" -MP -MMD -MF "${OBJECTDIR}/mcc_generated_files/tmr2.o.d" -o ${OBJECTDIR}/mcc_generated_files/tmr2.o mcc_generated_files/tmr2.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/mcc_generated_files/uart1.o: mcc_generated_files/uart1.c  .generated_files/909df5f49dc1df8a4c6b6c7f79d77180598bf6f6.flag .generated_files/8bac4a0766d39c6687560ebfeb650ad7e1a6910e.flag
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/uart1.o.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/uart1.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"." -I"src" -MP -MMD -MF "${OBJECTDIR}/mcc_generated_files/uart1.o.d" -o ${OBJECTDIR}/mcc_generated_files/uart1.o mcc_generated_files/uart1.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/mcc_generated_files/adc1.o: mcc_generated_files/adc1.c  .generated_files/f50a36baf68619ae984eb31f740a8df246fbf2ff.flag .generated_files/8bac4a0766d39c6687560ebfeb650ad7e1a6910e.flag
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/adc1.o.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/adc1.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"." -I"src" -MP -MMD -MF "${OBJECTDIR}/mcc_generated_files/adc1.o.d" -o ${OBJECTDIR}/mcc_generated_files/adc1.o mcc_generated_files/adc1.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/mcc_generated_files/tmr1.o: mcc_generated_files/tmr1.c  .generated_files/fec8ccfd264beb9104d6dde4ab88aeac57257812.flag .generated_files/8bac4a0766d39c6687560ebfeb650ad7e1a6910e.flag
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/tmr1.o.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/tmr1.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"." -I"src" -MP -MMD -MF "${OBJECTDIR}/mcc_generated_files/tmr1.o.d" -o ${OBJECTDIR}/mcc_generated_files/tmr1.o mcc_generated_files/tmr1.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/src/sas/debug.o: src/sas/debug.c  .generated_files/5823029436e98498fb9493b0f5fca307bea8a6a6.flag .generated_files/8bac4a0766d39c6687560ebfeb650ad7e1a6910e.flag
	@${MKDIR} "${OBJECTDIR}/src/sas" 
	@${RM} ${OBJECTDIR}/src/sas/debug.o.d 
	@${RM} ${OBJECTDIR}/src/sas/debug.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"." -I"src" -MP -MMD -MF "${OBJECTDIR}/src/sas/debug.o.d" -o ${OBJECTDIR}/src/sas/debug.o src/sas/debug.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/src/sas/pulse.o: src/sas/pulse.c  .generated_files/d7b180982af65a606002ee6226f42f520f979beb.flag .generated_files/8bac4a0766d39c6687560ebfeb650ad7e1a6910e.flag
	@${MKDIR} "${OBJECTDIR}/src/sas" 
	@${RM} ${OBJECTDIR}/src/sas/pulse.o.d 
	@${RM} ${OBJECTDIR}/src/sas/pulse.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"." -I"src" -MP -MMD -MF "${OBJECTDIR}/src/sas/pulse.o.d" -o ${OBJECTDIR}/src/sas/pulse.o src/sas/pulse.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/src/sas/timer.o: src/sas/timer.c  .generated_files/5bf559a456f3c9c25bcd2cad36e7a4181e178e06.flag .generated_files/8bac4a0766d39c6687560ebfeb650ad7e1a6910e.flag
	@${MKDIR} "${OBJECTDIR}/src/sas" 
	@${RM} ${OBJECTDIR}/src/sas/timer.o.d 
	@${RM} ${OBJECTDIR}/src/sas/timer.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"." -I"src" -MP -MMD -MF "${OBJECTDIR}/src/sas/timer.o.d" -o ${OBJECTDIR}/src/sas/timer.o src/sas/timer.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/src/ssl/bulbctrl.o: src/ssl/bulbctrl.c  .generated_files/e1f9167e0dc0b878ff8b4c9c0baea495d0fc8252.flag .generated_files/8bac4a0766d39c6687560ebfeb650ad7e1a6910e.flag
	@${MKDIR} "${OBJECTDIR}/src/ssl" 
	@${RM} ${OBJECTDIR}/src/ssl/bulbctrl.o.d 
	@${RM} ${OBJECTDIR}/src/ssl/bulbctrl.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"." -I"src" -MP -MMD -MF "${OBJECTDIR}/src/ssl/bulbctrl.o.d" -o ${OBJECTDIR}/src/ssl/bulbctrl.o src/ssl/bulbctrl.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/src/ssl/canbus.o: src/ssl/canbus.c  .generated_files/bf5d851e887fcaa3538fd88b41e7bed821215e56.flag .generated_files/8bac4a0766d39c6687560ebfeb650ad7e1a6910e.flag
	@${MKDIR} "${OBJECTDIR}/src/ssl" 
	@${RM} ${OBJECTDIR}/src/ssl/canbus.o.d 
	@${RM} ${OBJECTDIR}/src/ssl/canbus.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"." -I"src" -MP -MMD -MF "${OBJECTDIR}/src/ssl/canbus.o.d" -o ${OBJECTDIR}/src/ssl/canbus.o src/ssl/canbus.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/main.o: main.c  .generated_files/22994367979014b298df92bb7134ceaa1a08c4b4.flag .generated_files/8bac4a0766d39c6687560ebfeb650ad7e1a6910e.flag
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/main.o.d 
	@${RM} ${OBJECTDIR}/main.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"." -I"src" -MP -MMD -MF "${OBJECTDIR}/main.o.d" -o ${OBJECTDIR}/main.o main.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: compileCPP
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: link
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
dist/${CND_CONF}/${IMAGE_TYPE}/GwOutputCard_v5.0.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk    
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE) -g   -mprocessor=$(MP_PROCESSOR_OPTION)  -o dist/${CND_CONF}/${IMAGE_TYPE}/GwOutputCard_v5.0.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX} ${OBJECTFILES_QUOTED_IF_SPACED}          -DXPRJ_default=$(CND_CONF)  -legacy-libc  -std=gnu99 $(COMPARISON_BUILD)   -mreserve=data@0x0:0x1FC -mreserve=boot@0x1FC00490:0x1FC00BEF  -Wl,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_LD_POST)$(MP_LINKER_FILE_OPTION),--defsym=__MPLAB_DEBUG=1,--defsym=__DEBUG=1,-D=__DEBUG_D,--no-code-in-dinit,--no-dinit-in-serial-mem,-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map",--memorysummary,dist/${CND_CONF}/${IMAGE_TYPE}/memoryfile.xml -mdfp="${DFP_DIR}"
	
else
dist/${CND_CONF}/${IMAGE_TYPE}/GwOutputCard_v5.0.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk   
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE)  -mprocessor=$(MP_PROCESSOR_OPTION)  -o dist/${CND_CONF}/${IMAGE_TYPE}/GwOutputCard_v5.0.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} ${OBJECTFILES_QUOTED_IF_SPACED}          -DXPRJ_default=$(CND_CONF)  -legacy-libc  -std=gnu99 $(COMPARISON_BUILD)  -Wl,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_LD_POST)$(MP_LINKER_FILE_OPTION),--no-code-in-dinit,--no-dinit-in-serial-mem,-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map",--memorysummary,dist/${CND_CONF}/${IMAGE_TYPE}/memoryfile.xml -mdfp="${DFP_DIR}"
	${MP_CC_DIR}\\xc32-bin2hex dist/${CND_CONF}/${IMAGE_TYPE}/GwOutputCard_v5.0.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} 
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
