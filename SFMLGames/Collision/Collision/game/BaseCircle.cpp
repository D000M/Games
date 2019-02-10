/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   BaseCircle.cpp
 * Author: DooM
 * 
 * Created on January 26, 2019, 5:20 PM
 */

#include "BaseCircle.h"

BaseCircle::BaseCircle(float l_radius, float l_x, float l_y, sf::Color l_color) 
    : radius{l_radius},
      x{l_x},
      y{l_y}
      {
          m_circle.setRadius(l_radius);
          m_circle.setOrigin((l_radius * 2) / 2.0f, (l_radius * 2) / 2.0f);
          m_circle.setPosition(l_x, l_y);
          m_circle.setFillColor(l_color);
          m_isColliding = false;
          std::cout << "BaseCircle Constructor USED!\n";

}

BaseCircle::~BaseCircle() {
    std::cout << "~BaseCircle DECONSTRUCTOR USED!\n";
}

sf::CircleShape BaseCircle::GetCircle() const {
    return m_circle;
}

void BaseCircle::SetCirclePos(float l_x, float l_y) {
    m_circle.setPosition(l_x, l_y);
}

void BaseCircle::SetCircleOrigin(float l_x, float l_y) {
    m_circle.setOrigin(l_x / 2.0f, l_y / 2.0f);
}
