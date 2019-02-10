/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   State_Paused.h
 * Author: DooM
 *
 * Created on January 26, 2019, 1:20 PM
 */

#ifndef STATE_PAUSED_H
#define STATE_PAUSED_H

#include "BaseState.h"
#include "EventManager.h"

class State_Paused : public BaseState {
public:
    State_Paused(StateManager* l_state);
    virtual ~State_Paused();
    void OnCreate() override;
    void OnDestroy() override;
    
    void Acitvate() override;
    void Deactivate() override;

    void Draw() override;
    void Update(const sf::Time& l_time) override;

    void Unpause(EventDetails* l_details);
    
private:
    sf::Font m_font;
    sf::Text m_text;
    sf::RectangleShape m_rect;
};

#endif /* STATE_PAUSED_H */

