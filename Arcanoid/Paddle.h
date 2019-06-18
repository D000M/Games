/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Paddle.h
 * Author: default
 *
 * Created on June 10, 2019, 3:44 PM
 */

#ifndef PADDLE_H
#define PADDLE_H

#include <SFML/Graphics/RectangleShape.hpp>

constexpr float paddleWidth{80.f};
constexpr float paddleHeight{20.f};
constexpr float paddleSpeed{12.f};

class Paddle {
    sf::RectangleShape paddle;
    sf::Vector2f velocity;
public:
    Paddle(float mX, float mY);
    virtual ~Paddle();
    
    sf::RectangleShape* getPaddle();
    
    void update(const float& windowWidth, const float& windowHeight);

    float x();
    float y();
    float left();
    float right();
    float top();
    float bottom();
    
private:
    
};

#endif /* PADDLE_H */

