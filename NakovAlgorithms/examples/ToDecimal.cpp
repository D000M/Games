/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   ToDecimal.cpp
 * Author: default
 * 
 * Created on November 27, 2018, 2:30 PM
 */

#include "ToDecimal.h"
#include <iostream>

ToDecimal::ToDecimal(const std::string& str, int b) 
    : number{str},
      base{b},
      result{} {
          
        compute();
          
}

void ToDecimal::compute() {
    
    int temp = 0;
    
    for(int i = 0; i < number.length(); i++) {
        temp = (temp * base) + getValue(number.at(i));
    }
    result = temp;
}

void ToDecimal::setNumber(const std::string& str, int b) {
    number = str;
    base = b;
    result = 0;
    compute();
}


char ToDecimal::getValue(char c) {
    return (c >= '0' && c <= '9') ? (c - '0') : c - 'A' + 10;  
}

void ToDecimal::print() {
    std::cout << "The number: " << number << ", with base: " << base << " is equal to: " << result << " decimal.\n";
}

std::ostream& operator<<(std::ostream& os, const ToDecimal& obj) {
    os << "The number: " << obj.number << ", with base: " << obj.base << " is equal to: " << obj.result << " decimal.\n";
}