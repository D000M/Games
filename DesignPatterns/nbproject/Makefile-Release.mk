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
	${OBJECTDIR}/Behavioral/Mediator/ChatPerson2.o \
	${OBJECTDIR}/Behavioral/Mediator/ChatRoom2.o \
	${OBJECTDIR}/Behavioral/Observer/Observable.o \
	${OBJECTDIR}/Behavioral/Observer/Observer.o \
	${OBJECTDIR}/Behavioral/Observer/SaferObservable.o \
	${OBJECTDIR}/Creational/Builder/ComplicateBuilder/Person.o \
	${OBJECTDIR}/Creational/Builder/ComplicateBuilder/PersonBuilder.o \
	${OBJECTDIR}/Creational/Builder/VechicleBuilder/Vechicle.o \
	${OBJECTDIR}/Creational/Builder/VechicleBuilder/VechicleBuilder.o \
	${OBJECTDIR}/ORiley/ObserverPattern/DigitalDisplay.o \
	${OBJECTDIR}/ORiley/ObserverPattern/PCDisplay.o \
	${OBJECTDIR}/ORiley/ObserverPattern/PhoneDisplay.o \
	${OBJECTDIR}/ORiley/ObserverPattern/WeatherStation.o \
	${OBJECTDIR}/ORiley/StrategyPattern/DisplayAsGraphics.o \
	${OBJECTDIR}/ORiley/StrategyPattern/DisplayAsText.o \
	${OBJECTDIR}/ORiley/StrategyPattern/Duck.o \
	${OBJECTDIR}/ORiley/StrategyPattern/JetFlying.o \
	${OBJECTDIR}/ORiley/StrategyPattern/NoFlying.o \
	${OBJECTDIR}/ORiley/StrategyPattern/NoQuack.o \
	${OBJECTDIR}/ORiley/StrategyPattern/Quack.o \
	${OBJECTDIR}/ORiley/StrategyPattern/SimpleFlying.o \
	${OBJECTDIR}/Structural/Bridge/PimplIdiom/Person2.o \
	${OBJECTDIR}/Structural/Bridge/PimplIdiom/SecondAttempt.o \
	${OBJECTDIR}/main.o

# Test Directory
TESTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}/tests

# Test Files
TESTFILES= \
	${TESTDIR}/TestFiles/f1

# Test Object Files
TESTOBJECTFILES= \
	${TESTDIR}/SingletonTest.o

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
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/designpatterns

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/designpatterns: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.cc} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/designpatterns ${OBJECTFILES} ${LDLIBSOPTIONS}

${OBJECTDIR}/Behavioral/Mediator/ChatPerson2.o: Behavioral/Mediator/ChatPerson2.cpp
	${MKDIR} -p ${OBJECTDIR}/Behavioral/Mediator
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -std=c++17 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Behavioral/Mediator/ChatPerson2.o Behavioral/Mediator/ChatPerson2.cpp

${OBJECTDIR}/Behavioral/Mediator/ChatRoom2.o: Behavioral/Mediator/ChatRoom2.cpp
	${MKDIR} -p ${OBJECTDIR}/Behavioral/Mediator
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -std=c++17 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Behavioral/Mediator/ChatRoom2.o Behavioral/Mediator/ChatRoom2.cpp

${OBJECTDIR}/Behavioral/Observer/Observable.o: Behavioral/Observer/Observable.cpp
	${MKDIR} -p ${OBJECTDIR}/Behavioral/Observer
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -std=c++17 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Behavioral/Observer/Observable.o Behavioral/Observer/Observable.cpp

${OBJECTDIR}/Behavioral/Observer/Observer.o: Behavioral/Observer/Observer.cpp
	${MKDIR} -p ${OBJECTDIR}/Behavioral/Observer
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -std=c++17 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Behavioral/Observer/Observer.o Behavioral/Observer/Observer.cpp

${OBJECTDIR}/Behavioral/Observer/SaferObservable.o: Behavioral/Observer/SaferObservable.cpp
	${MKDIR} -p ${OBJECTDIR}/Behavioral/Observer
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -std=c++17 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Behavioral/Observer/SaferObservable.o Behavioral/Observer/SaferObservable.cpp

