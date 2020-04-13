/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   MyQueue.h
 * Author: default
 *
 * Created on August 23, 2019, 2:55 PM
 */

#ifndef MYQUEUE_H
#define MYQUEUE_H

class MyQueue {
public:
    MyQueue();
    MyQueue(int size);
    MyQueue(int size, int startPos);
    MyQueue(const MyQueue& orig);
    virtual ~MyQueue();
    
    void enqueue(int value);
    void enqueueCircular(int value);
    int dequeue();
    int dequeueCircular();
    
    void display();
    void displayCircular();
    bool isEmpty();
    bool isFull();
    
    bool isFullCircular();
    
private:
    int front;
    int rear;
    int size;
    int* arr;
};

#endif /* MYQUEUE_H */

