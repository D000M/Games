/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include <iostream>

#include "ExceptionExamples.h"

MyError::MyError(const char* const msg) : data{msg} {
    
}

void ex01f() {
    throw MyError("This Part Of the code throws error\n Error in ex01f()");
}

void testEx01f() {
    ex01f();
}

//////
// example 02
C01Rainbow::C01Rainbow() {
    std::cout << "C01Rainbow()\n";
}
C01Rainbow::~C01Rainbow() {
    std::cout << "~C01Rainbow()\n";
}
void c01oz() {
    C01Rainbow r;
    for(int i = 0; i < 3; i++) {
        std::cout << i << ": SSSSSSSSSSSSSSSSS\n";
    }
    throw 47;
}
void testC01Rainbow() {
    try {
        std::cout << "Inside Try block\n";
        c01oz();
    }
    catch(int) {
        std::cout << "Inside Catch Block\n";
    }
}

////Autoexcep.cpp
void testExceptThrow() {
    throw Except1();
}
void testAutoexcep() {
    try {
        testExceptThrow();
    }
    catch(Except2&) {
        std::cout << "Inside Catch Except2\n";
    }
    catch(Except1&) {
        std::cout << "Inside Catch Except1\n";
    }
}

/////////////
//example Trace.cpp
int Trace::counter = 0;
void testTrace() {
    try {
        Trace t1;
        Trace tArr[5]; //throws exception
        Trace t2;   //wont get here after throw
    }
    catch(int i) {
        std::cout << "Exception Caught: " << i << std::endl;
    }
}

//example 05 Wrapper.cpp
void testWrapper() {
    try {
        C01UseResources res;
    }
    catch(int) {
        std::cout << "Catch int handler\n";
    }
    catch(...) {
        std::cout << "Catch ... handler\n";
    }
}