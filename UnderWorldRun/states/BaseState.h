/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   BaseState.h
 * Author: default
 *
 * Created on July 27, 2018, 11:59 AM
 */

#ifndef BASESTATE_H
#define BASESTATE_H

#include <SFML/Graphics/View.hpp>
#include <SFML/System/Time.hpp>


class StateManager;

class BaseState {
    friend class StateManager;
public:
    BaseState(StateManager* stateMgr) 
        : m_stateManager{nullptr}, 
          m_transparent{false},
          m_transcendent{false} {}
          
    virtual ~BaseState() {}
    
    virtual void onCreate() = 0;
    virtual void onDestroy() = 0;
    
    virtual void activate() = 0;
    virtual void deactivate() = 0;
    
    virtual void update(sf::Time& time) = 0;
    virtual void draw() = 0;
    
    void setTransparent(const bool& transparent) {
        m_transparent = transparent;
    }
    bool isTransparent() const {
        return m_transparent;
    }
    void setTranscendent(const bool& transcendent) {
        m_transcendent = transcendent;
    }
    bool isTranscendent() const {
        return m_transcendent;
    }
    
    sf::View& getView() {
        return m_view;
    }
protected:
    StateManager* m_stateManager;
    bool m_transparent;
    bool m_transcendent;
    sf::View m_view;
};

#endif /* BASESTATE_H */

