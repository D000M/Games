/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   ToDecimal.h
 * Author: default
 *
 * Created on November 27, 2018, 2:30 PM
 */

#ifndef TODECIMAL_H
#define TODECIMAL_H

#include <string>
#include <iostream>
#include <ostream>

class ToDecimal {
    unsigned long result;
    int base;
    std::string number;
    
    void compute();
    char getValue(char c);
public:
    
    ToDecimal(const std::string& str, int b);
    
    void setNumber(const std::string& str, int b);
    
    
    void print();
    friend std::ostream& operator << (std::ostream& os, const ToDecimal& obj);
private:

};

#endif /* TODECIMAL_H */

