/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Adaptee.cpp
 * Author: default
 * 
 * Created on June 18, 2019, 2:53 PM
 */

#include <iostream>

#include "Adaptee.h"

Adaptee::Adaptee() {
}

Adaptee::~Adaptee() {
}

void Adaptee::specificRequest() {
    std::cout << "Adaptee Specific request\n";
}

