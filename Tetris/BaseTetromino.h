/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   BaseTetromino.h
 * Author: default
 *
 * Created on June 5, 2019, 12:50 PM
 */

#ifndef BASETETROMINO_H
#define BASETETROMINO_H

#include <iostream>
#include <functional>
#include <memory>
#include <map>
#include <string>
#include <SFML/Graphics/Drawable.hpp>

enum class TetrominoTypes {
    I,
    J,
    L,
    O,
    S,
    T,
    Z,
    COUNT
};

enum class Orientation {
    Horizontal,
    Verical,
    Right,
    Left,
    None
};

constexpr int sizeX = 10;
constexpr int sizeY = 20;

class BaseTetromino {
public:
    virtual ~BaseTetromino() {
        std::cout << "Base Tetromino Destroyed!\n";
    }
    
    virtual void createTetromino() = 0;
//    virtual void rotateLeft() = 0;
//    virtual void rotateRight() = 0;
//    virtual void draw() = 0;
    virtual void setOrientation() = 0;
    virtual void setStartPos() = 0;
    
    void resetTetro() {
        
    }
    
    int getPosition(int x, int y) {
        return squares[x][y];
    }
    bool isTetroBlocked(bool pos[sizeY][sizeX]) const {
        if(squareOneX + 2 > sizeY || squareTwoX + 2 > sizeY || squareThreeX + 2 > sizeY || squareFourX + 2 > sizeY) {
            return true;
        }
        for(int i = 0; i < sizeY; i++) {
            for(int j = 0; j < sizeX; j++) {
                if(pos[i][j] == true && squares[i - 1][j] == 1) {
                    return true;
                }
            }
        }
        
        return false;
    }
    
    void moveDown() {
        
        squares[squareOneX][squareOneY] = -1;
        squares[squareTwoX][squareTwoY] = -1;
        squares[squareThreeX][squareThreeY] = -1;
        squares[squareFourX][squareFourY] = -1;
        
        squares[++squareOneX][squareOneY] = 1;
        squares[++squareTwoX][squareTwoY] = 1;
        squares[++squareThreeX][squareThreeY] = 1;
        squares[++squareFourX][squareFourY] = 1;
             
    }
    void moveLeft() {
        squares[squareOneX][squareOneY] = -1;
        squares[squareTwoX][squareTwoY] = -1;
        squares[squareThreeX][squareThreeY] = -1;
        squares[squareFourX][squareFourY] = -1;
        
        squares[squareOneX][--squareOneY] = 1;
        squares[squareTwoX][--squareTwoY] = 1;
        squares[squareThreeX][--squareThreeY] = 1;
        squares[squareFourX][--squareFourY] = 1;
    }
    void moveRight() {
        squares[squareOneX][squareOneY] = -1;
        squares[squareTwoX][squareTwoY] = -1;
        squares[squareThreeX][squareThreeY] = -1;
        squares[squareFourX][squareFourY] = -1;
        
        squares[squareOneX][++squareOneY] = 1;
        squares[squareTwoX][++squareTwoY] = 1;
        squares[squareThreeX][++squareThreeY] = 1;
        squares[squareFourX][++squareFourY] = 1;
    }
//    virtual void updateSquares() = 0;
    
private:
protected:
    int squares[sizeY][sizeX];
    Orientation orientation;
    int squareOneX, squareOneY;
    int squareTwoX, squareTwoY;
    int squareThreeX, squareThreeY;
    int squareFourX, squareFourY;
};

class ITetromino : public BaseTetromino {
public:
    void createTetromino() override {
        std::cout << "I Tetromino created!\n";
    }
    void setOrientation() override {
        int orient = std::rand() % 2;
        
        if(orient == 0) {
            orientation = Orientation::Verical;             // |
        }           
        else {                                              // __    
            orientation = Orientation::Horizontal;
        }
        std::cout << "Orientation: " << static_cast<int>(orientation) << std::endl;
        setStartPos();
    }
    
