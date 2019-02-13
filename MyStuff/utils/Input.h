/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Input.h
 * Author: default
 *
 * Created on February 12, 2019, 4:05 PM
 */

#ifndef INPUT_H
#define INPUT_H

#include <iostream>


char getOperator() {
    while(true) {
        std::cout << "Input a operator from the following: [+ - * /]: ";
        char op;
        std::cin >> op;
        
        if(op == '+' || op == '-' || op == '*' || op == '/') {
            return op;
        }
        else {
            std::cout << "Wrong input try again!\n";
        }
    }
}

double getDouble() {
    while(true) {
        std::cout << "Input double: ";
        double d;
        std::cin >> d;
        if(std::cin.fail()) {   // has a previous extraction failed?
            // yep, so let's handle the failure
            std::cin.clear();   // put us back in 'normal' operation mode
            std::cin.ignore(32767, '\n');   // clear (up to 32767) characters out of the buffer until a '\n' character is removed
        }
        else {  // else our extraction succeeded
            std::cin.ignore(32767, '\n');   // clear (up to 32767) characters out of the buffer until a '\n' character is remove
            return d;   // so return the value we extracted
        }
    }
}
#endif /* INPUT_H */

