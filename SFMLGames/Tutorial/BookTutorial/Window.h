/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Window.h
 * Author: DooM
 *
 * Created on January 22, 2019, 8:24 PM
 */

#ifndef WINDOW_H
#define WINDOW_H

#include <string>
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/RenderWindow.hpp>


class Window {
public:
    Window();
    Window(const std::string& l_title, const sf::Vector2u& l_size);
    virtual ~Window();
    
    void BeginDraw();   //Clear the window
    void EndDraw();     //Display Changes
    
    void Update();
    
    bool IsDone();
    bool IsFullScreen();
    sf::Vector2u GetWindowSize();
    
    void ToggleFullScreen();
    void Draw(sf::Drawable& l_drawable);
    
private:
    
    void Setup(const std::string& l_title, const sf::Vector2u& l_size);
    void Destroy();
    void Create();

    sf::RenderWindow m_window;
    sf::Vector2u m_windowSize;
    std::string m_windowTitle;
    bool m_isDone;
    bool m_isFullScreen;
    
};

#endif /* WINDOW_H */

