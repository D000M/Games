/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   OverloadGlobalNewAndDelete.h
 * Author: default
 *
 * Created on December 11, 2019, 3:07 PM
 */

#ifndef OVERLOADGLOBALNEWANDDELETE_H
#define OVERLOADGLOBALNEWANDDELETE_H

#include <stdio.h>
#include <stdlib.h>


//Overload global operator new
void* operator new(size_t size) {
    printf("Global Operator new: %d Bytes allocated\n", size);
    void* objectMemory = malloc(size);
    if(!objectMemory) {
        puts("Out of memory for global operator new\n");
    }
    return objectMemory;
}

void operator delete(void* objectMemory) {
    puts("Global Operator delete:\n");
    free(objectMemory);
}
class TestNewDel {
    int arr[100];
public:
    TestNewDel() {
        printf("TestNewDel Constructor\n");
    }
    ~TestNewDel() {
        printf("TestNewDel Destructor\n");
    }
};

void testGlobalNewDel() {
    puts("Creating and destroying int: \n");
    int* p = new int(47);
    delete p;
    puts("Creating and destroying an TestNewDel: \n");
    TestNewDel* myClass = new TestNewDel();
    delete myClass;
    puts("Creating and destroying TestNewDel Arr: \n");
    TestNewDel* myArr = new TestNewDel[3];
    delete [] myArr;
}
#endif /* OVERLOADGLOBALNEWANDDELETE_H */

