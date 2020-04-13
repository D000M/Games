/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   CreateThreads.h
 * Author: default
 *
 * Created on November 30, 2019, 2:40 PM
 */

#ifndef CREATETHREADS_H
#define CREATETHREADS_H

#include <thread>
#include <iostream>
#include <queue>

//Create Thread Using Function Pointer
void threadFunction();
void executeFunctionPointer();


//Creating thread using Function Object
class DisplayThread {
public:
    void operator() () {
        for(int i{0}; i < 100; i++) {
            std::cout << "Thread function object!\n";
        }
    }
};
void executeFunctionObject();

//Create thread using lambda
void executeLambdaThread();


//Differentiating between threads
void threadFunction2();
void testDifferentiatingThreads();


//Joining threads with std::thread::join()
class WorkerThread {
public:
    static int nId;
    void operator() () {
        std::cout << "Worker Thread: " << nId++ << " is executing\n";
    }
};
void testJoiningThreads();


//We should no forget to call join() or detach in case of exception thats why we should always use RAII(RESOURCE ACQUISITION IS INITIALIZATION)
class ThreadRAII {
    std::thread& myThread;
public:
    ThreadRAII(std::thread& lThread) 
            : myThread{lThread} {}
            
    ~ThreadRAII() {
        //Check if thread is joinable()
        if(myThread.joinable()) {
            std::cout << "Thread detached\n";
            myThread.detach();
        }
    }
};
void testRAIIThread();


//Passing Arguments to threads Correct way, pass arguments by value
void threadCallback(int n, std::string str);
void testThreadCallback();

//Passing arguments to thread Wrong way dont pass them by address because some other thread can use this variable till this thread is using them too.
void wrongCallback(int* p);
void startNewThread();
void testWrongThreadCallback();


class SharedQueue {
    const int SIZE = 10;
    std::queue<std::string> myQueue;
public:
    void addElement(const std::string& elem) {
        
    }
};

#endif /* CREATETHREADS_H */

