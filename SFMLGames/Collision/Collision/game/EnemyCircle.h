/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   EnemyCircle.h
 * Author: DooM
 *
 * Created on February 9, 2019, 3:04 PM
 */

#ifndef ENEMYCIRCLE_H
#define ENEMYCIRCLE_H

#include "BaseCircle.h"


class EnemyCircle : public BaseCircle {
public:
    EnemyCircle(float l_rad, float l_x, float l_y, sf::Color l_color, sf::Vector2f l_speed);
    virtual ~EnemyCircle();
private:
    
};

#endif /* ENEMYCIRCLE_H */

