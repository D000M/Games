/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   AnotherClass.h
 * Author: default
 *
 * Created on May 29, 2019, 9:06 AM
 */

#ifndef ANOTHERCLASS_H
#define ANOTHERCLASS_H

#include "SingletonImplementation.h"


void testAnotherClass() {
    std::string cityName = "Delhi";
    std::cout << cityName << " has population: " << SingletonImplementation::SingletonDB::get().getPopulation(cityName) << std::endl;
    cityName = "Tokyo";
    std::cout << cityName << " has population: " << SingletonImplementation::SingletonDB::get().getPopulation(cityName) << std::endl;
}

#endif /* ANOTHERCLASS_H */

