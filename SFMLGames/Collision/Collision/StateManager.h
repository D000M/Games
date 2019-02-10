/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   StateManager.h
 * Author: DooM
 *
 * Created on January 26, 2019, 12:03 PM
 */

#ifndef STATEMANAGER_H
#define STATEMANAGER_H

#include <vector>
#include <map>
#include <functional>
#include "State_Intro.h"
#include "State_MainMenu.h"
#include "State_Game.h"
#include "State_Paused.h"
#include "SharedContext.h"


enum class StateType {
    Intro = 1, MainMenu, Game, Paused, GameOver, Credits
};

using StateContainer = std::vector<std::pair<StateType, BaseState*>>;

using TypeContainer = std::vector<StateType>;

using StateFactory = std::map<StateType, std::function<BaseState*(void)>>;

class StateManager {
public:
    StateManager(SharedContext* l_shared);
    ~StateManager();
    
    void Update(const sf::Time& l_time);
    void Draw();
    
    void ProcessRequests();
    
    SharedContext* GetContext();
    bool HasState(const StateType& l_type);
    
    void SwitchTo(const StateType& l_type);
    void Remove(const StateType& l_type);
    
private:
    //Methods
    void CreateState(const StateType& l_type);
    void RemoveState(const StateType& l_type);
    
    template<class T>
    void RegisterState(const StateType& l_type) {
        m_stateFactory[l_type] = [this]() -> BaseState* {
            return new T(this);
        };
    }
    
    SharedContext* m_shared;
    StateContainer m_states;
    TypeContainer m_toRemove;
    StateFactory m_stateFactory;
};

#endif /* STATEMANAGER_H */

