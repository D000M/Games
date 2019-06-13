/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   WeatherStation.cpp
 * Author: default
 * 
 * Created on June 13, 2019, 3:56 PM
 */

#include <algorithm>

#include "WeatherStation.h"

WeatherStation::WeatherStation() 
    : currTemp{0}{
    
}

WeatherStation::~WeatherStation() {
}

void WeatherStation::add(IObserver* obj) {
    observers.push_back(obj);
}

void WeatherStation::remove(IObserver* obj) {
    observers.erase(std::find(std::begin(observers), std::end(observers), obj));
}

void WeatherStation::notify() {
    for(auto& obj : observers) {
        obj->update();
    }
}

int WeatherStation::getTemperature() const {
    return currTemp;
}

void WeatherStation::setTemperature(int newTemp) {
    currTemp = newTemp;
    if(currTemp < 0 || currTemp >= 25 && currTemp < 35) {
        notify();
    }
}
