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
    m_context.m_eventManager = m_window.GetEventManager();

    m_stateManager.SwitchTo(StateType::Intro);
}

Game::~Game() {
}

sf::Time Game::GetElapsed() {
    return m_clock.getElapsedTime();
}

void Game::RestartClock() {
    m_elapsed = m_clock.restart();
}

Window* Game::GetWindow() {
    return &m_window;
}

void Game::Update() {
    m_window.Update();
    m_stateManager.Update(m_elapsed);
}

void Game::Render() {
    m_window.BeginDraw();
    // Render here.
    m_stateManager.Draw();
    m_window.EndDraw();
}

void Game::LateUpdate() {
    m_stateManager.ProcessRequests();
    RestartClock();
}
