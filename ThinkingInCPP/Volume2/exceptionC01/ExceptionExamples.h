/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   ExceptionExamples.h
 * Author: default
 *
 * Created on January 6, 2020, 1:19 PM
 */

#ifndef EXCEPTIONEXAMPLES_H
#define EXCEPTIONEXAMPLES_H

#include <iostream>


class MyError {
    const char* const data;
public:
    MyError(const char* const msg = "");
};

void ex01f();


void testEx01f();
////////////////////

class C01Rainbow {
public:
    C01Rainbow();
    ~C01Rainbow();
};

void c01oz();
void testC01Rainbow();

/////////////// 
//example 03 Autoexcp.cpp
class Except1 {};
class Except2 {
public:
    Except2(const Except1&) {}
};
void testExceptThrow();
void testAutoexcep();

////////////////
//example 04 Cleanup.cpp
class Trace {
    static int counter;
    int objId;
public:
    Trace() {
        objId = counter++;
        std::cout << "Constructing Trace # " << objId << std::endl;
        if(objId == 3) {
            throw 3;
        }
    }
    ~Trace() {
        std::cout << "Destructing Trace # " << objId << std::endl;
    }
};
void testTrace();


//example 05 Wrapped.cpp
template<class T, int size = 1>
class PtrWrap {
    T* ptr;
public:
    //Exception class
    class RangeError {
    public:
        RangeError(const char* msg = "RangeErrorMsg") {
            std::cout << msg << std::endl;
        }
    };   //end exception class
    
    PtrWrap() {
        ptr = new T[size];
        std::cout << "PtrWrap Constructor!\n";
    }
    ~PtrWrap() {
        delete [] ptr;
        std::cout << "PtrWrap Destructor!\n";
    }
    
    T& operator [] (int index) throw(RangeError) {
        if(index >= 0 && index < size) {
            return ptr[index];
        }
        throw RangeError("RangeError() operator [] (int index) / Index out of bound\n");
    }
};
class C01Cat {
public:
    C01Cat() {
        std::cout << "Cat() Constructor\n";
    }
    ~C01Cat() {
        std::cout << "~Cat() Destructor\n";
    }
    void g();
};
class C01Dog {
public:
    void* operator new[] (size_t) {
        std::cout << "Allocating C01Dog\n";
        throw 47;
    }
    void operator delete [] (void* p) {
        std::cout << "Deallocating C01Dog\n";
        ::operator delete[](p);
    }
};
class C01UseResources {
    PtrWrap<C01Cat, 3> cats;
    PtrWrap<C01Dog> dog;
public:
    C01UseResources() {
        std::cout << "C01UseResources Constructor\n";
    }
    ~C01UseResources() {
        std::cout << "C01UseResources Destructor\n";
    }
    void f() {
        cats[1].g();
    }
};
void testWrapper();
#endif /* EXCEPTIONEXAMPLES_H */

