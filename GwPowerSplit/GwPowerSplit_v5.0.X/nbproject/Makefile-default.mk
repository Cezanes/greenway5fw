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
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/GwPowerSplit_v5.0.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
else
IMAGE_TYPE=production
OUTPUT_SUFFIX=hex
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/GwPowerSplit_v5.0.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
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
SOURCEFILES_QUOTED_IF_SPACED=src/app/hostctrl.c src/app/logic.c src/cfg/app_config.c src/cfg/hw_config.c src/hal/can/CANConfiguration.c src/hal/can/CANErrorFunctions.c src/hal/can/CANEventFunctions.c src/hal/can/CANFilterFunctions.c src/hal/can/CANInfoFunctions.c src/hal/can/CANReceiveFunctions.c src/hal/can/CANTransmitFunctions.c src/hal/pin32.c src/hal/uart32mx.c mcc_generated_files/interrupt_manager.c mcc_generated_files/mcc.c mcc_generated_files/pin_manager.c mcc_generated_files/tmr2.c mcc_generated_files/uart1.c src/sas/debug.c src/sas/pulse.c src/sas/timer.c src/ssl/bulbctrl.c src/ssl/canbus.c main.c

# Object Files Quoted if spaced
OBJECTFILES_QUOTED_IF_SPACED=${OBJECTDIR}/src/app/hostctrl.o ${OBJECTDIR}/src/app/logic.o ${OBJECTDIR}/src/cfg/app_config.o ${OBJECTDIR}/src/cfg/hw_config.o ${OBJECTDIR}/src/hal/can/CANConfiguration.o ${OBJECTDIR}/src/hal/can/CANErrorFunctions.o ${OBJECTDIR}/src/hal/can/CANEventFunctions.o ${OBJECTDIR}/src/hal/can/CANFilterFunctions.o ${OBJECTDIR}/src/hal/can/CANInfoFunctions.o ${OBJECTDIR}/src/hal/can/CANReceiveFunctions.o ${OBJECTDIR}/src/hal/can/CANTransmitFunctions.o ${OBJECTDIR}/src/hal/pin32.o ${OBJECTDIR}/src/hal/uart32mx.o ${OBJECTDIR}/mcc_generated_files/interrupt_manager.o ${OBJECTDIR}/mcc_generated_files/mcc.o ${OBJECTDIR}/mcc_generated_files/pin_manager.o ${OBJECTDIR}/mcc_generated_files/tmr2.o ${OBJECTDIR}/mcc_generated_files/uart1.o ${OBJECTDIR}/src/sas/debug.o ${OBJECTDIR}/src/sas/pulse.o ${OBJECTDIR}/src/sas/timer.o ${OBJECTDIR}/src/ssl/bulbctrl.o ${OBJECTDIR}/src/ssl/canbus.o ${OBJECTDIR}/main.o
POSSIBLE_DEPFILES=${OBJECTDIR}/src/app/hostctrl.o.d ${OBJECTDIR}/src/app/logic.o.d ${OBJECTDIR}/src/cfg/app_config.o.d ${OBJECTDIR}/src/cfg/hw_config.o.d ${OBJECTDIR}/src/hal/can/CANConfiguration.o.d ${OBJECTDIR}/src/hal/can/CANErrorFunctions.o.d ${OBJECTDIR}/src/hal/can/CANEventFunctions.o.d ${OBJECTDIR}/src/hal/can/CANFilterFunctions.o.d ${OBJECTDIR}/src/hal/can/CANInfoFunctions.o.d ${OBJECTDIR}/src/hal/can/CANReceiveFunctions.o.d ${OBJECTDIR}/src/hal/can/CANTransmitFunctions.o.d ${OBJECTDIR}/src/hal/pin32.o.d ${OBJECTDIR}/src/hal/uart32mx.o.d ${OBJECTDIR}/mcc_generated_files/interrupt_manager.o.d ${OBJECTDIR}/mcc_generated_files/mcc.o.d ${OBJECTDIR}/mcc_generated_files/pin_manager.o.d ${OBJECTDIR}/mcc_generated_files/tmr2.o.d ${OBJECTDIR}/mcc_generated_files/uart1.o.d ${OBJECTDIR}/src/sas/debug.o.d ${OBJECTDIR}/src/sas/pulse.o.d ${OBJECTDIR}/src/sas/timer.o.d ${OBJECTDIR}/src/ssl/bulbctrl.o.d ${OBJECTDIR}/src/ssl/canbus.o.d ${OBJECTDIR}/main.o.d

