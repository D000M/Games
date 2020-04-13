/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   TStash.h
 * Author: default
 *
 * Created on December 21, 2019, 10:33 AM
 */

#ifndef TSTASH_H
#define TSTASH_H

#include <string.h>


template<typename T, int increment = 10>
class TStash {
    int quantity;
    int next;
    T** storage;
    void inflate(int increase = increment);
    
    public:
        TStash() : quantity{0}, next{0}, storage{nullptr} {}
        ~TStash();
        int add(T* elem);
        T* operator [] (int index) const;
        T* remove(int index);
        int count() const { return next; }
};

template<class T, int increment>
int TStash<T, increment>::add(T* elem) {
    if(next >= quantity) {
        inflate(increment);
    }
    storage[next++] = elem;
    return (next - 1);
}

template<class T, int increment>
TStash<T, increment>::~TStash() {
    for(int i = 0; i < next; i++) {
        delete storage[i];  //nullptr is ok
        storage[i] = nullptr;
    }
    delete [] storage;
}

template<class T, int increment>
T* TStash<T, increment>::operator [](int index) const {
    if(index < 0) {
        throw("Error index negative");
    }
    if(index >= next) {
        return nullptr; //
    }
    if(storage[index] == nullptr) {
        throw("Error nullptr in the storage");
    }
    return storage[index];
}

template<class T, int increment>
T* TStash<T, increment>::remove(int index) {
    //operator [] performs validity checks
    T* v = operator [](index);
    if(v != nullptr) {
        storage[index] = nullptr;
    }
    return v;
}

template<class T, int increment>
void TStash<T, increment>::inflate(int increase) {
    const int TPtrSize = sizeof(T*);
    T** st = new T*[quantity + increase];
    memset(st, 0, (quantity + increase) * TPtrSize);
    memcpy(st, storage, quantity * TPtrSize);
    quantity += increase;
    delete [] storage;  //Old storage
    storage = st;       //Point to new memory
}
#endif /* TSTASH_H */

