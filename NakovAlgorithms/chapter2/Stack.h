/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Stack.h
 * Author: default
 *
 * Created on December 4, 2018, 2:54 PM
 */

#ifndef STACK_H
#define STACK_H

#include <stdio.h>


/**
 * C language example of stack
 */
#define MAX 10

typedef int data;

data stack[MAX];

int top;

void init(void) {
    top = 0;
}

void push(data i) {
    if(top == MAX) {
        fprintf(stderr, "Stack overflow! \n");
    }
    else {
        stack[top++] = i;
    }
}

data pop(void) {
    if(top == 0) {
        fprintf(stderr, "Stack is empty! \n");
        return 0;
    }
    else {
        return stack[--top];
    }
}

int isEmpty(void) {
    return top == 0;
}

#endif /* STACK_H */

