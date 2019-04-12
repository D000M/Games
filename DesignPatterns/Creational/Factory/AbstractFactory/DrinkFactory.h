/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   DrinkFactory.h
 * Author: default
 *
 * Created on April 12, 2019, 4:30 PM
 */

#ifndef DRINKFACTORY_H
#define DRINKFACTORY_H

#include "HotDrink.h"
#include "HotDrinkFactory.h"
#include <map>
#include <functional>

namespace AbstractFactory {
    
    //This os OOP Approach
    class DrinkFactory {
        std::map<std::string, std::unique_ptr<HotDrinkFactory>> factories;
    public:
        DrinkFactory() {
            factories["coffee"] = std::make_unique<CoffeeFactory>();
            factories["tea"] = std::make_unique<TeaFactory>();
        }
        
        //We can provide parameter here for volume of a drink, but more modern approach e to use functional factory using lambda and funactional
        std::unique_ptr<HotDrink> makeDrink(const std::string& name) {
            auto drink = factories[name]->make();
            drink->prepare(200);
            return drink;
        } 
    };
    ////////////////End OOP Approach
    
    //Now days we can use modern c++ approach using lambda
    //Next Part is for Functional Factory
    class DrinkWithVolumeFactory {
        std::map<std::string, std::function<std::unique_ptr<HotDrink>() > > factories;
    public:
        DrinkWithVolumeFactory() {
            //We provide lambda method for Tea instead of using TeaFactory
            factories["tea"] = []() {
                auto tea = std::make_unique<Tea>();
                tea->prepare(200);
                return tea;
            };  //end of a lambda
            factories["coffee"] = []() {
                auto coffee = std::make_unique<Coffee>();
                coffee->prepare(50);
                return coffee;
            };  //end of a lambda
        }
        
        std::unique_ptr<HotDrink> makeDrink(const std::string& name) {
            return factories[name]();   //To invoke the lambda just find the object in the map and call the method with empty round brackets.
        }
    };
}

#endif /* DRINKFACTORY_H */

