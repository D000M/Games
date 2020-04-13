/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   testStrasen.h
 * Author: default
 *
 * Created on February 27, 2019, 2:17 PM
 */

#ifndef TESTSTRASEN_H
#define TESTSTRASEN_H
#include <iostream>
#include "StrasenSubcubic.h"


void testSimpleMultiply() {
    multiple2Matrix();
}
void print2DimmArray(int** arr, int size) {
    for(int i = 0; i < size; ++i) {
        for(int j = 0; j < size; ++j) {
            std::cout << arr[i][j] << " ";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}


void testRecursivelyMultiply() {
    constexpr int size = 32;
    int** A = new int*[size];
    for(int i = 0; i < size; ++i) {
        A[i] = new int[size];
        for(int j = 0; j < size; ++j) {
            A[i][j] = i + j + 2;
        }
    }
    print2DimmArray(A, size);
    int** B = new int*[size];
    for(int i = 0; i < size; ++i) {
        B[i] = new int[size];
        for(int j = 0; j < size; ++j) {
            B[i][j] = i * j + 3;
        }
    }
    print2DimmArray(B, size);
    int** C = new int*[size];
    for(int i = 0; i < size; ++i) {
        C[i] = new int[size];
        for(int j = 0; j < size; ++j) {
            C[i][j] = 0;
        }
    }
    recursiveMultiply(A, B, C, size);
    print2DimmArray(C, size);
    printCCCC();
    for(int i = 0; i < size; ++i) {
        delete[] A[i];
        delete[] B[i];
        delete[] C[i];
    }
    delete[] A;
    delete[] B;
    delete[] C;
}

#endif /* TESTSTRASEN_H */

