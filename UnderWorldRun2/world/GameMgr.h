/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   GameMgr.h
 * Author: default
 *
 * Created on August 15, 2018, 4:30 PM
 */

#ifndef GAMEMGR_H
#define GAMEMGR_H

#include "Map.h"
#include "ItemsDeck.h"
#include "Player.h"

class StateManager;

class GameMgr {
public:
    GameMgr(StateManager* stateMgr);
    virtual ~GameMgr();
        
    ItemsDeck* getItemsDeck();
    
    void update(const sf::Time& l_time);
    void draw(SharedContext* shared);
private:

    Map* m_gameMap;
    sf::Text m_text;
    sf::Font m_font;
    
    ItemsDeck* m_gameDeck;
    Player* m_player;
    
};

#endif /* GAMEMGR_H */

