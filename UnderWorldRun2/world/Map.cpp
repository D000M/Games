/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Map.cpp
 * Author: DooM
 * 
 * Created on July 30, 2018, 8:45 PM
 */

#include <fstream>
#include <iostream>
#include "../utils/Constants.h"
#include "Map.h"

Map::Map(SharedContext* context) 
    : m_context{context},
      m_player{context}{
    
    m_context->m_gameMap = this;
    loadMap("resources/maps/level1");
    m_background.setSize(sf::Vector2f{1080, 440});
    m_background.setFillColor(sf::Color{192,192,192});
    m_background.setPosition(50, 50);
    
}

Map::~Map() {
    
    m_context->m_gameMap = nullptr;
    
}

void Map::loadMap(const std::string& path) {
    std::ifstream file{path};
    if(!file.is_open()) {
        std::cerr << "! Map cant be loaded! " << path << std::endl;
        return;
    }
    
    std::string line;
    int row = 0;
    while(std::getline(file, line)) {
        Tile temp; 
        for(int i = 0; i < line.length(); i++) {
            switch(line.at(i)) {
                case '0':
                    temp = Tile::WALL;
                    rects[row][i].setFillColor(Constants::WALL);
                    break;
                case 'S':
                    temp = Tile::START;
                    rects[row][i].setFillColor(Constants::START);
                    break;
                case 'P':
                    temp = Tile::PATH;
                    rects[row][i].setFillColor(Constants::PATH);
                    break;
                case '?':
                    temp = Tile::CHANCE;
                    rects[row][i].setFillColor(Constants::CHANCE);
                    break;
                case 'J':
                    temp = Tile::JAIL;
                    rects[row][i].setFillColor(Constants::JAIL);
                    break;
                case 'G':
                    temp = Tile::GOLD_CAVE;
                    rects[row][i].setFillColor(Constants::GOLD);
                    break;
                case 'F': 
                    temp = Tile::FIRE_CAVE;
                    rects[row][i].setFillColor(Constants::FIRE);
                    break;
                case 'E':
                    temp = Tile::EXIT;
                    rects[row][i].setFillColor(Constants::EXIT);
                    break;
                case 'Z':
                    temp = Tile::EARTH_CAVE;
                    rects[row][i].setFillColor(Constants::EARTH);
                    break;
                case 'D':
                    temp = Tile::DEVIL_CAVE;
                    rects[row][i].setFillColor(Constants::DEVIL);
                    break;
                case 'B':
                    temp = Tile::BAT_CAVE;
                    rects[row][i].setFillColor(Constants::BAT);
                    break;
                case 'H':
                    temp = Tile::HOLE;
                    rects[row][i].setFillColor(Constants::HOLE);
                    break;
            }
            level[row][i] = temp;
        }
        row++;
    }
}

std::string Map::asString() {
    std::string strLevel = "";
    for(int i = 0; i < 11; i++) {
        for(int j = 0; j < 27; j++) {
            strLevel += tileToChar(i, j);
        }
        strLevel += '\n';
    }
    return strLevel;
}

char Map::tileToChar(int i, int j) {
    switch(level[i][j]) {
        case 0:
            return '0';
        case 1:
            return 'S';
        case 2:
            return 'P';
        case 3:
            return '?';
        case 4:
            return 'H';
        case 5:
            return 'F';
        case 6:
            return 'B';
        case 7:
            return 'Z';
        case 8:
            return 'D';
        case 9:
            return 'G';
        case 10:
            return 'J';
        case 11:
            return 'E';
    }
}


void Map::draw() {
    m_context->m_wind->getRenderWindow()->draw(m_background);

    for(int i = 0; i < 11; i++) {
        for(int j = 0; j < 27; j++) {
            rects[i][j].setSize(sf::Vector2f{36, 36});
            rects[i][j].setPosition(40 * j + 52, 40 * i + 52);
            rects[i][j].setScale(1.0f, 1.0f);
            m_context->m_wind->getRenderWindow()->draw(rects[i][j]);
        }
    }
    m_player.draw();
}

void Map::update() {
    m_player.update();
}