    void setStartPos() override {
        for(int i = 0; i < sizeY; i++) {
            for(int j = 0; j < sizeX; j++) {
                squares[i][j] = -1;
            }
        }
        switch(orientation) {
            case Orientation::Verical:
                squareOneX = 0; squareOneY = 4;
                squareTwoX = 1; squareTwoY = 4;
                squareThreeX = 2; squareThreeY = 4;
                squareFourX = 3; squareFourY = 4;
                std::cout << "Vertical!\n";
                break;
            case Orientation::Horizontal:
                squareOneX = 0; squareOneY = 3;
                squareTwoX = 0; squareTwoY = 4;
                squareThreeX = 0; squareThreeY = 5;
                squareFourX = 0; squareFourY = 6;
                std::cout << "Horizontal!\n";
                break;
        }
       
        squares[squareOneX][squareOneY] = 1;
        squares[squareTwoX][squareTwoY] = 1;
        squares[squareThreeX][squareThreeY] = 1;
        squares[squareFourX][squareFourY] = 1;
    }

};

class JTetromino : public BaseTetromino {
public:
    void createTetromino() override {
        std::cout << "J Tetromino created!\n";
    }
    void setOrientation() override {
        int orient = std::rand() % 4;

        if(orient == 0) {
            orientation = Orientation::Verical;
        }
        else if (orient == 1) {
            orientation = Orientation::Horizontal;
        }
        else if(orient == 2) {
            orientation = Orientation::Right;
        }
        else {
            orientation = Orientation::Left;
        }
        std::cout << "Orientation: " << static_cast<int>(orientation) << std::endl;
        setStartPos();
    }
    void setStartPos() override {
        for(int i = 0; i < sizeY; i++) {
            for(int j = 0; j < sizeX; j++) {
                squares[i][j] = -1;
            }
        }
        switch(orientation) {
            case Orientation::Verical:
                squareOneX = 0; squareOneY = 5;
                squareTwoX = 0; squareTwoY = 4;
                squareThreeX = 1; squareThreeY = 4;
                squareFourX = 2; squareFourY = 4;
                std::cout << "Vertical!\n";
                break;
            case Orientation::Horizontal:
                squareOneX = 0; squareOneY = 5;
                squareTwoX = 1; squareTwoY = 5;
                squareThreeX = 2; squareThreeY = 5;
                squareFourX = 2; squareFourY = 4;
                std::cout << "Horizontal!\n";
                break;
            case Orientation::Left:
                squareOneX = 0; squareOneY = 4;
                squareTwoX = 0; squareTwoY = 5;
                squareThreeX = 0; squareThreeY = 6;
                squareFourX = 1; squareFourY = 6;
                std::cout << "Left!\n";
                break;
            case Orientation::Right:
                squareOneX = 0; squareOneY = 4;
                squareTwoX = 1; squareTwoY = 4;
                squareThreeX = 1; squareThreeY = 5;
                squareFourX = 1; squareFourY = 6;
                std::cout << "Right!\n";
                break;
        }
       
        squares[squareOneX][squareOneY] = 1;
        squares[squareTwoX][squareTwoY] = 1;
        squares[squareThreeX][squareThreeY] = 1;
        squares[squareFourX][squareFourY] = 1;
    }
};

class LTetromino : public BaseTetromino {
public:
    void createTetromino() override {
        std::cout << "L Tetromino created!\n";
    }
    void setOrientation() override {
        int orient = std::rand() % 4;
        if(orient == 0) {
            orientation = Orientation::Verical;
        }
        else if (orient == 1) {
            orientation = Orientation::Horizontal;
        }
        else if(orient == 2) {
            orientation = Orientation::Right;
        }
        else {
            orientation = Orientation::Left;
        }
        std::cout << "Orientation: " << static_cast<int>(orientation) << std::endl;
        setStartPos();
    }
    void setStartPos() override {
        for(int i = 0; i < sizeY; i++) {
            for(int j = 0; j < sizeX; j++) {
                squares[i][j] = -1;
            }
        }
        switch(orientation) {
            case Orientation::Verical:
                squareOneX = 0; squareOneY = 4;
                squareTwoX = 0; squareTwoY = 5;
                squareThreeX = 1; squareThreeY = 5;
                squareFourX = 2; squareFourY = 5;
                std::cout << "Vertical!\n";
                break;
            case Orientation::Horizontal:
                squareOneX = 0; squareOneY = 4;
                squareTwoX = 1; squareTwoY = 4;
                squareThreeX = 2; squareThreeY = 4;
                squareFourX = 2; squareFourY = 5;
                std::cout << "Horizontal!\n";
                break;
            case Orientation::Left:
                squareOneX = 1; squareOneY = 4;
                squareTwoX = 1; squareTwoY = 5;
                squareThreeX = 1; squareThreeY = 6;
                squareFourX = 0; squareFourY = 6;
                std::cout << "Left!\n";
                break;
            case Orientation::Right:
                squareOneX = 0; squareOneY = 6;
                squareTwoX = 0; squareTwoY = 5;
                squareThreeX = 0; squareThreeY = 4;
                squareFourX = 1; squareFourY = 4;
                std::cout << "Right!\n";
                break;
        }
        squares[squareOneX][squareOneY] = 1;
        squares[squareTwoX][squareTwoY] = 1;
        squares[squareThreeX][squareThreeY] = 1;
        squares[squareFourX][squareFourY] = 1;
    }

};

