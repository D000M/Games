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
    m_gameMgr = new GameMgr{m_stateMgr};
}

void StateGame::onDestroy() {
    EventManager* evMgr = m_stateMgr->getContext()->m_eventManager;
    
    delete m_gameMgr;
    m_gameMgr = nullptr;

}

void StateGame::update(const sf::Time& l_time) {

    m_gameMgr->update(l_time);

}

void StateGame::draw() {
    m_gameMgr->draw(m_stateMgr->getContext());
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

