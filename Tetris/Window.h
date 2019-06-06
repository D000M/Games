/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Window.h
 * Author: default
 *
 * Created on June 4, 2019, 12:42 PM
 */

#ifndef WINDOW_H
#define WINDOW_H

#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <string>


class Window {
public:
    Window();
    Window(const sf::Vector2u& lSize, const sf::String& lTitle);
    
    ~Window();
    
    bool isWindowOpen() const;
    
    
    void beginDraw();
    void endDraw();
    
    void update();
    void clearWindow();
    
    sf::Vector2u getMainWindowSize() const;
    
    void draw(sf::Drawable& lDrawable);
    
    sf::RenderWindow* getRenderWindow();
 
private:
    void destroyWindow();
    void createWindow();
    void setupWindow(const sf::Vector2u& lSize, const sf::String& lTitle);
    
    sf::RenderWindow mMainWindow;
    sf::Vector2u mMainWindowSize;
    sf::String mWindowTitle;
    bool mIsDone;
    
};

#endif /* WINDOW_H */

