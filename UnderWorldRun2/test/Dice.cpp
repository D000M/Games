/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Dice.cpp
 * Author: default
 * 
 * Created on July 30, 2018, 10:59 AM
 */


#include "Dice.h"
#include <iostream>

Dice::Dice() 
    : m_diceResult{0} {
    std::cout << "Dice DEFAULT Constructor\n";
}

Dice::Dice(int n) 
    : m_diceResult{n} {
    std::cout << "Dice(int n) Constructor\n";
}
    
Dice::Dice(const Dice& orig) 
    : m_diceResult{orig.m_diceResult} {
    std::cout << "Dice COPY Constructor\n";
}

Dice& Dice::operator=(const Dice& obj) {
    std::cout << "Dice OPERATOR = ";
    if(this == &obj) {
        return *this;
    }
    m_diceResult = obj.m_diceResult;
    return *this;
}

Dice::~Dice() {
    std::cout << "Dice DESTRUCTOR\n";
}

void Dice::setDice(int n) {
    m_diceResult = n;
}

int Dice::getDice() const {
    return m_diceResult;
}

void Dice::printDice() {
    std::cout << "Dice result: " << m_diceResult << std::endl;
}

