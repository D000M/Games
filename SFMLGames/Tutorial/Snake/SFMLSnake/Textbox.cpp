/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Textbox.cpp
 * Author: DooM
 * 
 * Created on January 24, 2019, 8:16 PM
 */

#include "Textbox.h"

Textbox::Textbox() {
    Setup(5, 9, 200, sf::Vector2f{0, 0});
}

Textbox::Textbox(int l_visible, int l_charSize, int l_width, sf::Vector2f l_screenPos) {
    Setup(l_visible, l_charSize, l_width, l_screenPos);
}


Textbox::~Textbox() {
    Clear();
}

void Textbox::Setup(int l_visible, int l_charSize, int l_width, sf::Vector2f l_screenPos) {
    m_numVisible = l_visible;
    sf::Vector2f l_offset{2.0f, 2.0f};
    
    m_font.loadFromFile("resources/fonts/fallout.ttf");
    
    m_text.setFont(m_font);
    m_text.setString("");
    m_text.setCharacterSize(l_charSize);
    m_text.setColor(sf::Color::Green);
    m_text.setPosition(l_screenPos + l_offset);
    
    m_backDrop.setSize(sf::Vector2f{l_width, (l_visible * (l_charSize * 1.2))});
    m_backDrop.setFillColor(sf::Color{90, 90, 90, 90});
    m_backDrop.setPosition(l_screenPos);
}

void Textbox::Add(std::string l_message) {
    m_messages.push_back(l_message);
    if(m_messages.size() < 6) {
        return;
    }
    m_messages.erase(m_messages.begin());
}

void Textbox::Clear() {
    m_messages.clear();
}

void Textbox::Render(sf::RenderWindow& l_wind) {
    std::string l_content;
    
    for(auto& itr : m_messages) {
        l_content.append(itr + "\n");
    }
    
    if(l_content != "") {
        m_text.setString(l_content);
        l_wind.draw(m_backDrop);
        l_wind.draw(m_text);
    }
}
