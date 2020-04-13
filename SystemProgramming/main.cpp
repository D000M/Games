/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: default
 *
 * Created on November 20, 2019, 11:16 AM
 */

#include <cstdlib>
#include <string>
#include <iostream>

#include "SystemCallsAndDeviceDrivers/WorkingWithFiles/WriteFiles.h"
#include "SystemCallsAndDeviceDrivers/WorkingWithFiles/ReadFiles.h"
#include "SystemCallsAndDeviceDrivers/WorkingWithFiles/OpenFiles.h"
#include "SystemCallsAndDeviceDrivers/WorkingWithFiles/OtherSystemCallsForFiles.h"
#include "SystemCallsAndDeviceDrivers/WorkingWithFiles/RecursivePrintDirectory.h"
#include "SystemCallsAndDeviceDrivers/WorkingWithFiles/Usingmmap.h"
#include "SystemCallsAndDeviceDrivers/TimeAndDate/TimeTest.h"
#include "SystemCallsAndDeviceDrivers/TimeAndDate/TempFile.h"
#include "SystemCallsAndDeviceDrivers/UserInformation/GetUserInformation.h"
#include "SystemCallsAndDeviceDrivers/UserInformation/ResourceLimits.h"
#include "ProcessAndSignals/RunningOtherPrograms.h"
#include "PosixThreads/Threads.h"
#include "C++11Threads/ThreeDifferentWaysToCreateThreads/CreateThreads.h"

using namespace std;

/*
 * 
 */

void printCommandLineArgs(int argc, char* argv[]) {
    int arg;
    for(arg = 0; arg < argc; arg++) {
        if(argv[arg][0] == '-') {
            printf("option: %s\n", argv[arg] + 1);
        }
        else {
            printf("argument %d: %s\n", arg, argv[arg]);
        }
    }
    exit(0);
}

void printEnviroment() {
    char **env = environ;
    while(*env) {
        printf("%s/\n",*env);
        env++;
    }
    exit(0);
}

void towerOfHanoi(int disks, const std::string& leftPillar, const std::string& middlePillar, const std::string& rightPillar) {
    if(disks > 0) {
        towerOfHanoi(disks - 1, leftPillar, rightPillar, middlePillar);
        std::cout << "From: " << leftPillar << " to " << rightPillar << std::endl;
        towerOfHanoi(disks - 1, middlePillar, leftPillar, rightPillar);
    }
}


int main(int argc, char** argv) {
//
//    printToConsole();
//    readFromConsole();
//    copyFromBlocks();
//    testCopyFile();
//    testPrintHomeDirectory();
//    printDirectoryTree(argc, argv);
//    createRecords();
//    printCommandLineArgs(argc, argv);
//    printEnviroment();
//    testTime();
//    testDiffTime2();
//    testGMTtime();
//    testUsingLocalTime();
//    convertStructTmToTime();
//    testASCtime();
//    testCTime();
//    testSTRFTIMEandSTRPTIME();
//    testTMPNAMAndTMPFILE();
//    getUserIDInformation();
//    getHostName();
//    testResourceUsage();
    
//    runPS();
//    towerOfHanoi(3, "A", "B", "C");
    
//    testFork();
//    testWaitFork();
//    testSignalHandling();
//    testPThread();
//    test2Threads();
    
//    executeFunctionPointer();
//    executeFunctionObject();
//    executeLambdaThread();
//    testDifferentiatingThreads();
//    testJoiningThreads();
//    testRAIIThread();
//    testThreadCallback();
    testWrongThreadCallback();
    
    return 0;
}