# Object Files
OBJECTFILES=${OBJECTDIR}/src/app/hostctrl.o ${OBJECTDIR}/src/app/logic.o ${OBJECTDIR}/src/cfg/app_config.o ${OBJECTDIR}/src/cfg/hw_config.o ${OBJECTDIR}/src/hal/can/CANConfiguration.o ${OBJECTDIR}/src/hal/can/CANErrorFunctions.o ${OBJECTDIR}/src/hal/can/CANEventFunctions.o ${OBJECTDIR}/src/hal/can/CANFilterFunctions.o ${OBJECTDIR}/src/hal/can/CANInfoFunctions.o ${OBJECTDIR}/src/hal/can/CANReceiveFunctions.o ${OBJECTDIR}/src/hal/can/CANTransmitFunctions.o ${OBJECTDIR}/src/hal/pin32.o ${OBJECTDIR}/src/hal/uart32mx.o ${OBJECTDIR}/mcc_generated_files/interrupt_manager.o ${OBJECTDIR}/mcc_generated_files/mcc.o ${OBJECTDIR}/mcc_generated_files/pin_manager.o ${OBJECTDIR}/mcc_generated_files/tmr2.o ${OBJECTDIR}/mcc_generated_files/uart1.o ${OBJECTDIR}/src/sas/debug.o ${OBJECTDIR}/src/sas/pulse.o ${OBJECTDIR}/src/sas/timer.o ${OBJECTDIR}/src/ssl/bulbctrl.o ${OBJECTDIR}/src/ssl/canbus.o ${OBJECTDIR}/main.o

