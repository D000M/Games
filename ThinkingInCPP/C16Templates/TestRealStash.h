/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   TestRealStash.h
 * Author: default
 *
 * Created on December 21, 2019, 3:21 PM
 */

#ifndef TESTREALSTASH_H
#define TESTREALSTASH_H

#include <iostream>
#include <ostream>
#include <fstream>
#include <string>
#include "../utils/require.h"

#include "RealStack.h"
#include "RealStash.h"

class Int {
    int i;
public:
    Int(int ii = 0) : i{ii} {
        std::cout << " > " << i << ' ';
    }
    ~Int() {
        std::cout << " ~ " << i << ' ';
    }
    operator int () const {
        return i;
    }
    friend std::ostream& operator << (std::ostream& os, const Int& obj) {
        return os << "&Int: " << obj.i;
    }
    friend std::ostream& operator << (std::ostream& os, const Int* obj) {
        return os << "*Int: " << obj->i;
    }
};

void testStashTemplate() {
    {   //Force the destruction call
        Stash<Int> ints;
        for(int i = 0; i < 30; i++) {
            ints.add(new Int(i));
        }
        std::cout << std::endl;
        Stash<Int>::iterator it = ints.begin();
        it += 5;
        Stash<Int>::iterator it2 = it + 10;

        for(; it != it2; it++) {
            delete it.remove();
        }
        std::cout << std::endl;
        for(it = ints.begin(); it != ints.end(); it++) {
            if(*it) {
                std::cout << *it << std::endl;
            }
        }
    } //end of block   , ints destructor calls here
    
    std::cout << "\n----------------------------\n";
    std::ifstream file("C16Templates/TestRealStash.h");
    assure(file, "C16Templates/TestRealStash.h");
    
    Stash<std::string> stringStash;
    std::string line;
    while(std::getline(file, line)) {
        stringStash.add(new std::string{line});
    }
    Stash<std::string>::iterator sit = stringStash.begin();
    
    for(; sit != stringStash.end(); sit++) {
        std::cout << **sit << std::endl;
    }
    std::cout << "\n#########################\n";
    sit = stringStash.begin();
    int n = 26;
    sit += n;
    for(; sit != stringStash.end(); sit++) {
        std::cout << n++ << ": " << **sit << std::endl;
    }
}
#endif /* TESTREALSTASH_H */

