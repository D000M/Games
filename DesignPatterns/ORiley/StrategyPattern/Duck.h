/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Duck.h
 * Author: default
 *
 * Created on June 13, 2019, 1:57 PM
 */

#ifndef DUCK_H
#define DUCK_H

#include <string>

#include "IDisplayStrategy.h"
#include "IFlyStrategy.h"
#include "IQuackStrategy.h"


class Duck {
    std::string name;
public:
    Duck(const std::string& duck, IDisplayStrategy& d, IFlyStrategy& f, IQuackStrategy& q);
    virtual ~Duck();
    
    void executeDisplay();
    void executeFly();
    void executeQuack();
    
    void printDuck();
private:
    IDisplayStrategy& refDisplay;
    IFlyStrategy& refFly;
    IQuackStrategy& refQuack;
};

#endif /* DUCK_H */

