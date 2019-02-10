/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Textbox.h
 * Author: DooM
 *
 * Created on January 24, 2019, 8:16 PM
 */

#ifndef TEXTBOX_H
#define TEXTBOX_H

#include <vector>
#include <string>
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/RenderWindow.hpp>


using MessageContainer = std::vector<std::string>;

class Textbox {
public:
    Textbox();
    Textbox(int l_visible, int l_charSize, int l_width, sf::Vector2f l_screenPos);
    virtual ~Textbox();
    
    void Setup(int l_visible, int l_charSize, int l_width, sf::Vector2f l_screenPos);
    void Add(std::string l_message);
    void Clear();
    
    void Render(sf::RenderWindow& l_wind);
    
private:
    MessageContainer m_messages;
    int m_numVisible;
    sf::RectangleShape m_backDrop;
    sf::Font m_font;
    sf::Text m_text;
};

#endif /* TEXTBOX_H */

