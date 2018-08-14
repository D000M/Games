/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   PlayerDeck.h
 * Author: default
 *
 * Created on August 14, 2018, 2:59 PM
 */

#ifndef PLAYERDECK_H
#define PLAYERDECK_H

#include <vector>
#include <SFML/Graphics/Text.hpp>
#include "../SharedContext.h"
#include "Item.h"

class PlayerDeck {
public:
    PlayerDeck();
    virtual ~PlayerDeck();
    
    void addItem(Item& temp);
    Item removeItem(Item obj);
    
    void printDeck();
    int getDeckSize() const;
    
    void draw(SharedContext* context);
private:
    std::vector<Item> m_items; 
    
    sf::Text m_text;
    sf::Font m_font;
    
    std::string m_strItems;
};

#endif /* PLAYERDECK_H */

