/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   SharedContext.h
 * Author: default
 *
 * Created on July 27, 2018, 11:53 AM
 */

#ifndef SHAREDCONTEXT_H
#define SHAREDCONTEXT_H

#include "engine/Window.h"


struct SharedContext {
    
    SharedContext() 
        : m_gameWindow{nullptr},
          m_eventManager{nullptr} { 
    }
    
    Window* m_gameWindow;
    EventManager* m_eventManager;
};

#endif /* SHAREDCONTEXT_H */

