/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Ball.cpp
 * Author: default
 * 
 * Created on June 10, 2019, 11:24 AM
 */

#include "Ball.h"
#include <iostream>

Ball::Ball(float mX, float mY) {
    ball.setRadius(ballRadius);
    ball.setFillColor(sf::Color::Blue);
    ball.setOrigin(ballRadius, ballRadius);
    ball.setPosition(mX, mY);
    direction.x = -ballSpeed;
    direction.y = -ballSpeed;
}


Ball::~Ball() {
}

sf::CircleShape* Ball::getBall(){
    return &ball;
}

void Ball::update() {
    ball.move(direction.x, direction.y);
}

void Ball::checkDirection(float width, float height) {
    if(left() < 0) {
        direction.x = ballSpeed;
    }
    else if(top() < 0) {
        direction.y = ballSpeed;
    }
    else if(right() > width - ballRadius) {
        direction.x = -ballSpeed;
    }
    else if(bottom() > height - ballRadius) {
        direction.y = -ballSpeed;
    }
}

void Ball::setVelocity(float f) {
    direction.y = f;
}

float Ball::x() {
    return ball.getPosition().x;
}

float Ball::y() {
    return ball.getPosition().y;
}

float Ball::left() {
    return x() - ball.getRadius();
}

float Ball::right() {
    return x() + ball.getRadius();
}

float Ball::top() {
    return y() - ball.getRadius();
}

float Ball::bottom() {
    return y() + ball.getRadius();
}
