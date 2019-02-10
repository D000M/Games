/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   State_Paused.cpp
 * Author: DooM
 * 
 * Created on January 26, 2019, 1:20 PM
 */

#include "State_Paused.h"
#include "StateManager.h"

State_Paused::State_Paused(StateManager* l_state) 
    : BaseState(l_state) {
}

State_Paused::~State_Paused() {
}

void State_Paused::OnCreate() {
    SetTransparent(true);   //Set our transparency flag.
    m_font.loadFromFile("arial.ttf");
    m_text.setFont(m_font);
    m_text.setString(sf::String("GAME PAUSED"));
    m_text.setCharacterSize(14);
    m_text.setStyle(sf::Text::Bold);
    
    sf::Vector2u windowSize = m_stateMgr->GetContext()->m_wind->GetRenderWindow()->getSize();
    
    sf::FloatRect textRect = m_text.getLocalBounds();
    m_text.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
    m_text.setPosition(windowSize.x / 2.0f, windowSize.y / 2.0f);
    
    m_rect.setSize(sf::Vector2f{windowSize});
    m_rect.setPosition(0, 0);
    m_rect.setFillColor(sf::Color(0, 0, 0, 150));
    
    m_stateMgr->GetContext()->m_eventManager->AddCallback(StateType::Paused, "Key_P", &State_Paused::Unpause, this);
}

void State_Paused::OnDestroy() {
    m_stateMgr->GetContext()->m_eventManager->RemoveCallback(StateType::Paused, "Key_P");
}

void State_Paused::Acitvate() {

}

void State_Paused::Deactivate() {

}

void State_Paused::Draw() {
    m_stateMgr->GetContext()->m_wind->GetRenderWindow()->draw(m_rect);
    m_stateMgr->GetContext()->m_wind->GetRenderWindow()->draw(m_text);
}

void State_Paused::Update(const sf::Time& l_time) {
    
}

void State_Paused::Unpause(EventDetails* l_details) {
    m_stateMgr->SwitchTo(StateType::Game);
}
