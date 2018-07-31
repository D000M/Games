/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Constants.h
 * Author: default
 *
 * Created on July 31, 2018, 11:21 AM
 */

#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <SFML/Graphics/Color.hpp>

namespace Constants {
    static const sf::Color WALL = sf::Color{128,0,0};     //Empty space cant access
    static const sf::Color PATH = sf::Color{128,128,128};     //Accessable path
    static const sf::Color START = sf::Color::Green;        //Start position on the map
    static const sf::Color CHANCE = sf::Color{255,192,203};  //Chance color.
    static const sf::Color HOLE = sf::Color::Black;         //Hole color
    static const sf::Color FIRE = sf::Color{255,255,0};     //Fire Color
    static const sf::Color BAT = sf::Color{153,50,204};     //Fire Color
    static const sf::Color EARTH = sf::Color{222,184,135};  //Earth Cave.
    static const sf::Color DEVIL = sf::Color{255,0,0};      //Devil Cave.
    static const sf::Color GOLD = sf::Color{255,215,0};    //Gold Cave.
    static const sf::Color JAIL = sf::Color{70,130,180};    //JAIL.
    static const sf::Color EXIT = sf::Color{0,255,255};    //Exit.
}

#endif /* CONSTANTS_H */

