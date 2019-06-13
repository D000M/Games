/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   TotalSingletons.h
 * Author: default
 *
 * Created on May 29, 2019, 9:08 AM
 */

#ifndef TOTALSINGLETONS_H
#define TOTALSINGLETONS_H

#include "SingletonImplementation.h"
#include "AnotherClass.h"


void printTotalSngl() {
    SingletonImplementation::testSingletonDB();
    testAnotherClass();
    std::cout << SingletonImplementation::SingletonDB::numberInsantces << std::endl;
}

#endif /* TOTALSINGLETONS_H */

