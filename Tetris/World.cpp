/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   World.cpp
 * Author: default
 * 
 * Created on June 4, 2019, 2:54 PM
 */

#include "World.h"
#include <iostream>



World::World() {
    srand(std::time(nullptr));
    initGrid();
    initRects();
    playingTetro = nullptr;
    createTetromino();
    for(int i = 0; i < height; i++) {
        for(int j = 0; j < width; j++) {
            hashTable[i][j] = false;
        }
    }
    
}

World::~World() {
}

void World::initGrid() {
    for(size_t i = 0; i < height; i++) {
        for(size_t j = 0; j < width; j++) {
            gameGrid[i][j] = Colors::BLACK;
        }
    }
}

void World::initRects() {

    for(int i = 0; i < height; i++) {
        for(int j = 0; j < width; j++) {
            rects.emplace_back(sf::RectangleShape{sf::Vector2f{38, 38}});
        }
    }
    int startX = 40;
    int startY = 40;
    int count = 0;
    for(auto& elem : rects) {
        
        elem.setPosition(startX, startY);
        startX += 40;
        count++;
        elem.setFillColor(sf::Color::Black);
        if(count > 1 && count % 10 == 0) {
            startX = 40;
            startY += 40;
        }
    }
//    updateGrid();
}

void World::createTetromino() {
    srand(std::time(nullptr));
    int randNum = std::rand() % 7;
    TetrominoTypes temp = getTetromino(randNum);
    currType = temp;
    playingTetro = factoryTetro.create(temp);
    playingTetro->setOrientation();
    displayTetro(temp, true);
    
}

void World::displayTetro(const TetrominoTypes& type, bool startPos) {
    if(startPos) {
        for(int i = 0; i < height; i++) {
            for(int j = 0; j < width; j++) {
                if(playingTetro->getPosition(i, j) == 1) {
                    gameGrid[i][j] = getColorByTetro(type);
                }
            }
        }
    }
//    else {
//        playingTetro->moveDown();
//    }
}

void World::updateTetro() {
    for(int i = 0; i < height; i++) {
        for(int j = 0; j < width; j++) {
            if(playingTetro->getPosition(i, j) == 1 && hashTable[i][j] == false) {
                gameGrid[i][j] = getColorByTetro(currType);
            }
            else {
                if(hashTable[i][j] == false) {
                    gameGrid[i][j] = getColorByTetro(TetrominoTypes::COUNT);
                }
            }
        }
    }

    
    if(playingTetro->isTetroBlocked(hashTable)) {
        setCurrTetro();
        playingTetro = nullptr;
        createTetromino();
        playingTetro->moveDown();
    }
    else {
        playingTetro->moveDown();
    }
    std::cout << "Update\n";
}

void World::updateHorizontalMoving() {
    int index = 0;
    for(int i = 0; i < height; i++) {
        for(int j = 0; j < width; j++) {
            if(playingTetro->getPosition(i, j) == 1 && hashTable[i][j] == false) {
                gameGrid[i][j] = getColorByTetro(currType);
            }
            else {
                if(hashTable[i][j] == false) {
                    gameGrid[i][j] = getColorByTetro(TetrominoTypes::COUNT);
                }
            }
        }
    }
    for(size_t i = 0; i < height; i++) {
        for(size_t j = 0; j < width; j++) {
            setColors(gameGrid[i][j], index);
            index++;
        }
    }
}


void World::setCurrTetro() {
    for(int i = 0; i < height; i++) {
        for(int j = 0; j < width; j++) {
            if(gameGrid[i][j] != Colors::BLACK) {
                hashTable[i][j] = true;
            }
        }
    }
}

bool World::stopMovingDown() {
    bool bStopMoving = false;
    for(int i = 0; i < height; i++) {
        for(int j = 0; j < width; j++) {
            if(gameGrid[i][j] != Colors::BLACK && playingTetro->getPosition(i, j) == 1) {
                hashTable[i][j] = true;
                bStopMoving = true;
            }
        }
    }
    return bStopMoving;
}


Colors World::getColorByTetro(const TetrominoTypes& type) const {
    switch(type) {
        case TetrominoTypes::I:
            return Colors::CYAN;
        case TetrominoTypes::J:
            return Colors::BLUE;
        case TetrominoTypes::L:
            return Colors::ORANGE;
        case TetrominoTypes::O:
            return Colors::YELLOW;
        case TetrominoTypes::S:
            return Colors::GREEN;
        case TetrominoTypes::T:
            return Colors::PURPLE;
        case TetrominoTypes::Z:
            return Colors::RED;
    }
    return Colors::BLACK;
}

TetrominoTypes World::getTetromino(int type) {
    switch(type) {
        case 0:
            return TetrominoTypes::I;
        case 1:
            return TetrominoTypes::J;
        case 2:
            return TetrominoTypes::L;
        case 3:
            return TetrominoTypes::O;
        case 4:
            return TetrominoTypes::S;
        case 5:
            return TetrominoTypes::T;
        case 6:
            return TetrominoTypes::Z;
        default:
            break;
    }
    return TetrominoTypes::COUNT;
}

void World::setColors(const Colors& col, int index) {
    switch(col) {
        case Colors::BLACK:
            rects.at(index).setFillColor(sf::Color::Black);
            break;
        case Colors::CYAN:
            rects.at(index).setFillColor(sf::Color::Cyan);
            break;
        case Colors::YELLOW:
            rects.at(index).setFillColor(sf::Color::Yellow);
            break;
        case Colors::PURPLE:
            rects.at(index).setFillColor(sf::Color{218,112,214});
            break;
        case Colors::GREEN:
            rects.at(index).setFillColor(sf::Color::Green);
            break;
        case Colors::RED:
            rects.at(index).setFillColor(sf::Color::Red);
            break;
        case Colors::BLUE:
            rects.at(index).setFillColor(sf::Color::Blue);
            break;
        case Colors::ORANGE:
            rects.at(index).setFillColor(sf::Color{255,165,0});
            break;
        default:
            break;
    }
}



void World::updateGrid() {
    int index = 0;
    updateTetro();
    for(size_t i = 0; i < height; i++) {
        for(size_t j = 0; j < width; j++) {
            setColors(gameGrid[i][j], index);
            index++;
        }
    }
}

void World::render(sf::RenderWindow* lWindow) {
    for(auto& elem : rects) {
        lWindow->draw(elem);
    }
}

void World::update() {
    updateGrid();
}

Colors World::getRandomColor() const {
    Colors temp;
    int randCol = std::rand() % 8;
    switch(randCol) {
        case 0:
            temp = Colors::BLACK;
            break;
        case 1:
            temp = Colors::CYAN;
            break;
        case 2:
            temp = Colors::YELLOW;
            break;
        case 3:
            temp = Colors::PURPLE;
            break;
        case 4:
            temp = Colors::GREEN;
            break;
        case 5:
            temp = Colors::RED;
            break;
        case 6:
            temp = Colors::BLUE;
            break;
        case 7:
            temp = Colors::ORANGE;
            break;
        default:
            break;
    }
    return temp;
}

BaseTetromino* World::getTetro() {
    return playingTetro.get();
}
