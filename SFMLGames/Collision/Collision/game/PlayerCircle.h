/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   PlayerCircle.h
 * Author: DooM
 *
 * Created on January 26, 2019, 5:30 PM
 */

#ifndef PLAYERCIRCLE_H
#define PLAYERCIRCLE_H

#include "BaseCircle.h"


class PlayerCircle : public BaseCircle {
public:
    PlayerCircle(float l_radius, float l_x, float l_y, sf::Color l_color);
    virtual ~PlayerCircle();
    
private:

};

#endif /* PLAYERCIRCLE_H */

