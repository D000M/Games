/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   TestMyQueue.h
 * Author: default
 *
 * Created on August 23, 2019, 3:01 PM
 */

#ifndef TESTMYQUEUE_H
#define TESTMYQUEUE_H

#include <iostream>

#include "MyQueue.h"
#include "QueueLL.h"


void testMyQueue() {
    MyQueue q;
    q.enqueue(5);
    q.enqueue(15);
    q.enqueue(25);
    q.enqueue(35);
    q.enqueue(45);
    q.display();
    std::cout << q.dequeue() << std::endl;
    q.display();
    
    MyQueue q2{5};
    q2.enqueue(3);
    q2.enqueue(13);
    q2.enqueue(23);
    q2.enqueue(33);
    q2.enqueue(43);
    q2.enqueue(53);
    q2.display();
    std::cout << q2.dequeue() << std::endl;
    q2.display();
    
    MyQueue q3{5, 25};
    q3.enqueueCircular(10);
    q3.enqueueCircular(20);
    q3.enqueueCircular(30);
    q3.enqueueCircular(40);
    q3.enqueueCircular(50);
    q3.displayCircular();
    std::cout << q3.dequeueCircular() << std::endl;
    std::cout << q3.dequeueCircular() << std::endl;
    q3.displayCircular();
    q3.enqueueCircular(50);
    q3.enqueueCircular(60);
    q3.enqueueCircular(70);
    q3.displayCircular();
    std::cout << q3.dequeueCircular() << std::endl;
    std::cout << q3.dequeueCircular() << std::endl;
    q3.displayCircular();
}

void testQueueLL() {
    QueueLL myQueue;
    myQueue.enqueue(5);
    myQueue.enqueue(15);
    myQueue.enqueue(25);
    myQueue.enqueue(35);
    myQueue.enqueue(55);
    myQueue.enqueue(65);
    myQueue.printAllElements();
}

#endif /* TESTMYQUEUE_H */

