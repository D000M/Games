/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   SimpleFlying.h
 * Author: default
 *
 * Created on June 13, 2019, 2:00 PM
 */

#ifndef SIMPLEFLYING_H
#define SIMPLEFLYING_H

#include "IFlyStrategy.h"


class SimpleFlying : public IFlyStrategy{
public:
    SimpleFlying();
    virtual ~SimpleFlying();
    
    void fly() override;

private:

};

#endif /* SIMPLEFLYING_H */

