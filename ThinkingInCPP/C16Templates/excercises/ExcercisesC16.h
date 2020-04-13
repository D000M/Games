/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   ExcercisesC16.h
 * Author: default
 *
 * Created on December 21, 2019, 4:45 PM
 */

#ifndef EXCERCISESC16_H
#define EXCERCISESC16_H

#include <iostream>

template<typename T>
T fibonaciTemplate(T n) {
    if(n <= 1) {
        return 1;
    }
    return fibonaciTemplate(n - 1) + fibonaciTemplate(n - 2);
}

template<typename T>
T effectiveFibTemplate(T n) {
    const int size = 100;
    if (n >= 100) {
        throw ("To big fibonacci");
    }
    static int fibArr[size];
    fibArr[0] = fibArr[1] = 1;
    
    int i;
    for(i = 0; i < size; i++) {
        if(fibArr[i] == 0) {
            break;
        }
    }
    while(i <= n) {
        fibArr[i] = fibArr[i - 1] + fibArr[i - 2];
        i++;
    }
    return fibArr[int(n)];
}

void testFibonaciTemplate();

#endif /* EXCERCISESC16_H */

