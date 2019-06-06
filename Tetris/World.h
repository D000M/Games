/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   World.h
 * Author: default
 *
 * Created on June 4, 2019, 2:54 PM
 */

#ifndef WORLD_H
#define WORLD_H

#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <vector>

#include "BaseTetromino.h"

const int width = 10;
const int height = 20;

enum class Colors {
    BLACK,
    CYAN,
    YELLOW,
    PURPLE, 
    GREEN,
    RED,
    BLUE,
    ORANGE,
    COUNT
};

class World {
public:
    World();
    virtual ~World();
    
    void update();  //Update 
    void render(sf::RenderWindow* lWindow);
    
    void initGrid();
    void updateGrid();
    
    void initRects();
    void setColors(const Colors& col, int index);
    
    Colors getRandomColor() const;
    Colors getColorByTetro(const TetrominoTypes& type) const;
    void createTetromino();
    TetrominoTypes getTetromino(int type);
    
    void displayTetro(const TetrominoTypes& type, bool startPos = false);
    void updateTetro();
    
    void setCurrTetro();
    bool stopMovingDown();
    
    BaseTetromino* getTetro();
    
    void updateHorizontalMoving();
private:

    TetrominoTypes currType;
    
    TetrominoFactory factoryTetro;
    Colors gameGrid[height][width];
    std::vector<sf::RectangleShape> rects;
    
    std::unique_ptr<BaseTetromino> playingTetro;
    
    bool hashTable[height][width];
    
};

#endif /* WORLD_H */