class OTetromino : public BaseTetromino {
public:
    void createTetromino() override {
        std::cout << "O Tetromino created!\n";
        
    }
    void setOrientation() override {
        orientation = Orientation::None;
        setStartPos();
    }
    void setStartPos() override {
        for(int i = 0; i < sizeY; i++) {
            for(int j = 0; j < sizeX; j++) {
                squares[i][j] = -1;
            }
        }
        squareOneX = 0; squareOneY = 4;
        squareTwoX = 0; squareTwoY = 5;
        squareThreeX = 1; squareThreeY = 4;
        squareFourX = 1; squareFourY = 5;
        
        squares[squareOneX][squareOneY] = 1;
        squares[squareTwoX][squareTwoY] = 1;
        squares[squareThreeX][squareThreeY] = 1;
        squares[squareFourX][squareFourY] = 1;
    }

};

class STetromino : public BaseTetromino {
public:
    void createTetromino() override {
        std::cout << "S Tetromino created!\n";
    }
    void setOrientation() override {
        int orient = std::rand() % 2;
        if(orient == 0) {
            orientation = Orientation::Verical;             // |
        }           
        else {                                              // __    
            orientation = Orientation::Horizontal;
        }
        std::cout << "Orientation: " << static_cast<int>(orientation) << std::endl;
        setStartPos();
    }
    void setStartPos() override {
        for(int i = 0; i < sizeY; i++) {
            for(int j = 0; j < sizeX; j++) {
                squares[i][j] = -1;
            }
        }
        switch(orientation) {
            case Orientation::Verical:
                squareOneX = 0; squareOneY = 4;
                squareTwoX = 1; squareTwoY = 4;
                squareThreeX = 1; squareThreeY = 5;
                squareFourX = 2; squareFourY = 5;
                std::cout << "Vertical!\n";
                break;
            case Orientation::Horizontal:
                squareOneX = 0; squareOneY = 5;
                squareTwoX = 0; squareTwoY = 6;
                squareThreeX = 1; squareThreeY = 5;
                squareFourX = 1; squareFourY = 4;
                std::cout << "Horizontal!\n";
                break;
        }
       
        squares[squareOneX][squareOneY] = 1;
        squares[squareTwoX][squareTwoY] = 1;
        squares[squareThreeX][squareThreeY] = 1;
        squares[squareFourX][squareFourY] = 1;
    }

};

class TTetromino : public BaseTetromino {
public:
    void createTetromino() override {
        std::cout << "T Tetromino created!\n";
    }
    void setOrientation() override {
        int orient = std::rand() % 4;
        if(orient == 0) {
            orientation = Orientation::Verical;
        }
        else if (orient == 1) {
            orientation = Orientation::Horizontal;
        }
        else if(orient == 2) {
            orientation = Orientation::Right;
        }
        else {
            orientation = Orientation::Left;
        }
        std::cout << "Orientation: " << static_cast<int>(orientation) << std::endl;
        setStartPos();
    }
    void setStartPos() override {
        for(int i = 0; i < sizeY; i++) {
            for(int j = 0; j < sizeX; j++) {
                squares[i][j] = -1;
            }
        }
        switch(orientation) {
            case Orientation::Verical:
                squareOneX = 0; squareOneY = 4;
                squareTwoX = 0; squareTwoY = 5;
                squareThreeX = 0; squareThreeY = 6;
                squareFourX = 1; squareFourY = 5;
                std::cout << "Vertical\n";
                break;
            case Orientation::Horizontal:
                squareOneX = 0; squareOneY = 5;
                squareTwoX = 1; squareTwoY = 4;
                squareThreeX = 1; squareThreeY = 5;
                squareFourX = 1; squareFourY = 6;
                std::cout << "Horizontal\n";
                break;
            case Orientation::Right:
                squareOneX = 0; squareOneY = 4;
                squareTwoX = 1; squareTwoY = 4;
                squareThreeX = 1; squareThreeY = 5;
                squareFourX = 2; squareFourY = 4;
                std::cout << "Right\n";
                break;
            case Orientation::Left:
                squareOneX = 0; squareOneY = 5;
                squareTwoX = 1; squareTwoY = 5;
                squareThreeX = 1; squareThreeY = 4;
                squareFourX = 2; squareFourY = 5;
                std::cout << "Left\n";
                break;
        }
        
        
        squares[squareOneX][squareOneY] = 1;
        squares[squareTwoX][squareTwoY] = 1;
        squares[squareThreeX][squareThreeY] = 1;
        squares[squareFourX][squareFourY] = 1;
    }

};

