/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   FromDecimal.h
 * Author: default
 *
 * Created on November 27, 2018, 2:18 PM
 */

#ifndef FROMDECIMAL_H
#define FROMDECIMAL_H

#include <ostream>


class FromDecimal {
    int number;
    int base;
    std::string result;
public:
    FromDecimal(int n, int b = 2);
    
    void setSystem(int n, int b);
    void compute();
    
    void print();
    friend std::ostream& operator << (std::ostream& os, const FromDecimal& obj);
    
private:
    char getChar(char n);
};

#endif /* FROMDECIMAL_H */

