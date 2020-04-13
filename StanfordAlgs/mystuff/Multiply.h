/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Multiply.h
 * Author: default

 * Created on February 20, 2019, 3:24 PM
 */

#ifndef MULTIPLY_H
#define MULTIPLY_H

#include <iostream>
#include <cmath>
#include <algorithm>

void simpleMultiply(int64_t x, int64_t y) {
    int64_t result = 0;
    int num = y;
    int count = 0;
    int64_t tempResult = 0;
    while(std::abs(num) > 0) {
        int n = num % 10;
        result = x * n;
        num /= 10;
        for(int i = 0; i < count; ++i) {
            result *= 10;
        }
        tempResult += result;
        count++;
    }
    std::cout << x << " * " << y << " = " << tempResult << std::endl;
}

void karatsubaFourDigit(int first, int second) {
    int a = first / 100;
    int b = first % 100;
    int c = second / 100;
    int d = second % 100;
    int stepOne = a * c;
    int stepTwo = b * d;
    int stepThree = (a + b) * (c + d);
    int stepFour = stepThree - stepTwo - stepOne;
    stepOne = stepOne * 10000;
    stepFour = stepFour * 100;
    std::cout << first << " * " << second << " = " << int(stepOne + stepTwo + stepFour) << std::endl;
}

int getLength(int number) {
    int length = 0;
    while(number > 0) {
        number /= 10;
        length++;
    }
    return length;
}

int64_t karatsubaRecursive(int64_t x, int64_t y) {

    if(x < 10 || y < 10) {
        return x * y;
    }
    
    int64_t length = std::max(getLength(x), getLength(y));
    
    int64_t nulsX = 1;
    length /= 2;
    for(int i = 0; i < length; ++i) {
        nulsX *= 10;
    }
    int nulsY = 1;
    for(int i = 0; i < length; ++i) {
        nulsY *= 10;
    }
    int64_t a = x / nulsX;
    int64_t b = x % nulsX;
    int64_t c = y / nulsY;
    int64_t d = y % nulsY;
    int64_t ac = karatsubaRecursive(a, c);
    int64_t bd = karatsubaRecursive(b, d);
    int64_t ad_plus_bd = karatsubaRecursive(a + b, c + d) - ac - bd;

    return ac * std::pow(10, 2 * length) + (ad_plus_bd * std::pow(10, length)) + bd;
}

void testKaratsuba(int64_t a, int64_t b) {
    std::cout << a << " * " << b << " = " << karatsubaRecursive(a, b) << std::endl;
}
#endif /* MULTIPLY_H */

