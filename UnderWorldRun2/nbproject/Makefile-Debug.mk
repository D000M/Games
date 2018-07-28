#
# Generated Makefile - do not edit!
#
# Edit the Makefile in the project folder instead (../Makefile). Each target
# has a -pre and a -post target defined where you can add customized code.
#
# This makefile implements configuration specific macros and targets.


# Environment
MKDIR=mkdir
CP=cp
GREP=grep
NM=nm
CCADMIN=CCadmin
RANLIB=ranlib
CC=gcc
CCC=g++
CXX=g++
FC=gfortran
AS=as

# Macros
CND_PLATFORM=MinGW-Windows
CND_DLIB_EXT=dll
CND_CONF=Debug
CND_DISTDIR=dist
CND_BUILDDIR=build

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/engine/EventManager.o \
	${OBJECTDIR}/engine/Game.o \
	${OBJECTDIR}/engine/Window.o \
	${OBJECTDIR}/main.o \
	${OBJECTDIR}/states/StateManager.o \
	${OBJECTDIR}/states/gameStates/StateGame.o \
	${OBJECTDIR}/states/gameStates/StateIntro.o \
	${OBJECTDIR}/states/gameStates/StateMainMenu.o \
	${OBJECTDIR}/states/gameStates/StatePaused.o


# C Compiler Flags
CFLAGS=

# CC Compiler Flags
CCFLAGS=
CXXFLAGS=

# Fortran Compiler Flags
FFLAGS=

# Assembler Flags
ASFLAGS=

# Link Libraries and Options
LDLIBSOPTIONS=-lsfml-window -lsfml-system -lsfml-graphics -lsfml-audio -lsfml-network

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/underworldrun2.exe

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/underworldrun2.exe: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.cc} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/underworldrun2 ${OBJECTFILES} ${LDLIBSOPTIONS}

${OBJECTDIR}/engine/EventManager.o: engine/EventManager.cpp
	${MKDIR} -p ${OBJECTDIR}/engine
	${RM} "$@.d"
	$(COMPILE.cc) -g -std=c++14 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/engine/EventManager.o engine/EventManager.cpp

${OBJECTDIR}/engine/Game.o: engine/Game.cpp
	${MKDIR} -p ${OBJECTDIR}/engine
	${RM} "$@.d"
	$(COMPILE.cc) -g -std=c++14 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/engine/Game.o engine/Game.cpp

${OBJECTDIR}/engine/Window.o: engine/Window.cpp
	${MKDIR} -p ${OBJECTDIR}/engine
	${RM} "$@.d"
	$(COMPILE.cc) -g -std=c++14 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/engine/Window.o engine/Window.cpp

${OBJECTDIR}/main.o: main.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -std=c++14 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/main.o main.cpp

${OBJECTDIR}/states/StateManager.o: states/StateManager.cpp
	${MKDIR} -p ${OBJECTDIR}/states
	${RM} "$@.d"
	$(COMPILE.cc) -g -std=c++14 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/states/StateManager.o states/StateManager.cpp

${OBJECTDIR}/states/gameStates/StateGame.o: states/gameStates/StateGame.cpp
	${MKDIR} -p ${OBJECTDIR}/states/gameStates
	${RM} "$@.d"
	$(COMPILE.cc) -g -std=c++14 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/states/gameStates/StateGame.o states/gameStates/StateGame.cpp

${OBJECTDIR}/states/gameStates/StateIntro.o: states/gameStates/StateIntro.cpp
	${MKDIR} -p ${OBJECTDIR}/states/gameStates
	${RM} "$@.d"
	$(COMPILE.cc) -g -std=c++14 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/states/gameStates/StateIntro.o states/gameStates/StateIntro.cpp

${OBJECTDIR}/states/gameStates/StateMainMenu.o: states/gameStates/StateMainMenu.cpp
	${MKDIR} -p ${OBJECTDIR}/states/gameStates
	${RM} "$@.d"
	$(COMPILE.cc) -g -std=c++14 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/states/gameStates/StateMainMenu.o states/gameStates/StateMainMenu.cpp

${OBJECTDIR}/states/gameStates/StatePaused.o: states/gameStates/StatePaused.cpp
	${MKDIR} -p ${OBJECTDIR}/states/gameStates
	${RM} "$@.d"
	$(COMPILE.cc) -g -std=c++14 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/states/gameStates/StatePaused.o states/gameStates/StatePaused.cpp

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
