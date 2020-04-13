/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Stack.h
 * Author: default
 *
 * Created on August 8, 2019, 3:23 PM
 */

#ifndef STACK_H
#define STACK_H

class StackNode {
public:
    int data;
    StackNode* next;
};

class Stack {
    StackNode* topPtr;
public:
    Stack();
    Stack(const Stack& orig);
    virtual ~Stack();
    
    void push(int element);
    int pop();
    int peek(int index);
    int top();
private:

};

#endif /* STACK_H */

