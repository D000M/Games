/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   SharedContext.h
 * Author: DooM
 *
 * Created on January 26, 2019, 12:01 PM
 */

#ifndef SHAREDCONTEXT_H
#define SHAREDCONTEXT_H

#include "Window.h"


struct SharedContext {
    SharedContext() 
        : m_wind{nullptr},
          m_eventManager{nullptr}{}
    
    Window* m_wind;
    EventManager* m_eventManager;
};

#endif /* SHAREDCONTEXT_H */

