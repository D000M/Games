/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   State_MainMenu.h
 * Author: DooM
 *
 * Created on January 26, 2019, 1:19 PM
 */

#ifndef STATE_MAINMENU_H
#define STATE_MAINMENU_H

#include "BaseState.h"
#include "EventManager.h"


class State_MainMenu : public BaseState{
public:
    State_MainMenu(StateManager* l_state);
    virtual ~State_MainMenu();
    void Acitvate() override;
    void Deactivate() override;
    
    void OnCreate() override;
    void OnDestroy() override;
    
    void Draw() override;
    void Update(const sf::Time& l_time) override;
    
    void MouseClick(EventDetails* l_details);

private:
    sf::Font m_font;
    sf::Text m_text;
    
    sf::Vector2f m_buttonSize;
    sf::Vector2f m_buttonPos;
    unsigned int m_buttonPadding;
    
    sf::RectangleShape m_rects[3];
    sf::Text m_labels[3];
};

#endif /* STATE_MAINMENU_H */

