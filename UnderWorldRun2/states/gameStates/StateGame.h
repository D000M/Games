/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   StateGame.h
 * Author: DooM
 *
 * Created on July 28, 2018, 8:46 PM
 */

#ifndef STATEGAME_H
#define STATEGAME_H

#include "../BaseState.h"
#include "../../engine/EventManager.h"
#include "../../world/Map.h"

class StateGame : public BaseState {
public:
    StateGame(StateManager* l_stateManager);
    ~StateGame();

    void onCreate();
    void onDestroy();

    void activate();
    void deactivate();

    void update(const sf::Time& l_time);
    void draw();

    void mainMenu(EventDetails* l_details);
    void pause(EventDetails* l_details);
private:
//    sf::Texture m_texture;
//    sf::Sprite m_sprite;
//    sf::Vector2f m_increment;
    Map myMap;
    sf::Text m_text;
    sf::Font m_font;
};

#endif /* STATEGAME_H */

