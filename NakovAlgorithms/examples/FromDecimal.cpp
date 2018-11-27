/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   FromDecimal.cpp
 * Author: default
 * 
 * Created on November 27, 2018, 2:18 PM
 */

#include <algorithm>
#include <valarray>
#include <iostream>

#include "FromDecimal.h"

FromDecimal::FromDecimal(int n, int b) 
    : number{n},
      base{b},
      result{""}{
          
          compute();
}
      
char FromDecimal::getChar(char n) {
    return (n < 10) ? (n + '0') : (n + 'A' - 10);
}

void FromDecimal::compute() {
    bool addMinus = false;
    int temp = number;
    if(temp < 0) {
        addMinus = true;
        temp = abs(temp);
    }
    else if(temp == 0) {
        result = "0";
    }
    
    while(temp > 0) {
        result += getChar((char)(temp % base));
        temp = temp / base;
    }
    std::reverse(result.begin(), result.end());
    if(addMinus) {
        result = "-" + result;
    }
}

void FromDecimal::setSystem(int n, int b) {
    number = n;
    base = b;
    result = "";
    compute();
}


void FromDecimal::print() {
    std::cout << "The Decimal Number: " << number << " is equal to: " << result << " in system with base: " << base << std::endl;
}

std::ostream& operator<<(std::ostream& os, const FromDecimal& obj) {
    os << "The Decimal Number: " << obj.number << " is equal to " << obj.result << " in system with base: " << obj.base << std::endl;
}
