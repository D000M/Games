/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Duck.cpp
 * Author: default
 * 
 * Created on June 13, 2019, 1:57 PM
 */

#include "Duck.h"
#include <iostream>

Duck::Duck(const std::string& duck, IDisplayStrategy& d, IFlyStrategy& f, IQuackStrategy& q) 
   : name{duck},
     refDisplay{d}, 
     refFly{f},
     refQuack{q} {
    
}



Duck::~Duck() {
}

void Duck::executeDisplay() {
    refDisplay.display();
}

void Duck::executeFly() {
    refFly.fly();
}

void Duck::executeQuack() {
    refQuack.quack();
}

void Duck::printDuck() {
    std::cout << name << " ";
    executeDisplay();
    std::cout << " ";
    executeFly();
    std::cout << " ";
    executeQuack();
}
