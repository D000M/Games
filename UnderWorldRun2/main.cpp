/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: DooM
 *
 * Created on July 28, 2018, 11:35 AM
 */
#define __USE_MINGW_ANSI_STDIO 0

#include <cstdlib>
#include "engine/Game.h"

using namespace std;
/*
 * 
 */
int main(int argc, char** argv) {
    // Program entry point.
    Game game;
    while (!game.getGameWindow()->isClosed()) {
        game.update();
        game.render();
        game.lateUpdate();
    }
    
    return 0;
}

