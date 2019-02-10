/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: DooM
 *
 * Created on January 22, 2019, 6:28 PM
 */

#include <cstdlib>
#include <SDL2/SDL.h>

using namespace std;

/*
 * 
 */
int main(int argc, char** argv) {

    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_Window* window = SDL_CreateWindow("title", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED
            600, 400, SDL_WINDOW_SHOWN);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0);
    
    return 0;
}

