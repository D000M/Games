/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   EventManager.h
 * Author: DooM
 *
 * Created on July 28, 2018, 8:41 PM
 */

#ifndef EVENTMANAGER_H
#define EVENTMANAGER_H

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <vector>
#include <map>
#include <functional>
#include <fstream>
#include <sstream>
#include <iostream>

enum class EventType {
    KEYDOWN = sf::Event::KeyPressed,
    KEYUP = sf::Event::KeyReleased,
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

    EventInfo(int l_event) {
        m_code = l_event;
    }

    union {
        int m_code;
    };
};

struct EventDetails {

    EventDetails(const std::string& l_bindName)
    : m_name(l_bindName) {
        clear();
    }
    std::string m_name;

    sf::Vector2i m_size;
    sf::Uint32 m_textEntered;
    sf::Vector2i m_mouse;
    int m_mouseWheelDelta;
    int m_keyCode; // Single key code.

    void clear() {
        m_size = sf::Vector2i(0, 0);
        m_textEntered = 0;
        m_mouse = sf::Vector2i(0, 0);
        m_mouseWheelDelta = 0;
        m_keyCode = -1;
    }
};

using Events = std::vector<std::pair<EventType, EventInfo>>;

struct Binding {

    Binding(const std::string& l_name) : m_name(l_name), m_details(l_name), c(0) {
    }

    ~Binding() {
    }

    void BindEvent(EventType l_type, EventInfo l_info = EventInfo()) {
        m_events.emplace_back(l_type, l_info);
    }

    Events m_events;
    std::string m_name;
    int c; // Count of events that are "happening".

    EventDetails m_details;
};

using Bindings = std::map<std::string, Binding*>;
// Callback container.
using CallbackContainer = std::map<std::string, std::function<void(EventDetails*)>>;
// State callback container.
enum class StateType;
using Callbacks = std::map<StateType, CallbackContainer>;

class EventManager {
public:
    EventManager();
    ~EventManager();

    bool addBinding(Binding *l_binding);
    bool removeBinding(std::string l_name);

    void setCurrentState(StateType l_state);
    void setFocus(const bool& l_focus);

    // Needs to be defined in the header!

    template<class T>
    bool addCallback(StateType l_state, const std::string& l_name,
            void(T::*l_func)(EventDetails*), T* l_instance) {
        auto itr = m_callbacks.emplace(l_state, CallbackContainer()).first;
        auto temp = std::bind(l_func, l_instance, std::placeholders::_1);
        return itr->second.emplace(l_name, temp).second;
    }

    bool removeCallback(StateType l_state, const std::string& l_name) {
        auto itr = m_callbacks.find(l_state);
        if (itr == m_callbacks.end()) {
            return false;
        }
        auto itr2 = itr->second.find(l_name);
        if (itr2 == itr->second.end()) {
            return false;
        }
        itr->second.erase(l_name);
        return true;
    }

    void handleEvent(sf::Event& l_event);
    void update();

    // Getters.

    sf::Vector2i getMousePos(sf::RenderWindow* l_wind = nullptr) {
        return (l_wind ? sf::Mouse::getPosition(*l_wind) : sf::Mouse::getPosition());
    }
private:
    void loadBindings();

    StateType m_currentState;
    Bindings m_bindings;
    Callbacks m_callbacks;

    bool m_hasFocus;
};

#endif /* EVENTMANAGER_H */

