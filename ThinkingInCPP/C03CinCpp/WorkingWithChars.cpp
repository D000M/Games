/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include <iostream>

#include "WorkingWithChars.h"

void printASCIIChars() {
    for(int i = 0; i < 128; i++) {
        if( i != 26) {   //Ansi terminal clear screen
            std::cout << "value: " << i << " character: " << char(i) << "\n";
        }
    }
}