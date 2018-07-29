/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   BaseState.h
 * Author: DooM
 *
 * Created on July 28, 2018, 8:44 PM
 */

#ifndef BASESTATE_H
#define BASESTATE_H

#include <SFML/Graphics.hpp>
class StateManager;

class BaseState {
    friend class StateManager;
public:

    BaseState(StateManager* l_stateManager) : m_stateMgr(l_stateManager),
    m_transparent(false), m_transcendent(false) {
    }

    virtual ~BaseState() {
    }

    virtual void onCreate() = 0;
    virtual void onDestroy() = 0;

    virtual void activate() = 0;
    virtual void deactivate() = 0;

    virtual void update(const sf::Time& l_time) = 0;
    virtual void draw() = 0;

    void setTransparent(const bool& l_transparent) {
        m_transparent = l_transparent;
    }

    bool isTransparent()const {
        return m_transparent;
    }

    void setTranscendent(const bool& l_transcendence) {
        m_transcendent = l_transcendence;
    }

    bool isTranscendent()const {
        return m_transcendent;
    }

    StateManager* getStateManager() {
        return m_stateMgr;
    }
protected:
    StateManager* m_stateMgr;
    bool m_transparent;
    bool m_transcendent;
};

#endif /* BASESTATE_H */

