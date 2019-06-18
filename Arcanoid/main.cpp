/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: default
 *
 * Created on June 10, 2019, 11:01 AM
 */

#include <cstdlib>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>
#include <iostream>
#include <sstream>
#include "Ball.h"
#include "Paddle.h"
#include "Brick.h"
#include <algorithm>

using namespace std;

/*
 * 
 */
bool isGameRunning = true;

constexpr int windowWidth = 800;
constexpr int windowHeight = 600;

int brickRows = 5;
int brickCols = 11;

template<typename T1, typename T2>
bool isIntersect(T1& a, T2& b) {
    return a.right() >= b.left() && a.left() <= b.right() && a.bottom() >= b.top() && a.top() <= b.bottom();
}


void calculateBounce(Paddle& paddle, Ball& ball) {
    if(!isIntersect(paddle, ball)) {
        return;
    }

    ball.setVelocity(-5);

}

void checkBallBrickCollision(Brick& brick, Ball& ball, std::vector<Brick>& bricks) {
    
    if(!isIntersect(brick, ball)) {
        return;
    }
    
    brick.setDestroy(true);
    
    bricks.erase(std::remove_if(std::begin(bricks), std::end(bricks), [](const Brick& brick) {
        return brick.getDestroyed(); 
    }));
    
}

void loadBricks(std::vector<Brick>& bricks) {
    for(int x{0}; x < brickCols; x++) {
        for(int y{0}; y < brickRows; y++) {
            bricks.emplace_back((x + 1) * (brickWidth + 3) + 22,  (y + 2) * (brickHeight + 3));
        }
    }
}

void runArcanoid() {
    sf::RenderWindow window{{windowWidth, windowHeight}, "Arcanoid"};
    
    window.setPosition(sf::Vector2i{250, 250});
    window.setFramerateLimit(60);
    
    Ball ball{windowWidth / 2.0f, windowHeight / 2.0f};
    
    Paddle paddle{windowWidth / 2.f, windowHeight - 50};
    
    sf::Event event;
        
    std::vector<Brick> bricks;
    loadBricks(bricks);
    while(isGameRunning) {
        while(window.pollEvent(event)) {
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape) || event.type == sf::Event::Closed) {
                isGameRunning = false;
            }
        }
            
        window.clear(sf::Color{192, 192, 192});
        
        calculateBounce(paddle, ball);
        for(auto& brick : bricks) {
            checkBallBrickCollision(brick, ball, bricks);
        }
        
        
        ball.checkDirection(windowWidth, windowHeight);
        ball.update();
        paddle.update(windowWidth, windowHeight);
        
        for(auto& brick : bricks) {
            if(!brick.getDestroyed()) {
                window.draw(*brick.getBrick());
            }
        }
        window.draw(*paddle.getPaddle());
        window.draw(*ball.getBall());
        
        window.display();
    }
}

void printNumbers(int n) {
    static int i = 0;
    if(i++ <= n) {
        std::cout << i << " ";
        printNumbers(n);
    }
}

//template<typename T>
void swap(int& a, int& b) {
    int temp = a;
    a = b;
    b = temp;
}


void createBiggestNumber() {
    int arr[] = {109, 0, 3, 30, 34, 5, 9, 88, 99, 91, 100, 0}; //999918853433010910000
 
    std::string first;
    std::string second;
    
    for(int i = 0; i < 12; i++) {
        first = std::to_string(arr[i]);
        for(int j = i + 1; j < 12 - 1; j++) {
            second = std::to_string(arr[j]);
            if(first < second) {             
                swap(arr[i], arr[j]);
                std::string temp = first;
                first = second;
                second = temp;
                if(first.at(0) == second.at(0) && first.length() > second.length()) {
                    swap(arr[i], arr[j]);
                    temp = first;
                    first = second;
                    second = temp;
                }
            }
        }
    }
    std::stringstream ss;
    for(int i = 0; i < 12; i++) {
        ss << std::to_string(arr[i]);
    }
    std::cout << ss.str();
}

int main(int argc, char** argv) {

    runArcanoid();
    
    return 0;
}

