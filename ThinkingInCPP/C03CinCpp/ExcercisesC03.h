/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   ExcercisesC03.h
 * Author: default
 *
 * Created on December 3, 2019, 3:16 PM
 */

#ifndef EXCERCISESC03_H
#define EXCERCISESC03_H
#include <string>

//C03 Excercise 02
void printPrime(int value) {
    std::cout << "1 2 ";
    
    for(int i = 3; i < value; i++) {
        bool isPrime = true;
        for(int j = 2; j < i; j++) {
            if(i % j == 0) {
                isPrime = false;
            }
        }
        if(isPrime) {
            std::cout << i << " ";
        }
    }
}

//C03 Excercise 15
typedef struct C03Struct {
    std::string first;
    std::string second;
    int value;
}C03Struct;

void testExC03_15() {
    C03Struct myStruct;
    myStruct.first = "Vanya";
    myStruct.second = "Dimitrova";
    myStruct.value = 32;
    std::cout << myStruct.first << " " << myStruct.second << " " << myStruct.value << std::endl;
    
    C03Struct *ptrMyStruct = &myStruct;
    ptrMyStruct->first = "Deska";
    ptrMyStruct->second = "Naidenova";
    ptrMyStruct->value = 29;
    std::cout << myStruct.first << " " << myStruct.second << " " << myStruct.value << std::endl;
}


//C03 Excercise 22
void strToNums(const std::string& arr, const bool& toFloat = false) {
    if(toFloat) {
        float res = atof(arr.c_str());
        std::cout << res << std::endl;
    }
    else {
        int res = atoi(arr.c_str());
        std::cout << res << std::endl;
    }
}
#endif /* EXCERCISESC03_H */