${OBJECTDIR}/Creational/Builder/ComplicateBuilder/Person.o: Creational/Builder/ComplicateBuilder/Person.cpp
	${MKDIR} -p ${OBJECTDIR}/Creational/Builder/ComplicateBuilder
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -std=c++17 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Creational/Builder/ComplicateBuilder/Person.o Creational/Builder/ComplicateBuilder/Person.cpp

${OBJECTDIR}/Creational/Builder/ComplicateBuilder/PersonBuilder.o: Creational/Builder/ComplicateBuilder/PersonBuilder.cpp
	${MKDIR} -p ${OBJECTDIR}/Creational/Builder/ComplicateBuilder
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -std=c++17 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Creational/Builder/ComplicateBuilder/PersonBuilder.o Creational/Builder/ComplicateBuilder/PersonBuilder.cpp

${OBJECTDIR}/Creational/Builder/VechicleBuilder/Vechicle.o: Creational/Builder/VechicleBuilder/Vechicle.cpp
	${MKDIR} -p ${OBJECTDIR}/Creational/Builder/VechicleBuilder
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -std=c++17 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Creational/Builder/VechicleBuilder/Vechicle.o Creational/Builder/VechicleBuilder/Vechicle.cpp

${OBJECTDIR}/Creational/Builder/VechicleBuilder/VechicleBuilder.o: Creational/Builder/VechicleBuilder/VechicleBuilder.cpp
	${MKDIR} -p ${OBJECTDIR}/Creational/Builder/VechicleBuilder
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -std=c++17 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Creational/Builder/VechicleBuilder/VechicleBuilder.o Creational/Builder/VechicleBuilder/VechicleBuilder.cpp

${OBJECTDIR}/ORiley/ObserverPattern/DigitalDisplay.o: ORiley/ObserverPattern/DigitalDisplay.cpp
	${MKDIR} -p ${OBJECTDIR}/ORiley/ObserverPattern
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -std=c++17 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/ORiley/ObserverPattern/DigitalDisplay.o ORiley/ObserverPattern/DigitalDisplay.cpp

${OBJECTDIR}/ORiley/ObserverPattern/PCDisplay.o: ORiley/ObserverPattern/PCDisplay.cpp
	${MKDIR} -p ${OBJECTDIR}/ORiley/ObserverPattern
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -std=c++17 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/ORiley/ObserverPattern/PCDisplay.o ORiley/ObserverPattern/PCDisplay.cpp

${OBJECTDIR}/ORiley/ObserverPattern/PhoneDisplay.o: ORiley/ObserverPattern/PhoneDisplay.cpp
	${MKDIR} -p ${OBJECTDIR}/ORiley/ObserverPattern
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -std=c++17 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/ORiley/ObserverPattern/PhoneDisplay.o ORiley/ObserverPattern/PhoneDisplay.cpp

${OBJECTDIR}/ORiley/ObserverPattern/WeatherStation.o: ORiley/ObserverPattern/WeatherStation.cpp
	${MKDIR} -p ${OBJECTDIR}/ORiley/ObserverPattern
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -std=c++17 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/ORiley/ObserverPattern/WeatherStation.o ORiley/ObserverPattern/WeatherStation.cpp

${OBJECTDIR}/ORiley/StrategyPattern/DisplayAsGraphics.o: ORiley/StrategyPattern/DisplayAsGraphics.cpp
	${MKDIR} -p ${OBJECTDIR}/ORiley/StrategyPattern
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -std=c++17 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/ORiley/StrategyPattern/DisplayAsGraphics.o ORiley/StrategyPattern/DisplayAsGraphics.cpp

${OBJECTDIR}/ORiley/StrategyPattern/DisplayAsText.o: ORiley/StrategyPattern/DisplayAsText.cpp
	${MKDIR} -p ${OBJECTDIR}/ORiley/StrategyPattern
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -std=c++17 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/ORiley/StrategyPattern/DisplayAsText.o ORiley/StrategyPattern/DisplayAsText.cpp

${OBJECTDIR}/ORiley/StrategyPattern/Duck.o: ORiley/StrategyPattern/Duck.cpp
	${MKDIR} -p ${OBJECTDIR}/ORiley/StrategyPattern
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -std=c++17 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/ORiley/StrategyPattern/Duck.o ORiley/StrategyPattern/Duck.cpp

