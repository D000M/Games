/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   StateIntro.cpp
 * Author: DooM
 * 
 * Created on July 28, 2018, 8:46 PM
 */
#define __USE_MINGW_ANSI_STDIO 0
#include "StateIntro.h"
#include "../StateManager.h"

StateIntro::StateIntro(StateManager* l_stateManager)
    : BaseState(l_stateManager) {
}

StateIntro::~StateIntro() {
}

void StateIntro::onCreate() {
//    m_timePassed = 0.0f;

    sf::Vector2u windowSize = m_stateMgr->getContext()->m_wind->getRenderWindow()->getSize();
//
//    m_introTexture.loadFromFile("resources/textures/intro.png");
//    m_introSprite.setTexture(m_introTexture);
//    m_introSprite.setOrigin(m_introTexture.getSize().x / 2.0f,
//            m_introTexture.getSize().y / 2.0f);
//
//    m_introSprite.setPosition(windowSize.x / 2.0f, 0);

    m_font.loadFromFile("resources/fonts/arial.ttf");
    m_text.setFont(m_font);
//    m_text.setString({"Press SPACE to continue"});
    m_text.setCharacterSize(24);
    m_text.setString("Roll");
    sf::FloatRect textRect = m_text.getLocalBounds();
    m_text.setOrigin(textRect.left + textRect.width / 2.0f,
            textRect.top + textRect.height / 2.0f);
    m_text.setPosition(windowSize.x / 2.0f, windowSize.y / 2.0f);

    EventManager* evMgr = m_stateMgr->getContext()->m_eventManager;
    evMgr->addCallback(StateType::INTRO, "Key_R", &StateIntro::rollDice, this);
    evMgr->addCallback(StateType::INTRO, "Key_C", &StateIntro::continueToGame, this);
}

void StateIntro::onDestroy() {
    EventManager* evMgr = m_stateMgr->getContext()->m_eventManager;
    evMgr->removeCallback(StateType::INTRO, "Key_R");
}

void StateIntro::update(const sf::Time& l_time) {
//    if (m_timePassed < 5.0f) { // Less than five seconds.
//        m_timePassed += l_time.asSeconds();
//        m_introSprite.setPosition(
//                m_introSprite.getPosition().x,
//                m_introSprite.getPosition().y + (48 * l_time.asSeconds()));
//    }
    m_text.setString("Result: " + std::to_string(t.getDiceResult()));
}

void StateIntro::draw() {
    sf::RenderWindow* window = m_stateMgr->getContext()->m_wind->getRenderWindow();
//
//    window->draw(m_introSprite);
//    if (m_timePassed >= 5.0f) {
        window->draw(m_text);
//    }
}

void StateIntro::rollDice(EventDetails* l_details) {
//    if (m_timePassed >= 5.0f) {
//        m_stateMgr->switchTo(StateType::MAINMENU);
//        m_stateMgr->remove(StateType::INTRO);
//    }
    t.rollDice();
}

void StateIntro::activate() {
}

void StateIntro::continueToGame(EventDetails* details) {
    m_stateMgr->switchTo(StateType::GAME);
    m_stateMgr->remove(StateType::INTRO);
}

void StateIntro::deactivate() {
}

