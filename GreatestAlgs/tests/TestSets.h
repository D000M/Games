/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   TestSets.h
 * Author: default
 *
 * Created on February 28, 2019, 5:21 PM
 */

#ifndef TESTSETS_H
#define TESTSETS_H

#include <vector>
#include "../sets/Set.h"
#include <iostream>

void foundElement(Set s, int elem) {
//    for(int i = 0; i < s.)
}

void testSimpleSets() {
    std::vector<int> v1{1, 2, 3, 4};
    std::vector<int> v2{5, 6, 7, 8};
    Set s1(v1);
    Set s2(v2);
    s1.printSet();
    s2.printSet();
    
    if(s2.find(2)) {
        std::cout << "Element " << 2 << " found!\n";
    }
    else {
        std::cout << "Element not Found!\n";
    }
    s1.unionSets(s2);
    s1.printSet();
}


#endif /* TESTSETS_H */

