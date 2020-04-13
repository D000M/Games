/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   RecurrenceRelations.h
 * Author: default
 *
 * Created on March 1, 2019, 12:40 PM
 */

#ifndef RECURRENCERELATIONS_H
#define RECURRENCERELATIONS_H

#include <iostream>
#include <string>
#include <valarray>

/**
 * Recurrence Time
 * T(n) = { 1               n = 0        // simple case
 *        { T(n - 1) + 1    n > 0        // n - 1 case
 * @param n
 */
void test(int n) {
    if(n > 0) {
        std::cout << n << std::endl;
        test(n - 1);
    }
}

/**
 * Recurrence time
 * T(n) = { 1               n = 0
 *        { T(n - 1) + n    n > 0 
 * BigOh(n^2)
 * @param n
 */
void test2(int n) {
    if(n > 0) {
        for(int i = 0; i < n; i++) {
            std::cout << n << " ";
        }
        std::cout << std::endl;
        test2(n - 1);
    }
}

void test3(int n) {
    if(n > 0) {
        for(int i = 1; i < n; i *= 2) {
            std::cout << i << " ";
        }
        std::cout << std::endl;
        test3(n - 1);
    }
}


/**
 * T(n) = { 1             n = 0
 *        { 2T(n - 1) + 1 n > 0  
 * O(2^n)
 */
int count = 0;
void test4(int n, const std::string s) {

    if(n > 0) {
//        std::cout << s << n << "\n";  
        test4(n - 1, "first: ");
        test4(n - 1, "second: ");
    }
}

/**
 * T(n) = {1 n <= 1024}
 *        {T(n * 2) + 1}
 * @param n
 */
void printSquareOfTwo(int n) {
    if( n <= 1024 ) {
        std::cout << n << " ";
        printSquareOfTwo(n * 2);
    }
}
#endif /* RECURRENCERELATIONS_H */

