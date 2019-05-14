/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   ToyFactory.h
 * Author: default
 *
 * Created on March 14, 2019, 10:23 AM
 */

#ifndef TOYFACTORY_H
#define TOYFACTORY_H

#include "Toy.h"


class ToyFactory {
public:
    static Toy* createToy(const std::string& name) {
        Toy* myToy = nullptr;
        if(name == "Car") {
            myToy = new Car;
        }
        else if(name == "Plane") {
            myToy = new Plane;
        }
        else if(name == "Bike") {
            myToy = new Bike;
        }
        myToy->prepareParts();
        myToy->combineParts();
        myToy->assembleParts();
        myToy->applyLabel();
        return myToy;
    }
};


#endif /* TOYFACTORY_H */

