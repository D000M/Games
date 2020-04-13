/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Stack.cpp
 * Author: default
 * 
 * Created on August 8, 2019, 3:23 PM
 */

#include "Stack.h"
#include <iostream>
Stack::Stack() {
}

Stack::Stack(const Stack& orig) {
}

Stack::~Stack() {
    if(topPtr) {
//        delete topPtr;
    }
}

void Stack::push(int element) {
    StackNode* temp = new StackNode;
    if(temp) {
        temp->data = element;
        temp->next = topPtr;
        topPtr = temp;
    }
}

int Stack::pop() {
    int element = -1;
    if(topPtr) {
        StackNode* temp = topPtr;
        element = topPtr->data;
        topPtr = topPtr->next;
        delete temp;
    }
    return element;
}

int Stack::top() {
    if(topPtr) {
        return topPtr->data;
    }
    return -1;
}

int Stack::peek(int index) {
    StackNode* temp = topPtr;
    for(int i = 0; temp && i < index; i++) {
        temp = temp->next;
    }
    return temp->data;
}



