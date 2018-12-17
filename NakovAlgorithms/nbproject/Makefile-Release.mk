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
	${OBJECTDIR}/chapter2/BinaryTree.o \
	${OBJECTDIR}/chapter2/MyList.o \
	${OBJECTDIR}/chapter2/MyQueue.o \
	${OBJECTDIR}/chapter2/MyStack.o \
	${OBJECTDIR}/chapter2/MyTree.o \
	${OBJECTDIR}/chapter2/Tree.o \
	${OBJECTDIR}/chapter2/hashTables/CHashTables/CHash.o \
	${OBJECTDIR}/chapter2/hashTables/HashTables/HashTable.o \
	${OBJECTDIR}/examples/ChapterOne.o \
	${OBJECTDIR}/examples/Coding.o \
	${OBJECTDIR}/examples/Combinatorics.o \
	${OBJECTDIR}/examples/FromDecimal.o \
	${OBJECTDIR}/examples/Recursive.o \
	${OBJECTDIR}/examples/RomangDigits.o \
	${OBJECTDIR}/examples/ToDecimal.o \
	${OBJECTDIR}/main.o \
	${OBJECTDIR}/utils/BinarySearchTree.o


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

${OBJECTDIR}/chapter2/BinaryTree.o: chapter2/BinaryTree.cpp
	${MKDIR} -p ${OBJECTDIR}/chapter2
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -std=c++14 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/chapter2/BinaryTree.o chapter2/BinaryTree.cpp

${OBJECTDIR}/chapter2/MyList.o: chapter2/MyList.cpp
	${MKDIR} -p ${OBJECTDIR}/chapter2
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -std=c++14 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/chapter2/MyList.o chapter2/MyList.cpp

${OBJECTDIR}/chapter2/MyQueue.o: chapter2/MyQueue.cpp
	${MKDIR} -p ${OBJECTDIR}/chapter2
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -std=c++14 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/chapter2/MyQueue.o chapter2/MyQueue.cpp

${OBJECTDIR}/chapter2/MyStack.o: chapter2/MyStack.cpp
	${MKDIR} -p ${OBJECTDIR}/chapter2
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -std=c++14 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/chapter2/MyStack.o chapter2/MyStack.cpp

${OBJECTDIR}/chapter2/MyTree.o: chapter2/MyTree.cpp
	${MKDIR} -p ${OBJECTDIR}/chapter2
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -std=c++14 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/chapter2/MyTree.o chapter2/MyTree.cpp

${OBJECTDIR}/chapter2/Tree.o: chapter2/Tree.cpp
	${MKDIR} -p ${OBJECTDIR}/chapter2
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -std=c++14 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/chapter2/Tree.o chapter2/Tree.cpp

${OBJECTDIR}/chapter2/hashTables/CHashTables/CHash.o: chapter2/hashTables/CHashTables/CHash.c
	${MKDIR} -p ${OBJECTDIR}/chapter2/hashTables/CHashTables
	${RM} "$@.d"
	$(COMPILE.c) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/chapter2/hashTables/CHashTables/CHash.o chapter2/hashTables/CHashTables/CHash.c

${OBJECTDIR}/chapter2/hashTables/HashTables/HashTable.o: chapter2/hashTables/HashTables/HashTable.cpp
	${MKDIR} -p ${OBJECTDIR}/chapter2/hashTables/HashTables
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -std=c++14 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/chapter2/hashTables/HashTables/HashTable.o chapter2/hashTables/HashTables/HashTable.cpp

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

${OBJECTDIR}/utils/BinarySearchTree.o: utils/BinarySearchTree.cpp
	${MKDIR} -p ${OBJECTDIR}/utils
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -std=c++14 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/utils/BinarySearchTree.o utils/BinarySearchTree.cpp

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
