/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   StatePaused.h
 * Author: DooM
 *
 * Created on July 28, 2018, 8:46 PM
 */

#ifndef STATEPAUSED_H
#define STATEPAUSED_H

#include "../BaseState.h"
#include "../../engine/EventManager.h"

class StatePaused : public BaseState {
public:
    StatePaused(StateManager* l_stateManager);
    ~StatePaused();

    void OnCreate();
    void OnDestroy();

    void Activate();
    void Deactivate();

    void Update(const sf::Time& l_time);
    void Draw();

    void Unpause(EventDetails* l_details);
private:
    sf::Font m_font;
    sf::Text m_text;
    sf::RectangleShape m_rect;
};

#endif /* STATEPAUSED_H */

