/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Window.h
 * Author: default
 *
 * Created on June 7, 2019, 2:42 PM
 */

#ifndef WINDOW_H
#define WINDOW_H

#include <SFML/System/Vector2.hpp>
#include <string>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

class Window {
public:
    Window();
    Window(const std::string& lTitle, const sf::Vector2u& lSize);
    ~Window();
    
    void beginDraw();       //Clear the window
    void endDraw();         //Display Changes
    
    void update();
    
    bool isDone();
    bool isFullScreen(); 
    
    sf::Vector2u getWindowSize() const;
    
    void toggleFullScreen();
    
    void draw(const sf::Drawable& lDrawable);
    
    void setRenderWindowPosition(const sf::Vector2i& lPos);
    
private:
    
    void setup(const std::string& lTitle, const sf::Vector2u& lSize);
    void destroy();
    void create();
    
    sf::RenderWindow mRenderWindow;
    sf::Vector2u mWindowSize;
    std::string mWindowTitle;
    
    bool mIsDone;
    bool mIsFullScreen;
    
};

#endif /* WINDOW_H */

