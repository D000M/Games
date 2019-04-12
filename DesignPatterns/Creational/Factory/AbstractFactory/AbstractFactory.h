/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   AbstractFactory.h
 * Author: default
 *
 * Created on April 12, 2019, 4:05 PM
 */

#ifndef ABSTRACTFACTORY_H
#define ABSTRACTFACTORY_H

#include <memory>

#include "HotDrinkFactory.h"
#include "DrinkFactory.h"


namespace AbstractFactory {
    
    //Bad way of approaching
    std::unique_ptr<HotDrink> makeDrink(const std::string& type) {
        std::unique_ptr<HotDrink> drink;
        if(type == "Tea") {
            drink = std::make_unique<Tea>();
            drink->prepare(200);
        }
        else {
            drink = std::make_unique<Coffee>();
            drink->prepare(50);
        }
        return drink;
    }
    void testBadAbstractFactory() {
        auto d = makeDrink("Tea");
    }
    ///////////////////
    
    //Right way OOP approach
    void testRightOOPAbstractFactory() {
        AbstractFactory::DrinkFactory df;
        auto coffee = df.makeDrink("coffee");
        auto tea = df.makeDrink("tea");
//        df.makeDrink("Wtf");
    }
    
    //Right Way Modern C++ Approach
    void testRightModernAbstractFactory() {
        AbstractFactory::DrinkWithVolumeFactory dwv;
        auto coffee = dwv.makeDrink("coffee");
        auto tea = dwv.makeDrink("tea");
    }
    
    
} //end of namespace AbstractFactory


#endif /* ABSTRACTFACTORY_H */

