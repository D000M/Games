/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Brick.cpp
 * Author: default
 * 
 * Created on June 12, 2019, 3:30 PM
 */

#include "Brick.h"

Brick::Brick(float mX, float mY) {
    brick.setPosition(mX, mY);
    brick.setFillColor(sf::Color::Green);
    brick.setSize({brickWidth, brickHeight});
    brick.setOrigin(brickWidth / 2.f, brickHeight / 2.f);
}

Brick::~Brick() {
}

void Brick::setDestroy(bool lDestroyed) {
    isDestroyed = lDestroyed;
}

bool Brick::getDestroyed() const {
    return isDestroyed;
}

float Brick::x() {
    return brick.getPosition().x;
}

float Brick::y() {
    return brick.getPosition().y;
}

float Brick::left() {
    return x() - brickWidth / 2.f;
}

float Brick::right() {
    return x() + brickWidth / 2.f;
}

float Brick::top() {
    return y() - brickHeight / 2.f;
}

float Brick::bottom() {
    return y() + brickHeight / 2.f;
}

sf::RectangleShape* Brick::getBrick() {
    return &brick;
}
