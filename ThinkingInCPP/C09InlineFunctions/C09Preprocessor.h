/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   C09Preprocessor.h
 * Author: default
 *
 * Created on December 6, 2019, 12:55 PM
 */

#ifndef C09PREPROCESSOR_H
#define C09PREPROCESSOR_H

#include <iostream>

#include "Time.h"


#define F(x) (x + 1); std::cout << #x << " = " <<  x; std::cout << "\n";
#define F2(x)(x + 1)
//#define FuncF(x) ;

void testFPreProc() {
    F(2);
    F(3);
    std::cout << F2(2) << "\n" << F2(3) << std::endl;
}


void testingTime() {
    Time start;
    for(int i = 1; i <= 1000; i++) {
        std::cout << i << ' ';
        if(i % 10 == 0) {
            std::cout << std::endl;
        }
    }
    Time end;
    std::cout << std::endl;
    std::cout << "Program start: " << start.ascii();
    std::cout << "Program end: " << end.ascii();
    std::cout << "Delta time: " << end.delta(&start);
}

//More Preprocessors futures
//Value of any variable
#define DEBUG(x) std::cout << #x " = " << x << std::endl

#define TRACE(x) std::cerr << #x << std::endl; x

void testDebugAndTrace() {
    DEBUG("55");
    TRACE("Error Here" + 10);
}

int recursiveDecrement(int n) {
    if (n == 0) {
        return 0;
    }
    std::cout << n << "\n";
    return recursiveDecrement(n - 1);
}
void testRecursiveDecrement() {
    std::cout << recursiveDecrement(10) << std::endl;
}
#endif /* C09PREPROCESSOR_H */

