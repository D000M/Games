/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   MyQueue.cpp
 * Author: default
 * 
 * Created on August 23, 2019, 2:55 PM
 */

#include <iostream>

#include "MyQueue.h"

MyQueue::MyQueue() {
    front = rear = -1;
    size = 10;
    arr = new int[size];
}
MyQueue::MyQueue(int size) 
    : size{size},
      front{-1},
      rear{-1},
      arr{nullptr} {
          arr = new int[this->size];
}

MyQueue::MyQueue(int size, int startPos)
    : size{size},
      front{0},
      rear{0},
      arr{nullptr} {
          arr = new int[this->size];
}

MyQueue::MyQueue(const MyQueue& orig) {
}

MyQueue::~MyQueue() {
    if(arr) {
        std::cout << "MyQueue with size: " << size << ", Deleted!\n";
        delete [] arr;
    }
}

bool MyQueue::isEmpty() {
    return front == rear;
}

bool MyQueue::isFull() {
    return rear == size - 1;
}

void MyQueue::enqueue(int value) {
    if(isFull()) {
        return;
    }
    rear++;
    arr[rear] = value;
}

int MyQueue::dequeue() {
    if(isEmpty()) {
        return -1;
    }
    front++;
    return arr[front];
}

void MyQueue::display() {
    for(int i = front + 1; i <= rear; i++) {
        std::cout << arr[i] << " ";
    }
    std::cout << std::endl;
}

bool MyQueue::isFullCircular() {
    return ((rear + 1) % size) == front;
}

void MyQueue::enqueueCircular(int value) {
    if(isFullCircular()) {
        std::cout << "Queue is Full!\n";
        return;
    }
    else {
        rear = (rear + 1) % size;
        arr[rear] = value;
    }
}

int MyQueue::dequeueCircular() {
    if(isEmpty()) {
        std::cout << "Queue is Empty!\n";
        return -1;
    }
    front = (front + 1) % size;
    return arr[front];
}

void MyQueue::displayCircular() {
    int i = front + 1;
    if(i >= size) {
        i = 0;
    }
    do {
        std::cout << arr[i] << " ";
        i = (i + 1) % size;
    }
    while((rear + 1) % size != i);
    std::cout << std::endl;
}
