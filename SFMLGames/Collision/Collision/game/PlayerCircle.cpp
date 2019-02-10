/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   PlayerCircle.cpp
 * Author: DooM
 * 
 * Created on January 26, 2019, 5:30 PM
 */

#include "PlayerCircle.h"

PlayerCircle::PlayerCircle(float l_rad, float l_x, float l_y, sf::Color l_color) 
    : BaseCircle(l_rad, l_x, l_y, l_color) {
    std::cout << "PlayerCircle Constructor USED!\n";
}

PlayerCircle::~PlayerCircle() {
    std::cout << "~PlayerCircle DECONSTRUCTOR USED!\n";
}

