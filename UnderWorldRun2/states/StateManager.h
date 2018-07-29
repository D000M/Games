/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   StateManager.h
 * Author: DooM
 *
 * Created on July 28, 2018, 8:44 PM
 */

#ifndef STATEMANAGER_H
#define STATEMANAGER_H

#include <vector>
#include <map>
#include "gameStates/StateIntro.h"
#include "gameStates/StateMainMenu.h"
#include "gameStates/StateGame.h"
#include "gameStates/StatePaused.h"
#include "../SharedContext.h"

enum class StateType {
    INTRO = 1, 
    MAINMENU, 
    GAME, 
    PAUSED, 
    GAMEOVER, 
    CREDITS
};

// State container.
using StateContainer = std::vector<std::pair<StateType, BaseState*>>;
// Type container.
using TypeContainer = std::vector<StateType>;
// State factory.
using StateFactory = std::map<StateType, std::function<BaseState*(void) >>;

class StateManager {
public:
    StateManager(SharedContext* l_shared);
    ~StateManager();

    void update(const sf::Time& l_time);
    void draw();

    void processRequests();

    SharedContext* getContext();
    bool hasState(const StateType& l_type);

    void switchTo(const StateType& l_type);
    void remove(const StateType& l_type);
private:
    // Methods.
    void createState(const StateType& l_type);
    void removeState(const StateType& l_type);

    template<class T>
    void registerState(const StateType& l_type) {
        m_stateFactory[l_type] = [this]() -> BaseState* {
            return new T(this);
        };
    }

    // Members.
    SharedContext* m_shared;
    StateContainer m_states;
    TypeContainer m_toRemove;
    StateFactory m_stateFactory;
};

#endif /* STATEMANAGER_H */

