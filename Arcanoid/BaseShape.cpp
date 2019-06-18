/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   BaseShape.cpp
 * Author: default
 * 
 * Created on June 10, 2019, 12:37 PM
 */

#include <iostream>

#include "BaseShape.h"

BaseShape::BaseShape(sf::Shape* shape, float mX, float mY) {
    shape = shape;
    shape->setPosition(mX, mY);
    std::cout << "BaseShape Created!\n";
}


BaseShape::~BaseShape() {
    if(shape) {
        delete shape;
        shape = nullptr;
    }
    std::cout << "BaseShape Destroyed\n";
}

