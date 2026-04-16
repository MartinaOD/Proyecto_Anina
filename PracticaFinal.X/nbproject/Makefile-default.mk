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
FINAL_IMAGE=${DISTDIR}/PracticaFinal.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
else
IMAGE_TYPE=production
OUTPUT_SUFFIX=hex
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=${DISTDIR}/PracticaFinal.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
endif

ifeq ($(COMPARE_BUILD), true)
COMPARISON_BUILD=-mafrlcsj
else
COMPARISON_BUILD=
endif

# Object Directory
OBJECTDIR=build/${CND_CONF}/${IMAGE_TYPE}

# Distribution Directory
DISTDIR=dist/${CND_CONF}/${IMAGE_TYPE}

# Source Files Quoted if spaced
SOURCEFILES_QUOTED_IF_SPACED=Pic32Ini.c UART1simple.c buzzer.c leds.c fsm.c game.c buttons.c timers.c main_prueba_juegobasico.c dificultad.c

# Object Files Quoted if spaced
OBJECTFILES_QUOTED_IF_SPACED=${OBJECTDIR}/Pic32Ini.o ${OBJECTDIR}/UART1simple.o ${OBJECTDIR}/buzzer.o ${OBJECTDIR}/leds.o ${OBJECTDIR}/fsm.o ${OBJECTDIR}/game.o ${OBJECTDIR}/buttons.o ${OBJECTDIR}/timers.o ${OBJECTDIR}/main_prueba_juegobasico.o ${OBJECTDIR}/dificultad.o
POSSIBLE_DEPFILES=${OBJECTDIR}/Pic32Ini.o.d ${OBJECTDIR}/UART1simple.o.d ${OBJECTDIR}/buzzer.o.d ${OBJECTDIR}/leds.o.d ${OBJECTDIR}/fsm.o.d ${OBJECTDIR}/game.o.d ${OBJECTDIR}/buttons.o.d ${OBJECTDIR}/timers.o.d ${OBJECTDIR}/main_prueba_juegobasico.o.d ${OBJECTDIR}/dificultad.o.d

# Object Files
OBJECTFILES=${OBJECTDIR}/Pic32Ini.o ${OBJECTDIR}/UART1simple.o ${OBJECTDIR}/buzzer.o ${OBJECTDIR}/leds.o ${OBJECTDIR}/fsm.o ${OBJECTDIR}/game.o ${OBJECTDIR}/buttons.o ${OBJECTDIR}/timers.o ${OBJECTDIR}/main_prueba_juegobasico.o ${OBJECTDIR}/dificultad.o

# Source Files
SOURCEFILES=Pic32Ini.c UART1simple.c buzzer.c leds.c fsm.c game.c buttons.c timers.c main_prueba_juegobasico.c dificultad.c



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
	${MAKE}  -f nbproject/Makefile-default.mk ${DISTDIR}/PracticaFinal.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}

