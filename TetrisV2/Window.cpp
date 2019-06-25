/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Window.cpp
 * Author: default
 * 
 * Created on June 7, 2019, 2:42 PM
 */

#include <SFML/Window/Event.hpp>

#include "Window.h"

Window::Window() {
    setup("Default Window", sf::Vector2u{640, 480});
}

Window::Window(const std::string& lTitle, const sf::Vector2u& lSize) {
    setup(lTitle, lSize);
}

Window::~Window() {
    destroy();
}

void Window::setup(const std::string& lTitle, const sf::Vector2u& lSize) {
    mWindowTitle = lTitle;
    mWindowSize = lSize;
    mIsDone = false;
    mIsFullScreen = false;
    
    create();
}

void Window::create() {
    auto style = (mIsFullScreen ? sf::Style::Fullscreen : sf::Style::Default);
    mRenderWindow.create({mWindowSize.x, mWindowSize.y, 32}, mWindowTitle, style);
}

void Window::destroy() {
    mRenderWindow.close();
}

void Window::update() {
    sf::Event event;
    
    while(mRenderWindow.pollEvent(event)) {
        if(event.type == sf::Event::Closed) {
            mIsDone = true;
        }
        else if(event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::F5) {
            toggleFullScreen();
        }
    }
}

void Window::toggleFullScreen() {
    mIsFullScreen = !mIsFullScreen;
    destroy();
    create();
}

void Window::beginDraw() {
    mRenderWindow.clear(sf::Color::Black);
}

void Window::endDraw() {
    mRenderWindow.display();
}

bool Window::isDone() {
    return mIsDone;
}

bool Window::isFullScreen() {
    return mIsFullScreen;
}

sf::Vector2u Window::getWindowSize() const {
    return mWindowSize;
}

void Window::draw(const sf::Drawable& lDrawable) {
    mRenderWindow.draw(lDrawable);
}

void Window::setRenderWindowPosition(const sf::Vector2i& lPos) {
    mRenderWindow.setPosition(lPos);
}
