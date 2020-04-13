/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   SmartPointer.h
 * Author: default
 *
 * Created on December 7, 2019, 3:37 PM
 */

#ifndef SMARTPOINTER_H
#define SMARTPOINTER_H

#include <iostream>
#include <vector>

class Obj {
    static int i;
    static int j;
public:
    void incrementI() const { std::cout << i++ << std::endl; }
    void incrementJ() const { std::cout << j++ << std::endl; }
};
int Obj::i = 0;
int Obj::j = 0;

//Container
class ObjContainer {
    std::vector<Obj*> myVect;
public:
    void add(Obj* obj) {
        myVect.emplace_back(obj);
    }
    
    friend class SmartPointer;
};

class SmartPointer {
    ObjContainer& container;
    int index;
public:
    SmartPointer(ObjContainer& objCont) : container{objCont}, index{0} {}
    
    //Return value indicates end of the list
    bool operator ++ () {   //Prefix
        if(index >= container.myVect.size()) {
            return false;
        }
        if(container.myVect[++index] == nullptr) {
            return false;
        }
        return true;
    }
    bool operator ++ (int) {//Postfix
        return operator++();    //Use prefix version
    }
    Obj* operator -> () const {
        if(container.myVect[index] == nullptr) {
            throw ("ERROR nullptr value at index: " + index);
        }
        return container.myVect[index];
    }
};

void testSmartPointer() {
    const int size = 10;
    Obj objects[size];
    ObjContainer cont;
    for(int i = 0; i < size; i++) {
        cont.add(&objects[i]);
    }
    SmartPointer iter(cont);    //Create an iterator.
    do {
        iter->incrementI();
        iter->incrementJ();
    }
    while(iter++);
}
#endif /* SMARTPOINTER_H */

