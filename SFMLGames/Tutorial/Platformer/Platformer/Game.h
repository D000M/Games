/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Game.h
 * Author: DooM
 *
 * Created on January 24, 2019, 11:08 PM
 */

#ifndef GAME_H
#define GAME_H
#include "Window.h"
#include "EventManager.h"
#include "StateManager.h"
#include "SharedContext.h"
#include <iostream>

class Game {
public:
    Game();
    ~Game();

    void Update();
    void Render();
    void LateUpdate();
    
    sf::Time GetElapsed();

    Window* GetWindow();
    
private:
    SharedContext m_context;
    Window m_window;
    StateManager m_stateManager;
    sf::Clock m_clock;
    sf::Time m_elapsed;
    
    void RestartClock();
};
#endif /* GAME_H */

