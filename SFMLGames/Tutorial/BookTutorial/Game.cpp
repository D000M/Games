/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Game.cpp
 * Author: DooM
 * 
 * Created on January 22, 2019, 8:43 PM
 */

#include "Game.h"

Game::Game() 
    : m_window{"Chapter 2", sf::Vector2u{640, 480}} {
    //Setting up class members
    m_cloudTexture.loadFromFile("resources/cloud.png");
    m_cloud.setTexture(m_cloudTexture);
    m_increment = sf::Vector2i{400, 400};
}

Game::~Game() {
}

void Game::HandleInput() {

}

void Game::Update() {
    m_window.Update();
    MoveCloud();
}

void Game::MoveCloud() {
    sf::Vector2u l_windSize = m_window.GetWindowSize();
    sf::Vector2u l_textSize = m_cloudTexture.getSize();
    
    if((m_cloud.getPosition().x > l_windSize.x - l_textSize.x && m_increment.x > 0) ||
            m_cloud.getPosition().x < 0 && m_increment.x < 0) {
        m_increment.x = -m_increment.x;
    }
    if((m_cloud.getPosition().y > l_windSize.y - l_textSize.y && m_increment.y > 0) ||
            m_cloud.getPosition().y < 0 && m_increment.y < 0) {
        m_increment.y = -m_increment.y;
    }
    
    float fElapsed = m_elapsed.asSeconds();
    
    m_cloud.setPosition(m_cloud.getPosition().x + (m_increment.x * fElapsed), m_cloud.getPosition().y + (m_increment.y * fElapsed));
}

void Game::Render() {
    m_window.BeginDraw();   //Clear the window
    m_window.Draw(m_cloud);
    m_window.EndDraw(); //Display the content
}

Window* Game::GetWindow() {
    return &m_window;
}

sf::Time Game::GetElapsed() {
    return m_elapsed;
}

void Game::RestartClock() {
    m_elapsed = m_clock.restart();
}
