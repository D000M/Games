/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   StateGame.cpp
 * Author: DooM
 * 
 * Created on July 28, 2018, 8:46 PM
 */

#include "StateGame.h"
#include "../StateManager.h"

StateGame::StateGame(StateManager* l_stateManager)
: BaseState(l_stateManager) {
}

StateGame::~StateGame() {
}

void StateGame::onCreate() {
//    m_texture.loadFromFile("resources/textures/Mushroom.png");
//    m_sprite.setTexture(m_texture);
//    m_sprite.setPosition(0, 0);
//    m_increment = sf::Vector2f(400.0f, 400.0f);
//
//    EventManager* evMgr = m_stateMgr->getContext()->m_eventManager;
//    evMgr->addCallback(StateType::GAME, "Key_Escape", &StateGame::mainMenu, this);
//    evMgr->addCallback(StateType::GAME, "Key_P", &StateGame::pause, this);
    
    m_font.loadFromFile("resources/fonts/arial.ttf");
    m_text.setFont(m_font);
    m_text.setCharacterSize(24);
    
    m_text.setString(myMap.asString());
    m_text.setPosition(50, 50);
}

void StateGame::onDestroy() {
    EventManager* evMgr = m_stateMgr->getContext()->m_eventManager;
//    evMgr->removeCallback(StateType::GAME, "Key_Escape");
//    evMgr->removeCallback(StateType::GAME, "Key_P");
}

void StateGame::update(const sf::Time& l_time) {
//    sf::Vector2u l_windSize = m_stateMgr->getContext()->m_wind->getWindowSize();
//    sf::Vector2u l_textSize = m_texture.getSize();
//
//    if ((m_sprite.getPosition().x > l_windSize.x - l_textSize.x && m_increment.x > 0) ||
//            (m_sprite.getPosition().x < 0 && m_increment.x < 0)) {
//        m_increment.x = -m_increment.x;
//    }
//
//    if ((m_sprite.getPosition().y > l_windSize.y - l_textSize.y && m_increment.y > 0) ||
//            (m_sprite.getPosition().y < 0 && m_increment.y < 0)) {
//        m_increment.y = -m_increment.y;
//    }
//
//    m_sprite.setPosition(m_sprite.getPosition().x + (m_increment.x * l_time.asSeconds()),
//            m_sprite.getPosition().y + (m_increment.y * l_time.asSeconds()));
}

void StateGame::draw() {
    m_stateMgr->getContext()->m_wind->getRenderWindow()->draw(m_text);
}

void StateGame::mainMenu(EventDetails* l_details) {
    m_stateMgr->switchTo(StateType::MAINMENU);
}

void StateGame::pause(EventDetails* l_details) {
    m_stateMgr->switchTo(StateType::PAUSED);
}

void StateGame::activate() {
}

void StateGame::deactivate() {
}