class ZTetromino : public BaseTetromino {
public:
    void createTetromino() override {
        std::cout << "Z Tetromino created!\n";
        
    }
    void setOrientation() override {
        int orient = std::rand() % 2;

        if(orient == 0) {
            orientation = Orientation::Verical;             // |
        }           
        else {                                              // __    
            orientation = Orientation::Horizontal;
        }
        std::cout << "Orientation: " << static_cast<int>(orientation) << std::endl;
        setStartPos();
    }
    void setStartPos() override {
        for(int i = 0; i < sizeY; i++) {
            for(int j = 0; j < sizeX; j++) {
                squares[i][j] = -1;
            }
        }
        switch(orientation) {
            case Orientation::Verical:
                squareOneX = 0; squareOneY = 5;
                squareTwoX = 1; squareTwoY = 5;
                squareThreeX = 1; squareThreeY = 4;
                squareFourX = 2; squareFourY = 4;
                std::cout << "Vertical!\n";
                break;
            case Orientation::Horizontal:
                squareOneX = 0; squareOneY = 5;     //5
                squareTwoX = 0; squareTwoY = 4;     //6        
                squareThreeX = 1; squareThreeY = 5; //5
                squareFourX = 1; squareFourY = 6;   //4
                std::cout << "Horizontal!\n";
                break;
        }
       
        squares[squareOneX][squareOneY] = 1;
        squares[squareTwoX][squareTwoY] = 1;
        squares[squareThreeX][squareThreeY] = 1;
        squares[squareFourX][squareFourY] = 1;
    }
};

class TetrominoFactory {
    std::map<TetrominoTypes, std::function<std::unique_ptr<BaseTetromino>() > > tetrominoFactory;
public:
    TetrominoFactory() {
        tetrominoFactory[TetrominoTypes::I] = []() {
            auto ITetro = std::make_unique<ITetromino>();
            ITetro->createTetromino();
            return ITetro;
        };

        tetrominoFactory[TetrominoTypes::J] = []() {
           auto JTetro = std::make_unique<JTetromino>();
           JTetro->createTetromino();
           return JTetro;
        };
        
        tetrominoFactory[TetrominoTypes::L] = []() {
           auto LTetro = std::make_unique<LTetromino>();
           LTetro->createTetromino();
           return LTetro;
        };
        
        tetrominoFactory[TetrominoTypes::O] = []() {
           auto OTetro = std::make_unique<OTetromino>();
           OTetro->createTetromino();
           return OTetro;
        };
        
        tetrominoFactory[TetrominoTypes::S] = []() {
           auto STetro = std::make_unique<STetromino>();
           STetro->createTetromino();
           return STetro;
        };
        
        tetrominoFactory[TetrominoTypes::T] = []() {
           auto TTetro = std::make_unique<TTetromino>();
           TTetro->createTetromino();
           return TTetro;
        };
        
        tetrominoFactory[TetrominoTypes::Z] = []() {
           auto ZTetro = std::make_unique<ZTetromino>();
           ZTetro->createTetromino();
           return ZTetro;
        };
    }
    
    //Public method to return tetrominos from the factory
    std::unique_ptr<BaseTetromino> create(const TetrominoTypes& type) {
        return tetrominoFactory[type]();    //Call as function cause map.second is a pointer to function.
    }
};
#endif /* BASETETROMINO_H */