${OBJECTDIR}/ORiley/StrategyPattern/JetFlying.o: ORiley/StrategyPattern/JetFlying.cpp
	${MKDIR} -p ${OBJECTDIR}/ORiley/StrategyPattern
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -std=c++17 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/ORiley/StrategyPattern/JetFlying.o ORiley/StrategyPattern/JetFlying.cpp

${OBJECTDIR}/ORiley/StrategyPattern/NoFlying.o: ORiley/StrategyPattern/NoFlying.cpp
	${MKDIR} -p ${OBJECTDIR}/ORiley/StrategyPattern
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -std=c++17 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/ORiley/StrategyPattern/NoFlying.o ORiley/StrategyPattern/NoFlying.cpp

${OBJECTDIR}/ORiley/StrategyPattern/NoQuack.o: ORiley/StrategyPattern/NoQuack.cpp
	${MKDIR} -p ${OBJECTDIR}/ORiley/StrategyPattern
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -std=c++17 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/ORiley/StrategyPattern/NoQuack.o ORiley/StrategyPattern/NoQuack.cpp

${OBJECTDIR}/ORiley/StrategyPattern/Quack.o: ORiley/StrategyPattern/Quack.cpp
	${MKDIR} -p ${OBJECTDIR}/ORiley/StrategyPattern
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -std=c++17 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/ORiley/StrategyPattern/Quack.o ORiley/StrategyPattern/Quack.cpp

${OBJECTDIR}/ORiley/StrategyPattern/SimpleFlying.o: ORiley/StrategyPattern/SimpleFlying.cpp
	${MKDIR} -p ${OBJECTDIR}/ORiley/StrategyPattern
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -std=c++17 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/ORiley/StrategyPattern/SimpleFlying.o ORiley/StrategyPattern/SimpleFlying.cpp

${OBJECTDIR}/Structural/Bridge/PimplIdiom/Person2.o: Structural/Bridge/PimplIdiom/Person2.cpp
	${MKDIR} -p ${OBJECTDIR}/Structural/Bridge/PimplIdiom
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -std=c++17 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Structural/Bridge/PimplIdiom/Person2.o Structural/Bridge/PimplIdiom/Person2.cpp

${OBJECTDIR}/Structural/Bridge/PimplIdiom/SecondAttempt.o: Structural/Bridge/PimplIdiom/SecondAttempt.cpp
	${MKDIR} -p ${OBJECTDIR}/Structural/Bridge/PimplIdiom
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -std=c++17 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Structural/Bridge/PimplIdiom/SecondAttempt.o Structural/Bridge/PimplIdiom/SecondAttempt.cpp

${OBJECTDIR}/main.o: main.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -std=c++17 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/main.o main.cpp

# Subprojects
.build-subprojects:

# Build Test Targets
.build-tests-conf: .build-tests-subprojects .build-conf ${TESTFILES}
.build-tests-subprojects:

${TESTDIR}/TestFiles/f1: ${TESTDIR}/SingletonTest.o ${OBJECTFILES:%.o=%_nomain.o}
	${MKDIR} -p ${TESTDIR}/TestFiles
	${LINK.cc} -o ${TESTDIR}/TestFiles/f1 $^ ${LDLIBSOPTIONS}   


