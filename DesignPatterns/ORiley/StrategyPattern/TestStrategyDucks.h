/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   TestStrategyDucks.h
 * Author: default
 *
 * Created on June 13, 2019, 2:12 PM
 */

#ifndef TESTSTRATEGYDUCKS_H
#define TESTSTRATEGYDUCKS_H

#include "DisplayAsText.h"
#include "DisplayAsGraphics.h"
#include "SimpleFlying.h"
#include "NoFlying.h"
#include "JetFlying.h"
#include "NoQuack.h"
#include "Quack.h"
#include "Duck.h"


void testStrategyDucks() {
    
    DisplayAsText text;
    DisplayAsGraphics graphic;
    
    SimpleFlying simpleFly;
    NoFlying noFly;
    JetFlying jetFly;
    
    NoQuack noQuack;
    Quack quack;
    
    Duck d1("Simple Duck: ", text, simpleFly, quack);
    Duck d2("Rubber Duck: ", graphic, noFly, noQuack);
    Duck d3("Mountain Duck: ", text, jetFly, quack );
    d1.printDuck();
    std::cout << std::endl;
    d2.printDuck();
    std::cout << std::endl;
    d3.printDuck();
    std::cout << std::endl;
    
}

#endif /* TESTSTRATEGYDUCKS_H */

