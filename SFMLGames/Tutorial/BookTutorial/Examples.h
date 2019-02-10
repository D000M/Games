/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Examples.h
 * Author: DooM
 *
 * Created on January 22, 2019, 8:24 PM
 */

#ifndef EXAMPLES_H
#define EXAMPLES_H

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>

void chapterOne() {
        
    sf::RenderWindow window(sf::VideoMode{640, 480}, "First Window!");
    
    sf::RectangleShape rectangle{sf::Vector2f{128.0f, 128.0f}};
    rectangle.setFillColor(sf::Color::Red);
    rectangle.setPosition(320, 240);
    rectangle.setOrigin(rectangle.getSize().x / 2, rectangle.getSize().y / 2);
    
    sf::Texture cloudTexture;
    cloudTexture.loadFromFile("resources/cloud.png");
    sf::Sprite cloud{cloudTexture};
    sf::Vector2u size = cloudTexture.getSize();
    cloud.setOrigin(size.x / 2, size.y / 2);
    sf::Vector2f increment{0.04f, 0.04f};
    
    while(window.isOpen()) {
        sf::Event event;
        while(window.pollEvent(event)) {
            if(event.type == sf::Event::Closed) {
                //Close Window Button clicked
                window.close();
            }
        }
        if((cloud.getPosition().x + (size.x / 2) > window.getSize().x && increment.x > 0) ||
                (cloud.getPosition().x - (size.x / 2) < 0 && increment.x < 0)) {
            //Reverse direction on X axis
            increment.x = -increment.x;
        }
        if((cloud.getPosition().y + (size.y / 2) > window.getSize().y && increment.y > 0) ||
                (cloud.getPosition().y - (size.y / 2) < 0 && increment.y < 0)) {
            //Reverse direction on X axis
            increment.y = -increment.y;
        }
        
        cloud.setPosition(cloud.getPosition() + increment);
        
        window.clear(sf::Color{255,255,255,255});
        //Draw Here
        window.draw(rectangle);
        window.draw(cloud);
        //Display the window
        window.display();
    }
    
}

#endif /* EXAMPLES_H */

