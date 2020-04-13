/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include <iostream>

#include "BinaryOperations.h"

void printBinary(const unsigned char value) {
    for(int i = 7; i >= 0; i--) {
        if(value & (1 << i)) {
            std::cout << "1";
        }
        else {
            std::cout << "0";
        }
    }
}


#define PRINT(STR, EXPR) \
    std::cout << STR + ": "; printBinary(EXPR); std::cout << std::endl;

void testBinary() {
    for(int i = 0; i < 256; i++) {
        PRINT(std::to_string(i), i);
    }
}