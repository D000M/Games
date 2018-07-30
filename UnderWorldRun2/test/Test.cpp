/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Test.cpp
 * Author: default
 * 
 * Created on July 30, 2018, 11:00 AM
 */

#include "Test.h"
#include "../utils/RNGGenerator.h"

Test::Test() : m_dice{} {
}

Test::~Test() {
}

void Test::rollDice() {
    
    int r = getRandomInteger(1, 6);
    std::cout << "Result: " << r << std::endl;
    m_dice.setDice(r);
    
}

int Test::getDiceResult() {
    return m_dice.getDice();
}

