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
CND_CONF=Release
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
	${OBJECTDIR}/states/gameStates/StatePaused.o \
	${OBJECTDIR}/test/Dice.o \
	${OBJECTDIR}/utils/RNGGenerator.o \
	${OBJECTDIR}/world/Item.o \
	${OBJECTDIR}/world/ItemsDeck.o \
	${OBJECTDIR}/world/Map.o \
	${OBJECTDIR}/world/Player.o \
	${OBJECTDIR}/world/PlayerDeck.o


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
LDLIBSOPTIONS=

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/underworldrun2.exe

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/underworldrun2.exe: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.cc} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/underworldrun2 ${OBJECTFILES} ${LDLIBSOPTIONS}

${OBJECTDIR}/engine/EventManager.o: engine/EventManager.cpp
	${MKDIR} -p ${OBJECTDIR}/engine
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -std=c++14 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/engine/EventManager.o engine/EventManager.cpp

${OBJECTDIR}/engine/Game.o: engine/Game.cpp
	${MKDIR} -p ${OBJECTDIR}/engine
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -std=c++14 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/engine/Game.o engine/Game.cpp

${OBJECTDIR}/engine/Window.o: engine/Window.cpp
	${MKDIR} -p ${OBJECTDIR}/engine
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -std=c++14 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/engine/Window.o engine/Window.cpp

${OBJECTDIR}/main.o: main.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -std=c++14 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/main.o main.cpp

${OBJECTDIR}/states/StateManager.o: states/StateManager.cpp
	${MKDIR} -p ${OBJECTDIR}/states
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -std=c++14 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/states/StateManager.o states/StateManager.cpp

${OBJECTDIR}/states/gameStates/StateGame.o: states/gameStates/StateGame.cpp
	${MKDIR} -p ${OBJECTDIR}/states/gameStates
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -std=c++14 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/states/gameStates/StateGame.o states/gameStates/StateGame.cpp

${OBJECTDIR}/states/gameStates/StateIntro.o: states/gameStates/StateIntro.cpp
	${MKDIR} -p ${OBJECTDIR}/states/gameStates
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -std=c++14 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/states/gameStates/StateIntro.o states/gameStates/StateIntro.cpp

${OBJECTDIR}/states/gameStates/StateMainMenu.o: states/gameStates/StateMainMenu.cpp
	${MKDIR} -p ${OBJECTDIR}/states/gameStates
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -std=c++14 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/states/gameStates/StateMainMenu.o states/gameStates/StateMainMenu.cpp

${OBJECTDIR}/states/gameStates/StatePaused.o: states/gameStates/StatePaused.cpp
	${MKDIR} -p ${OBJECTDIR}/states/gameStates
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -std=c++14 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/states/gameStates/StatePaused.o states/gameStates/StatePaused.cpp

${OBJECTDIR}/test/Dice.o: test/Dice.cpp
	${MKDIR} -p ${OBJECTDIR}/test
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -std=c++14 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/test/Dice.o test/Dice.cpp

${OBJECTDIR}/utils/RNGGenerator.o: utils/RNGGenerator.cpp
	${MKDIR} -p ${OBJECTDIR}/utils
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -std=c++14 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/utils/RNGGenerator.o utils/RNGGenerator.cpp

${OBJECTDIR}/world/Item.o: world/Item.cpp
	${MKDIR} -p ${OBJECTDIR}/world
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -std=c++14 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/world/Item.o world/Item.cpp

${OBJECTDIR}/world/ItemsDeck.o: world/ItemsDeck.cpp
	${MKDIR} -p ${OBJECTDIR}/world
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -std=c++14 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/world/ItemsDeck.o world/ItemsDeck.cpp

${OBJECTDIR}/world/Map.o: world/Map.cpp
	${MKDIR} -p ${OBJECTDIR}/world
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -std=c++14 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/world/Map.o world/Map.cpp

${OBJECTDIR}/world/Player.o: world/Player.cpp
	${MKDIR} -p ${OBJECTDIR}/world
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -std=c++14 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/world/Player.o world/Player.cpp

${OBJECTDIR}/world/PlayerDeck.o: world/PlayerDeck.cpp
	${MKDIR} -p ${OBJECTDIR}/world
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -std=c++14 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/world/PlayerDeck.o world/PlayerDeck.cpp

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
