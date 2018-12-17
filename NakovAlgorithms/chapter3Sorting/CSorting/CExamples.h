/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   CExamples.h
 * Author: default
 *
 * Created on December 15, 2018, 11:46 AM
 */

#ifndef CEXAMPLES_H
#define CEXAMPLES_H

#include <stdlib.h>
#include <iostream>

#include "CSorts.h"


#ifdef __cplusplus
extern "C" {
#endif


void testCInsertionV1() {
    for(int i = 0; i < 10; i++) {
        int num = std::rand() % 100;
        m[i].key = num;
    }
    for(int i = 0; i < 10; i++) {
        std::cout << m[i].key << " ";
    }
    std::cout << std::endl;
    straightInsertionSortV2(m, 10);
    for(int i = 0; i < 10; i++) {
        std::cout << m[i].key << " ";
    }
    std::cout << std::endl;
}

void testShellSortV1() {
    
    struct CElem m[MAX_ELEM + steps0 + 2];
    
    for(int i = 0; i < MAX_ELEM + steps0 + 2; i++) {
        m[i].key = std::rand() % 1000 + 1;
    }
    for(int i = 0; i < MAX_ELEM + steps0 + 2; i++) {
        std::cout << m[i].key << " ";
    }
    std::cout << std::endl;
    shellSort(m + steps0 + 1, MAX_ELEM);
    std::cout << "Shell Sort:\n";
    for(int i = steps0 + 2; i < MAX_ELEM + steps0 + 2; i++) {
        std::cout << m[i].key << " ";
    }
}

void testBubbleSort1() {
    for(int i = 0; i < MAX_ELEM; i++) {
        m[i].key = std::rand() % 1000 + 1;
    }
    for(int i = 0; i < MAX_ELEM; i++) {
        std::cout << m[i].key << " ";
    }
    std::cout << std::endl;
    std::cout << "Bubble Sort: \n";
    bubbleSortV1(m, MAX_ELEM);
    for(int i = 0; i < MAX_ELEM; i++) {
        std::cout << m[i].key << " ";
    }
}

void testCQuickSort() {
    for(int i = 0; i < MAX_ELEM; i++) {
        m[i].key = std::rand() % 1000 + 1;
    }
    for(int i = 0; i < MAX_ELEM; i++) {
        std::cout << m[i].key << " ";
    }
    std::cout << std::endl;
    std::cout << "Quick Sort@@: \n";
    quickSort(0, 99);
    for(int i = 0; i < MAX_ELEM; i++) {
        std::cout << m[i].key << " ";
    }
}
void testCQuickSortV2() {
    for(int i = 0; i < MAX_ELEM; i++) {
        m[i].key = std::rand() % 1000 + 1;
    }
    for(int i = 0; i < MAX_ELEM; i++) {
        std::cout << m[i].key << " ";
    }
    std::cout << std::endl;
    std::cout << "Quick Sort2: \n";
    quickSortPartV2(0, 99);
    for(int i = 0; i < MAX_ELEM; i++) {
        std::cout << m[i].key << " ";
    }
}

void testQuickSortV3() {
    for(int i = 0; i < MAX_ELEM; i++) {
        m[i].key = std::rand() % 1000 + 1;
    }
    for(int i = 0; i < MAX_ELEM; i++) {
        std::cout << m[i].key << " ";
    }
    std::cout << std::endl;
    std::cout << "Quick Sort3: \n";
    quickSortV3();
    for(int i = 0; i < MAX_ELEM; i++) {
        std::cout << m[i].key << " ";
    }
}

void testCombSort() {
    for(int i = 0; i < MAX_ELEM; i++) {
        m[i].key = std::rand() % 1000 + 1;
    }
    for(int i = 0; i < MAX_ELEM; i++) {
        std::cout << m[i].key << " ";
    }
    std::cout << std::endl;
    std::cout << "Comb Sort: \n";
    combSortC(m, MAX_ELEM);
    for(int i = 0; i < MAX_ELEM; i++) {
        std::cout << m[i].key << " ";
    }
}
#ifdef __cplusplus
}
#endif

#endif /* CEXAMPLES_H */

