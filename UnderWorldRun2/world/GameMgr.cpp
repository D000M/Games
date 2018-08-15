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

GameMgr::GameMgr(StateManager* stateMgr) 
    : m_shared{stateMgr->getContext()} {
        
    
    m_gameMap = new Map(stateMgr->getContext());
    m_font.loadFromFile("resources/fonts/arial.ttf");
    m_text.setFont(m_font);
    m_text.setCharacterSize(24);
    
    m_text.setString(m_gameMap->asString());
    m_text.setPosition(50, 50);
    m_gameDeck = new ItemsDeck{};

    m_players.push_back(new Player{stateMgr->getContext(), 0});
    m_players.push_back(new Player{stateMgr->getContext(), 1});
    m_players.push_back(new Player{stateMgr->getContext(), 2});
    
    for(int i = 0; i < m_players.size(); ++i) {
        m_players.at(i)->setDeck(m_gameDeck->getItem());
        m_players.at(i)->setDeck(m_gameDeck->getItem());
        m_players.at(i)->setDeck(m_gameDeck->getItem());
        m_players.at(i)->setDeck(m_gameDeck->getItem());
        m_players.at(i)->setDeck(m_gameDeck->getItem());
    }
    for(int i = 0; i < m_players.size(); ++i) {
        m_players.at(i)->printDeck();
        std::cout << "###############\n";
    }

    m_gameDeck->printRemainingDeck();
    m_turnState = DEFAULT;
    m_gameTurn = 1;
    m_shared->m_eventManager->addCallback(StateType::GAME, "Key_R", &GameMgr::roll, this);

}


GameMgr::~GameMgr() {
    for(int i = 0; i < m_players.size(); i++) {
        delete m_players.at(i);
        m_players.at(i) = nullptr;
    }
    delete m_gameDeck;
    m_gameDeck = nullptr;
    delete m_gameMap;
    m_gameMap = nullptr;
    m_shared->m_eventManager->removeCallback(StateType::GAME, "Key_R");
}

ItemsDeck* GameMgr::getItemsDeck() {
    return m_gameDeck;
}

void GameMgr::update(const sf::Time& l_time) {
    m_gameMap->update();
    for(int i = 0; i < m_players.size(); i++) {
        m_players.at(i)->update();
    }
}

void GameMgr::draw(SharedContext* shared) {
    shared->m_wind->getRenderWindow()->draw(m_text);
    m_gameMap->draw();
    for(int i = 0; i < m_players.size(); i++) {
        m_players.at(i)->draw();
    }
}

void GameMgr::roll(EventDetails* details) {
    m_players.at(2)->rollDice();
}
