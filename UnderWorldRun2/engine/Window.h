/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Window.h
 * Author: DooM
 *
 * Created on July 28, 2018, 8:41 PM
 */

#ifndef WINDOW_H
#define WINDOW_H

#pragma once
#include <string>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include "EventManager.h"

class Window {
public:
    /**
     * Default Constructor
     */
    Window();
    
    /**
     * User defined constructor
     * @param title - const std::string& window title.
     * @param size - const sf::Vector2u& window size.
     */
    Window(const std::string& title, const sf::Vector2u& size);
    
    /**
     * Destructor
     */
    ~Window();

    // ###################       METHODS       ####################### //
    /**
     * Clear contents on the window
     */
    void clearWindow();
    /**
     * Draw Stuff on the window.
     */
    void drawWindow();

    /**
     * Update stuff on the window. Using the EventManager.
     */
    void update();

    /**
     * Method to check if window is closed
     * @return - true window is closed, false if window is open.
     */
    bool isClosed();
    
    /**
     * Method to set full screen on, off
     * @return - true if window is full screen, false if window is not full screen.
     */
    bool isFullscreen();
    
    /**
     * Method to provide information if window is on focus.
     * @return - true if window is on focus, false if window is not on focus.
     */
    bool isFocused();

    /**
     * Callback function to turn on, off fullscreen mode.
     * Provided from keys.cfg file.
     * @param details buttons information for EventDetails. 
     */
    void toggleFullscreen(EventDetails* details);
    
    /**
     * Callback function to close the program.
     * @param details 
     */
    void close(EventDetails* details = nullptr);

    /**
     * Get Method for the sf::RenderWindow.
     * @return the adress of the m_renderWindow;
     */
    sf::RenderWindow* getRenderWindow();
    
    /**
     * Get Method for the game EventManager.
     * @return the adress of the m_eventManager;
     */
    EventManager* getEventManager();
    
    /**
     * Method to get the m_gameWindow size;
     * @return sf::Vector2u size.
     */
    sf::Vector2u getWindowSize();
    
private:
    //Helper Methods.
    
    /**
     * Method to setup the m_gameWindow member variable.
     * @param title set the member variable: std::string& m_windowTitle.
     * @param size  set the member variable: sf::Vector2u& m_windowSize;
     */
    void setupWindow(const std::string& title, const sf::Vector2u& size);
    void createWindow();

    /**
     * sf::RenderWindow to draw
     */
    sf::RenderWindow m_renderWindow;
    
    /**
     * EventManager object.
     */
    EventManager m_eventManager;
    
    /**
     * The sf::RenderWindow size.
     */
    sf::Vector2u m_windowSize;
    
    /**
     * The sf::RenderWindow title
     */
    std::string m_windowTitle;
    
    /**
     * Flag to check if window is open/closed
     */
    bool m_isClose;
    /**
     * Flag to check if window is full/not-full screen
     */
    bool m_isFullscreen;
    /**
     * Flag to check if window is on-focus/not-on-focus 
     */
    bool m_isFocused;
};

#endif /* WINDOW_H */

