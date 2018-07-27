/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   StateGame.cpp
 * Author: default
 * 
 * Created on July 27, 2018, 3:16 PM
 */

#include "StateGame.h"
#include "../StateManager.h"

StateGame::StateGame(StateManager* stateMgr) 
    : BaseState(stateMgr) {
}

StateGame::~StateGame() {
}

void StateGame::onCreate() {
    std::cout << "State Game On\n";
    
    m_stateManager->getContext()->m_eventManager->addCallback(StateType::GAME, "Return_To_Intro", &StateGame::returnToIntro, this);
}

void StateGame::deactivate() {
    std::cout << "State Game Off\n";
    m_stateManager->getContext()->m_eventManager->removeCallback(StateType::GAME, "Return_To_Intro");
}

void StateGame::activate() {
    
}

void StateGame::onDestroy() {

}

void StateGame::draw() {

}

void StateGame::update(sf::Time& time) {

}

void StateGame::returnToIntro(EventDetails* details) {
    m_stateManager->switchTo(StateType::INTRO);
    m_stateManager->remove(StateType::GAME);
}
    
