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

class StateGame : public BaseState {
public:
    StateGame(StateManager* l_stateManager);
    ~StateGame();

    void OnCreate();
    void OnDestroy();

    void Activate();
    void Deactivate();

    void Update(const sf::Time& l_time);
    void Draw();

    void MainMenu(EventDetails* l_details);
    void Pause(EventDetails* l_details);
private:
    sf::Texture m_texture;
    sf::Sprite m_sprite;
    sf::Vector2f m_increment;
};

#endif /* STATEGAME_H */

