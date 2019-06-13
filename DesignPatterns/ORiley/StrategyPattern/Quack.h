/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Quack.h
 * Author: default
 *
 * Created on June 13, 2019, 2:03 PM
 */

#ifndef QUACK_H
#define QUACK_H

#include "IQuackStrategy.h"


class Quack : public IQuackStrategy {
public:
    Quack();
    virtual ~Quack();
    
    void quack() override;

private:

};

#endif /* QUACK_H */

