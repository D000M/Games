/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "CLib.h"
#include <iostream>
#include <cassert>

using namespace C04;

const int increment = 100;

void initialize(C04Stash* s, int size) {
    s->size = size;
    s->quantity = 0;
    s->next = 0;
    s->storage = 0;
}

void inflate(C04::C04Stash* s, const int increase) {
    assert(increase > 0);
    int newQuantity = s->quantity + increase;
    int newBytes = newQuantity * s->size;
    int oldBytes = s->quantity * s->size;
    
    unsigned char* b = new unsigned char[newBytes];
    for(int i = 0; i < oldBytes; i++) {
        b[i] = s->storage[i];
    }
    
    delete [] (s->storage);
    s->storage = b;
    s->quantity = newQuantity;
}
int add(C04Stash* s, const void* element) {
    if(s->next >= s->quantity) {
        //inflate(s, increment);
    }
    //Copy element into storage
    //Starting on the next empty space
    int startBytes = s->next * s->size;
    unsigned char* elem = (unsigned char*)element;
    
    for(int i = 0; i < s->size; i++) {
        s->storage[startBytes + i] = elem[i];
    }
    s->next++;
    return(s->next - 1);    //return index number
}

void* fetch(C04Stash* s, int index) {
    assert(0 <= index);
    
    if(index >= s->next) {
        return 0;
    }
    return &(s->storage[index * s->size]);
}

int count(C04Stash* s) {
    return s->next;
}


void cleanup(C04Stash* s) {
    if(s->storage != 0) {
        std::cout << "Freeing Storage!\n";
        delete [] s->storage;
    }
}