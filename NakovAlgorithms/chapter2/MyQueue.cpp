/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   MyQueue.cpp
 * Author: default
 * 
 * Created on December 4, 2018, 4:34 PM
 */

#include <iostream>

#include "MyQueue.h"

void MyQueue::init() {
    front = rear = 0;
    empty = 1;
}

void MyQueue::put(int elem) {
    if(front == rear && !empty) {
        std::cerr << "Queue Overflow! \n";
        return;
    }
    
    data[rear++] = elem;
    if(rear >= MAX_SIZE) {
        rear = 0;
    }
    
    empty = 0;
}

int MyQueue::get() {
    int result;
    if(empty) {
        std::cerr << "Queue is Empty! \n";
        return 0;
    }
    
    result = data[front++];
    if(front >= MAX_SIZE) {
        front = 0;
    }
    if(front == rear) {
        empty = 1;
    }
    return result;
}

