/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   ch2.h
 * Author: default
 *
 * Created on September 28, 2018, 2:08 PM
 */

#ifndef CH2_H
#define CH2_H

#include <SFML/Window/Window.hpp>
#include <GL/gl.h>
#include <SFML/Window/Event.hpp>

#include "Shader.h"



//Upside down triangle
void excersiceOne() {
    float vertices[] = {
        -0.8f, -0.8f, 0.0f,
        -0.2f, -0.8f, 0.0f,
        -0.5f,  0.1f, 0.0f
    };
    
    sf::Window window(sf::VideoMode(800, 600), "OpenGL 2", sf::Style::Default, sf::ContextSettings(32));
    window.setVerticalSyncEnabled(true);
    window.setActive(true);
    
    GLuint VAO, VBO;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);
    
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    
    Shader myShader("opengl/shaders/vertex/vs2.vs", "opengl/shaders/fragment/fs2.fs");
    
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    
    bool running = true;
    bool reverse = false;
    float timeValue = 0.0;
    
    while(running) {
        sf::Event event;
        
        while(window.pollEvent(event)) {
            if(event.type == sf::Event::Closed) {
                running = false;
            }
            else if(event.type == sf::Event::Resized) {
                glViewport(0, 0, event.size.width, event.size.height);
            }

        }
                    
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

//            sf::Time myTime = clock.getElapsedTime();
        if(!reverse) {
            timeValue += 0.01;
            if(timeValue >= 1.2) {
                reverse = true;
            }
        }
        else {
            timeValue -= 0.01;
            if(timeValue <= -0.2) {
                reverse = false;
            }
        }
//            std::cout << timeValue << std::endl;
//            float offset = sin(timeValue) / 2.0f + 0.005f;
        myShader.setFloat("xOffset", timeValue );
        myShader.use();

//            clock.restart();
        glDrawArrays(GL_TRIANGLES, 0, 3);

        window.display();
    }
}


#endif /* CH2_H */

