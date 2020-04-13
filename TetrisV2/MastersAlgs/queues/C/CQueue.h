/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   CQueue.h
 * Author: default
 *
 * Created on August 23, 2019, 2:04 PM
 */

#ifndef CQUEUE_H
#define CQUEUE_H

#include <stdio.h>
#include <stdlib.h>


#ifdef __cplusplus
extern "C" {
#endif

    struct CQueue {
        int size;
        int front;
        int rear;
        int* queue;
    };
    //Functions for the CQueue
    bool isCQEmpty(struct CQueue* q) {
        return q->front == q->rear;
    }
    bool isCQFull(struct CQueue* q) {
        return q->rear == q->size - 1;
    }
    
    void initQueue(struct CQueue* q) {
        printf("Enter Size of the Array: ");
        scanf("%d", &q->size);
        q->queue = (int*)malloc(q->size * sizeof(int));
        q->front = q->rear = -1;
    }
    
    void freeCQResources(CQueue* q) {
        if(q->queue != nullptr) {
            printf("Elements deleted!\n");
            free(q->queue);
        }
    }
    
    void enqueue(struct CQueue* q, int value) {
        
        if(isCQFull(q)) {
            printf("Queue is full!\n");
            return;
        }
        q->rear++;
        q->queue[q->rear] = value;
        
    }
    int dequeue(struct CQueue* q) {
        int x = -1;
        
        if(isCQEmpty(q)) {
            printf("Queue is Empty!\n");
            return x;
        }
        q->front++;
        x = q->queue[q->front];
        
        return x;
    }
    
    void displayCQueue(struct CQueue q) {
        for(int i = q.front + 1; i <= q.rear; i++) {
            printf("%d ", q.queue[i]);
        }
        printf("\n");
    }
    
    void testCQueue() {
        //Initializing a queue
        struct CQueue q;
        q.queue = nullptr;
        initQueue(&q);
        enqueue(&q, 10);
        enqueue(&q, 20);
        enqueue(&q, 30);
        enqueue(&q, 40);
        enqueue(&q, 50);
        displayCQueue(q);
        printf("%d\n", dequeue(&q));
        displayCQueue(q);
        freeCQResources(&q);
        
    }
#ifdef __cplusplus
}
#endif

#endif /* CQUEUE_H */

