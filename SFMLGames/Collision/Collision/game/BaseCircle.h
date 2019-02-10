/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   BaseCircle.h
 * Author: DooM
 *
 * Created on January 26, 2019, 5:20 PM
 */

#ifndef BASECIRCLE_H
#define BASECIRCLE_H
#include <iostream>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/CircleShape.hpp>


class BaseCircle {
public:
    BaseCircle(float l_radius, float l_x, float l_y, sf::Color l_color);
    virtual ~BaseCircle();
    
    sf::CircleShape GetCircle() const;
    void SetCirclePos(float l_x, float l_y);
    void SetCircleOrigin(float l_x, float l_y);
    sf::Vector2f getDirection() const;
    void SetXDirection();
    void SetYDirection();
    void SetXCollision(float newDir);
    void SetYCollision(float newDir);
    bool m_isColliding;
    int mass;
protected:
    float radius;
    float x;
    float y;
    sf::CircleShape m_circle;
    sf::Vector2f m_direction;
    
};

#endif /* BASECIRCLE_H */

