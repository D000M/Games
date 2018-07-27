/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   StateGame.h
 * Author: default
 *
 * Created on July 27, 2018, 3:16 PM
 */

#ifndef STATEGAME_H
#define STATEGAME_H

#include "../BaseState.h"
#include "../../engine/EventManager.h"

class StateGame : public BaseState {
public:
    StateGame(StateManager* stateMgr);
    virtual ~StateGame();
    
    void onCreate() override;
    void onDestroy() override;

    void activate() override;
    void deactivate() override;
    
    void draw() override;
    void update(sf::Time& time) override;
    
    void returnToIntro(EventDetails* details);
private:

};

#endif /* STATEGAME_H */

