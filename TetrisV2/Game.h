/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Game.h
 * Author: default
 *
 * Created on June 7, 2019, 2:57 PM
 */

#ifndef GAME_H
#define GAME_H

#include "Window.h"


class Game {
public:
    Game();
    ~Game();
    
    void handleInput();
    void update();
    void render();
    
    Window* getWindow();
    sf::Time getElapsed() const;
    void restartClock();
    
private:

    Window mWindow;
    sf::Clock mClock;
    sf::Time mElapsed;
    
};

#endif /* GAME_H */

