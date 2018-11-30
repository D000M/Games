/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: default
 *
 * Created on November 23, 2018, 10:31 AM
 */

#include <cstdlib>
#include "examples/Externs.h"
#include "examples/FromDecimal.h"
#include "examples/ToDecimal.h"
#include "examples/Recursive.h"
#include "examples/Combinatorics.h"
#include "examples/Coding.h"
#include <iostream>
#include <complex>

using namespace std;

/*
 * 
 */

#define MAXN 100

void testCoding() {
    const unsigned int n = 6;
    const unsigned int perm[MAXN] = {
      5, 3, 6, 4, 2, 1  
    };
    const unsigned long code = 551;
    unsigned int dPerm[MAXN];
    
    Coding c;
    std::cout << "Дадената пермутациа се кодира като: " << c.codePerm(n, perm, n) << std::endl;
    std::cout << "Декодираме пермутациата отговаряща на числото: " << code << "\n";
    c.decodePerm(code, n, dPerm, n);
    for(int i = 0; i < n; i++) {
        std::cout << dPerm[i] << " ";
    }
}

int main(int argc, char** argv) {

    testEx1162("10");
    
    return 0;
}

