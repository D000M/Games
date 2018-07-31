/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   SharedContext.h
 * Author: DooM
 *
 * Created on July 28, 2018, 8:46 PM
 */

#ifndef SHAREDCONTEXT_H
#define SHAREDCONTEXT_H

#include "engine/Window.h"
#include "engine/EventManager.h"

class Map;

struct SharedContext {

    SharedContext()
        : m_wind(nullptr),
          m_eventManager(nullptr),
          m_gameMap{nullptr}{
    }
    Window* m_wind;
    EventManager* m_eventManager;
    Map* m_gameMap;
};

#endif /* SHAREDCONTEXT_H */

