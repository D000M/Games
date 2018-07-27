/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Window.cpp
 * Author: DooM
 * 
 * Created on July 26, 2018, 7:49 PM
 */

#include <SFML/Window/Event.hpp>

#include "Window.h"

Window::Window() {
    setupWindow("Default", sf::Vector2u{1280, 720});
}

Window::Window(const std::string& title, const sf::Vector2u& size) {
    setupWindow(title, size);
}

Window::~Window() {
    m_renderWindow.close();
}

void Window::setupWindow(const std::string& title, const sf::Vector2u& size) {
    
    m_windowTitle = title;
    m_windowSize = size;
    m_isFullScreen = false;
    m_isClosed = false;
    m_isFocused = true;
    
    m_eventManager.addCallback(StateType(0), "Fullscreen_toggle", &Window::toggleFullScreen, this);
    m_eventManager.addCallback(StateType(0), "Window_close", &Window::closeWindow, this);

    createWindow();
}

void Window::createWindow() {
    
    sf::Uint32 style = sf::Style::Default;
    
    if(m_isFullScreen) {
        style = sf::Style::Fullscreen;
    }
    
    m_renderWindow.create(sf::VideoMode{m_windowSize.x, m_windowSize.y, 32}, m_windowTitle, style);
            
}

void Window::clearWindow() {
    
    m_renderWindow.clear(sf::Color::Black);
    
}

void Window::drawWindow() {
    
    m_renderWindow.display();
    
}

bool Window::isClosed() const {
    return m_isClosed;
}

bool Window::isFocused() const {
    return m_isFocused;
}

bool Window::isFullScreen() const {
    return m_isFullScreen;
}

sf::RenderWindow* Window::getRenderWindow(){
    return &m_renderWindow;
}

EventManager* Window::getEventManager() {
    return &m_eventManager;
}

void Window::toggleFullScreen(EventDetails* details) {
    m_isFullScreen = !m_isFullScreen;
    m_renderWindow.close();
    createWindow();
}

void Window::closeWindow(EventDetails* details) {
    m_isClosed = true;
}

sf::Vector2u Window::getWindowSize() const {
    return m_windowSize;
}

void Window::update() {
    
    sf::Event event;
    
    while(m_renderWindow.pollEvent(event)) {
        if(event.type == sf::Event::LostFocus) {
            m_isFocused = false;
            m_eventManager.setFocus(false);
        }
        else if(event.type == sf::Event::GainedFocus) {
            m_isFocused = true;
            m_eventManager.setFocus(true);
        }
        m_eventManager.handleEvent(event);
    }
    
    m_eventManager.update();
}

