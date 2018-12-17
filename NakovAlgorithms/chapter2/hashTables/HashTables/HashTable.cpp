/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   HashTable.cpp
 * Author: default
 * 
 * Created on December 14, 2018, 4:25 PM
 */

#include "HashTable.h"

int HashTable::hashFunction(int k) {
    return (k % size);
}

void HashTable::initHashTable() {
    for(int i = 0; i < size; i++) {
        nodes[i] = nullptr;
    }
}

void HashTable::put(int k, int d) {
    int place = hashFunction(k);
    std::cout << place << std::endl;
    insertBegin(nodes[place], k, d);
}

int HashTable::get(int k) {
    int place = hashFunction(k);
    std::cout << place << std::endl;
    Node* ptrN = search(nodes[place], k);
    return (ptrN != nullptr) ? ptrN->data : -1;
}
