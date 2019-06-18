/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Paddle.cpp
 * Author: default
 * 
 * Created on June 10, 2019, 3:44 PM
 */

#include <SFML/Window/Keyboard.hpp>
#include <iostream>

#include "Paddle.h"

Paddle::Paddle(float mX, float mY) {
    paddle.setPosition(mX, mY);
    paddle.setFillColor(sf::Color::Red);
    paddle.setSize({paddleWidth, paddleHeight});
    paddle.setOrigin(paddleWidth / 2.f, paddleHeight / 2.f);
}

Paddle::~Paddle() {
}

sf::RectangleShape* Paddle::getPaddle() {
    return &paddle;
}

void Paddle::update(const float& windowWidth, const float& windowHeight) {
    paddle.move(velocity);
    
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left) && left() > 0) {
        velocity.x = -paddleSpeed;
    }
    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right) && right() < windowWidth) {
        velocity.x = paddleSpeed;
    }
    else {
        velocity.x = 0;
    }
}

float Paddle::x() {
    return paddle.getPosition().x;
}
float Paddle::y() {
    return paddle.getPosition().y;
}

float Paddle::left() {
    return x() - paddle.getSize().x / 2.f;
}

float Paddle::right() {
    return x() + paddle.getSize().x / 2.f;
}

float Paddle::top() {
    return y() - paddle.getSize().y / 2.f;
}

float Paddle::bottom() {
    return y() + paddle.getSize().y / 2.f;
}



