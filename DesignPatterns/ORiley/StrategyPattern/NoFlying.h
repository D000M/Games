/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   NoFlying.h
 * Author: default
 *
 * Created on June 13, 2019, 2:02 PM
 */

#ifndef NOFLYING_H
#define NOFLYING_H

#include "IFlyStrategy.h"


class NoFlying : public IFlyStrategy {
public:
    NoFlying();
    virtual ~NoFlying();
    
    void fly() override;

private:
    
};

#endif /* NOFLYING_H */

