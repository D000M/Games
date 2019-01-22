/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   HorseMoving.h
 * Author: default
 *
 * Created on January 16, 2019, 2:57 PM
 */

#ifndef HORSEMOVING_H
#define HORSEMOVING_H

#include <stdlib.h>
#include <iostream>


constexpr int BOARD_SIZE = 8;

int board[BOARD_SIZE][BOARD_SIZE] = {};

//Ruls for horse moving
constexpr int maxDiff = 8;
const int diffX[maxDiff] = {
    1, 1, -1, -1, 2, -2, 2, -2
};
const int diffY[maxDiff] = {
    2, -2, 2, -2, 1, 1, -1, -1
};

int newRow;
int newCol;

void printBoard() {
    for(int i = 0; i < BOARD_SIZE; i++) {
        for(int j = 0; j < BOARD_SIZE; j++) {
            std::cout << board[i][j] << "\t"; 
        }
        std::cout << std::endl;
    }
    exit(0);    
}

void nextHorseMove(int row, int col, int move) {
    board[row][col] = move;
    if(move == BOARD_SIZE * BOARD_SIZE) {
        printBoard();
        return;
    }
    for(int i = 0; i < maxDiff; i++) {
        newRow = row + diffX[i];
        newCol = col + diffY[i];
        if((newRow >= 0 && newRow < BOARD_SIZE && newCol >= 0 && newCol < BOARD_SIZE) && board[newRow][newCol] == 0) {
            nextHorseMove(newRow, newCol, move + 1);
        }
    }
    board[row][col] = 0;
}

void testHorseMoving() {
//    printBoard();
    nextHorseMove(0, 0, 1);
    std::cout << "The solution isnt found!\n";
}


#endif /* HORSEMOVING_H */