# Source Files
SOURCEFILES=src/app/hostctrl.c src/app/logic.c src/cfg/app_config.c src/cfg/hw_config.c src/hal/can/CANConfiguration.c src/hal/can/CANErrorFunctions.c src/hal/can/CANEventFunctions.c src/hal/can/CANFilterFunctions.c src/hal/can/CANInfoFunctions.c src/hal/can/CANReceiveFunctions.c src/hal/can/CANTransmitFunctions.c src/hal/pin32.c src/hal/uart32mx.c mcc_generated_files/interrupt_manager.c mcc_generated_files/mcc.c mcc_generated_files/pin_manager.c mcc_generated_files/tmr2.c mcc_generated_files/uart1.c src/sas/debug.c src/sas/pulse.c src/sas/timer.c src/ssl/bulbctrl.c src/ssl/canbus.c main.c



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
	${MAKE}  -f nbproject/Makefile-default.mk dist/${CND_CONF}/${IMAGE_TYPE}/GwPowerSplit_v5.0.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}

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
${OBJECTDIR}/src/app/hostctrl.o: src/app/hostctrl.c  .generated_files/38adba3ae0c07d83b9e46f4c8add8773a021fbed.flag .generated_files/8bac4a0766d39c6687560ebfeb650ad7e1a6910e.flag
	@${MKDIR} "${OBJECTDIR}/src/app" 
	@${RM} ${OBJECTDIR}/src/app/hostctrl.o.d 
	@${RM} ${OBJECTDIR}/src/app/hostctrl.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"." -I"src" -MP -MMD -MF "${OBJECTDIR}/src/app/hostctrl.o.d" -o ${OBJECTDIR}/src/app/hostctrl.o src/app/hostctrl.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/src/app/logic.o: src/app/logic.c  .generated_files/14965b0d291c4a484fda8591e1a834e32ea957f3.flag .generated_files/8bac4a0766d39c6687560ebfeb650ad7e1a6910e.flag
	@${MKDIR} "${OBJECTDIR}/src/app" 
	@${RM} ${OBJECTDIR}/src/app/logic.o.d 
	@${RM} ${OBJECTDIR}/src/app/logic.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"." -I"src" -MP -MMD -MF "${OBJECTDIR}/src/app/logic.o.d" -o ${OBJECTDIR}/src/app/logic.o src/app/logic.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/src/cfg/app_config.o: src/cfg/app_config.c  .generated_files/3d4e3f219056e03bfc20a22b6ab98cb53cfea38e.flag .generated_files/8bac4a0766d39c6687560ebfeb650ad7e1a6910e.flag
	@${MKDIR} "${OBJECTDIR}/src/cfg" 
	@${RM} ${OBJECTDIR}/src/cfg/app_config.o.d 
	@${RM} ${OBJECTDIR}/src/cfg/app_config.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"." -I"src" -MP -MMD -MF "${OBJECTDIR}/src/cfg/app_config.o.d" -o ${OBJECTDIR}/src/cfg/app_config.o src/cfg/app_config.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/src/cfg/hw_config.o: src/cfg/hw_config.c  .generated_files/d98095eae6c3eb45212995ab8e211f03d01983e3.flag .generated_files/8bac4a0766d39c6687560ebfeb650ad7e1a6910e.flag
	@${MKDIR} "${OBJECTDIR}/src/cfg" 
	@${RM} ${OBJECTDIR}/src/cfg/hw_config.o.d 
	@${RM} ${OBJECTDIR}/src/cfg/hw_config.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"." -I"src" -MP -MMD -MF "${OBJECTDIR}/src/cfg/hw_config.o.d" -o ${OBJECTDIR}/src/cfg/hw_config.o src/cfg/hw_config.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/src/hal/can/CANConfiguration.o: src/hal/can/CANConfiguration.c  .generated_files/ec008e0891e7121648d0496963b747885b1ad34b.flag .generated_files/8bac4a0766d39c6687560ebfeb650ad7e1a6910e.flag
	@${MKDIR} "${OBJECTDIR}/src/hal/can" 
	@${RM} ${OBJECTDIR}/src/hal/can/CANConfiguration.o.d 
	@${RM} ${OBJECTDIR}/src/hal/can/CANConfiguration.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"." -I"src" -MP -MMD -MF "${OBJECTDIR}/src/hal/can/CANConfiguration.o.d" -o ${OBJECTDIR}/src/hal/can/CANConfiguration.o src/hal/can/CANConfiguration.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/src/hal/can/CANErrorFunctions.o: src/hal/can/CANErrorFunctions.c  .generated_files/e124d071d716f190fc32f6ff9e0efcdf36f4d96c.flag .generated_files/8bac4a0766d39c6687560ebfeb650ad7e1a6910e.flag
	@${MKDIR} "${OBJECTDIR}/src/hal/can" 
	@${RM} ${OBJECTDIR}/src/hal/can/CANErrorFunctions.o.d 
	@${RM} ${OBJECTDIR}/src/hal/can/CANErrorFunctions.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"." -I"src" -MP -MMD -MF "${OBJECTDIR}/src/hal/can/CANErrorFunctions.o.d" -o ${OBJECTDIR}/src/hal/can/CANErrorFunctions.o src/hal/can/CANErrorFunctions.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/src/hal/can/CANEventFunctions.o: src/hal/can/CANEventFunctions.c  .generated_files/28cccf1fbb26fdcfa79507b56f4487deb036e86b.flag .generated_files/8bac4a0766d39c6687560ebfeb650ad7e1a6910e.flag
	@${MKDIR} "${OBJECTDIR}/src/hal/can" 
	@${RM} ${OBJECTDIR}/src/hal/can/CANEventFunctions.o.d 
	@${RM} ${OBJECTDIR}/src/hal/can/CANEventFunctions.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"." -I"src" -MP -MMD -MF "${OBJECTDIR}/src/hal/can/CANEventFunctions.o.d" -o ${OBJECTDIR}/src/hal/can/CANEventFunctions.o src/hal/can/CANEventFunctions.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/src/hal/can/CANFilterFunctions.o: src/hal/can/CANFilterFunctions.c  .generated_files/7dc5392b4406e20415e299c319b634226f8ddd81.flag .generated_files/8bac4a0766d39c6687560ebfeb650ad7e1a6910e.flag
	@${MKDIR} "${OBJECTDIR}/src/hal/can" 
	@${RM} ${OBJECTDIR}/src/hal/can/CANFilterFunctions.o.d 
	@${RM} ${OBJECTDIR}/src/hal/can/CANFilterFunctions.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"." -I"src" -MP -MMD -MF "${OBJECTDIR}/src/hal/can/CANFilterFunctions.o.d" -o ${OBJECTDIR}/src/hal/can/CANFilterFunctions.o src/hal/can/CANFilterFunctions.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/src/hal/can/CANInfoFunctions.o: src/hal/can/CANInfoFunctions.c  .generated_files/78ae8137cb2a568f75d940b382c0d8c7029d976.flag .generated_files/8bac4a0766d39c6687560ebfeb650ad7e1a6910e.flag
	@${MKDIR} "${OBJECTDIR}/src/hal/can" 
	@${RM} ${OBJECTDIR}/src/hal/can/CANInfoFunctions.o.d 
	@${RM} ${OBJECTDIR}/src/hal/can/CANInfoFunctions.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"." -I"src" -MP -MMD -MF "${OBJECTDIR}/src/hal/can/CANInfoFunctions.o.d" -o ${OBJECTDIR}/src/hal/can/CANInfoFunctions.o src/hal/can/CANInfoFunctions.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/src/hal/can/CANReceiveFunctions.o: src/hal/can/CANReceiveFunctions.c  .generated_files/eae6d2a6e77f368ee4fb4213d057019370d75c5c.flag .generated_files/8bac4a0766d39c6687560ebfeb650ad7e1a6910e.flag
	@${MKDIR} "${OBJECTDIR}/src/hal/can" 
	@${RM} ${OBJECTDIR}/src/hal/can/CANReceiveFunctions.o.d 
	@${RM} ${OBJECTDIR}/src/hal/can/CANReceiveFunctions.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"." -I"src" -MP -MMD -MF "${OBJECTDIR}/src/hal/can/CANReceiveFunctions.o.d" -o ${OBJECTDIR}/src/hal/can/CANReceiveFunctions.o src/hal/can/CANReceiveFunctions.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/src/hal/can/CANTransmitFunctions.o: src/hal/can/CANTransmitFunctions.c  .generated_files/5a383d7b9e923e495e4e5d84c7b0a8f4de64637a.flag .generated_files/8bac4a0766d39c6687560ebfeb650ad7e1a6910e.flag
	@${MKDIR} "${OBJECTDIR}/src/hal/can" 
	@${RM} ${OBJECTDIR}/src/hal/can/CANTransmitFunctions.o.d 
	@${RM} ${OBJECTDIR}/src/hal/can/CANTransmitFunctions.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"." -I"src" -MP -MMD -MF "${OBJECTDIR}/src/hal/can/CANTransmitFunctions.o.d" -o ${OBJECTDIR}/src/hal/can/CANTransmitFunctions.o src/hal/can/CANTransmitFunctions.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/src/hal/pin32.o: src/hal/pin32.c  .generated_files/d5a194853ec934af5f00196dc2172fc4f9035199.flag .generated_files/8bac4a0766d39c6687560ebfeb650ad7e1a6910e.flag
	@${MKDIR} "${OBJECTDIR}/src/hal" 
	@${RM} ${OBJECTDIR}/src/hal/pin32.o.d 
	@${RM} ${OBJECTDIR}/src/hal/pin32.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"." -I"src" -MP -MMD -MF "${OBJECTDIR}/src/hal/pin32.o.d" -o ${OBJECTDIR}/src/hal/pin32.o src/hal/pin32.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/src/hal/uart32mx.o: src/hal/uart32mx.c  .generated_files/ffe32fb9b2d95a4e250cec69c34f9838194982d0.flag .generated_files/8bac4a0766d39c6687560ebfeb650ad7e1a6910e.flag
	@${MKDIR} "${OBJECTDIR}/src/hal" 
	@${RM} ${OBJECTDIR}/src/hal/uart32mx.o.d 
	@${RM} ${OBJECTDIR}/src/hal/uart32mx.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"." -I"src" -MP -MMD -MF "${OBJECTDIR}/src/hal/uart32mx.o.d" -o ${OBJECTDIR}/src/hal/uart32mx.o src/hal/uart32mx.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/mcc_generated_files/interrupt_manager.o: mcc_generated_files/interrupt_manager.c  .generated_files/1294cf87d24e20bb8dd1f65036c6d1b83d1fcff7.flag .generated_files/8bac4a0766d39c6687560ebfeb650ad7e1a6910e.flag
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/interrupt_manager.o.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/interrupt_manager.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"." -I"src" -MP -MMD -MF "${OBJECTDIR}/mcc_generated_files/interrupt_manager.o.d" -o ${OBJECTDIR}/mcc_generated_files/interrupt_manager.o mcc_generated_files/interrupt_manager.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/mcc_generated_files/mcc.o: mcc_generated_files/mcc.c  .generated_files/93818cfb8b940a86d10c66ed28879b515032fdf3.flag .generated_files/8bac4a0766d39c6687560ebfeb650ad7e1a6910e.flag
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/mcc.o.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/mcc.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"." -I"src" -MP -MMD -MF "${OBJECTDIR}/mcc_generated_files/mcc.o.d" -o ${OBJECTDIR}/mcc_generated_files/mcc.o mcc_generated_files/mcc.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/mcc_generated_files/pin_manager.o: mcc_generated_files/pin_manager.c  .generated_files/fe4964d338a3ae91bd2327d02ff64422bcebc04a.flag .generated_files/8bac4a0766d39c6687560ebfeb650ad7e1a6910e.flag
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/pin_manager.o.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/pin_manager.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"." -I"src" -MP -MMD -MF "${OBJECTDIR}/mcc_generated_files/pin_manager.o.d" -o ${OBJECTDIR}/mcc_generated_files/pin_manager.o mcc_generated_files/pin_manager.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/mcc_generated_files/tmr2.o: mcc_generated_files/tmr2.c  .generated_files/735e75f415eee8db3543a08f64127faa003a9170.flag .generated_files/8bac4a0766d39c6687560ebfeb650ad7e1a6910e.flag
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/tmr2.o.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/tmr2.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"." -I"src" -MP -MMD -MF "${OBJECTDIR}/mcc_generated_files/tmr2.o.d" -o ${OBJECTDIR}/mcc_generated_files/tmr2.o mcc_generated_files/tmr2.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/mcc_generated_files/uart1.o: mcc_generated_files/uart1.c  .generated_files/9c9c479f22d4b9b069840e4a644dd74795da2e22.flag .generated_files/8bac4a0766d39c6687560ebfeb650ad7e1a6910e.flag
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/uart1.o.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/uart1.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"." -I"src" -MP -MMD -MF "${OBJECTDIR}/mcc_generated_files/uart1.o.d" -o ${OBJECTDIR}/mcc_generated_files/uart1.o mcc_generated_files/uart1.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/src/sas/debug.o: src/sas/debug.c  .generated_files/aaffc51fe1858ffbf9574b2434b5108fe09887d7.flag .generated_files/8bac4a0766d39c6687560ebfeb650ad7e1a6910e.flag
	@${MKDIR} "${OBJECTDIR}/src/sas" 
	@${RM} ${OBJECTDIR}/src/sas/debug.o.d 
	@${RM} ${OBJECTDIR}/src/sas/debug.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"." -I"src" -MP -MMD -MF "${OBJECTDIR}/src/sas/debug.o.d" -o ${OBJECTDIR}/src/sas/debug.o src/sas/debug.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/src/sas/pulse.o: src/sas/pulse.c  .generated_files/f4dc0004b77b88a1a1e63fb5217e281f3d407065.flag .generated_files/8bac4a0766d39c6687560ebfeb650ad7e1a6910e.flag
	@${MKDIR} "${OBJECTDIR}/src/sas" 
	@${RM} ${OBJECTDIR}/src/sas/pulse.o.d 
	@${RM} ${OBJECTDIR}/src/sas/pulse.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"." -I"src" -MP -MMD -MF "${OBJECTDIR}/src/sas/pulse.o.d" -o ${OBJECTDIR}/src/sas/pulse.o src/sas/pulse.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/src/sas/timer.o: src/sas/timer.c  .generated_files/10af51eae84388e9b97438b692e6ee1229303f50.flag .generated_files/8bac4a0766d39c6687560ebfeb650ad7e1a6910e.flag
	@${MKDIR} "${OBJECTDIR}/src/sas" 
	@${RM} ${OBJECTDIR}/src/sas/timer.o.d 
	@${RM} ${OBJECTDIR}/src/sas/timer.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"." -I"src" -MP -MMD -MF "${OBJECTDIR}/src/sas/timer.o.d" -o ${OBJECTDIR}/src/sas/timer.o src/sas/timer.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/src/ssl/bulbctrl.o: src/ssl/bulbctrl.c  .generated_files/a508c03586477648863592d60350b487f82695ef.flag .generated_files/8bac4a0766d39c6687560ebfeb650ad7e1a6910e.flag
	@${MKDIR} "${OBJECTDIR}/src/ssl" 
	@${RM} ${OBJECTDIR}/src/ssl/bulbctrl.o.d 
	@${RM} ${OBJECTDIR}/src/ssl/bulbctrl.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"." -I"src" -MP -MMD -MF "${OBJECTDIR}/src/ssl/bulbctrl.o.d" -o ${OBJECTDIR}/src/ssl/bulbctrl.o src/ssl/bulbctrl.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/src/ssl/canbus.o: src/ssl/canbus.c  .generated_files/b0ea9fe8830edaa1f85975297da2cb3ba241c6ba.flag .generated_files/8bac4a0766d39c6687560ebfeb650ad7e1a6910e.flag
	@${MKDIR} "${OBJECTDIR}/src/ssl" 
	@${RM} ${OBJECTDIR}/src/ssl/canbus.o.d 
	@${RM} ${OBJECTDIR}/src/ssl/canbus.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"." -I"src" -MP -MMD -MF "${OBJECTDIR}/src/ssl/canbus.o.d" -o ${OBJECTDIR}/src/ssl/canbus.o src/ssl/canbus.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/main.o: main.c  .generated_files/3b893c2bbdb41aea808e0b02187f946914f13cc.flag .generated_files/8bac4a0766d39c6687560ebfeb650ad7e1a6910e.flag
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/main.o.d 
	@${RM} ${OBJECTDIR}/main.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"." -I"src" -MP -MMD -MF "${OBJECTDIR}/main.o.d" -o ${OBJECTDIR}/main.o main.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	
