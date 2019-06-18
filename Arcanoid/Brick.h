/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Brick.h
 * Author: default
 *
 * Created on June 12, 2019, 3:30 PM
 */

#ifndef BRICK_H
#define BRICK_H

#include <SFML/Graphics/RectangleShape.hpp>


constexpr float brickWidth{60.f};
constexpr float brickHeight{20.f};


class Brick {
    sf::RectangleShape brick;
    
    bool isDestroyed{false};
public:
    Brick(float mX, float mY);
    virtual ~Brick();
    
    float x();
    float y();
    float left();
    float right();
    float top();
    float bottom();
    
    void setDestroy(bool lDestroyed);
    bool getDestroyed() const;
    
    sf::RectangleShape* getBrick();
    
private:

};

#endif /* BRICK_H */

