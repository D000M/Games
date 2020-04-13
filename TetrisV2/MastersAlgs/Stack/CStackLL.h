/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   CStackLL.h
 * Author: default
 *
 * Created on August 8, 2019, 12:59 PM
 */

#ifndef CSTACKLL_H
#define CSTACKLL_H

#include <stdlib.h>
#include <cstdio>


#ifdef __cplusplus
extern "C" {
#endif

    struct CStackNode {
        int data;
        struct CStackNode* next;
    };

    struct CStackLL {
        struct CStackNode* top;
    };
    
    bool isEmptyLL(struct CStackLL stack) {
        if(!stack.top) {
            return true;
        }
        return false;
    }
    
    void pushCStackLL(struct CStackLL* stack, int element) {
        struct CStackNode* temp = (struct CStackNode*)malloc(sizeof(struct CStackNode));
        temp->data = element;
        temp->next = stack->top;
        stack->top = temp;
    }

    int popCStackLL(struct CStackLL* stack) {
        struct CStackNode* temp = stack->top;
        int element = -1;
        if(temp) {
            element = temp->data;
            stack->top = stack->top->next;
            free(temp);
        }
        return element;
    }
    
    void testCStackLL() {
        struct CStackLL stack;
        stack.top = NULL;
        
        pushCStackLL(&stack, 10);
        pushCStackLL(&stack, 20);
        pushCStackLL(&stack, 30);
        pushCStackLL(&stack, 40);
        pushCStackLL(&stack, 50);
        
        printf("%d ", popCStackLL(&stack));
        printf("%d ", popCStackLL(&stack));
        printf("%d ", popCStackLL(&stack));
        printf("%d ", popCStackLL(&stack));
        printf("%d ", popCStackLL(&stack));
    }
    
#ifdef __cplusplus
}
#endif

#endif /* CSTACKLL_H */

