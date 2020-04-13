/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   CLib.h
 * Author: default
 *
 * Created on December 3, 2019, 3:59 PM
 */

#ifndef CLIB_H
#define CLIB_H

namespace C04 {
    typedef struct C04Stash {
        int size;
        int quantity;
        int next;
        unsigned char* storage;
    }C04Stash;

    void initialize(C04Stash* s, int size);
    void inflate(C04Stash* s, const int increase);
    void cleanup(C04Stash* s);
    void add(C04Stash* s, const void* element);
    void* fetch(C04Stash* s, int index);
    int count(C04Stash* s);
    
}

#endif /* CLIB_H */

