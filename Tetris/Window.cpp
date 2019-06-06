/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Window.cpp
 * Author: default
 * 
 * Created on June 4, 2019, 12:42 PM
 */

#include <SFML/Window/Event.hpp>

#include "Window.h"

Window::Window() {
    setupWindow(sf::Vector2u{640, 480}, "Tetris");
}

Window::Window(const sf::Vector2u& lSize, const sf::String& title) {
    setupWindow(lSize, title);
}

Window::~Window() {
    destroyWindow();
}

bool Window::isWindowOpen() const {
    return mIsDone;
}

void Window::setupWindow(const sf::Vector2u& lSize, const sf::String& title) {
    mMainWindowSize = lSize;
    mWindowTitle = title;
    mIsDone = true;
    createWindow();
}

void Window::createWindow() {
    mMainWindow.create({mMainWindowSize.x, mMainWindowSize.y, 32}, mWindowTitle);
}

void Window::destroyWindow() {
    mMainWindow.close();
}

void Window::clearWindow() {
    mMainWindow.clear();
}

void Window::beginDraw() {
    mMainWindow.clear(sf::Color{192,192,192});
}

void Window::endDraw() {
    mMainWindow.display();
}

sf::Vector2u Window::getMainWindowSize() const {
    return mMainWindowSize;
}

void Window::draw(sf::Drawable& lDrawable) {
    mMainWindow.draw(lDrawable);
}

sf::RenderWindow* Window::getRenderWindow() {
    return &mMainWindow;
}

void Window::update() {
    sf::Event event;
    
    while(mMainWindow.pollEvent(event)) {
        if(event.type == sf::Event::Closed) {
            mIsDone = false;
        }
    }
}


