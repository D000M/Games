/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   WeatherStation.h
 * Author: default
 *
 * Created on June 13, 2019, 3:56 PM
 */

#ifndef WEATHERSTATION_H
#define WEATHERSTATION_H

#include <vector>

#include "IObserver.h"
#include "IObservable.h"


class WeatherStation : public IObservable {
public:
    WeatherStation();
    virtual ~WeatherStation();
    
    void add(IObserver* obj) override;
    void remove(IObserver* obj) override;
    void notify() override;
    
    int getTemperature() const;
    void setTemperature(int newTemp);
private:
    std::vector<IObserver*> observers;
    int currTemp;
};

#endif /* WEATHERSTATION_H */

