/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   PCDisplay.cpp
 * Author: default
 * 
 * Created on June 13, 2019, 4:01 PM
 */

#include <iostream>

#include "PCDisplay.h"

PCDisplay::PCDisplay(const WeatherStation& obj) 
    : station{obj} {
    pcDisplayTemp = 0;
}



PCDisplay::~PCDisplay() {
}

void PCDisplay::update() {
    pcDisplayTemp = station.getTemperature();
    print();
}

void PCDisplay::print() {
    std::cout << "PC Display Temp: " << pcDisplayTemp << std::endl;
}
