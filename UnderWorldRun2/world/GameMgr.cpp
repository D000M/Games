/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   GameMgr.cpp
 * Author: default
 * 
 * Created on August 15, 2018, 4:30 PM
 */

#include "GameMgr.h"
#include "../states/StateManager.h"

GameMgr::GameMgr(StateManager* stateMgr) {
        
    
    m_gameMap = new Map(stateMgr->getContext());
    m_font.loadFromFile("resources/fonts/arial.ttf");
    m_text.setFont(m_font);
    m_text.setCharacterSize(24);
    
    m_text.setString(m_gameMap->asString());
    m_text.setPosition(50, 50);
    m_gameDeck = new ItemsDeck{};
    m_player = new Player{stateMgr->getContext()};
    
    m_player->setDeck(m_gameDeck->getItem());
    m_player->setDeck(m_gameDeck->getItem());
    m_player->setDeck(m_gameDeck->getItem());
    m_player->setDeck(m_gameDeck->getItem());
    m_player->setDeck(m_gameDeck->getItem());
    
    m_player->printDeck();
    
    m_gameDeck->printRemainingDeck();
}


GameMgr::~GameMgr() {
    delete m_player;
    m_player = nullptr;
    delete m_gameDeck;
    m_gameDeck = nullptr;
    delete m_gameMap;
    m_gameMap = nullptr;
}

ItemsDeck* GameMgr::getItemsDeck() {
    return m_gameDeck;
}

void GameMgr::update(const sf::Time& l_time) {
    m_gameMap->update();
    m_player->update();
}

void GameMgr::draw(SharedContext* shared) {
    shared->m_wind->getRenderWindow()->draw(m_text);
    m_gameMap->draw();
    m_player->draw();
}
