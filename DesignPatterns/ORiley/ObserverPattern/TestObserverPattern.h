/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   TestObserverPattern.h
 * Author: default
 *
 * Created on June 13, 2019, 4:00 PM
 */

#ifndef TESTOBSERVERPATTERN_H
#define TESTOBSERVERPATTERN_H

#include <iostream>

#include "WeatherStation.h"
#include "PhoneDisplay.h"
#include "PCDisplay.h"
#include "DigitalDisplay.h"


void testObserversORiley() {
    
    WeatherStation station;
    PhoneDisplay phoneDisplay{station};
    PCDisplay pcDisplay{station};
    DigitalDisplay digitDisplay{station};
    station.add(&phoneDisplay);
    station.add(&pcDisplay);
    station.add(&digitDisplay);
    
    station.setTemperature(-5);
    std::cout << std::endl;
    station.setTemperature(5);
    std::cout << std::endl;
    station.setTemperature(15);
    std::cout << std::endl;
    station.setTemperature(30);
    std::cout << std::endl;
    station.remove(&phoneDisplay);
    station.setTemperature(28);
    
    
}

#endif /* TESTOBSERVERPATTERN_H */

