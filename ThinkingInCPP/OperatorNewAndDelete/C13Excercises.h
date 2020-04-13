/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   C13Excercises.h
 * Author: default
 *
 * Created on December 11, 2019, 4:29 PM
 */

#ifndef C13EXCERCISES_H
#define C13EXCERCISES_H

#include <stdio.h>
#include <vector>

class Counted {
    int id;
    static int count;
public:
    Counted() : id{count++} {
        printf("Counted: %d Constructed\n", id);
    }
    ~Counted() {
        printf("Counted: %d Destroyed\n", id);
    }
    
    void printMsg() {
        printf("printMsg: %d\n", id);
    }
};
int Counted::count = 1;

void Ex1TestCounted() {
    Counted c1;
    Counted c2;
    Counted c3;
    
    Counted* c4 = new Counted();
    delete c4;
    
    Counted* cArr = new Counted[10];
    delete [] cArr;
}

void Ex4CountedVec() {
    std::vector<Counted*> myVec;
    myVec.emplace_back(new Counted);
    myVec.emplace_back(new Counted);
    myVec.emplace_back(new Counted);
    myVec.emplace_back(new Counted);
    myVec.emplace_back(new Counted);
    for(auto&& elem : myVec) {
        elem->printMsg();
        delete elem;
        elem = nullptr;
    }
}

void Ex8TestArrCounted() {
    Counted* c1 = new Counted;
    void* vp = &c1;
    Counted* c5 = static_cast<Counted*>(vp);
    c5->printMsg();
    Counted* c2 = (Counted*)vp;
    c2->printMsg();
    delete c1;
}
#endif /* C13EXCERCISES_H */

