/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   PCDisplay.h
 * Author: default
 *
 * Created on June 13, 2019, 4:01 PM
 */

#ifndef PCDISPLAY_H
#define PCDISPLAY_H

#include "IObserver.h"
#include "WeatherStation.h"


class PCDisplay : public IObserver {
    const WeatherStation& station;
    int pcDisplayTemp;
public:
    PCDisplay(const WeatherStation& obj);
    virtual ~PCDisplay();
    
    void update() override;
    void print();
private:

};

#endif /* PCDISPLAY_H */

