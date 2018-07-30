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

#include "Map.h"

Map::Map() {
    loadMap("resources/maps/level1");
}

Map::~Map() {
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
                    break;
                case 'S':
                    temp = Tile::START;
                    break;
                case 'P':
                    temp = Tile::PATH;
                    break;
                case 'C':
                    temp = Tile::CHANCE;
                    break;
                case 'J':
                    temp = Tile::JAIL;
                    break;
                case 'G':
                    temp = Tile::GOLD_CAVE;
                    break;
                case 'F': 
                    temp = Tile::FIRE_CAVE;
                    break;
                case 'E':
                    temp = Tile::EXIT;
                    break;
                case 'Z':
                    temp = Tile::EARTH_CAVE;
                    break;
                case 'D':
                    temp = Tile::DEVIL_CAVE;
                    break;
                case 'B':
                    temp = Tile::BAT_CAVE;
                    break;
                case 'H':
                    temp = Tile::HOLE;
                    break;
            }
            level[row][i] = temp;
        }
        row++;
    }
    for(int i = 0; i < 11; i++) {
        for(int j = 0; j < 27; j++) {
            std::cout << level[i][j] << " ";
        }
        std::cout << std::endl;
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
