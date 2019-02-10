/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   State_Intro.h
 * Author: DooM
 *
 * Created on January 26, 2019, 1:18 PM
 */

#ifndef STATE_INTRO_H
#define STATE_INTRO_H

#include "BaseState.h"
#include "EventManager.h"

class State_Intro : public BaseState {
public:
    State_Intro(StateManager* l_state);
    virtual ~State_Intro();
    
    void OnCreate() override;
    void OnDestroy() override;
    
    void Acitvate() override;
    void Deactivate() override;
    
    void Draw() override;
    void Update(const sf::Time& l_time) override;
    
    void Continue(EventDetails* l_details);
    
private:
    sf::Texture m_introTexture;
    sf::Sprite m_sprite;
    sf::Font m_font;
    sf::Text m_text;
    
    float m_timePassed;
};

#endif /* STATE_INTRO_H */

