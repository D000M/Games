/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   PhoneDisplay.h
 * Author: default
 *
 * Created on June 13, 2019, 4:01 PM
 */

#ifndef PHONEDISPLAY_H
#define PHONEDISPLAY_H

#include "IObserver.h"
#include "WeatherStation.h"


class PhoneDisplay : public IObserver {
    const WeatherStation& station;
    int phoneTemperature;
public:
    PhoneDisplay(const WeatherStation& obj);
    virtual ~PhoneDisplay();
    
    void update() override; 

    void print();
private:

};

#endif /* PHONEDISPLAY_H */

