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

Player::Player(SharedContext* shared) 
    : m_shared{shared} {
    
    m_playerFig.setFillColor(sf::Color::Red);
    m_playerFig.setPosition(sf::Vector2f{140, 603});
    m_playerFig.setRadius(12);
    
    m_font.loadFromFile("resources/fonts/arial.ttf");
    m_text.setFont(m_font);
    m_text.setCharacterSize(22);
    m_text.setString("Player1: ");
    m_text.setFillColor(sf::Color::Red);
    m_text.setPosition(sf::Vector2f{50, 600});
    
    m_diceText.setFont(m_font);
    m_diceText.setCharacterSize(22);
    m_diceText.setString("Roll: ");
    m_diceText.setFillColor(sf::Color::White);
    m_diceText.setPosition(sf::Vector2f{180, 600});
    
    m_shared->m_eventManager->addCallback(StateType::GAME, "Key_R", &Player::rollDice, this);
}

Player::~Player() {
    m_shared->m_eventManager->removeCallback(StateType::GAME, "Key_R");
}

void Player::draw() {
    m_shared->m_wind->getRenderWindow()->draw(m_text);
    m_shared->m_wind->getRenderWindow()->draw(m_playerFig);
    m_shared->m_wind->getRenderWindow()->draw(m_diceText);
}

void Player::update() {
    m_diceText.setString("Roll: " + std::to_string(m_dice.getDice()));
}

void Player::rollDice(EventDetails* details) {
    int result = getRandomInteger(1, 6);
    m_dice.setDice(result);
}
