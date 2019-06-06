/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Game.cpp
 * Author: default
 * 
 * Created on June 4, 2019, 12:59 PM
 */

#include "Game.h"
#include <iostream>

Game::Game() 
    : mWindow{sf::Vector2u{800, 880}, "Tetris v0.1a"},
      worldGrid{} {
    mClock.restart();
    srand(std::time(nullptr));
    mElapsed = 0.0f;
    oneClick = false;
}

Game::~Game() {
}

void Game::handleInput() {
    
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && !oneClick) {
        std::cout << "Right Pressed!\n";
        oneClick = true;
        worldGrid.getTetro()->moveRight();
//        worldGrid.updateHorizontalMoving();
    }
    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && !oneClick) {
        std::cout << "Left Pressed!\n";
        oneClick = true;
        worldGrid.getTetro()->moveLeft();
//        worldGrid.updateHorizontalMoving();
    }
//    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && m_snake.GetPhysicalDiretion() != Direction::DOWN) {
//        m_snake.SetDirection(Direction::UP);
//    }
//    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && m_snake.GetPhysicalDiretion() != Direction::UP) {
//        m_snake.SetDirection(Direction::DOWN);
//    }
//    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && m_snake.GetPhysicalDiretion() != Direction::LEFT) {
//        worldGrid.
//    }
//    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && m_snake.GetPhysicalDiretion() != Direction::RIGHT) {
//        m_snake.SetDirection(Direction::LEFT);
//    }
}

void Game::update() {
    mWindow.update();
    float lTimeStep = 1.0f/1;
    worldGrid.updateHorizontalMoving();
    if(mElapsed >= lTimeStep) {
        //update world
        worldGrid.update();
        mElapsed -= lTimeStep;
        oneClick = false;
    }
}

void Game::render() {
    mWindow.beginDraw();
    worldGrid.render(mWindow.getRenderWindow());
    //Rend objects here
    
    
    mWindow.endDraw();
}

sf::Time Game::getElapsed() {
    return mClock.getElapsedTime();
}

void Game::restartClock() {
    mElapsed += mClock.restart().asSeconds();
}

Window* Game::getWindow(){
    return &mWindow;
}
