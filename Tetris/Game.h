/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Game.h
 * Author: default
 *
 * Created on June 4, 2019, 12:59 PM
 */

#ifndef GAME_H
#define GAME_H

#include "Window.h"
#include "World.h"
#include <memory>

class Game {
public:
    Game();
    virtual ~Game();
    
    void handleInput();
    void update();
    void render();
    
    Window* getWindow();
    sf::Time getElapsed();
    void restartClock();
    
private:
    Window mWindow;
    sf::Clock mClock;
    float mElapsed;
    World worldGrid;
    bool oneClick;
};

#endif /* GAME_H */

