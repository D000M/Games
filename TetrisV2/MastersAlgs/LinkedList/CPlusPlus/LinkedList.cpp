/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   LinkedList.cpp
 * Author: default
 * 
 * Created on July 29, 2019, 2:24 PM
 */

#include <iostream>

#include "LinkedList.h"

LinkedList::LinkedList() {
    node = new Node;
    node->data = 0;
    node->next = nullptr;
}
LinkedList::LinkedList(int data) {
    node = new Node;
    node->data = data;
    node->next = nullptr;
}
LinkedList::LinkedList(const LinkedList& orig) {
}

LinkedList::~LinkedList() {
    std::cout << "\n~Destructor()\n";
    while(node) {
        std::cout << "Element Deleted: " << node->data << "\n";
        delete node;
        node = node->next;
    }
    std::cout << "End Destructor()\n";
}

void LinkedList::insertAt(int pos, int element) {
    if(pos < 0) {
        return;
    }
    
    Node* temp;
    if(pos == 0) {
        temp = new Node;
        temp->data = element;
        temp->next = node;
        node = temp;
        return;
    }
    else if(pos > 0) {
        if(pos > lengthR(node)) {
            pos = lengthR(node);
        }
        
        int index = 0;
        temp = new Node;
        Node* list = node;
        while(list) {
            if(index == pos - 1) {
                temp->data = element;
                temp->next = list->next;
                list->next = temp;
                break;
            }
            index++;
            list = list->next;
        }
    }
}

int LinkedList::deleteAt(int pos) {
    int element = -1;
    Node* temp = nullptr;
    if(pos == 0) {
        temp = node;
        node = node->next;
        element = temp->data;
        std::cout << "Element Deleted at Pos: " << pos << ", Element: " << element << std::endl;
        delete temp;
        return element;
    }
    else {
        Node* current = node;
        for(int i = 0; i <= pos - 1 && current; i++) {
            temp = current;
            current = current->next;
//            std::cout << temp->data << " ";
        }
        if(current) {
            temp->next = current->next;
            element = current->data;
            std::cout << "Element Deleted at Pos: " << pos << ", Element: " << element << std::endl;
            delete current;
        }
    }
    return element;
}

int LinkedList::length() {
    int size = 0;
    Node* temp = node;
    while(temp) {
        size++;
        temp = temp->next;
    }
    return size;
}

int LinkedList::lengthR(Node* test) {
    if(test) {
        return lengthR(test->next) + 1;
    }
    else {
        return 0;
    }
}

void LinkedList::printList() {
    Node* temp = node;
    while(temp) {
        std::cout << temp->data << " ";
        temp = temp->next;
    }
    std::cout << std::endl;
}

void LinkedList::printListR() {
    static Node* temp = node;
    if(temp) {
        std::cout << temp->data << " ";
        temp = temp->next;
        printListR();
    }
}

Node* LinkedList::getNode() const {
    return node;
}
