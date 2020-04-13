/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   TestDivideAndConquer.h
 * Author: default
 *
 * Created on February 22, 2019, 3:00 PM
 */

#ifndef TESTDIVIDEANDCONQUER_H
#define TESTDIVIDEANDCONQUER_H

#include "DivideAndConquer.h"


void testBruteForce( ) {
    int arr[] = {
        6, 5, 4, 3, 2, 1
    };
    bruteForce(arr, 6);
}

void testCountInversions() {
    int arr[] = { 7, 6, 1, 2, 3, 4, 5};
    int a = mergeAndCountInversions(arr, 7);
    std::cout << a << std::endl;
}

#endif /* TESTDIVIDEANDCONQUER_H */

