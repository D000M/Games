/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   NoQuack.cpp
 * Author: default
 * 
 * Created on June 13, 2019, 2:04 PM
 */

#include <iostream>

#include "NoQuack.h"

NoQuack::NoQuack() {
}

NoQuack::~NoQuack() {
}

void NoQuack::quack() {
    std::cout << "cannot quack.";
}
