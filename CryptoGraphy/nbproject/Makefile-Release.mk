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
	${OBJECTDIR}/lecture1/CeaserCipher.o \
	${OBJECTDIR}/lecture1/CeaserDecrypthor.o \
	${OBJECTDIR}/lecture1/ViginerCipher.o \
	${OBJECTDIR}/lecture1/ViginerDecryptor.o \
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
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/cryptography

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/cryptography: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.cc} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/cryptography ${OBJECTFILES} ${LDLIBSOPTIONS}

${OBJECTDIR}/lecture1/CeaserCipher.o: lecture1/CeaserCipher.cpp
	${MKDIR} -p ${OBJECTDIR}/lecture1
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -std=c++14 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/lecture1/CeaserCipher.o lecture1/CeaserCipher.cpp

${OBJECTDIR}/lecture1/CeaserDecrypthor.o: lecture1/CeaserDecrypthor.cpp
	${MKDIR} -p ${OBJECTDIR}/lecture1
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -std=c++14 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/lecture1/CeaserDecrypthor.o lecture1/CeaserDecrypthor.cpp

${OBJECTDIR}/lecture1/ViginerCipher.o: lecture1/ViginerCipher.cpp
	${MKDIR} -p ${OBJECTDIR}/lecture1
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -std=c++14 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/lecture1/ViginerCipher.o lecture1/ViginerCipher.cpp

${OBJECTDIR}/lecture1/ViginerDecryptor.o: lecture1/ViginerDecryptor.cpp
	${MKDIR} -p ${OBJECTDIR}/lecture1
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -std=c++14 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/lecture1/ViginerDecryptor.o lecture1/ViginerDecryptor.cpp

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
