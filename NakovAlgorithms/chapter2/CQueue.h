/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   CQueue.h
 * Author: default
 *
 * Created on December 4, 2018, 3:21 PM
 */

#ifndef CQUEUE_H
#define CQUEUE_H

#include <stdio.h>


#define MAX 10

typedef int dataQ;
dataQ queue[MAX];

int front, rear, empty;

void initQ(void) {
    front = rear = 0;
    empty = 1;
}

void putQ(dataQ i) {
    if(front == rear && !empty) {   //Overflow check
        fprintf(stderr, "Overflow! \n");
        return;
    }
    queue[rear++] = i;
    if(rear >= MAX) {
        rear = 0;
    }
    empty = 0;
}

dataQ getQ(void) {
    dataQ x;
    if(empty) {
        fprintf(stderr, "Queue is Empty! \n");
        return 0;
    }
    x = queue[front++];
    if(front >= MAX) {
        front = 0;
    }
    if(front == rear) {
        empty = 1;
    }
    return x;
}
#endif /* CQUEUE_H */

