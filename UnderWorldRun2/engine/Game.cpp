/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Game.cpp
 * Author: DooM
 * 
 * Created on July 28, 2018, 8:41 PM
 */

#include "Game.h"

Game::Game() : m_window("Chapter 5", sf::Vector2u(800, 600)), m_stateManager(&m_context) {
    m_clock.restart();
    srand(time(nullptr));

    m_context.m_wind = &m_window;
    m_context.m_eventManager = m_window.getEventManager();

    m_stateManager.switchTo(StateType::INTRO);
}

Game::~Game() {
}

sf::Time Game::getElapsed() {
    return m_clock.getElapsedTime();
}

void Game::restartClock() {
    m_elapsed = m_clock.restart();
}

Window* Game::getWindow() {
    return &m_window;
}

void Game::update() {
    m_window.update();
    m_stateManager.update(m_elapsed);
}

void Game::render() {
    m_window.beginDraw();
    // Render here.
    m_stateManager.draw();
    m_window.endDraw();
}

void Game::lateUpdate() {
    m_stateManager.processRequests();
    restartClock();
}
