/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   StateManager.h
 * Author: default
 *
 * Created on July 27, 2018, 1:31 PM
 */

#ifndef STATEMANAGER_H
#define STATEMANAGER_H

#include <vector>
#include <functional>

#include "BaseState.h"
#include "../SharedContext.h"

enum class StateType {
    INTRO = 1,
    MAIN_MENU,
    GAME,
    PAUSED,
    GAMEOVER,
    CREDITS
};

using StateContainer = std::vector<std::pair<StateType, BaseState*>>;

using TypeContainer = std::vector<StateType>;

using StateFactory = std::map<StateType, std::function<BaseState*(void)>>;


class StateManager {
public:
    StateManager(SharedContext* shared);
    virtual ~StateManager();
    
    void update(sf::Time& time);
    void draw();
    
    void processRequests();
    
    SharedContext* getContext();
    bool hasState(const StateType& type);
    
    void switchTo(const StateType& type);
    void remove(const StateType& type);
    
private:

    //Methods
    void createState(const StateType& type);
    void removeState(const StateType& type);
    
    template<class T>
    void registerState(const StateType& type) {
        m_stateFactory[type] = [this]() -> BaseState* {
            return new T(this);
        };
    }
    
    //Members
    SharedContext* m_sharedContext;
    StateContainer m_states;
    TypeContainer m_stateToRemove;
    StateFactory m_stateFactory;
};

#endif /* STATEMANAGER_H */

