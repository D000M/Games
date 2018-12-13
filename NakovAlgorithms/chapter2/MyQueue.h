/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   MyQueue.h
 * Author: default
 *
 * Created on December 4, 2018, 4:34 PM
 */

#ifndef MYQUEUE_H
#define MYQUEUE_H

#define MAX_SIZE 10

class MyQueue {
    
    int front;
    int rear;
    int empty;
    char data[MAX_SIZE];
    
public:
    void init();
    void put(int elem);
    int get();
};

#endif /* MYQUEUE_H */

