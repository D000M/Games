/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   TemplateMethod.h
 * Author: default
 *
 * Created on May 22, 2019, 4:36 PM
 */

#ifndef TEMPLATEMETHOD_H
#define TEMPLATEMETHOD_H

#include <iostream>


namespace TemplateMethod {
    
    class IGame {
    public:
        IGame(int numberOfPlayers)
            : numberOfPlayers(numberOfPlayers) {
        }

    protected:
        int numberOfPlayers;
        int currentPlayer{0};
        virtual void start() = 0;
        virtual bool haveWinner() = 0;
        virtual void takeTurn() = 0;
        virtual int getWinner() = 0;
    public:
        
        void run() {
            start();
            while(!haveWinner()) {
                takeTurn();
            }
            std::cout << "Player: " << getWinner() << " wins.\n";
        }
    };
    
    class Chess : public IGame {
        
    public:
        
        Chess() : IGame(2) {}
        
    protected:
        void start() override {
            std::cout << "Starting a game of chess with: " << numberOfPlayers << " players\n";
        }
        bool haveWinner() override {
            return turn == maxTurns;
        }
        void takeTurn() override {
            std::cout << "Turn: " << turn << " taken by player: " << currentPlayer << std::endl;
            ++turn;
            currentPlayer = (currentPlayer + 1) % numberOfPlayers;  //Cycle the players 0/1/0/1/0/1
        }
        int getWinner() override {
            return currentPlayer;
        }

    private:
        int turn{0};
        int maxTurns{10};
    };
    
    
    void simulateChessGame() {
        Chess chess;
        chess.run();
    }
}

#endif /* TEMPLATEMETHOD_H */

