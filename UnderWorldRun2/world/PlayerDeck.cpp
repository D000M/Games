/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   PlayerDeck.cpp
 * Author: default
 * 
 * Created on August 14, 2018, 2:59 PM
 */

#include <algorithm>
#include <SFML/Graphics/RenderTarget.hpp>

#include "PlayerDeck.h"

PlayerDeck::PlayerDeck() {
    m_font.loadFromFile("resources/fonts/fallout.ttf");
    m_text.setFont(m_font);
    m_text.setCharacterSize(22);
    m_text.setString("Items: ");
    m_text.setFillColor(sf::Color::Green);
    m_text.setPosition(50, 650);
    m_strItems = "Items: ";
}

PlayerDeck::~PlayerDeck() {
}

void PlayerDeck::addItem(Item& temp) {
    m_items.push_back(temp);
    m_strItems += temp.getItemName() + " ";
}

//Item PlayerDeck::removeItem(Item obj) {
//    auto elem = std::find(m_items.begin(), m_items.end(), obj);
//    Item temp = m_items.at(elem);
//    m_items.erase(elem);
//    
//    return temp;
//}

void PlayerDeck::printDeck(){
    for(int i = 0; i < m_items.size(); ++i) {
        m_items.at(i).printItem();
    }
    m_text.setString(m_strItems);
}

int PlayerDeck::getDeckSize() const {
    return m_items.size();
}

void PlayerDeck::draw(SharedContext* context) {
    for(int i = 0; i < m_items.size(); ++i) {
        context->m_wind->getRenderWindow()->draw(m_text);
    }
}
