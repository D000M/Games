/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   State_Game.h
 * Author: DooM
 *
 * Created on January 26, 2019, 1:20 PM
 */

#ifndef STATE_GAME_H
#define STATE_GAME_H

#include "BaseState.h"
#include "EventManager.h"


class State_Game : public BaseState {
public:
    State_Game(StateManager* l_state);
    virtual ~State_Game();
    
    void OnCreate() override;
    void OnDestroy() override;

    void Acitvate() override;
    void Deactivate() override;

    void Draw() override;
    void Update(const sf::Time& l_time) override;

    void MainMenu(EventDetails* l_details);
    void Pause(EventDetails* l_details);
private:
    sf::Texture m_texture;
    sf::Sprite m_sprite;
    sf::Vector2f m_increment;
};

#endif /* STATE_GAME_H */

