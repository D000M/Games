/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Combinatorics.cpp
 * Author: default
 * 
 * Created on November 28, 2018, 3:18 PM
 */
#include <iostream>
#include "Combinatorics.h"

Combinatorics::Combinatorics() {
    n = 4;
    k = 2;
    for(int i = 0; i < n; i++) {
        used[i] = false;
        taken[i] = -1;
    }
    
}


void Combinatorics::print() {
//    int sum = 0;
//    bool bPrint = false;
//    for(int i = 0; i < n; i++) {
//        sum += permutation[i];
//        if(sum == 20) {
//            bPrint = true;
//        }
//        
//    }
    for(int i = 0; i < n; i++) {
//        if(bPrint) {
            std::cout << permutation[i]<< " ";
//        }
    }
//    if(bPrint) {
        std::cout << std::endl;
//    }
}

void Combinatorics::permute(int i) {
    if(i >= n) {
        print();
        return;
    }
    for(int k = 0; k < n; k++) {
        if(!used[k]) {
            used[k] = true;
            permutation[i] = k + 1;
            permute(i + 1);
            used[k] = false;
        }
    }
}

void Combinatorics::testPermutation() {

    permute(0);
}

void Combinatorics::print2(int i) {
    std::cout << "( ";
    for(int l = 0; l < i; l++) {
        std::cout << taken[l] + 1 << " ";
    }
    std::cout << " )\n";
}

void Combinatorics::variate(int i) {
    if(i >= k) {
        print2(i);
        return;
    }
    for(int j = 0; j < n; j++) {
        taken[i] = j;
        variate(i + 1);
    }
}

void Combinatorics::testWithRepeat() {
    variate(0);
}
