/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Recursive.cpp
 * Author: default
 * 
 * Created on November 28, 2018, 1:05 PM
 */

#include <math.h>
#include <complex>
#include <iostream>
#include "Recursive.h"

unsigned long Recursive::factoriel(int n) {
    if(n < 2) {
        return 1;
    }
    return n * factoriel(n - 1);
}

unsigned long Recursive::naturalNumsSum(int n) {
    if(n < 1) {
        return 0;
    }
    return n + naturalNumsSum(n - 1);
}

unsigned long Recursive::naturalNumsSumFrom(int start, int n) {
    if(n < start) {
        return 0;
    }
    return n + naturalNumsSumFrom(start, n - 1);
}

unsigned long Recursive::fib(int n) {
    if(n <= 2) {
        return 1;
    }
    return fib(n - 1) + fib(n - 2);
}

unsigned long Recursive::moaverFib(int n) {
    return ((1 / sqrt(5)) * ( std::pow(((1 + sqrt(5)) / 2), n) - ( std::pow(((1 - sqrt(5)) / 2), n))));
}

unsigned long Recursive::GCD(int first, int second) {
    if(second == 0) {
        return first;
    }
    return GCD(second, first % second);
}

void Recursive::cutDrobs(int a, int b) {
    if(GCD(a, b) == 1) {
        std::cout << a << "/" << b << std::endl;
        return;
    }
    int divisor = GCD(a, b);
    std::cout << a / divisor << "/" << b / divisor << std::endl;
}

unsigned long Recursive::NOK(int numbers[], int next) {
    if(next == 2) {
        return (numbers[0] * numbers[1]) / GCD(numbers[0], numbers[1]);
    }
    else {
        int num = NOK(numbers, next - 1);
        return (numbers[next - 1] * num) / GCD(numbers[next - 1], num);
    }
}

void Recursive::printN(int n) {
    if(n >= 10) {
        printN(n / 10);
    }
    std::cout << n % 10 << " "; 
}

static constexpr int n = 6;
int i = n + 1;
unsigned long Recursive::factoriel2() {
    if(i == 1) {
        return 1;
    }
    return --i * factoriel2();
}

void Recursive::testFactoriel2() {
    i = n + 1;
    std::cout << n << "! = " << factoriel2() << std::endl; 
}

void Recursive::printRed(int k, long result) {
    std::cout << result << " ";
    if(k < n) {
        printRed(k + 1, result * 10);
    }
    std::cout << result << " ";
}

unsigned long Recursive::fibMem(int n) {
    if(fibNext[n] == 0) {
        if(n < 2) {
            fibNext[n] = 1;
        }
        else {
            fibNext[n] = fibMem(n - 1) + fibMem(n - 2);
        }
    }
    return fibNext[n];
}

void Recursive::testFibMem() {
    for(int i = 0; i < MAX_FIB; i++) {
        fibNext[i] = 0;
    }
    std::cout << fibMem(35);
}
int tribCount = 0;
unsigned long Recursive::tribonaci(unsigned long n) {
//    tribCount++;
    if(n <= 3) {
        return 1;
    }
    return tribonaci(n - 1) + tribonaci(n - 2) + tribonaci(n - 3); 
}

unsigned long Recursive::tribMem(unsigned long n) {
    tribCount++;
    if(tribNext[n] == 0) {
        if(n < 4) {
            tribNext[n] = 1;
        }
        else {
            tribNext[n] = tribMem(n - 1) + tribMem(n - 2) + tribMem(n - 3);
        }
    }
    return tribNext[n];
}

void Recursive::testTribMem() {
    for(int i = 0; i < MAX_FIB; i++) {
        tribNext[i] = 0;
    }
    std::cout << tribMem(20);
}


unsigned long Recursive::fibFromRow(unsigned int row, unsigned long n) {
    if(n < row) {
        return row;
    }
    return fibFromRow(row, n - 1) + fibFromRow(row, n - 2);
}

unsigned int Recursive::palindrome(int n) {
    
    int reverse = n;
    int reversedNumber = 0;
    int remainder;
    while(reverse != 0)
    {
        remainder = reverse % 10;
        reversedNumber = reversedNumber * 10 + remainder;
        reverse /= 10;
    }
    if(n == reversedNumber) {
        return 1;
    }
//    std::cout << n << " + " << reversedNumber << std::endl;
    int sum = n + reversedNumber;
    return 1 + palindrome(sum);
}

void Recursive::printPiramid(int n, int stop) {

    if(n < stop) {
        printPiramid(n + 1, stop);
    }

    for(int i = n; i >= 1; i--) {
        std::cout << " ";
    }
    int count = 1;
    for(int i = 0; i < count; i++) {
        std::cout << n;
    }
    std::cout << std::endl;
}

int Recursive::initArray(int n, int size) {
    if(n == size) {
        return n;
    }
    return n + initArray(n + 1, size);
}

void Recursive::testRecInitArray() {
    int size = 100;
    int arr[size];
    
    int a = initArray(1, 10);
    
}
