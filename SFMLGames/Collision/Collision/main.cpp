/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: DooM
 *
 * Created on January 26, 2019, 3:57 PM
 */

#include <cstdlib>
#include <iostream>
#include "EventManager.h"
#include "Game.h"

using namespace std;

/*
 * 
 */
int main(int argc, char** argv) {

    Game game;

    while(!game.GetWindow()->IsDone()) {
        game.Update();
        game.Render();
        game.LateUpdate();
    }
    
    return 0;
}

