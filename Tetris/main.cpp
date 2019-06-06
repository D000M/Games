/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: default
 *
 * Created on June 4, 2019, 12:41 PM
 */

#include <cstdlib>

#include "Window.h"
#include "Game.h"

using namespace std;

/*
 * 
 */
int main(int argc, char** argv) {
    
    Game g;
    while(g.getWindow()->isWindowOpen()) {
        g.handleInput();
        g.update();
        g.render();
        g.restartClock();
    }

    return 0;
}

