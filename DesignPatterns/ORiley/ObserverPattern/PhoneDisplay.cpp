/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   PhoneDisplay.cpp
 * Author: default
 * 
 * Created on June 13, 2019, 4:01 PM
 */

#include <iostream>

#include "PhoneDisplay.h"

PhoneDisplay::PhoneDisplay(const WeatherStation& obj)
    : station{obj} {
    phoneTemperature = 0;
}


PhoneDisplay::~PhoneDisplay() {
}

void PhoneDisplay::update() {
    phoneTemperature = station.getTemperature();
    print();
}

void PhoneDisplay::print() {
    std::cout << "Phone Display Temperature: " << phoneTemperature << std::endl;
}
