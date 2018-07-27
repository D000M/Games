/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Test.h
 * Author: default
 *
 * Created on July 27, 2018, 11:17 AM
 */

#ifndef TEST_H
#define TEST_H

#include "Dice.h"


class Test {
public:
    Test();
    virtual ~Test();
    
    void rollDice();
    int getDiceResult();
private:
    Dice m_dice;
};

#endif /* TEST_H */

