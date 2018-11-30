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
CND_PLATFORM=GNU-Linux
CND_DLIB_EXT=so
CND_CONF=Release
CND_DISTDIR=dist
CND_BUILDDIR=build

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/examples/ChapterOne.o \
	${OBJECTDIR}/examples/Coding.o \
	${OBJECTDIR}/examples/Combinatorics.o \
	${OBJECTDIR}/examples/FromDecimal.o \
	${OBJECTDIR}/examples/Recursive.o \
	${OBJECTDIR}/examples/RomangDigits.o \
	${OBJECTDIR}/examples/ToDecimal.o \
	${OBJECTDIR}/main.o


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
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/nakovalgorithms

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/nakovalgorithms: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.cc} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/nakovalgorithms ${OBJECTFILES} ${LDLIBSOPTIONS}

${OBJECTDIR}/examples/ChapterOne.o: examples/ChapterOne.cpp
	${MKDIR} -p ${OBJECTDIR}/examples
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -std=c++14 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/examples/ChapterOne.o examples/ChapterOne.cpp

${OBJECTDIR}/examples/Coding.o: examples/Coding.cpp
	${MKDIR} -p ${OBJECTDIR}/examples
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -std=c++14 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/examples/Coding.o examples/Coding.cpp

${OBJECTDIR}/examples/Combinatorics.o: examples/Combinatorics.cpp
	${MKDIR} -p ${OBJECTDIR}/examples
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -std=c++14 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/examples/Combinatorics.o examples/Combinatorics.cpp

${OBJECTDIR}/examples/FromDecimal.o: examples/FromDecimal.cpp
	${MKDIR} -p ${OBJECTDIR}/examples
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -std=c++14 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/examples/FromDecimal.o examples/FromDecimal.cpp

${OBJECTDIR}/examples/Recursive.o: examples/Recursive.cpp
	${MKDIR} -p ${OBJECTDIR}/examples
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -std=c++14 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/examples/Recursive.o examples/Recursive.cpp

${OBJECTDIR}/examples/RomangDigits.o: examples/RomangDigits.cpp
	${MKDIR} -p ${OBJECTDIR}/examples
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -std=c++14 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/examples/RomangDigits.o examples/RomangDigits.cpp

${OBJECTDIR}/examples/ToDecimal.o: examples/ToDecimal.cpp
	${MKDIR} -p ${OBJECTDIR}/examples
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -std=c++14 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/examples/ToDecimal.o examples/ToDecimal.cpp

${OBJECTDIR}/main.o: main.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -std=c++14 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/main.o main.cpp

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