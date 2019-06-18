/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   BaseShape.h
 * Author: default
 *
 * Created on June 10, 2019, 12:37 PM
 */

#ifndef BASESHAPE_H
#define BASESHAPE_H

#include <SFML/Graphics/Shape.hpp>
#include <memory>


class BaseShape {
    
    sf::Shape* shape;
    
public:
    BaseShape(sf::Shape* shape, float mX, float mY);
    virtual ~BaseShape();
    
    float getXPos() {
        return shape->getLocalBounds().left;
    }
    float getYPos() {
        return shape->getLocalBounds().top;
    }
    float getWidth() {
        return shape->getLocalBounds().width;
    } 
    float getHeight() {
        return shape->getLocalBounds().height;
    }
private:

};

#endif /* BASESHAPE_H */

