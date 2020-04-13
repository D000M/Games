/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   AutoCounterTest.h
 * Author: default
 *
 * Created on December 21, 2019, 11:29 AM
 */

#ifndef AUTOCOUNTERTEST_H
#define AUTOCOUNTERTEST_H

#include "TStash.h"
#include "AutoCounter.h"

#include <iostream>
#include <fstream>
#include <string>

void testAutoCounter() {
    TStash<AutoCounter> acStash;
    
    for(int i = 0; i < 10; i++) {
        acStash.add(AutoCounter::create());
    }
    std::cout << "Remove 5 manualy:\n";
    
    for(int i = 0; i < 5; i++) {
        delete acStash.remove(i);
    }
    std::cout << "Remove 2 Without deleted them:\n";
    //to generate cleanup error message
    std::cout << acStash.remove(5) << std::endl;
    std::cout << acStash.remove(6) << std::endl;
    
    std::cout << "The Destructor cleans up the rest:\n";
    
    //Test from earlier chapters
    std::ifstream file("C16Templates/AutoCounter.h");
    assure(file, "C16Templates/AutoCounter.h");
    TStash<std::string> stringStash;
    std::string line;
    while(std::getline(file, line)) {
        stringStash.add(new std::string(line));
    }
    
    for(int i = 0; stringStash[i]; i++) {
        std::cout << "stringStash[" << i << "] = " << *stringStash[i] << std::endl;
    }
    
}

#endif /* AUTOCOUNTERTEST_H */

