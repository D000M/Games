/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   SecondAttempt.cpp
 * Author: default
 * 
 * Created on April 18, 2019, 5:25 PM
 */

#include <iostream>

#include "SecondAttempt.h"

class SecondAttempt::SecondAttemptImpl {
public:
    void greet(SecondAttempt* atmpt);
};

void SecondAttempt::SecondAttemptImpl::greet(SecondAttempt* atmpt) {
    std::cout << "Hello: " << atmpt->name << std::endl;
}

SecondAttempt::SecondAttempt() 
    : implement{new SecondAttemptImpl} {

}

SecondAttempt::~SecondAttempt() {
    delete implement;
}

void SecondAttempt::greet() {
    implement->greet(this);
}


