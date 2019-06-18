/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Ball.h
 * Author: default
 *
 * Created on June 10, 2019, 11:24 AM
 */

#ifndef BALL_H
#define BALL_H

#include <SFML/Graphics/CircleShape.hpp>

#include "BaseShape.h"

constexpr float ballRadius{10.0f};
constexpr float ballSpeed{5.f};

class Ball {
    sf::CircleShape ball;
    sf::Vector2f direction;
public:
    Ball(float mX, float mY);
    ~Ball();
    
    sf::CircleShape* getBall();
    
    void update();
    void checkDirection(float width, float height);

    float x();
    float y();
    float left();
    float right();
    float top();
    float bottom();
    
    void setVelocity(float f);

private:
    
};

#endif /* BALL_H */

