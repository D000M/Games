/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   HashTable.h
 * Author: default
 *
 * Created on December 14, 2018, 4:25 PM
 */

#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <iostream>


class HashTable {
    
    struct Node {
        int key;
        int data;
        Node* next;
    };
    
    static constexpr int size = 211;
    
    Node* nodes[size];
    
            
    void insertBegin(Node* pos, int k, int d) {
        pos = new Node;
        pos->key = k;
        pos->data = d;
        pos->next = nullptr;
    }

    void deleteNode(Node* n, int k) {
        Node* current = n;
        Node* save;
        if(n->key == k) {
            current = n->next;
            delete n;
            n = current;
            return;
        }
        while(current->next != nullptr && current->next->key != k) {
            current = current->next;
        }
        if(current == nullptr) {
            std::cout << "The Element wasnt found!\n";
            return;
        }
        else {
            save = current->next;
            current->next = current->next->next;
            delete save;
        }
    }

    Node* search(Node* p, int k) {
        while(p != nullptr) {
            if(p->key == k) {
                return p;
            }
            p = p->next;
        }
    }
public:
    //Hash function
    int hashFunction(int k);
    
    void initHashTable();
    
    void put(int k, int d);
    int get(int k);
    
private:

};

#endif /* HASHTABLE_H */

