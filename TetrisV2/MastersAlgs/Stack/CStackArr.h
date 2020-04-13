/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   CStackArr.h
 * Author: default
 *
 * Created on August 7, 2019, 1:07 PM
 */

#ifndef CSTACKARR_H
#define CSTACKARR_H

#include <stdio.h>
#include <stdlib.h>
#include <iostream>


#ifdef __cplusplus
extern "C" {
#endif

    struct CStackArr {
        int size;
        int top;
        int* Arr;
    };

    struct CStackArr* initCStackArr() {
        struct CStackArr* s;
        s = (struct CStackArr*)malloc(sizeof(struct CStackArr));
        printf("Enter Size of the Stack: ");
        scanf("%d", &s->size);
        s->Arr = (int*)malloc(s->size * sizeof(int)); 
        //stack.Arr = new int[stack.size];
        s->top = -1;
        
        return s;
    }
    
    bool isEmpty(struct CStackArr s) {
        return s.top == -1;
    }
    
    bool isFull(struct CStackArr s) {
        return s.top == s.size - 1;
    }
    
    void push(struct CStackArr* s, int value) {
        if(isFull(*s)) {
            printf("Stack is Full! We cant Insert More Elements in the Stack!\n");
        }
        else {
            s->Arr[++s->top] = value;
        }
    }
    
    int pop(struct CStackArr* s) {
        int element = -1;
        if(isEmpty(*s)) {
            printf("Stack Is Empty, Cannot be pop-ed!\n");
        }
        else {
            element = s->Arr[s->top--];
        }
        return element;
    }
    
    int peek(struct CStackArr s, int index) {
        int pos = s.top - index;
        int element = -1;
        if(pos < s.size && pos >= 0) {
            element = s.Arr[pos];
        }
        return element;
    }
    
    int stackTop(struct CStackArr s) {
        if(isEmpty(s)) {
            return -1;
        }
        else {
            return s.Arr[s.top];
        }
    }
    
    void freeCStackArrMemory(struct CStackArr* s) {
        free(s->Arr);
        free(s);
    }
    
    void testCStackArr() {
        struct CStackArr* stack = initCStackArr();
        
        if(isEmpty(*stack)) {
            std::cout << "Stack is Empty!\n";
        }
        push(stack, 5);
        push(stack, 15);
        push(stack, 25);
        push(stack, 35);
        push(stack, 45);
        int elemFound = peek(*stack, 0);
        std::cout << "Element Found: " << elemFound << std::endl;
        if(isFull(*stack)) {
            std::cout << "Stack is Full!\n";
        }
        std::cout << std::endl;
        std::cout << "StackTop: " << stackTop(*stack) << std::endl;
        for(int i = 0; i < stack->size; i++) {
            std::cout << pop(stack) << " ";
        }
        
        freeCStackArrMemory(stack);
    }

#ifdef __cplusplus
}
#endif

#endif /* CSTACKARR_H */

