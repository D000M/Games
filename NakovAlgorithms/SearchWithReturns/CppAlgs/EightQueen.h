/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   EightQueen.h
 * Author: default
 *
 * Created on January 16, 2019, 3:46 PM
 */

#ifndef EIGHTQUEEN_H
#define EIGHTQUEEN_H

#include "HorseMoving.h"

constexpr int BOARD_SIZE2 = 15;

int queens[BOARD_SIZE2];
int column[BOARD_SIZE2];
int RD[2 * BOARD_SIZE2 - 1]; //Right diagonal
int LD[2 * BOARD_SIZE2]; //Left Diagonal.

void printQueenBoard() {
    for(int i = 0; i < BOARD_SIZE2; i++) {
        std::cout << std::endl;
        for(int j = 0; j < BOARD_SIZE2; j++) {
            if(queens[i] == j) {
                std::cout << "Q ";
            }
            else {
                std::cout << "x ";
            }
        }
    }
    std::cout << std::endl;
    exit(0);
}

void nextQueen(int currQueen) {
    if(currQueen == BOARD_SIZE2) {
        printQueenBoard();
        return;
    }
    for(int i = 0; i < BOARD_SIZE2; i++) {
        if(column[i] && RD[currQueen + i] && LD[BOARD_SIZE2 + currQueen - i]) {
            column[i] = 0;
            RD[currQueen + i] = 0;
            LD[BOARD_SIZE2 + currQueen - i] = 0;
            queens[currQueen] = i;
            nextQueen(currQueen + 1);
            column[i] = 1;
            RD[currQueen + i] = 1;
            LD[BOARD_SIZE2 + currQueen - i] = 1;
        }
    }
}

void testQueens() {
    std::fill_n(column, BOARD_SIZE2, 1);
    std::fill_n(RD, 2 * BOARD_SIZE2 - 1, 1);
    std::fill_n(LD, 2 * BOARD_SIZE2, 1);
    nextQueen(0);
    std::cout << "Zadachata nqma reshenie!\n";
}

#endif /* EIGHTQUEEN_H */

