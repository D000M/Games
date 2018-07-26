/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Window.h
 * Author: DooM
 *
 * Created on July 26, 2018, 7:49 PM
 */

#ifndef WINDOW_H
#define WINDOW_H

#include <SFML/Graphics/RenderWindow.hpp>
#include "EventManager.h"

class Window {
public:
    /**
     * Default Constructor
     */
    Window();
    /**
     * Custom Constructor
     * @param title - the Window Title
     * @param size - the Window Size
     */
    Window(const std::string& title, const sf::Vector2u& size);
    /**
     * Destructor. Close the window.
     */
    virtual ~Window();
    
    /**
     * Clear stuff on the window and set the background to black
     */
    void clearWindow();
    /**
     * Display window 
     */
    void drawWindow();
    
    /**
     * Update window.
     */
    void update();
    
    /**
     * Close The window
     * @return true if window is closed, false if is open.
     */
    bool isClosed() const;
    /**
     * Check If window is on FullScreen Mode
     * @return true if is full screen, false if is not full screen.
     */
    bool isFullScreen() const;
    /**
     * Check if window is on focus
     * @return true if is on focus, false if is not on focus.
     */
    bool isFocused() const;
    
    /**
     * Get the render window.
     * @return m_window;
     */
    sf::RenderWindow* getRenderWindow();
    
    EventManager* getEventManager();
    /**
     * Get Window Size
     * @return m_windowSize;
     */
    sf::Vector2u getWindowSize() const;
    
    //callbacks
    void toggleFullScreen(EventDetails* details);
    void closeWindow(EventDetails* details = nullptr);
private:
    
    //Helper Methods
    /**
     * Set the window with title and size.
     * @param title window title
     * @param size window size
     */
    void setupWindow(const std::string& title, const sf::Vector2u& size);
    
    /**
     * Create the Window.
     */
    void createWindow();
    
    //MainWindow.
    sf::RenderWindow m_renderWindow;
    
    EventManager m_eventManager;
    //Window Size.
    sf::Vector2u m_windowSize;
    //Window Title.
    std::string m_windowTitle;
    //Is Window Closed: true - window closed, false - window open.
    bool m_isClosed;
    //Is Window Full Screen: true - window is Full Screen, false - window is not Full Screen.
    bool m_isFullScreen;
    //Is Window Focused: true - window is on focus, false - window is not on focus.
    bool m_isFocused;
    
};

#endif /* WINDOW_H */

