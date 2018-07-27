/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   EventManager.h
 * Author: default
 *
 * Created on May 10, 2018, 10:16 AM
 */

#ifndef EVENTMANAGER_H
#define EVENTMANAGER_H

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <vector>
#include <unordered_map>
#include <functional>
#include <fstream>
#include <sstream>
#include <iostream>

enum class EventType {
    KEY_DOWN = sf::Event::KeyPressed,
    KEY_UP = sf::Event::KeyReleased,
    M_BUTTON_DOWN = sf::Event::MouseButtonPressed,
    M_BUTTON_UP = sf::Event::MouseButtonReleased,
    MOUSE_WHEEL = sf::Event::MouseWheelMoved,
    WINDOW_RESIZED = sf::Event::Resized,
    GAINED_FOCUS = sf::Event::GainedFocus,
    LOST_FOCUS = sf::Event::LostFocus,
    MOUSE_ENTERED = sf::Event::MouseEntered,
    MOUSE_LEFT = sf::Event::MouseLeft,
    CLOSED = sf::Event::Closed,
    TEXT_ENTERED = sf::Event::TextEntered,
    KEYBOARD = sf::Event::Count + 1, 
    MOUSE, 
    JOYSTICK
};

struct EventInfo {

    EventInfo() {
        m_code = 0;
    }

    EventInfo(int event) {
        m_code = event;
    }

    union {
        int m_code;
    };
};

struct EventDetails {

    EventDetails(const std::string& bindName)
    : m_name(bindName) {
        clearDetails();
    }
    std::string m_name;

    sf::Vector2i m_size;
    sf::Uint32 m_textEntered;
    sf::Vector2i m_mouse;
    int m_mouseWheelDelta;
    int m_keyCode; // Single key code.

    void clearDetails() {
        m_size = sf::Vector2i(0, 0);
        m_textEntered = 0;
        m_mouse = sf::Vector2i(0, 0);
        m_mouseWheelDelta = 0;
        m_keyCode = -1;
    }
};

using Events = std::vector<std::pair<EventType, EventInfo>>;

struct Binding {

    Binding(const std::string& name) 
        : m_name(name), 
          m_details(name), 
          c(0) {
    }

    void bindEvent(EventType type, EventInfo info = EventInfo()) {
        m_events.emplace_back(type, info);
    }

    Events m_events;
    std::string m_name;
    int c; // Count of events that are "happening".

    EventDetails m_details;
};

using Bindings = std::map<std::string, Binding*>;
using CallbackContainer = std::map<std::string, std::function<void(EventDetails*)>>;

enum class StateType;
using Callbacks = std::map<StateType, CallbackContainer>;

class EventManager {
public:
    EventManager();
    ~EventManager();

    bool addBinding(Binding *l_binding);
    bool removeBinding(std::string l_name);

    void setFocus(const bool& l_focus);

    // Needs to be defined in the header!

    template<class T>
    bool addCallback(StateType state, const std::string& name, void(T::*func)(EventDetails*), T* instance) {
        auto it = m_callbacks.emplace(state, CallbackContainer()).first;
        auto temp = std::bind(func, instance, std::placeholders::_1);
        return it->second.emplace(name, temp).second;
    }

    bool removeCallback(StateType state, const std::string& name) {
        auto it = m_callbacks.find(state);
        
        if(it == m_callbacks.end()) {
            return false;
        }
        
        auto it2 = it->second.find(name);
        if(it2 == it->second.end()) {
            return false;
        }
        
        it->second.erase(name);
        return true;
    }

    void handleEvent(sf::Event& event);
    void update();

    sf::Vector2i getMousePos(sf::RenderWindow* wind = nullptr) {
        return (wind ? sf::Mouse::getPosition(*wind) : sf::Mouse::getPosition());
    }

    void setCurrentState(const StateType& type);
private:
    void loadBindings();

    Bindings m_bindings;
    Callbacks m_callbacks;
    StateType m_currentState;
    bool m_hasFocus;
};

#endif /* EVENTMANAGER_H */

