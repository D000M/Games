/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   IOStreamOverload.h
 * Author: default
 *
 * Created on December 7, 2019, 4:00 PM
 */

#ifndef IOSTREAMOVERLOAD_H
#define IOSTREAMOVERLOAD_H

#include <string.h>
#include <ostream>
#include <sstream>
#include <iostream>

class IntArray {
    enum {
        SIZE = 5
    };
    int data[SIZE];
public:
    IntArray() {
        memset(data, 0, SIZE * sizeof(*data));
    }
    
    int& operator [] (int index) {
        if(index < 0 || index >= SIZE) {
            throw("ERROR Index out of range!\n");
        }
        return data[index];
    }
    
    friend std::ostream& operator << (std::ostream& os, const IntArray& obj);
    friend std::istream& operator >> (std::istream& is, IntArray& obj);
};

std::ostream& operator << (std::ostream& os, const IntArray& obj) {
    for(int i = 0; i < obj.SIZE; i++) {
        os << obj.data[i];
        if(i != obj.SIZE - 1) {
            os << ", ";
        }
    }
    os << std::endl;
    return os;
}
std::istream& operator >> (std::istream& is, IntArray& obj) {
    for(int i = 0; i < obj.SIZE; i++) {
        is >> obj.data[i];
    }
    return is;
}

void testIOOverload() {
    std::stringstream input("10 15 20 35 50");
    IntArray myArr;
    input >> myArr;
    myArr[4] = -100;
    std::cout << myArr;
}
#endif /* IOSTREAMOVERLOAD_H */

