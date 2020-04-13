/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   QueueLL.cpp
 * Author: default
 * 
 * Created on August 27, 2019, 2:03 PM
 */

#include <iostream>

#include "QueueLL.h"

QueueLL::QueueLL() 
    : front{nullptr},
      rear{nullptr},
      size{0}{
}

QueueLL::QueueLL(const QueueLL& orig) {
}

QueueLL::~QueueLL() {
}

bool QueueLL::isEmpty() {
    return front == nullptr;
}

void QueueLL::enqueue(int elem) {
    QNode* temp = new QNode;
    
    if(temp == nullptr) {
        std::cout << "Queue is Full No memory in HEAP!\n";
    }
    else {
        temp->data = elem;
        temp->next = nullptr;
        if(isEmpty()) {
            front = rear = temp;
        }
        else {
            rear->next = temp;
            rear = temp;
        }
        size++;
    }
    
}

int QueueLL::dequeue() {
    int x = -1;
    QNode* temp;
    
    if(isEmpty()) {
        std::cout << "Queue is Empty!\n";
    }
    else {
        temp = front;
        front = front->next;
        x = temp->data;
        delete temp;
    }
    return x;
}

void QueueLL::printAllElements() {
    while(front) {
        std::cout << dequeue() << " ";
    }
}

int QueueLL::getSize() const {
    return size;
}
