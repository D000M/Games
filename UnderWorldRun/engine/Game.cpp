/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Game.cpp
 * Author: DooM
 * 
 * Created on July 26, 2018, 8:23 PM
 */

#include "Game.h"

Game::Game() 
    : m_gameWindow{"Under World Run", sf::Vector2u{1280, 720}},
      m_stateManager{&m_context}{
    
    m_gameClock.restart();
    srand(time(nullptr));
        
    m_context.m_gameWindow = &m_gameWindow;
    m_context.m_eventManager = m_gameWindow.getEventManager();
    
    m_stateManager.switchTo(StateType::INTRO);
}

Game::~Game() {
}

sf::Time Game::getElapsedTime() const {
    
    return m_gameClock.getElapsedTime();
    
}

void Game::restartClock() {
    m_elapsedTime = m_gameClock.restart();
}

Window* Game::getGameWindow() {
    return &m_gameWindow;
}

//All Game Functionality

void Game::update() {
    m_gameWindow.update();
    m_stateManager.update(m_elapsedTime);
}

void Game::render() {
    //Clear Stuff on the screen.
    m_gameWindow.clearWindow();
    
    //Draw Stuff
    m_stateManager.draw();
    
    //Draw stuff on the screen
    m_gameWindow.drawWindow();
}

void Game::lateUpdate() {
    m_stateManager.processRequests();
    restartClock();
}
