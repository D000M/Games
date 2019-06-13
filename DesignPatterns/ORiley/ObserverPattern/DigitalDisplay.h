/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   DigitalDisplay.h
 * Author: default
 *
 * Created on June 13, 2019, 4:34 PM
 */

#ifndef DIGITALDISPLAY_H
#define DIGITALDISPLAY_H

#include "IObserver.h"
#include "WeatherStation.h"


class DigitalDisplay : public IObserver {
    const WeatherStation& station;
    int digitTemperature;
public:
    DigitalDisplay(const WeatherStation& obj);
    virtual ~DigitalDisplay();
    
    void update() override;
    void print();

private:

};

#endif /* DIGITALDISPLAY_H */

