/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Light.cpp
 * Author: default
 * 
 * Created on June 18, 2019, 12:46 PM
 */

#include <iostream>

#include "Light.h"

Light::Light() {
}

Light::~Light() {
}

void Light::on() {
    std::cout << "Light is ON\n";
}

void Light::off() {
    std::cout << "Light is OFF\n";
}
