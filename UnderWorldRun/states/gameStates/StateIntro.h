/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   StateIntro.h
 * Author: default
 *
 * Created on July 27, 2018, 3:16 PM
 */

#ifndef STATEINTRO_H
#define STATEINTRO_H

#include "../BaseState.h"
#include "../../engine/EventManager.h"

class StateIntro : public BaseState {
public:
    StateIntro(StateManager* stateMgr);
    virtual ~StateIntro();
    
    void activate() override;
    void deactivate() override;
    void onCreate() override;
    void onDestroy() override;
    void draw() override;
    void update(sf::Time& time) override;

    //Callbacks
    void continueToGame(EventDetails* details);
private:

    
};

#endif /* STATEINTRO_H */

