/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   EventManager.cpp
 * Author: DooM
 * 
 * Created on July 26, 2018, 8:37 PM
 */
#include <cstring>
#include <fstream>
#include <iostream>
#include <sstream>
#include "EventManager.h"

EventManager::EventManager() 
    : m_currentState{StateType(0)},
      m_hasFocus{true} {
        loadBindings();
}

EventManager::~EventManager() {
    for(auto& it : m_bindings) {
        delete it.second;
    }
}

bool EventManager::addBinding(Binding* binding) {
    if(m_bindings.find(binding->m_name) != m_bindings.end()) {
        return false;
    }
    
    return m_bindings.emplace(binding->m_name, binding).second;
}

bool EventManager::removeBinding(std::string name) {
    auto it = m_bindings.find(name);
    if(it == m_bindings.end()) {
        return false;
    }
    delete it->second;
    m_bindings.erase(it);
    return true;
}

void EventManager::setCurrentState(StateType state) {
    m_currentState = state;
}

void EventManager::setFocus(bool focus) {
    m_hasFocus = focus;
}

void EventManager::handleEvent(sf::Event& event) {
    //Handling SFML events.
    for(auto& b_itr : m_bindings) {
        Binding* bind = b_itr.second;
        for(auto& e_itr : bind->m_events) {
            EventType sfmlEvent = (EventType)event.type;
            if(e_itr.first != sfmlEvent) {
                continue;
            }
            if(sfmlEvent == EventType::KEY_DOWN || sfmlEvent == EventType::KEY_UP) {
                if(e_itr.second.m_code == event.key.code) {
                    // Matching event/keystroke.
                    // Increase count.
                    if(bind->m_details.m_keyCode != -1) {
                        bind->m_details.m_keyCode = e_itr.second.m_code;
                    }
                    ++(bind->c);
                    break;
                }
            }
            else if(sfmlEvent == EventType::MOUSE_DOWN || sfmlEvent == EventType::MOUSE_UP) {
                if(e_itr.second.m_code == event.mouseButton.button) {
                    // Matching event/keystroke.
                    // Increase count.
                    bind->m_details.m_mouse.x = event.mouseButton.x;
                    bind->m_details.m_mouse.y = event.mouseButton.y;
                    if(bind->m_details.m_keyCode != -1) {
                        bind->m_details.m_keyCode = e_itr.second.m_code;
                    }
                    ++(bind->c);
                    break;
                }
            }
            else {
                // No need for additional checking.
                if(sfmlEvent == EventType::MOUSE_WHEEL) {
                    bind->m_details.m_mouseWheelDelta = event.mouseWheel.delta;
                }
                else if(sfmlEvent == EventType::WINDOW_RESIZED) {
                    bind->m_details.m_size.x = event.size.width;
                    bind->m_details.m_size.y = event.size.height;
                }
                else if(sfmlEvent == EventType::TEXT_ENTERED) {
                    bind->m_details.m_textEntered = event.text.unicode;
                }
                ++(bind->c);
            }
        }
    }
}

void EventManager::update() {
    if(!m_hasFocus) {
        return;
    }
    for(auto& b_itr : m_bindings) {
        Binding* bind = b_itr.second;
        for(auto& e_itr : bind->m_events) {
            switch(e_itr.first) {
                case (EventType::KEYBOARD):
                    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key(e_itr.second.m_code))) {
                        if(bind->m_details.m_keyCode != -1) {
                            bind->m_details.m_keyCode = e_itr.second.m_code;
                        }\
                        ++(bind->c);
                    }
                    break;
                case (EventType::MOUSE):
                    if(sf::Mouse::isButtonPressed(sf::Mouse::Button(e_itr.second.m_code))) {
                        if(bind->m_details.m_keyCode != -1) {
                            bind->m_details.m_keyCode = e_itr.second.m_code;
                        }
                        ++(bind->c);
                    }
                    break;
                case (EventType::JOYSTICK):
                    //Up for expansion
                    break;
            }
        }
        
        if(bind->m_events.size() == bind->c) {
            auto stateCallbacks = m_callbacks.find(m_currentState);
            auto otherCallbacks = m_callbacks.find(StateType(0));
            
            if(stateCallbacks != m_callbacks.end()) {
                auto callItr = stateCallbacks->second.find(bind->m_name);
                if(callItr != stateCallbacks->second.end()) {
                    //Pass in information about the events.
                    callItr->second(&bind->m_details);
                }
            }
            
            if(otherCallbacks != m_callbacks.end()) {
                auto callItr = otherCallbacks->second.find(bind->m_name);
                if(callItr != otherCallbacks->second.end()) {
                    //Pass in information about the events.
                    callItr->second(&bind->m_details);
                }
            }
        }
        bind->c = 0;
        bind->m_details.clear();
    }
}

void EventManager::loadBindings() {
    std::string delimiter = ":";
    
    std::ifstream bindings;
    bindings.open("configs/keys.cfg");
    if(!bindings.is_open()) {
        std::cout << "! Failed to loading configs/keys.cfg" << std::endl;
        return;
    }
    std::string line;
    while(std::getline(bindings, line)) {
        std::stringstream keystream{line};
        std::string callbackName;
        keystream >> callbackName;
        Binding* bind = new Binding(callbackName);
        while(!keystream.eof()) {
            std::string keyval;
            keystream >> keyval;
            int start = 0;
            int end = keyval.find(delimiter);
            if(end == std::string::npos) {
                delete bind;
                bind = nullptr;
                break;
            }
            
            EventType type = EventType(stoi(keyval.substr(start, end - start)));
            
            EventInfo eventInfo;
            int code = stoi(keyval.substr(end + delimiter.length(),
                    keyval.find(delimiter, end + delimiter.length())));
            eventInfo.m_code = code;
            
            bind->bindEvent(type, eventInfo);
        }
        if(!addBinding(bind)) {
            delete bind;
        }
        bind = nullptr;
    }
    bindings.close();
}

