/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include <iostream>
#include <thread>
#include <vector>
#include <algorithm>

#include "CreateThreads.h"


//Creating Thread using function Pointer
void threadFunction() {
    for(int i{0}; i < 100; i++) {
        std::cout << "Thread Function Executing!\n";
    }
}

void executeFunctionPointer() {
    std::thread threadObj{threadFunction};
    for(int i{0}; i < 100; i++) {
        std::cout << "Main Function Executing!\n";
    }
    threadObj.join();
    std::cout << "Exiting from main function!\n";
}
////////////////


//Creating Thread using Function Object

void executeFunctionObject() {
    std::thread otherObj{ (DisplayThread()) };
    for(int i{0}; i < 100; i++) {
        std::cout << "Main Object\n";
    }
    std::cout << "Waiting for thread to complete!\n";
    otherObj.join();
    std::cout << "Exiting from main thread!\n";
}


//Create thread using lambda
void executeLambdaThread() {
    std::thread otherObj{[]() {
        for(int i{0}; i < 10000; i++) {
            std::cout << "Other Object Thread\n";
        }
    } };
    
    for(int i{0}; i < 10000; i++) {
        std::cout << "Main Thread Object\n";
    }
    
    otherObj.join();
    std::cout << "Exiting from main Thread!\n";
}

//Differentiating between threads
void threadFunction2() {
    std::cout << "Inside Thread Id: " << std::this_thread::get_id() << std::endl;
}

void testDifferentiatingThreads() {
    std::thread objOne{threadFunction2};
    std::thread objTwo{threadFunction2};
    
    if(objOne.get_id() != objTwo.get_id()) {
        std::cout << "Both Threads has different IDs\n";
    }
    
    std::cout << "From main thread ID of objOne thread: " << objOne.get_id() << std::endl;
    std::cout << "From main thread ID of objTwo thread: " << objTwo.get_id() << std::endl;
    
    objOne.join();
    objTwo.join();
}


//Joining threads
int WorkerThread::nId = 0;
void testJoiningThreads() {
    std::vector<std::thread> threadList;
    for(int i{0}; i < 10; i++) {
        threadList.emplace_back(std::thread{WorkerThread()});
    }
    
    std::cout << "Wait for all WorkerThread to finish!\n";
    if(threadList.at(0).joinable()) {
        std::cout << "Detaching thread.\n";
        threadList.at(0).detach();
    }
    if(threadList.at(0).joinable()) {
        std::cout << "Wont Enter here.\n";
        threadList.at(0).detach();
    }
    //+1 because we already detach the thread at position 0
    std::for_each(std::begin(threadList) + 1, std::end(threadList), std::mem_fn(&std::thread::join));
    //Before detach() threads always check if thread is join-able.
    
    
    std::cout << "Exiting from the main thread!\n";
}

//RAII thread for exceptions
void testRAIIThread() {
    std::thread myThread{threadFunction};
    
    //If we comment this line the thread wont call detach() and the program will terminate
    ThreadRAII autoJoin(myThread);
}


//Passing arguments to threads
void threadCallback(int n, std::string str) {
    std::cout << "Number passed: " << n << std::endl;
    std::cout << "String passed: " << str << std::endl;
}
void testThreadCallback() {
    int n = 10;
    std::string str = "Second Arg";
    std::thread objOne{threadCallback, n, str};
    if(objOne.joinable()) {
        std::cout << "Join the thread to the main thread\n";
        objOne.join();
    }
    if(objOne.joinable()) {
        std::cout << "Cant enter here after first join()\n";
        objOne.join();
    }
}

//Wrong pass callback by address
void wrongCallback(int* p) {
    std::cout << "Inside Thread: "" : p = " << *p << std::endl;
    std::chrono::milliseconds duration{1000};
    std::this_thread::sleep_for(duration);
    *p = 20;
}
void startNewThread() {
    int i = 10;
    std::cout << "Inside Main Thread i = " << i << std::endl;
    std::thread otherObj{wrongCallback, &i};
    
    ThreadRAII cleanThread{otherObj};
    std::cout << "Inside Main Thread i = " << i << std::endl;
}
void testWrongThreadCallback() {
    startNewThread();
    std::this_thread::sleep_for(std::chrono::milliseconds{2000});
    
}