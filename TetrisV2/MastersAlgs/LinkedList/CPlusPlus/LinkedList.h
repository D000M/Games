/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   LinkedList.h
 * Author: default
 *
 * Created on July 29, 2019, 2:24 PM
 */

#ifndef LINKEDLIST_H
#define LINKEDLIST_H

class Node {
public:
    int data;
    Node* next;
};

class LinkedList {
    Node* node;
public:
    LinkedList();
    LinkedList(int data);
    LinkedList(const LinkedList& orig);
    virtual ~LinkedList();
    
    void insertAt(int pos, int element);
    int deleteAt(int pos);
    int length();
    int lengthR(Node* test);
    
    void printList();
    void printListR();
    
    Node* getNode() const;
private:

};

#endif /* LINKEDLIST_H */

