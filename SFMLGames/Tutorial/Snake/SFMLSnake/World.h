/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   World.h
 * Author: DooM
 *
 * Created on January 22, 2019, 10:13 PM
 */

#ifndef WORLD_H
#define WORLD_H

#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/CircleShape.hpp>

#include "Snake.h"


class World {
public:
    World(const sf::Vector2u& l_windSize);
    virtual ~World();
    
    int GetBlockSize();
    
    void RespawnApple();
    
    void Update(Snake& l_player);
    void Render(sf::RenderWindow& l_window);
    
private:
    
    sf::Vector2u m_windowSize;
    sf::Vector2i m_item;
    int m_blockSize;
    
    sf::CircleShape m_appleShape;
    sf::RectangleShape m_bounds[4];
    
};

#endif /* WORLD_H */

