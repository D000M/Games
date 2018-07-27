/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Test.cpp
 * Author: default
 * 
 * Created on July 27, 2018, 11:17 AM
 */

#include "Test.h"

Test::Test() : m_dice{} {
}

Test::~Test() {
}

void Test::rollDice() {
    srand(time(nullptr));
    
    int r = std::rand() % 6 + 1;
    m_dice.setDice(r);
    
}

int Test::getDiceResult() {
    return m_dice.getDice();
}