else
${OBJECTDIR}/src/app/hostctrl.o: src/app/hostctrl.c  .generated_files/3d3f0293918002cee4dc67fe9420411c7aaf9157.flag .generated_files/8bac4a0766d39c6687560ebfeb650ad7e1a6910e.flag
	@${MKDIR} "${OBJECTDIR}/src/app" 
	@${RM} ${OBJECTDIR}/src/app/hostctrl.o.d 
	@${RM} ${OBJECTDIR}/src/app/hostctrl.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"." -I"src" -MP -MMD -MF "${OBJECTDIR}/src/app/hostctrl.o.d" -o ${OBJECTDIR}/src/app/hostctrl.o src/app/hostctrl.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/src/app/logic.o: src/app/logic.c  .generated_files/74fc3929e056ceda02174dab96ada9947c040ae5.flag .generated_files/8bac4a0766d39c6687560ebfeb650ad7e1a6910e.flag
	@${MKDIR} "${OBJECTDIR}/src/app" 
	@${RM} ${OBJECTDIR}/src/app/logic.o.d 
	@${RM} ${OBJECTDIR}/src/app/logic.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"." -I"src" -MP -MMD -MF "${OBJECTDIR}/src/app/logic.o.d" -o ${OBJECTDIR}/src/app/logic.o src/app/logic.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/src/cfg/app_config.o: src/cfg/app_config.c  .generated_files/986f63c8ce32a980102ee0a82c7785b9652788b1.flag .generated_files/8bac4a0766d39c6687560ebfeb650ad7e1a6910e.flag
	@${MKDIR} "${OBJECTDIR}/src/cfg" 
	@${RM} ${OBJECTDIR}/src/cfg/app_config.o.d 
	@${RM} ${OBJECTDIR}/src/cfg/app_config.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"." -I"src" -MP -MMD -MF "${OBJECTDIR}/src/cfg/app_config.o.d" -o ${OBJECTDIR}/src/cfg/app_config.o src/cfg/app_config.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/src/cfg/hw_config.o: src/cfg/hw_config.c  .generated_files/faa683fa1be5055057f951f61e30046f5171a84a.flag .generated_files/8bac4a0766d39c6687560ebfeb650ad7e1a6910e.flag
	@${MKDIR} "${OBJECTDIR}/src/cfg" 
	@${RM} ${OBJECTDIR}/src/cfg/hw_config.o.d 
	@${RM} ${OBJECTDIR}/src/cfg/hw_config.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"." -I"src" -MP -MMD -MF "${OBJECTDIR}/src/cfg/hw_config.o.d" -o ${OBJECTDIR}/src/cfg/hw_config.o src/cfg/hw_config.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/src/hal/can/CANConfiguration.o: src/hal/can/CANConfiguration.c  .generated_files/a80668a4e6d06444ab4fa60be69312d75fbedee5.flag .generated_files/8bac4a0766d39c6687560ebfeb650ad7e1a6910e.flag
	@${MKDIR} "${OBJECTDIR}/src/hal/can" 
	@${RM} ${OBJECTDIR}/src/hal/can/CANConfiguration.o.d 
	@${RM} ${OBJECTDIR}/src/hal/can/CANConfiguration.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"." -I"src" -MP -MMD -MF "${OBJECTDIR}/src/hal/can/CANConfiguration.o.d" -o ${OBJECTDIR}/src/hal/can/CANConfiguration.o src/hal/can/CANConfiguration.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/src/hal/can/CANErrorFunctions.o: src/hal/can/CANErrorFunctions.c  .generated_files/e8a5983c7c2a4f08c0947a201d78b4029f9aab2a.flag .generated_files/8bac4a0766d39c6687560ebfeb650ad7e1a6910e.flag
	@${MKDIR} "${OBJECTDIR}/src/hal/can" 
	@${RM} ${OBJECTDIR}/src/hal/can/CANErrorFunctions.o.d 
	@${RM} ${OBJECTDIR}/src/hal/can/CANErrorFunctions.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"." -I"src" -MP -MMD -MF "${OBJECTDIR}/src/hal/can/CANErrorFunctions.o.d" -o ${OBJECTDIR}/src/hal/can/CANErrorFunctions.o src/hal/can/CANErrorFunctions.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/src/hal/can/CANEventFunctions.o: src/hal/can/CANEventFunctions.c  .generated_files/99fa1b95bdf40473924804227a44cb6636de18f9.flag .generated_files/8bac4a0766d39c6687560ebfeb650ad7e1a6910e.flag
	@${MKDIR} "${OBJECTDIR}/src/hal/can" 
	@${RM} ${OBJECTDIR}/src/hal/can/CANEventFunctions.o.d 
	@${RM} ${OBJECTDIR}/src/hal/can/CANEventFunctions.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"." -I"src" -MP -MMD -MF "${OBJECTDIR}/src/hal/can/CANEventFunctions.o.d" -o ${OBJECTDIR}/src/hal/can/CANEventFunctions.o src/hal/can/CANEventFunctions.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/src/hal/can/CANFilterFunctions.o: src/hal/can/CANFilterFunctions.c  .generated_files/f60ef358e93a8be1203ad7afd70c968c42cce307.flag .generated_files/8bac4a0766d39c6687560ebfeb650ad7e1a6910e.flag
	@${MKDIR} "${OBJECTDIR}/src/hal/can" 
	@${RM} ${OBJECTDIR}/src/hal/can/CANFilterFunctions.o.d 
	@${RM} ${OBJECTDIR}/src/hal/can/CANFilterFunctions.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"." -I"src" -MP -MMD -MF "${OBJECTDIR}/src/hal/can/CANFilterFunctions.o.d" -o ${OBJECTDIR}/src/hal/can/CANFilterFunctions.o src/hal/can/CANFilterFunctions.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/src/hal/can/CANInfoFunctions.o: src/hal/can/CANInfoFunctions.c  .generated_files/ed3ff46842624609d7020a08a6716eecf62c77d0.flag .generated_files/8bac4a0766d39c6687560ebfeb650ad7e1a6910e.flag
	@${MKDIR} "${OBJECTDIR}/src/hal/can" 
	@${RM} ${OBJECTDIR}/src/hal/can/CANInfoFunctions.o.d 
	@${RM} ${OBJECTDIR}/src/hal/can/CANInfoFunctions.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"." -I"src" -MP -MMD -MF "${OBJECTDIR}/src/hal/can/CANInfoFunctions.o.d" -o ${OBJECTDIR}/src/hal/can/CANInfoFunctions.o src/hal/can/CANInfoFunctions.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/src/hal/can/CANReceiveFunctions.o: src/hal/can/CANReceiveFunctions.c  .generated_files/5869cacc14dae1bcc99e447aafc4a3ca10e52c26.flag .generated_files/8bac4a0766d39c6687560ebfeb650ad7e1a6910e.flag
	@${MKDIR} "${OBJECTDIR}/src/hal/can" 
	@${RM} ${OBJECTDIR}/src/hal/can/CANReceiveFunctions.o.d 
	@${RM} ${OBJECTDIR}/src/hal/can/CANReceiveFunctions.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"." -I"src" -MP -MMD -MF "${OBJECTDIR}/src/hal/can/CANReceiveFunctions.o.d" -o ${OBJECTDIR}/src/hal/can/CANReceiveFunctions.o src/hal/can/CANReceiveFunctions.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/src/hal/can/CANTransmitFunctions.o: src/hal/can/CANTransmitFunctions.c  .generated_files/d2343774988f95d7ef5d9543865c7ab35f32848a.flag .generated_files/8bac4a0766d39c6687560ebfeb650ad7e1a6910e.flag
	@${MKDIR} "${OBJECTDIR}/src/hal/can" 
	@${RM} ${OBJECTDIR}/src/hal/can/CANTransmitFunctions.o.d 
	@${RM} ${OBJECTDIR}/src/hal/can/CANTransmitFunctions.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"." -I"src" -MP -MMD -MF "${OBJECTDIR}/src/hal/can/CANTransmitFunctions.o.d" -o ${OBJECTDIR}/src/hal/can/CANTransmitFunctions.o src/hal/can/CANTransmitFunctions.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/src/hal/pin32.o: src/hal/pin32.c  .generated_files/e31ecd36cc341c4eddc716cc0146b1bf9217ae51.flag .generated_files/8bac4a0766d39c6687560ebfeb650ad7e1a6910e.flag
	@${MKDIR} "${OBJECTDIR}/src/hal" 
	@${RM} ${OBJECTDIR}/src/hal/pin32.o.d 
	@${RM} ${OBJECTDIR}/src/hal/pin32.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"." -I"src" -MP -MMD -MF "${OBJECTDIR}/src/hal/pin32.o.d" -o ${OBJECTDIR}/src/hal/pin32.o src/hal/pin32.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/src/hal/uart32mx.o: src/hal/uart32mx.c  .generated_files/fcf54574fbe2b7a8d717b1c8038a413c41703220.flag .generated_files/8bac4a0766d39c6687560ebfeb650ad7e1a6910e.flag
	@${MKDIR} "${OBJECTDIR}/src/hal" 
	@${RM} ${OBJECTDIR}/src/hal/uart32mx.o.d 
	@${RM} ${OBJECTDIR}/src/hal/uart32mx.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"." -I"src" -MP -MMD -MF "${OBJECTDIR}/src/hal/uart32mx.o.d" -o ${OBJECTDIR}/src/hal/uart32mx.o src/hal/uart32mx.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/mcc_generated_files/interrupt_manager.o: mcc_generated_files/interrupt_manager.c  .generated_files/f7676935f59a876db299bbff411fea0458e9e7c5.flag .generated_files/8bac4a0766d39c6687560ebfeb650ad7e1a6910e.flag
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/interrupt_manager.o.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/interrupt_manager.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"." -I"src" -MP -MMD -MF "${OBJECTDIR}/mcc_generated_files/interrupt_manager.o.d" -o ${OBJECTDIR}/mcc_generated_files/interrupt_manager.o mcc_generated_files/interrupt_manager.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/mcc_generated_files/mcc.o: mcc_generated_files/mcc.c  .generated_files/a0c93696ab78d1d6de741931a0a4449a46a14dc3.flag .generated_files/8bac4a0766d39c6687560ebfeb650ad7e1a6910e.flag
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/mcc.o.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/mcc.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"." -I"src" -MP -MMD -MF "${OBJECTDIR}/mcc_generated_files/mcc.o.d" -o ${OBJECTDIR}/mcc_generated_files/mcc.o mcc_generated_files/mcc.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/mcc_generated_files/pin_manager.o: mcc_generated_files/pin_manager.c  .generated_files/d71889eb66e8639f83a723730f5817310f4971ba.flag .generated_files/8bac4a0766d39c6687560ebfeb650ad7e1a6910e.flag
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/pin_manager.o.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/pin_manager.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"." -I"src" -MP -MMD -MF "${OBJECTDIR}/mcc_generated_files/pin_manager.o.d" -o ${OBJECTDIR}/mcc_generated_files/pin_manager.o mcc_generated_files/pin_manager.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/mcc_generated_files/tmr2.o: mcc_generated_files/tmr2.c  .generated_files/8d715768f3cde77849e70f72ac4fe7d6e23f987a.flag .generated_files/8bac4a0766d39c6687560ebfeb650ad7e1a6910e.flag
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/tmr2.o.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/tmr2.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"." -I"src" -MP -MMD -MF "${OBJECTDIR}/mcc_generated_files/tmr2.o.d" -o ${OBJECTDIR}/mcc_generated_files/tmr2.o mcc_generated_files/tmr2.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/mcc_generated_files/uart1.o: mcc_generated_files/uart1.c  .generated_files/2f1629345a18ce3db81d6757e65a57ec758ffbd4.flag .generated_files/8bac4a0766d39c6687560ebfeb650ad7e1a6910e.flag
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/uart1.o.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/uart1.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"." -I"src" -MP -MMD -MF "${OBJECTDIR}/mcc_generated_files/uart1.o.d" -o ${OBJECTDIR}/mcc_generated_files/uart1.o mcc_generated_files/uart1.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/src/sas/debug.o: src/sas/debug.c  .generated_files/9dcaebe72c7ba1d775cd448b3d78f4c22eb34c12.flag .generated_files/8bac4a0766d39c6687560ebfeb650ad7e1a6910e.flag
	@${MKDIR} "${OBJECTDIR}/src/sas" 
	@${RM} ${OBJECTDIR}/src/sas/debug.o.d 
	@${RM} ${OBJECTDIR}/src/sas/debug.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"." -I"src" -MP -MMD -MF "${OBJECTDIR}/src/sas/debug.o.d" -o ${OBJECTDIR}/src/sas/debug.o src/sas/debug.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/src/sas/pulse.o: src/sas/pulse.c  .generated_files/e82c1df0aa4fd88c4da6b7b7e9e6b1a8cb678ab6.flag .generated_files/8bac4a0766d39c6687560ebfeb650ad7e1a6910e.flag
	@${MKDIR} "${OBJECTDIR}/src/sas" 
	@${RM} ${OBJECTDIR}/src/sas/pulse.o.d 
	@${RM} ${OBJECTDIR}/src/sas/pulse.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"." -I"src" -MP -MMD -MF "${OBJECTDIR}/src/sas/pulse.o.d" -o ${OBJECTDIR}/src/sas/pulse.o src/sas/pulse.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/src/sas/timer.o: src/sas/timer.c  .generated_files/d6bcab27683bf5710df411ad3608629885e6974f.flag .generated_files/8bac4a0766d39c6687560ebfeb650ad7e1a6910e.flag
	@${MKDIR} "${OBJECTDIR}/src/sas" 
	@${RM} ${OBJECTDIR}/src/sas/timer.o.d 
	@${RM} ${OBJECTDIR}/src/sas/timer.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"." -I"src" -MP -MMD -MF "${OBJECTDIR}/src/sas/timer.o.d" -o ${OBJECTDIR}/src/sas/timer.o src/sas/timer.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/src/ssl/bulbctrl.o: src/ssl/bulbctrl.c  .generated_files/c73f11460c1682124831970a95c75c747afe9702.flag .generated_files/8bac4a0766d39c6687560ebfeb650ad7e1a6910e.flag
	@${MKDIR} "${OBJECTDIR}/src/ssl" 
	@${RM} ${OBJECTDIR}/src/ssl/bulbctrl.o.d 
	@${RM} ${OBJECTDIR}/src/ssl/bulbctrl.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"." -I"src" -MP -MMD -MF "${OBJECTDIR}/src/ssl/bulbctrl.o.d" -o ${OBJECTDIR}/src/ssl/bulbctrl.o src/ssl/bulbctrl.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/src/ssl/canbus.o: src/ssl/canbus.c  .generated_files/62dcfa99e16c4cdbd967dccd5ee0284b4e40136e.flag .generated_files/8bac4a0766d39c6687560ebfeb650ad7e1a6910e.flag
	@${MKDIR} "${OBJECTDIR}/src/ssl" 
	@${RM} ${OBJECTDIR}/src/ssl/canbus.o.d 
	@${RM} ${OBJECTDIR}/src/ssl/canbus.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"." -I"src" -MP -MMD -MF "${OBJECTDIR}/src/ssl/canbus.o.d" -o ${OBJECTDIR}/src/ssl/canbus.o src/ssl/canbus.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/main.o: main.c  .generated_files/69cf94797aa6e2744ca826b03a927db4b20c5d24.flag .generated_files/8bac4a0766d39c6687560ebfeb650ad7e1a6910e.flag
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
dist/${CND_CONF}/${IMAGE_TYPE}/GwPowerSplit_v5.0.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk    
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE) -g   -mprocessor=$(MP_PROCESSOR_OPTION)  -o dist/${CND_CONF}/${IMAGE_TYPE}/GwPowerSplit_v5.0.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX} ${OBJECTFILES_QUOTED_IF_SPACED}          -DXPRJ_default=$(CND_CONF)  -legacy-libc  -std=gnu99 $(COMPARISON_BUILD)   -mreserve=data@0x0:0x1FC -mreserve=boot@0x1FC00490:0x1FC00BEF  -Wl,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_LD_POST)$(MP_LINKER_FILE_OPTION),--defsym=__MPLAB_DEBUG=1,--defsym=__DEBUG=1,-D=__DEBUG_D,--no-code-in-dinit,--no-dinit-in-serial-mem,-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map",--memorysummary,dist/${CND_CONF}/${IMAGE_TYPE}/memoryfile.xml -mdfp="${DFP_DIR}"
	
else
dist/${CND_CONF}/${IMAGE_TYPE}/GwPowerSplit_v5.0.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk   
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE)  -mprocessor=$(MP_PROCESSOR_OPTION)  -o dist/${CND_CONF}/${IMAGE_TYPE}/GwPowerSplit_v5.0.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} ${OBJECTFILES_QUOTED_IF_SPACED}          -DXPRJ_default=$(CND_CONF)  -legacy-libc  -std=gnu99 $(COMPARISON_BUILD)  -Wl,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_LD_POST)$(MP_LINKER_FILE_OPTION),--no-code-in-dinit,--no-dinit-in-serial-mem,-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map",--memorysummary,dist/${CND_CONF}/${IMAGE_TYPE}/memoryfile.xml -mdfp="${DFP_DIR}"
	${MP_CC_DIR}\\xc32-bin2hex dist/${CND_CONF}/${IMAGE_TYPE}/GwPowerSplit_v5.0.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} 
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
