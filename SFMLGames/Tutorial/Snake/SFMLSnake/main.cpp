/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: DooM
 *
 * Created on January 22, 2019, 9:20 PM
 */
#define __USE_MINGW_ANSI_STDIO 0
#include <cstdlib>

#include "Game.h"

using namespace std;

/*
 * 
 */
int main(int argc, char** argv) {

    Game game;
    while(!game.GetWindow()->IsDone()) {
        game.HandleInput();
        game.Update();
        game.Render();
        game.RestartClock();
    }
    
    return 0;
}

