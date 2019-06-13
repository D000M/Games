/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   JetFlying.h
 * Author: default
 *
 * Created on June 13, 2019, 2:01 PM
 */

#ifndef JETFLYING_H
#define JETFLYING_H

#include "IFlyStrategy.h"


class JetFlying : public IFlyStrategy {
public:
    JetFlying();
    virtual ~JetFlying();
    
    void fly() override;    

private:

};

#endif /* JETFLYING_H */

