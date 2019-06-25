/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Game.cpp
 * Author: default
 * 
 * Created on June 7, 2019, 2:57 PM
 */

#include "Game.h"

Game::Game() 
    : mWindow{"Chapter 2", sf::Vector2u{800, 600}} {
    mWindow.setRenderWindowPosition(sf::Vector2i{250, 200});
}

Game::~Game() {
}

void Game::handleInput() {

}


void Game::update() {
    mWindow.update();
}

void Game::render() {
    mWindow.beginDraw();
    
    //mWindow.draw(lDrawable);  //Draw here
    
    mWindow.endDraw();
}

sf::Time Game::getElapsed() const {
    return mElapsed;
}

void Game::restartClock() {
    mElapsed = mClock.restart();
}

Window* Game::getWindow(){
    return &mWindow;
}
