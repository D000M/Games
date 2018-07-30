/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Window.cpp
 * Author: DooM
 * 
 * Created on July 28, 2018, 8:41 PM
 */

#include "Window.h"

Window::Window() {
    setupWindow("Window", sf::Vector2u(1280, 720));
}

Window::Window(const std::string& title, const sf::Vector2u& size) {
    setupWindow(title, size);
}

Window::~Window() {
    m_gameWindow.close();
}

void Window::setupWindow(const std::string& title, const sf::Vector2u& size) {
    m_windowTitle = title;
    m_windowSize = size;
    m_isFullscreen = false;
    m_isClose = false;
    m_isFocused = true;

    m_eventManager.addCallback(StateType(0), "Fullscreen_toggle", &Window::toggleFullscreen, this);
    m_eventManager.addCallback(StateType(0), "Window_close", &Window::close, this);

    createWindow();
}

void Window::createWindow() {
    sf::Uint32 style = sf::Style::Default;
    if (m_isFullscreen) {
        style = sf::Style::Fullscreen;
    }

    m_gameWindow.create(sf::VideoMode(m_windowSize.x, m_windowSize.y, 32), m_windowTitle, style);
}

void Window::clearWindow() {
    m_gameWindow.clear(sf::Color::Black);
}

void Window::drawWindow() {
    m_gameWindow.display();
}

bool Window::isClosed() {
    return m_isClose;
}

bool Window::isFullscreen() {
    return m_isFullscreen;
}

bool Window::isFocused() {
    return m_isFocused;
}

sf::RenderWindow* Window::getRenderWindow() {
    return &m_gameWindow;
}

EventManager* Window::getEventManager() {
    return &m_eventManager;
}

sf::Vector2u Window::getWindowSize() {
    return m_windowSize;
}

void Window::toggleFullscreen(EventDetails* details) {
    m_isFullscreen = !m_isFullscreen;
    m_gameWindow.close();
    createWindow();
}

void Window::close(EventDetails* details) {
    m_isClose = true;
}

void Window::update() {
    sf::Event event;

    while (m_gameWindow.pollEvent(event)) {
        if (event.type == sf::Event::LostFocus) {
            m_isFocused = false;
            m_eventManager.setFocus(false);
        } else if (event.type == sf::Event::GainedFocus) {
            m_isFocused = true;
            m_eventManager.setFocus(true);
        }
        m_eventManager.handleEvent(event);
    }

    m_eventManager.update();
}
