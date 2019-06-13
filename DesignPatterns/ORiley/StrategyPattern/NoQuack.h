/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   NoQuack.h
 * Author: default
 *
 * Created on June 13, 2019, 2:04 PM
 */

#ifndef NOQUACK_H
#define NOQUACK_H

#include "IQuackStrategy.h"


class NoQuack : public IQuackStrategy {
public:
    NoQuack();
    virtual ~NoQuack();
    
    void quack() override;

private:

};

#endif /* NOQUACK_H */