MP_PROCESSOR_OPTION=32MX230F064D
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
${OBJECTDIR}/Pic32Ini.o: Pic32Ini.c  .generated_files/flags/default/2a8104c68d3bd5b98eba4731db09226ba0e993c2 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/Pic32Ini.o.d 
	@${RM} ${OBJECTDIR}/Pic32Ini.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -MP -MMD -MF "${OBJECTDIR}/Pic32Ini.o.d" -o ${OBJECTDIR}/Pic32Ini.o Pic32Ini.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/UART1simple.o: UART1simple.c  .generated_files/flags/default/ae26b60d095d0d21d2d456fd653b79b021490b6 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/UART1simple.o.d 
	@${RM} ${OBJECTDIR}/UART1simple.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -MP -MMD -MF "${OBJECTDIR}/UART1simple.o.d" -o ${OBJECTDIR}/UART1simple.o UART1simple.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/buzzer.o: buzzer.c  .generated_files/flags/default/87bf3cd99f3d15feec9c3ca74a296e38818b1db0 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/buzzer.o.d 
	@${RM} ${OBJECTDIR}/buzzer.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -MP -MMD -MF "${OBJECTDIR}/buzzer.o.d" -o ${OBJECTDIR}/buzzer.o buzzer.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/leds.o: leds.c  .generated_files/flags/default/82bfbbafde0548280fb7c334f43f50ae59073594 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/leds.o.d 
	@${RM} ${OBJECTDIR}/leds.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -MP -MMD -MF "${OBJECTDIR}/leds.o.d" -o ${OBJECTDIR}/leds.o leds.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/fsm.o: fsm.c  .generated_files/flags/default/28bf2086bfbb45104159136de77030005453515b .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/fsm.o.d 
	@${RM} ${OBJECTDIR}/fsm.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -MP -MMD -MF "${OBJECTDIR}/fsm.o.d" -o ${OBJECTDIR}/fsm.o fsm.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/game.o: game.c  .generated_files/flags/default/3c2898f7eeba6d8abb109e352fc737b9f20dbff9 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/game.o.d 
	@${RM} ${OBJECTDIR}/game.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -MP -MMD -MF "${OBJECTDIR}/game.o.d" -o ${OBJECTDIR}/game.o game.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/buttons.o: buttons.c  .generated_files/flags/default/a61304083a69d864c184e8d6a915c0d8ce155bc0 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/buttons.o.d 
	@${RM} ${OBJECTDIR}/buttons.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -MP -MMD -MF "${OBJECTDIR}/buttons.o.d" -o ${OBJECTDIR}/buttons.o buttons.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/timers.o: timers.c  .generated_files/flags/default/dc74b9bb80dc78480eeb66c9b981942134ba3da4 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/timers.o.d 
	@${RM} ${OBJECTDIR}/timers.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -MP -MMD -MF "${OBJECTDIR}/timers.o.d" -o ${OBJECTDIR}/timers.o timers.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/main_prueba_juegobasico.o: main_prueba_juegobasico.c  .generated_files/flags/default/9fe3adf768482d2896793f9d94acbcc794e74f8d .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/main_prueba_juegobasico.o.d 
	@${RM} ${OBJECTDIR}/main_prueba_juegobasico.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -MP -MMD -MF "${OBJECTDIR}/main_prueba_juegobasico.o.d" -o ${OBJECTDIR}/main_prueba_juegobasico.o main_prueba_juegobasico.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/dificultad.o: dificultad.c  .generated_files/flags/default/460dda59d8d650a168dbd2eb4eb24d9dcaf2bd09 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/dificultad.o.d 
	@${RM} ${OBJECTDIR}/dificultad.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -MP -MMD -MF "${OBJECTDIR}/dificultad.o.d" -o ${OBJECTDIR}/dificultad.o dificultad.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
