/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Map.h
 * Author: DooM
 *
 * Created on July 30, 2018, 8:45 PM
 */

#ifndef MAP_H
#define MAP_H

#include <array>
#include <SFML/Graphics/RectangleShape.hpp>
#include <vector>
#include "../SharedContext.h"

enum Tile {
    WALL = 0,
    START,
    PATH,
    CHANCE,
    HOLE,
    FIRE_CAVE,
    BAT_CAVE,
    EARTH_CAVE,
    DEVIL_CAVE,
    GOLD_CAVE,
    JAIL,    
    EXIT
};

class Map {
public:
    Map(SharedContext* context);
    virtual ~Map();
        
    void draw();
    void update();
    
    char tileToChar(int i, int j);
    std::string asString();
    
private:
    
    void loadMap(const std::string& path);
    
    SharedContext* m_context;
    std::array<std::array<Tile, 27>, 11> level;
    std::vector<sf::RectangleShape> rects;
    
    sf::RectangleShape m_background;
    
};

#endif /* MAP_H */

