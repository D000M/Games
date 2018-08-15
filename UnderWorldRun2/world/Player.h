/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Player.h
 * Author: default
 *
 * Created on July 31, 2018, 2:17 PM
 */

#ifndef PLAYER_H
#define PLAYER_H

#define __USE_MINGW_ANSI_STDIO 0

#include <SFML/Graphics/CircleShape.hpp>
#include "../SharedContext.h"
#include "../engine/EventManager.h"
#include "../test/Dice.h"
#include "PlayerDeck.h"

class Player {
public:
    Player(SharedContext* shared, int id);
    virtual ~Player();

    void draw();
    void update();

    void move(EventDetails* details);

    void rollDice();
    
    void setDeck(Item& obj);
    void printDeck();
private:

    SharedContext* m_shared;
    sf::CircleShape m_playerFig;
    sf::Font m_font;
    sf::Text m_text;
    sf::Vector2u m_playerPos;
    Dice m_dice;
    sf::Text m_diceText;
    
    PlayerDeck m_playDeck;
    int m_playerID;
};

#endif /* PLAYER_H */

