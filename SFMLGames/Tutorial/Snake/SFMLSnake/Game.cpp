/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Game.cpp
 * Author: DooM
 * 
 * Created on January 22, 2019, 9:21 PM
 */

#include <SFML/Window/Keyboard.hpp>

#include "Game.h"

Game::Game() : m_window("Snake", sf::Vector2u(800, 600)),
	m_snake(m_world.GetBlockSize()), 
	m_world(sf::Vector2u(800, 600)) {
        m_clock.restart();
        srand(time(nullptr));
        m_elapsed = 0.0f;
        m_textBox.Setup(5, 14, 350, sf::Vector2f{255, 0});
        m_textBox.Add("Seeded random generator with: " + std::to_string(time(NULL)));
}

Game::~Game() {
}

void Game::HandleInput() {
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && m_snake.GetPhysicalDiretion() != Direction::DOWN) {
        m_snake.SetDirection(Direction::UP);
    }
    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && m_snake.GetPhysicalDiretion() != Direction::UP) {
        m_snake.SetDirection(Direction::DOWN);
    }
    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && m_snake.GetPhysicalDiretion() != Direction::LEFT) {
        m_snake.SetDirection(Direction::RIGHT);
    }
    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && m_snake.GetPhysicalDiretion() != Direction::RIGHT) {
        m_snake.SetDirection(Direction::LEFT);
    }
}

void Game::Update() {
    m_window.Update();
    
    float timestep = 1.0f / m_snake.GetSpeed();
    
    if(m_elapsed >= timestep) {
        m_snake.Tick();
        m_world.Update(m_snake);
        m_elapsed -= timestep;
        if(m_snake.HasLost()) {
            m_snake.Reset();
        }
    }
}

void Game::Render() {
    m_window.BeginDraw();   //Clear the window
    //Render Here
    m_world.Render(*m_window.GetRenderWindow());
    m_snake.Render(*m_window.GetRenderWindow());
    m_textBox.Render(*m_window.GetRenderWindow());
    
    m_window.EndDraw(); //Display the content
}

Window* Game::GetWindow() {
    return &m_window;
}

sf::Time Game::GetElapsed() {
    return m_clock.getElapsedTime();
}

void Game::RestartClock() {
    m_elapsed += m_clock.restart().asSeconds();
}

