/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Game.h
 * Author: DooM
 *
 * Created on January 22, 2019, 9:21 PM
 */

#ifndef GAME_H
#define GAME_H
#define __USE_MINGW_ANSI_STDIO 0
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>

#include "Window.h"
#include "World.h"
#include "Textbox.h"


class Game {
public:
    Game();
    virtual ~Game();
    
    void HandleInput();
    void Update();
    void Render();
    
    Window* GetWindow();
    
    sf::Time GetElapsed();
    void RestartClock();
private:
    
    Window m_window;
    
    sf::Clock m_clock;
    Textbox m_textBox;
    
    float m_elapsed;
    World m_world;
    Snake m_snake;
};

#endif /* GAME_H */

