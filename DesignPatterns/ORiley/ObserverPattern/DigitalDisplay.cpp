/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   DigitalDisplay.cpp
 * Author: default
 * 
 * Created on June 13, 2019, 4:34 PM
 */

#include <iostream>

#include "DigitalDisplay.h"

DigitalDisplay::DigitalDisplay(const WeatherStation& obj)
    : station{obj} {
    
}


DigitalDisplay::~DigitalDisplay() {
}

void DigitalDisplay::update() {
    digitTemperature = station.getTemperature();
    print();
}

void DigitalDisplay::print() {
    std::cout << "Digit Display Temperature: " << digitTemperature << std::endl;
}

