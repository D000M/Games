/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   SecondAttempt.h
 * Author: default
 *
 * Created on April 18, 2019, 5:25 PM
 */

#ifndef SECONDATTEMPT_H
#define SECONDATTEMPT_H

#include <string>


class SecondAttempt {
public:
    
    std::string name;
    
    SecondAttempt();
    ~SecondAttempt();
    
    class SecondAttemptImpl;
    SecondAttemptImpl* implement;
    
    void greet();
private:

};

#endif /* SECONDATTEMPT_H */

