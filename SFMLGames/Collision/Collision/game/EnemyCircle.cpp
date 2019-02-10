/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   EnemyCircle.cpp
 * Author: DooM
 * 
 * Created on February 9, 2019, 3:04 PM
 */

#include "EnemyCircle.h"

EnemyCircle::EnemyCircle(float l_rad, float l_x, float l_y, sf::Color l_color, sf::Vector2f l_speed) 
    : BaseCircle(l_rad, l_x, l_y, l_color) {
    std::cout << "EnemyCircle Constructor USED!\n";
    m_direction = sf::Vector2f{l_speed.x, l_speed.y};
    mass = std::rand() % 6 + 1;
}


EnemyCircle::~EnemyCircle() {
    std::cout << "~EnemyCircle Destructor USED!\n";
}

sf::Vector2f BaseCircle::getDirection() const {
    return m_direction;
}

void BaseCircle::SetXDirection() {
    m_direction.x = -m_direction.x;
}

void BaseCircle::SetYDirection() {
    m_direction.y = -m_direction.y;
}

void BaseCircle::SetXCollision(float newDir) {
    m_direction.x = newDir;
}

void BaseCircle::SetYCollision(float newDir) {
    m_direction.y = newDir;
}
