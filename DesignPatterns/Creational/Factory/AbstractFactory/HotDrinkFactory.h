/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   HotDrinkFactory.h
 * Author: default
 *
 * Created on April 12, 2019, 4:22 PM
 */

#ifndef HOTDRINKFACTORY_H
#define HOTDRINKFACTORY_H

#include "HotDrink.h"




namespace AbstractFactory {
    
    //Our Abstract Factory
    struct HotDrinkFactory {        
        virtual std::unique_ptr<AbstractFactory::HotDrink> make() const = 0;
    };
    
    struct TeaFactory : HotDrinkFactory {
        std::unique_ptr<AbstractFactory::HotDrink> make() const override {
            return std::make_unique<Tea>();
        }
    };
    
    struct CoffeeFactory : HotDrinkFactory {
        std::unique_ptr<AbstractFactory::HotDrink> make() const override {
            return std::make_unique<Coffee>();
        }
    };
}

#endif /* HOTDRINKFACTORY_H */