${TESTDIR}/SingletonTest.o: SingletonTest.cpp 
	${MKDIR} -p ${TESTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -I. -std=c++17 -MMD -MP -MF "$@.d" -o ${TESTDIR}/SingletonTest.o SingletonTest.cpp


${OBJECTDIR}/Behavioral/Mediator/ChatPerson2_nomain.o: ${OBJECTDIR}/Behavioral/Mediator/ChatPerson2.o Behavioral/Mediator/ChatPerson2.cpp 
	${MKDIR} -p ${OBJECTDIR}/Behavioral/Mediator
	@NMOUTPUT=`${NM} ${OBJECTDIR}/Behavioral/Mediator/ChatPerson2.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -O2 -std=c++17 -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Behavioral/Mediator/ChatPerson2_nomain.o Behavioral/Mediator/ChatPerson2.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/Behavioral/Mediator/ChatPerson2.o ${OBJECTDIR}/Behavioral/Mediator/ChatPerson2_nomain.o;\
	fi

${OBJECTDIR}/Behavioral/Mediator/ChatRoom2_nomain.o: ${OBJECTDIR}/Behavioral/Mediator/ChatRoom2.o Behavioral/Mediator/ChatRoom2.cpp 
	${MKDIR} -p ${OBJECTDIR}/Behavioral/Mediator
	@NMOUTPUT=`${NM} ${OBJECTDIR}/Behavioral/Mediator/ChatRoom2.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -O2 -std=c++17 -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Behavioral/Mediator/ChatRoom2_nomain.o Behavioral/Mediator/ChatRoom2.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/Behavioral/Mediator/ChatRoom2.o ${OBJECTDIR}/Behavioral/Mediator/ChatRoom2_nomain.o;\
	fi

${OBJECTDIR}/Behavioral/Observer/Observable_nomain.o: ${OBJECTDIR}/Behavioral/Observer/Observable.o Behavioral/Observer/Observable.cpp 
	${MKDIR} -p ${OBJECTDIR}/Behavioral/Observer
	@NMOUTPUT=`${NM} ${OBJECTDIR}/Behavioral/Observer/Observable.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -O2 -std=c++17 -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Behavioral/Observer/Observable_nomain.o Behavioral/Observer/Observable.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/Behavioral/Observer/Observable.o ${OBJECTDIR}/Behavioral/Observer/Observable_nomain.o;\
	fi

${OBJECTDIR}/Behavioral/Observer/Observer_nomain.o: ${OBJECTDIR}/Behavioral/Observer/Observer.o Behavioral/Observer/Observer.cpp 
	${MKDIR} -p ${OBJECTDIR}/Behavioral/Observer
	@NMOUTPUT=`${NM} ${OBJECTDIR}/Behavioral/Observer/Observer.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -O2 -std=c++17 -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Behavioral/Observer/Observer_nomain.o Behavioral/Observer/Observer.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/Behavioral/Observer/Observer.o ${OBJECTDIR}/Behavioral/Observer/Observer_nomain.o;\
	fi

${OBJECTDIR}/Behavioral/Observer/SaferObservable_nomain.o: ${OBJECTDIR}/Behavioral/Observer/SaferObservable.o Behavioral/Observer/SaferObservable.cpp 
	${MKDIR} -p ${OBJECTDIR}/Behavioral/Observer
	@NMOUTPUT=`${NM} ${OBJECTDIR}/Behavioral/Observer/SaferObservable.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -O2 -std=c++17 -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Behavioral/Observer/SaferObservable_nomain.o Behavioral/Observer/SaferObservable.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/Behavioral/Observer/SaferObservable.o ${OBJECTDIR}/Behavioral/Observer/SaferObservable_nomain.o;\
	fi

${OBJECTDIR}/Creational/Builder/ComplicateBuilder/Person_nomain.o: ${OBJECTDIR}/Creational/Builder/ComplicateBuilder/Person.o Creational/Builder/ComplicateBuilder/Person.cpp 
	${MKDIR} -p ${OBJECTDIR}/Creational/Builder/ComplicateBuilder
	@NMOUTPUT=`${NM} ${OBJECTDIR}/Creational/Builder/ComplicateBuilder/Person.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -O2 -std=c++17 -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Creational/Builder/ComplicateBuilder/Person_nomain.o Creational/Builder/ComplicateBuilder/Person.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/Creational/Builder/ComplicateBuilder/Person.o ${OBJECTDIR}/Creational/Builder/ComplicateBuilder/Person_nomain.o;\
	fi

${OBJECTDIR}/Creational/Builder/ComplicateBuilder/PersonBuilder_nomain.o: ${OBJECTDIR}/Creational/Builder/ComplicateBuilder/PersonBuilder.o Creational/Builder/ComplicateBuilder/PersonBuilder.cpp 
	${MKDIR} -p ${OBJECTDIR}/Creational/Builder/ComplicateBuilder
	@NMOUTPUT=`${NM} ${OBJECTDIR}/Creational/Builder/ComplicateBuilder/PersonBuilder.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -O2 -std=c++17 -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Creational/Builder/ComplicateBuilder/PersonBuilder_nomain.o Creational/Builder/ComplicateBuilder/PersonBuilder.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/Creational/Builder/ComplicateBuilder/PersonBuilder.o ${OBJECTDIR}/Creational/Builder/ComplicateBuilder/PersonBuilder_nomain.o;\
	fi

${OBJECTDIR}/Creational/Builder/VechicleBuilder/Vechicle_nomain.o: ${OBJECTDIR}/Creational/Builder/VechicleBuilder/Vechicle.o Creational/Builder/VechicleBuilder/Vechicle.cpp 
	${MKDIR} -p ${OBJECTDIR}/Creational/Builder/VechicleBuilder
	@NMOUTPUT=`${NM} ${OBJECTDIR}/Creational/Builder/VechicleBuilder/Vechicle.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -O2 -std=c++17 -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Creational/Builder/VechicleBuilder/Vechicle_nomain.o Creational/Builder/VechicleBuilder/Vechicle.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/Creational/Builder/VechicleBuilder/Vechicle.o ${OBJECTDIR}/Creational/Builder/VechicleBuilder/Vechicle_nomain.o;\
	fi

${OBJECTDIR}/Creational/Builder/VechicleBuilder/VechicleBuilder_nomain.o: ${OBJECTDIR}/Creational/Builder/VechicleBuilder/VechicleBuilder.o Creational/Builder/VechicleBuilder/VechicleBuilder.cpp 
	${MKDIR} -p ${OBJECTDIR}/Creational/Builder/VechicleBuilder
	@NMOUTPUT=`${NM} ${OBJECTDIR}/Creational/Builder/VechicleBuilder/VechicleBuilder.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -O2 -std=c++17 -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Creational/Builder/VechicleBuilder/VechicleBuilder_nomain.o Creational/Builder/VechicleBuilder/VechicleBuilder.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/Creational/Builder/VechicleBuilder/VechicleBuilder.o ${OBJECTDIR}/Creational/Builder/VechicleBuilder/VechicleBuilder_nomain.o;\
	fi

${OBJECTDIR}/ORiley/ObserverPattern/DigitalDisplay_nomain.o: ${OBJECTDIR}/ORiley/ObserverPattern/DigitalDisplay.o ORiley/ObserverPattern/DigitalDisplay.cpp 
	${MKDIR} -p ${OBJECTDIR}/ORiley/ObserverPattern
	@NMOUTPUT=`${NM} ${OBJECTDIR}/ORiley/ObserverPattern/DigitalDisplay.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -O2 -std=c++17 -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/ORiley/ObserverPattern/DigitalDisplay_nomain.o ORiley/ObserverPattern/DigitalDisplay.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/ORiley/ObserverPattern/DigitalDisplay.o ${OBJECTDIR}/ORiley/ObserverPattern/DigitalDisplay_nomain.o;\
	fi

${OBJECTDIR}/ORiley/ObserverPattern/PCDisplay_nomain.o: ${OBJECTDIR}/ORiley/ObserverPattern/PCDisplay.o ORiley/ObserverPattern/PCDisplay.cpp 
	${MKDIR} -p ${OBJECTDIR}/ORiley/ObserverPattern
	@NMOUTPUT=`${NM} ${OBJECTDIR}/ORiley/ObserverPattern/PCDisplay.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -O2 -std=c++17 -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/ORiley/ObserverPattern/PCDisplay_nomain.o ORiley/ObserverPattern/PCDisplay.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/ORiley/ObserverPattern/PCDisplay.o ${OBJECTDIR}/ORiley/ObserverPattern/PCDisplay_nomain.o;\
	fi

${OBJECTDIR}/ORiley/ObserverPattern/PhoneDisplay_nomain.o: ${OBJECTDIR}/ORiley/ObserverPattern/PhoneDisplay.o ORiley/ObserverPattern/PhoneDisplay.cpp 
	${MKDIR} -p ${OBJECTDIR}/ORiley/ObserverPattern
	@NMOUTPUT=`${NM} ${OBJECTDIR}/ORiley/ObserverPattern/PhoneDisplay.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -O2 -std=c++17 -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/ORiley/ObserverPattern/PhoneDisplay_nomain.o ORiley/ObserverPattern/PhoneDisplay.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/ORiley/ObserverPattern/PhoneDisplay.o ${OBJECTDIR}/ORiley/ObserverPattern/PhoneDisplay_nomain.o;\
	fi

${OBJECTDIR}/ORiley/ObserverPattern/WeatherStation_nomain.o: ${OBJECTDIR}/ORiley/ObserverPattern/WeatherStation.o ORiley/ObserverPattern/WeatherStation.cpp 
	${MKDIR} -p ${OBJECTDIR}/ORiley/ObserverPattern
	@NMOUTPUT=`${NM} ${OBJECTDIR}/ORiley/ObserverPattern/WeatherStation.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -O2 -std=c++17 -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/ORiley/ObserverPattern/WeatherStation_nomain.o ORiley/ObserverPattern/WeatherStation.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/ORiley/ObserverPattern/WeatherStation.o ${OBJECTDIR}/ORiley/ObserverPattern/WeatherStation_nomain.o;\
	fi

${OBJECTDIR}/ORiley/StrategyPattern/DisplayAsGraphics_nomain.o: ${OBJECTDIR}/ORiley/StrategyPattern/DisplayAsGraphics.o ORiley/StrategyPattern/DisplayAsGraphics.cpp 
	${MKDIR} -p ${OBJECTDIR}/ORiley/StrategyPattern
	@NMOUTPUT=`${NM} ${OBJECTDIR}/ORiley/StrategyPattern/DisplayAsGraphics.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -O2 -std=c++17 -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/ORiley/StrategyPattern/DisplayAsGraphics_nomain.o ORiley/StrategyPattern/DisplayAsGraphics.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/ORiley/StrategyPattern/DisplayAsGraphics.o ${OBJECTDIR}/ORiley/StrategyPattern/DisplayAsGraphics_nomain.o;\
	fi

${OBJECTDIR}/ORiley/StrategyPattern/DisplayAsText_nomain.o: ${OBJECTDIR}/ORiley/StrategyPattern/DisplayAsText.o ORiley/StrategyPattern/DisplayAsText.cpp 
	${MKDIR} -p ${OBJECTDIR}/ORiley/StrategyPattern
	@NMOUTPUT=`${NM} ${OBJECTDIR}/ORiley/StrategyPattern/DisplayAsText.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -O2 -std=c++17 -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/ORiley/StrategyPattern/DisplayAsText_nomain.o ORiley/StrategyPattern/DisplayAsText.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/ORiley/StrategyPattern/DisplayAsText.o ${OBJECTDIR}/ORiley/StrategyPattern/DisplayAsText_nomain.o;\
	fi

${OBJECTDIR}/ORiley/StrategyPattern/Duck_nomain.o: ${OBJECTDIR}/ORiley/StrategyPattern/Duck.o ORiley/StrategyPattern/Duck.cpp 
	${MKDIR} -p ${OBJECTDIR}/ORiley/StrategyPattern
	@NMOUTPUT=`${NM} ${OBJECTDIR}/ORiley/StrategyPattern/Duck.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -O2 -std=c++17 -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/ORiley/StrategyPattern/Duck_nomain.o ORiley/StrategyPattern/Duck.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/ORiley/StrategyPattern/Duck.o ${OBJECTDIR}/ORiley/StrategyPattern/Duck_nomain.o;\
	fi

${OBJECTDIR}/ORiley/StrategyPattern/JetFlying_nomain.o: ${OBJECTDIR}/ORiley/StrategyPattern/JetFlying.o ORiley/StrategyPattern/JetFlying.cpp 
	${MKDIR} -p ${OBJECTDIR}/ORiley/StrategyPattern
	@NMOUTPUT=`${NM} ${OBJECTDIR}/ORiley/StrategyPattern/JetFlying.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -O2 -std=c++17 -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/ORiley/StrategyPattern/JetFlying_nomain.o ORiley/StrategyPattern/JetFlying.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/ORiley/StrategyPattern/JetFlying.o ${OBJECTDIR}/ORiley/StrategyPattern/JetFlying_nomain.o;\
	fi

${OBJECTDIR}/ORiley/StrategyPattern/NoFlying_nomain.o: ${OBJECTDIR}/ORiley/StrategyPattern/NoFlying.o ORiley/StrategyPattern/NoFlying.cpp 
	${MKDIR} -p ${OBJECTDIR}/ORiley/StrategyPattern
	@NMOUTPUT=`${NM} ${OBJECTDIR}/ORiley/StrategyPattern/NoFlying.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -O2 -std=c++17 -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/ORiley/StrategyPattern/NoFlying_nomain.o ORiley/StrategyPattern/NoFlying.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/ORiley/StrategyPattern/NoFlying.o ${OBJECTDIR}/ORiley/StrategyPattern/NoFlying_nomain.o;\
	fi

${OBJECTDIR}/ORiley/StrategyPattern/NoQuack_nomain.o: ${OBJECTDIR}/ORiley/StrategyPattern/NoQuack.o ORiley/StrategyPattern/NoQuack.cpp 
	${MKDIR} -p ${OBJECTDIR}/ORiley/StrategyPattern
	@NMOUTPUT=`${NM} ${OBJECTDIR}/ORiley/StrategyPattern/NoQuack.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -O2 -std=c++17 -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/ORiley/StrategyPattern/NoQuack_nomain.o ORiley/StrategyPattern/NoQuack.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/ORiley/StrategyPattern/NoQuack.o ${OBJECTDIR}/ORiley/StrategyPattern/NoQuack_nomain.o;\
	fi

${OBJECTDIR}/ORiley/StrategyPattern/Quack_nomain.o: ${OBJECTDIR}/ORiley/StrategyPattern/Quack.o ORiley/StrategyPattern/Quack.cpp 
	${MKDIR} -p ${OBJECTDIR}/ORiley/StrategyPattern
	@NMOUTPUT=`${NM} ${OBJECTDIR}/ORiley/StrategyPattern/Quack.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -O2 -std=c++17 -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/ORiley/StrategyPattern/Quack_nomain.o ORiley/StrategyPattern/Quack.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/ORiley/StrategyPattern/Quack.o ${OBJECTDIR}/ORiley/StrategyPattern/Quack_nomain.o;\
	fi

${OBJECTDIR}/ORiley/StrategyPattern/SimpleFlying_nomain.o: ${OBJECTDIR}/ORiley/StrategyPattern/SimpleFlying.o ORiley/StrategyPattern/SimpleFlying.cpp 
	${MKDIR} -p ${OBJECTDIR}/ORiley/StrategyPattern
	@NMOUTPUT=`${NM} ${OBJECTDIR}/ORiley/StrategyPattern/SimpleFlying.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -O2 -std=c++17 -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/ORiley/StrategyPattern/SimpleFlying_nomain.o ORiley/StrategyPattern/SimpleFlying.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/ORiley/StrategyPattern/SimpleFlying.o ${OBJECTDIR}/ORiley/StrategyPattern/SimpleFlying_nomain.o;\
	fi

${OBJECTDIR}/Structural/Bridge/PimplIdiom/Person2_nomain.o: ${OBJECTDIR}/Structural/Bridge/PimplIdiom/Person2.o Structural/Bridge/PimplIdiom/Person2.cpp 
	${MKDIR} -p ${OBJECTDIR}/Structural/Bridge/PimplIdiom
	@NMOUTPUT=`${NM} ${OBJECTDIR}/Structural/Bridge/PimplIdiom/Person2.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -O2 -std=c++17 -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Structural/Bridge/PimplIdiom/Person2_nomain.o Structural/Bridge/PimplIdiom/Person2.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/Structural/Bridge/PimplIdiom/Person2.o ${OBJECTDIR}/Structural/Bridge/PimplIdiom/Person2_nomain.o;\
	fi

${OBJECTDIR}/Structural/Bridge/PimplIdiom/SecondAttempt_nomain.o: ${OBJECTDIR}/Structural/Bridge/PimplIdiom/SecondAttempt.o Structural/Bridge/PimplIdiom/SecondAttempt.cpp 
	${MKDIR} -p ${OBJECTDIR}/Structural/Bridge/PimplIdiom
	@NMOUTPUT=`${NM} ${OBJECTDIR}/Structural/Bridge/PimplIdiom/SecondAttempt.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -O2 -std=c++17 -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Structural/Bridge/PimplIdiom/SecondAttempt_nomain.o Structural/Bridge/PimplIdiom/SecondAttempt.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/Structural/Bridge/PimplIdiom/SecondAttempt.o ${OBJECTDIR}/Structural/Bridge/PimplIdiom/SecondAttempt_nomain.o;\
	fi

${OBJECTDIR}/main_nomain.o: ${OBJECTDIR}/main.o main.cpp 
	${MKDIR} -p ${OBJECTDIR}
	@NMOUTPUT=`${NM} ${OBJECTDIR}/main.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -O2 -std=c++17 -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/main_nomain.o main.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/main.o ${OBJECTDIR}/main_nomain.o;\
	fi

# Run Test Targets
.test-conf:
	@if [ "${TEST}" = "" ]; \
	then  \
	    ${TESTDIR}/TestFiles/f1 || true; \
	else  \
	    ./${TEST} || true; \
	fi

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
