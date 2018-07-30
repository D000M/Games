/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Dice.h
 * Author: default
 *
 * Created on July 30, 2018, 10:59 AM
 */

#ifndef DICE_H
#define DICE_H

#include <ostream>

class Dice {
public:
    
    Dice();
    Dice(int n);
    Dice(const Dice& orig);
    Dice& operator = (const Dice& obj);
    
    virtual ~Dice();
    
    friend std::ostream& operator << (std::ostream& os, const Dice& obj) {
        return os << obj.m_diceResult;
    }
    
    void setDice(int n);
    int getDice() const;
    
    void printDice();
private:
    int m_diceResult;
};

#endif /* DICE_H */

