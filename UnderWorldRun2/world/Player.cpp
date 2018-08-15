/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Player.cpp
 * Author: default
 * 
 * Created on July 31, 2018, 2:17 PM
 */

#include "Player.h"
#include "../states/StateManager.h"
#include "../utils/RNGGenerator.h"

const std::string playerName[] = {
    "Player1",
    "Player2",
    "Player3"
};
const sf::Color playerColor[] = {
    sf::Color::Red,
    sf::Color::Blue,
    sf::Color::Yellow
};
const float playerXPos[] = {
    503,
    553,
    603
};
Player::Player(SharedContext* shared, int id) 
    : m_shared{shared},
      m_playDeck{id},
      m_playerID{id}{
    
    m_playerFig.setFillColor(playerColor[m_playerID]);
    m_playerFig.setPosition(sf::Vector2f{140, playerXPos[m_playerID]});
    m_playerFig.setRadius(12);
    
    m_font.loadFromFile("resources/fonts/arial.ttf");
    m_text.setFont(m_font);
    m_text.setCharacterSize(22);
    m_text.setString(playerName[m_playerID]);
    m_text.setFillColor(playerColor[m_playerID]);
    m_text.setPosition(sf::Vector2f{50, playerXPos[m_playerID] - 3});
    
    m_diceText.setFont(m_font);
    m_diceText.setCharacterSize(22);
    m_diceText.setString("Roll: ");
    m_diceText.setFillColor(sf::Color::White);
    m_diceText.setPosition(sf::Vector2f{180, playerXPos[m_playerID] - 3});

    m_shared->m_eventManager->addCallback(StateType::GAME, "Key_R", &Player::rollDice, this);
}

Player::~Player() {
    m_shared->m_eventManager->removeCallback(StateType::GAME, "Key_R");
}

void Player::draw() {
    m_shared->m_wind->getRenderWindow()->draw(m_text);
    m_shared->m_wind->getRenderWindow()->draw(m_playerFig);
    m_shared->m_wind->getRenderWindow()->draw(m_diceText);
    m_playDeck.draw(m_shared);
}

void Player::update() {
    m_diceText.setString("Roll: " + std::to_string(m_dice.getDice()));
}

void Player::rollDice(EventDetails* details) {
    int result = getRandomInteger(1, 6);
    m_dice.setDice(result);
}

void Player::setDeck(Item& obj) {
    m_playDeck.addItem(obj);
}

void Player::printDeck() {
    m_playDeck.printDeck();
}
