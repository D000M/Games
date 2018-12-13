/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   MyStack.cpp
 * Author: default
 * 
 * Created on December 4, 2018, 4:33 PM
 */

#include <iostream>

#include "MyStack.h"

void MyStack::init() {
    top = 0;
}

void MyStack::push(int elem) {
    if(top == MAX_SIZE) {
        std::cerr << "Stack overflow! \n";
        return;
    }
    data[top++] = elem;
}

int MyStack::pop() {
    if(top == 0) {
        std::cerr << "Stack is empty! \n";
        return 0;
    }
    return data[--top];
}

bool MyStack::isEmpty() const {
    return top == 0;
}



