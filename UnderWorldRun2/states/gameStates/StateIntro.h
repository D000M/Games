/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   StateIntro.h
 * Author: DooM
 *
 * Created on July 28, 2018, 8:46 PM
 */

#ifndef STATEINTRO_H
#define STATEINTRO_H

#include "../BaseState.h"
#include "../../engine/EventManager.h"

class StateIntro : public BaseState {
public:
    StateIntro(StateManager* l_stateManager);
    ~StateIntro();

    void onCreate();
    void onDestroy();

    void activate();
    void deactivate();

    void update(const sf::Time& l_time);
    void draw();

    void continueToGame(EventDetails* l_details);
private:
    sf::Texture m_introTexture;
    sf::Sprite m_introSprite;
    sf::Font m_font;
    sf::Text m_text;

    float m_timePassed;
};

#endif /* STATEINTRO_H */

