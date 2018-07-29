/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   StatePaused.cpp
 * Author: DooM
 * 
 * Created on July 28, 2018, 8:46 PM
 */

#include "StatePaused.h"
#include "../StateManager.h"

StatePaused::StatePaused(StateManager* l_stateManager)
: BaseState(l_stateManager) {
}

StatePaused::~StatePaused() {
}

void StatePaused::onCreate() {
    setTransparent(true); // Set our transparency flag.
    m_font.loadFromFile("resources/fonts/arial.ttf");
    m_text.setFont(m_font);
    m_text.setString(sf::String("PAUSED"));
    m_text.setCharacterSize(14);
    m_text.setStyle(sf::Text::Bold);

    sf::Vector2u windowSize = m_stateMgr->getContext()->m_wind->getRenderWindow()->getSize();

    sf::FloatRect textRect = m_text.getLocalBounds();
    m_text.setOrigin(textRect.left + textRect.width / 2.0f,
            textRect.top + textRect.height / 2.0f);
    m_text.setPosition(windowSize.x / 2.0f, windowSize.y / 2.0f);

    m_rect.setSize(sf::Vector2f(windowSize));
    m_rect.setPosition(0, 0);
    m_rect.setFillColor(sf::Color(0, 0, 0, 150));

    EventManager* evMgr = m_stateMgr->getContext()->m_eventManager;
    evMgr->addCallback(StateType::PAUSED, "Key_P", &StatePaused::unpause, this);
}

void StatePaused::onDestroy() {
    EventManager* evMgr = m_stateMgr->getContext()->m_eventManager;
    evMgr->removeCallback(StateType::PAUSED, "Key_P");
}

void StatePaused::draw() {
    sf::RenderWindow* wind = m_stateMgr->getContext()->m_wind->getRenderWindow();
    wind->draw(m_rect);
    wind->draw(m_text);
}

void StatePaused::unpause(EventDetails* l_details) {
    m_stateMgr->switchTo(StateType::GAME);
}

void StatePaused::activate() {
}

void StatePaused::deactivate() {
}

void StatePaused::update(const sf::Time& l_time) {
}
