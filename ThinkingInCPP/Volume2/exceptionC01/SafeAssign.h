/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   SafeAssign.h
 * Author: default
 *
 * Created on January 9, 2020, 4:00 PM
 */

#ifndef SAFEASSIGN_H
#define SAFEASSIGN_H

#include <iostream>
#include <new>
#include <cstring>
#include <cstddef>

/**
 * Rules for operator = 
 * 
1.  Make sure you’re not assigning to self. If you are, go to step 6. (This is strictly an optimization.)

2.  Allocate new memory required by pointer data members.

3.  Copy data from the old memory to the new.

4.  Delete the old memory.

5.  Update the object’s state by assigning the new heap pointers to the pointer data members.

6.  Return *this.
 * 
 */

//SafeAssign.cpp example

//A class that has 2 member pointers that use heap
class HasPointers {
    //A Handle class to hold the data
    struct MyData {
        const char* theString;
        const int* theInts;
        size_t numInts;
        MyData(const char* pString, const int* pInts, size_t nInts) 
            : theString{pString},
              theInts{pInts},
              numInts{nInts} {
            
        }
    }*theData;  //The Handle
    
    //Clone and cleanup functions
    static MyData* clone(const char* otherString, const int* otherInts, size_t nInts) {
        char* newChars = new char[strlen(otherString) + 1];
        int* newInts;
        
        try {
            newInts = new int[nInts];
        }
        catch(std::bad_alloc&) {
            delete [] newChars;
            throw;
        }
        
        try {
            // This example uses built-in types, so it won't
            // throw, but for class types it could throw, so we
            // use a try block for illustration. (This is the
            // point of the example!)
            strcpy(newChars, otherString);
            for(size_t i{0}; i < nInts; i++) {
                newInts[i] = otherInts[i];
            }
        }
        catch(...) {
            delete [] newInts;
            delete [] newChars;
            throw;
        }
        return new MyData(newChars, newInts, nInts);
    }
    
    static MyData* clone(const MyData* otherData) {
        return clone(otherData->theString, otherData->theInts, otherData->numInts);
    }
    static void cleanup(const MyData* data) {
        delete [] data->theString;
        delete [] data->theInts;
        delete data;
    }
    
public:
    HasPointers(const char* someString, const int* someInt, size_t numInts) {
        theData = clone(someString, someInt, numInts);
    }
    HasPointers(const HasPointers& source) {
        theData = clone(source.theData);
    }
    HasPointers& operator = (const HasPointers& other) {
        if(this != &other) {
            MyData* newData = clone(other.theData->theString, other.theData->theInts, other.theData->numInts);
            cleanup(theData);
            theData = newData;
        }
        return *this;
    }
    ~HasPointers() {
        cleanup(theData);
    }
    
    friend std::ostream& operator << (std::ostream& os, const HasPointers& obj) {
        os << obj.theData->theString << ": ";
        for(size_t i{0}; i < obj.theData->numInts; i++) {
            os << obj.theData->theInts[i] << " ";
        }
        return os;
    }
};

void testSafeAssignment();
#endif /* SAFEASSIGN_H */

