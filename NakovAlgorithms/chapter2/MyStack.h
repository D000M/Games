/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   MyStack.h
 * Author: default
 *
 * Created on December 4, 2018, 4:33 PM
 */

#ifndef MYSTACK_H
#define MYSTACK_H

/**
 * Int Stack
 */

#define MAX_SIZE 10

class MyStack {
    int top;
    char data[MAX_SIZE];
public:
    
    void init();
    void push(int elem);
    int pop();
    bool isEmpty() const;
    
private:

};

#endif /* MYSTACK_H */

