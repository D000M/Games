/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   StateManager.cpp
 * Author: default
 * 
 * Created on July 27, 2018, 1:31 PM
 */

#include <SFML/Graphics/RenderTarget.hpp>
#include <algorithm>
#include <map>

#include "StateManager.h"
#include "gameStates/StateGame.h"
#include "gameStates/StateIntro.h"

StateManager::StateManager(SharedContext* shared) 
    : m_sharedContext{shared} {
    //Register State here
    //!example
//    registerState<StateNameClass>(StateType::Type);
    registerState<StateIntro>(StateType::INTRO);
    registerState<StateGame>(StateType::GAME);
}

StateManager::~StateManager() {
    for(auto& it : m_states) {
        it.second->onDestroy();
        delete it.second;
    }
}

void StateManager::draw() {
    if(m_states.empty()) {
        return;
    }
    
    if(m_states.back().second->isTransparent() && m_states.size() > 1) {
        auto it = m_states.end();
        
        while(it != m_states.begin()) {
            
            if(it != m_states.end()) {
                
                if(!it->second->isTransparent()) {
                    break;
                }
                
            }
            
            --it;
            
        }
        
        for(; it != m_states.end(); ++it) {
            m_sharedContext->m_gameWindow->getRenderWindow()->setView(it->second->getView());
            it->second->draw();
        }
        
    }
    else {
        m_states.back().second->draw();
    }
    
}   //End Method draw();

void StateManager::update(sf::Time& time) {
    
    if(m_states.empty()) {
        return;
    }
    
    if(m_states.back().second->isTranscendent() && m_states.size() > 1) {
        
        auto it = m_states.end();
        while(it != m_states.begin()) {
            if(it != m_states.end()) {
                if(!it->second->isTranscendent()) {
                    break;
                }
            }
            --it;
        }
        for(; it != m_states.end(); ++it) {
            it->second->update(time);
        }
        
    }
    else {
        m_states.back().second->update(time);
    }
    
}   //End update

SharedContext* StateManager::getContext() {
    return m_sharedContext;
}

bool StateManager::hasState(const StateType& type) {
    
    for(auto it = m_states.begin(); it != m_states.end(); ++it) {
        if(it->first == type) {  
            auto removed = std::find(m_stateToRemove.begin(), m_stateToRemove.end(), type);
            if(removed == m_stateToRemove.end()) {  
                return true; 
            }
            return false;
        }
        return false;
    }
    return false;   
}

void StateManager::remove(const StateType& type) {
    m_stateToRemove.push_back(type);
}

void StateManager::processRequests() {
    while(m_stateToRemove.begin() != m_stateToRemove.end()) {
        removeState(*m_stateToRemove.begin());
        m_stateToRemove.erase(m_stateToRemove.begin());
    }
}

void StateManager::switchTo(const StateType& type) {
    
    std::cout << "QQQQQQQQQ\n";
    m_sharedContext->m_eventManager->setCurrentState(type);
    
    for(auto it = m_states.begin(); it != m_states.end(); ++it) {
        if(it->first == type) {
            m_states.back().second->deactivate();
            
            StateType tmpType = it->first;
            BaseState* tmpState = it->second;
            m_states.erase(it);
            m_states.emplace_back(tmpType, tmpState);
            tmpState->activate();
            
            m_sharedContext->m_gameWindow->getRenderWindow()->setView(tmpState->getView());
            
            return;
        }
    }
    std::cout << "YYYYYYYY\n";
    //The state type not found
    if(!m_states.empty()) {
        m_states.back().second->deactivate();
    }
    createState(type);
    m_states.back().second->activate();
    
    m_sharedContext->m_gameWindow->getRenderWindow()->setView(m_states.back().second->getView());
}

void StateManager::createState(const StateType& type) {
        
    std::cout << "UUUUUUUU\n";
    auto newState = m_stateFactory.find(type);
    
    if(newState == m_stateFactory.end()) {
        return;
    }
    
    BaseState* state = newState->second();
    
    state->m_view = m_sharedContext->m_gameWindow->getRenderWindow()->getDefaultView();
    std::cout << "WWWWWW\n";
    m_states.emplace_back(type, state);
    state->onCreate();
    
}

void StateManager::removeState(const StateType& type) {
    
    for(auto it = m_states.begin(); it != m_states.end(); ++it) {
        if(it->first == type) {
            it->second->onDestroy();
            delete it->second;
            m_states.erase(it);
            return;
        }
    }
    
}
