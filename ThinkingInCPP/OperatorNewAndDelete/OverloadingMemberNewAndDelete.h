/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   OverloadingMemberNewAndDelete.h
 * Author: default
 *
 * Created on December 11, 2019, 3:27 PM
 */

#ifndef OVERLOADINGMEMBERNEWANDDELETE_H
#define OVERLOADINGMEMBERNEWANDDELETE_H

#include <ostream>
#include <fstream>
#include <iostream>
#include <cstddef>
#include <new>

std::ofstream toFile("Framis.out");

class Framis {
    enum {
        size = 100
    };
    char c[size];
    static unsigned char pool[];
    static bool alloc_map[];
    
public:
    enum {
        psize = 100
    };
    Framis() {
        toFile << "Framis Constructor\n";
    }
    ~Framis() {
        toFile << "~Framis Destructor ... \n";
    }
    
    void* operator new(size_t) throw(std::bad_alloc);
    void operator delete(void*);
};

unsigned char Framis::pool[psize * sizeof(Framis)];
bool Framis::alloc_map[psize] = {false};

void* Framis::operator new(size_t) throw(std::bad_alloc) {
    for(int i = 0; i < psize; i++) {
        if(!alloc_map[i]) {
            toFile << "using block " << i << " ... ";
            alloc_map[i] = true;
            return pool + (i * sizeof(Framis));
        }
    }
    toFile << "out of memory!\n";
    throw std::bad_alloc();
}
void Framis::operator delete(void* objectMemory) {
    if(!objectMemory) {
        return;
    }
    unsigned long block = (unsigned long)objectMemory - (unsigned long)pool;
    block /= sizeof(Framis);
    toFile << "freeing block: " << block << std::endl;
    // Mark it free
    alloc_map[block] = false;
}

void testMemberNewDelete() {
    Framis* myArr[Framis::psize];
    
    try {
        for(int i = 0; i < Framis::psize; i++) {
            myArr[i] = new Framis;
        }
        new Framis; //Out of memory
    }
    catch(std::bad_alloc) {
        std::cerr << "Out Of Memory!\n";
    }
    
    delete myArr[10];   //Free 1 element memory
    myArr[10] = nullptr;
    //Use one free memory
    Framis* newElem = new Framis;
    delete newElem;
    
    for(int i = 0; i < Framis::psize; i++) {
        delete myArr[i];
        //Delete myArr[10] OK!
    }
//    delete [] myArr;
}
#endif /* OVERLOADINGMEMBERNEWANDDELETE_H */

