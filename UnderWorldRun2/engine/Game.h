/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Game.h
 * Author: DooM
 *
 * Created on July 28, 2018, 8:41 PM
 */

#ifndef GAME_H
#define GAME_H

#include "Window.h"
#include "EventManager.h"
#include "../states/StateManager.h"
#include "../SharedContext.h"
#include <iostream>

class Game {
public:
    
    /**
     * Default Constructor
     */
    Game();
    /**
     * Destructor
     */
    ~Game();

    /**
     * Updating method.
     * Update the current stuff on the window.
     * Update current state 
     */
    void update();
    
    /**
     * Drawing method.
     * Clear the stuff on the window, then draw the current state stuff,
     * and display the new stuff on the window.
     */
    void render();
    
    /**
     * Restart the clock.
     * and process requests from StateManager.
     */
    void lateUpdate();

    /**
     * Get Elapsed Time
     * @return sf::Time m_clock.getElapsed();
     */
    sf::Time getElapsed();

    /**
     * Method to get Window object adress.
     * @return m_gameWindow;
     */
    Window* getGameWindow();
    
private:
    //The SharedContext object.
    SharedContext m_context;
    //The Game Window object
    Window m_gameWindow;
    //The StateManager object.
    StateManager m_stateManager;
    //sf::Clock object.
    sf::Clock m_clock;
    //sf::Time object
    sf::Time m_elapsed;
    
    //helper methods
    /**
     * Method to restart the current time.
     */
    void restartClock();
};

#endif /* GAME_H */

