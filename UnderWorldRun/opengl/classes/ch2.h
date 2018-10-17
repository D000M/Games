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
#include "../imageHelpler.h"


//Upside down triangle
void excersiceOne() {
    float vertices[] = {
        0.8f,  0.8f, 0.0f,
       -0.8f,  0.8f, 0.0f,
        -0.8f,  -0.8f, 0.0f 
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
            if(timeValue <= -0.8) {
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

//using Textures
void testTexture() {
        
    sf::Window window(sf::VideoMode(800, 600), "OpenGL 2", sf::Style::Default, sf::ContextSettings(32));
    window.setVerticalSyncEnabled(true);
    window.setActive(true);
    
    std::vector<std::string> myGSLSVarAttribs = {
        "aPos", "aColor", "aTexCoord"
    };
    Shader ourShader("opengl/shaders/vertex/textureVertex.vs", "opengl/shaders/fragment/fragment2S.fs", myGSLSVarAttribs);

    //for this texture we will use rectangle shape
    float vertices[] = {
          //position,              // colors,            // texture coords
        0.5f,  0.5f, 0.0f,      1.0f, 0.0f, 0.0f,         2.0f, 2.0f,        // top right
        0.5f, -0.5f, 0.0f,      0.0f, 1.0f, 0.0f,         2.0f, 0.0f,        // bottom right
       -0.5f, -0.5f, 0.0f,      0.0f, 0.0f, 1.0f,         0.0f, 0.0f,        // bottom left
       -0.5f,  0.5f, 0.0f,      1.0f, 1.0f, 0.0f,         0.0f, 2.0f         // top left
    };
    unsigned int indices[] = {
       0, 1, 3,     //first triangle,
       1, 2, 3      //second triangle
    };

    unsigned int VAO, VBO, EBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);
    
    glBindVertexArray(VAO);
    
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
    
    /**
     * Options for texture Wrapping
     * 
        GL_REPEAT: The default behavior for textures. Repeats the texture image.
        GL_MIRRORED_REPEAT: Same as GL_REPEAT but mirrors the image with each repeat.
        GL_CLAMP_TO_EDGE: Clamps the coordinates between 0 and 1. 
     *              The result is that higher coordinates become clamped to the edge, resulting in a stretched edge pattern.
        GL_CLAMP_TO_BORDER: Coordinates outside the range are now given a user-specified border color.

     */
        
    //position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    
    // color attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    // texture coord attribute
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);
    
    //The whole process of loading the texture looks something like this.
    unsigned int texture1, texture2;
    glGenTextures(1, &texture1);
    glBindTexture(GL_TEXTURE_2D, texture1);
    
    //Set the texture wrapping/filtering options (on the currently bound texture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    
    //load and generate texture.
    int width, height, nrChannels;
    unsigned char *data = stbi_load("opengGLResources/container.jpg", &width, &height, &nrChannels, 0);

    if(data) {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else {
        std::cerr << "Failed to load texture: " << "opengGLResources/container.jpg" << std::endl;
    }
    //when the texture is loaded is good practice to unload the image memory
    stbi_image_free(data);

    //texture 2
    glGenTextures(1, &texture2);
    glBindTexture(GL_TEXTURE_2D, texture2);
    //Set the texture wrapping/filtering options (on the currently bound texture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    stbi_set_flip_vertically_on_load(true);
    data = stbi_load("opengGLResources/awesomeface.png", &width, &height, &nrChannels, 0);

    if(data) {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else {
        std::cerr << "Failed to load texture: " << "opengGLResources/awesomeface.png" << std::endl;
    }
    stbi_image_free(data);
    // tell opengl for each sampler to which texture unit it belongs to (only has to be done once)
    // -------------------------------------------------------------------------------------------
    ourShader.use(); // don't forget to activate/use the shader before setting uniforms!
    // either set it manually like so:
    glUniform1i(glGetUniformLocation(ourShader.ID, "texture1"), 0);
    // or set it via the texture class
    ourShader.setInt("texture2", 1);
    
    bool running = true;
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
                    
        glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        // bind textures on corresponding texture units
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture1);
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, texture2);
//        // bind Texture
//        glBindTexture(GL_TEXTURE_2D, texture);
//        
//        ourShader.use();
//        glUniform1i(glGetUniformLocation(ourShader.ID, "texture1"), 0); // set it manually
        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        window.display();
    }
    //optional after we finish the program.
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
}

#endif /* CH2_H */

