/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Game.h
 * Author: DooM
 *
 * Created on July 26, 2018, 8:23 PM
 */

#ifndef GAME_H
#define GAME_H

#include <SFML/System/Clock.hpp>

#include "Window.h"
#include "../states/StateManager.h"
#include "EventManager.h"

class Game {
public:
    Game();
    ~Game();
    
    /**
     * Update all the game stuff
     */
    void update();
    /**
     * Render all stuff on the screen
     */
    void render();
    /**
     * Provide late update
     */
    void lateUpdate();
    
    /**
     * Get elapsed time 
     * @return m_gameClock.
     */
    sf::Time getElapsedTime() const;
    
    /**
     * Get the game window
     * @return m_gameWindow
     */
    Window* getGameWindow();
private:
    
    /**
     * Restart the time
     */
    void restartClock();
    
    SharedContext m_context;
    Window m_gameWindow;
    sf::Clock m_gameClock;
    sf::Time m_elapsedTime;
    StateManager m_stateManager;
};

#endif /* GAME_H */