else
${OBJECTDIR}/Pic32Ini.o: Pic32Ini.c  .generated_files/flags/default/e0c80a6299768cacbcc2389b015a35b6f262dbc2 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/Pic32Ini.o.d 
	@${RM} ${OBJECTDIR}/Pic32Ini.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -MP -MMD -MF "${OBJECTDIR}/Pic32Ini.o.d" -o ${OBJECTDIR}/Pic32Ini.o Pic32Ini.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/UART1simple.o: UART1simple.c  .generated_files/flags/default/231dfb61979c37ae116cf6b780bea07fc32e0e10 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/UART1simple.o.d 
	@${RM} ${OBJECTDIR}/UART1simple.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -MP -MMD -MF "${OBJECTDIR}/UART1simple.o.d" -o ${OBJECTDIR}/UART1simple.o UART1simple.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/buzzer.o: buzzer.c  .generated_files/flags/default/b61a4b3703bf23dd52034656354458a9173e6daa .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/buzzer.o.d 
	@${RM} ${OBJECTDIR}/buzzer.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -MP -MMD -MF "${OBJECTDIR}/buzzer.o.d" -o ${OBJECTDIR}/buzzer.o buzzer.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/leds.o: leds.c  .generated_files/flags/default/4c5a16d9c48463db33533537a85799e3afe320a1 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/leds.o.d 
	@${RM} ${OBJECTDIR}/leds.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -MP -MMD -MF "${OBJECTDIR}/leds.o.d" -o ${OBJECTDIR}/leds.o leds.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/fsm.o: fsm.c  .generated_files/flags/default/10f7d99171ad45255174eaebc120cbd8d4228c24 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/fsm.o.d 
	@${RM} ${OBJECTDIR}/fsm.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -MP -MMD -MF "${OBJECTDIR}/fsm.o.d" -o ${OBJECTDIR}/fsm.o fsm.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/game.o: game.c  .generated_files/flags/default/11d8103a671eb2302ac38ef63f1ab5712573bb6a .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/game.o.d 
	@${RM} ${OBJECTDIR}/game.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -MP -MMD -MF "${OBJECTDIR}/game.o.d" -o ${OBJECTDIR}/game.o game.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/buttons.o: buttons.c  .generated_files/flags/default/16b124b991a825e28aa82663f34044894945e03a .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/buttons.o.d 
	@${RM} ${OBJECTDIR}/buttons.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -MP -MMD -MF "${OBJECTDIR}/buttons.o.d" -o ${OBJECTDIR}/buttons.o buttons.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/timers.o: timers.c  .generated_files/flags/default/ff5fac61c4ddcf8b6e8ca75eeb386fc3d21ce175 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/timers.o.d 
	@${RM} ${OBJECTDIR}/timers.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -MP -MMD -MF "${OBJECTDIR}/timers.o.d" -o ${OBJECTDIR}/timers.o timers.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/main_prueba_juegobasico.o: main_prueba_juegobasico.c  .generated_files/flags/default/50cd37d81f8b5cdbd97c2a3ca47392c2b7199e99 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/main_prueba_juegobasico.o.d 
	@${RM} ${OBJECTDIR}/main_prueba_juegobasico.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -MP -MMD -MF "${OBJECTDIR}/main_prueba_juegobasico.o.d" -o ${OBJECTDIR}/main_prueba_juegobasico.o main_prueba_juegobasico.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/dificultad.o: dificultad.c  .generated_files/flags/default/7cbc7e2704164ed2034fa604f6a191ede0a3ae48 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/dificultad.o.d 
	@${RM} ${OBJECTDIR}/dificultad.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -MP -MMD -MF "${OBJECTDIR}/dificultad.o.d" -o ${OBJECTDIR}/dificultad.o dificultad.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: compileCPP
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: link
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${DISTDIR}/PracticaFinal.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk    
	@${MKDIR} ${DISTDIR} 
	${MP_CC} $(MP_EXTRA_LD_PRE) -g -mdebugger -D__MPLAB_DEBUGGER_PK3=1 -mprocessor=$(MP_PROCESSOR_OPTION)  -o ${DISTDIR}/PracticaFinal.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX} ${OBJECTFILES_QUOTED_IF_SPACED}          -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)   -mreserve=data@0x0:0x1FC -mreserve=boot@0x1FC00490:0x1FC00BEF  -Wl,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_LD_POST)$(MP_LINKER_FILE_OPTION),--defsym=__MPLAB_DEBUG=1,--defsym=__DEBUG=1,-D=__DEBUG_D,--defsym=__MPLAB_DEBUGGER_PK3=1,--defsym=_min_heap_size=255,--no-code-in-dinit,--no-dinit-in-serial-mem,-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map",--memorysummary,${DISTDIR}/memoryfile.xml -mdfp="${DFP_DIR}"
	
else
${DISTDIR}/PracticaFinal.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk   
	@${MKDIR} ${DISTDIR} 
	${MP_CC} $(MP_EXTRA_LD_PRE)  -mprocessor=$(MP_PROCESSOR_OPTION)  -o ${DISTDIR}/PracticaFinal.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} ${OBJECTFILES_QUOTED_IF_SPACED}          -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -Wl,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_LD_POST)$(MP_LINKER_FILE_OPTION),--defsym=_min_heap_size=255,--no-code-in-dinit,--no-dinit-in-serial-mem,-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map",--memorysummary,${DISTDIR}/memoryfile.xml -mdfp="${DFP_DIR}"
	${MP_CC_DIR}\\xc32-bin2hex ${DISTDIR}/PracticaFinal.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} 
endif


# Subprojects
.build-subprojects:


# Subprojects
.clean-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${OBJECTDIR}
	${RM} -r ${DISTDIR}

# Enable dependency checking
.dep.inc: .depcheck-impl

DEPFILES=$(wildcard ${POSSIBLE_DEPFILES})
ifneq (${DEPFILES},)
include ${DEPFILES}
endif
