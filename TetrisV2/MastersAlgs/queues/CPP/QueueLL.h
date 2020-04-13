/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   QueueLL.h
 * Author: default
 *
 * Created on August 27, 2019, 2:03 PM
 */

#ifndef QUEUELL_H
#define QUEUELL_H

class QNode {
public:
    int data;
    QNode* next;
};

class QueueLL {
private:
    QNode* front;
    QNode* rear;
    int size;
public:
    QueueLL();
    QueueLL(const QueueLL& orig);
    virtual ~QueueLL();
    
    void enqueue(int elem);
    int dequeue();
    bool isEmpty();
    
    void printAllElements();
    int getSize() const;
private:

};

#endif /* QUEUELL_H */

