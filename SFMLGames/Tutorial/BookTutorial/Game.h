/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Game.h
 * Author: DooM
 *
 * Created on January 22, 2019, 8:43 PM
 */

#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>

#include "Window.h"


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
    
    void MoveCloud();
    Window m_window;
    
    sf::Texture m_cloudTexture;
    sf::Sprite m_cloud;
    sf::Vector2i m_increment;
    
    sf::Clock m_clock;
    sf::Time m_elapsed;
};

#endif /* GAME_H */

