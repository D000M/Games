/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: DooM
 *
 * Created on July 26, 2018, 6:35 PM
 */

#include <cstdlib>
#include <iostream>

#include "engine/Game.h"

using namespace std;

/*
 * 
 */
int main(int argc, char** argv) {
    std::cout << "add 1 line\n";
    Game game;
    while(!game.getGameWindow()->isClosed()) {
        game.update();
        game.render();
        game.lateUpdate();
    }
    
    return 0;
}

