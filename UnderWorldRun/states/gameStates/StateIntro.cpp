/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   StateIntro.cpp
 * Author: default
 * 
 * Created on July 27, 2018, 3:16 PM
 */

#include "StateIntro.h"
#include "../StateManager.h"
#include <iostream>

StateIntro::StateIntro(StateManager* stateMgr) 
    : BaseState(stateMgr) {
}


StateIntro::~StateIntro() {
}

void StateIntro::onCreate() {
    std::cout << "State Intro Created.\n";
    
    m_stateManager->getContext()->m_eventManager->addCallback(StateType::INTRO, "Continue_To_Game", &StateIntro::continueToGame, this);
}

void StateIntro::onDestroy() {
    m_stateManager->getContext()->m_eventManager->removeCallback(StateType::INTRO, "Continue_To_Game");
}

void StateIntro::update(sf::Time& time) {
    std::cout << "1111\n";
}

void StateIntro::draw() {
    std::cout << "22222222\n";
}

void StateIntro::continueToGame(EventDetails* details) {
    std::cout << "EEEEEEEe\n";
    m_stateManager->switchTo(StateType::GAME);
    m_stateManager->remove(StateType::INTRO);
}

void StateIntro::activate() {
    std::cout << "BBBBB\n";
}

void StateIntro::deactivate() {
    std::cout << "CCCCCC\n";
}
