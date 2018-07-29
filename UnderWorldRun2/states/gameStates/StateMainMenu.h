/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   StateMainMenu.h
 * Author: DooM
 *
 * Created on July 28, 2018, 8:46 PM
 */

#ifndef STATEMAINMENU_H
#define STATEMAINMENU_H

#include "../BaseState.h"
#include "../../engine/EventManager.h"

class StateMainMenu : public BaseState {
public:
    StateMainMenu(StateManager* l_stateManager);
    ~StateMainMenu();

    void onCreate();
    void onDestroy();

    void activate();
    void deactivate();

    void update(const sf::Time& l_time);
    void draw();

    void mouseClick(EventDetails* l_details);
private:
    sf::Font m_font;
    sf::Text m_text;

    sf::Vector2f m_buttonSize;
    sf::Vector2f m_buttonPos;
    unsigned int m_buttonPadding;

    sf::RectangleShape m_rects[3];
    sf::Text m_labels[3];
};

#endif /* STATEMAINMENU_H */

