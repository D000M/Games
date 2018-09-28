/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   ch1.h
 * Author: default
 *
 * Created on September 19, 2018, 2:42 PM
 */

#ifndef CH1_H
#define CH1_H

#define GL_GLEXT_PROTOTYPES     //Define GL_GLTEXT_PROTOTYPES for gl to work.

#include <SFML/OpenGL.hpp>
#include <SFML/Window/Window.hpp>
#include <SFML/Window/Event.hpp>
#include <GL/glext.h>
//#include <GL/gle>
#include <GL/freeglut.h>
#include <SDL2/SDL_opengl_glext.h>
#include <SDL2/SDL_opengl.h>

//#include <SDL2/SDL_opengl.h>
//#include <SDL2/SDL_opengl_glext.h>
//#include <SDL2/SDL_opengl_glext.h>



using namespace std;

/*
 * 
 */


/*
 *#version - declare the version of GLSL (OpenGL Shading Language) 330 correspond to 3.3 OpenGL, and 420 for example is for 4.2 OpenGL
 * 'in' - input variable 'vec3' because every vertex is 3D,  named aPos
 * since our input vector is 3D we have to cast to vec4(aPos.x, aPos.y, aPos.z, 1.0f), our gl_Position = vec4();
 */
//For Creating Triangle
//const char* vertexShaderSource = "#version 110 core\n"
//    "layout (location = 0) in vec3 aPos;\n"
//    "void main()\n"
//    "{\n"
//    "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
//    "}\0";
////For seting collor of the triangle
//const char* fragmentShaderSource = "#version 110 core\n"
//    "out vec4 FragColor;\n"
//    "void main()\n"
//    "{\n"
//    "   FragColor = vec4(1.0f, 0.2f, 0.5f, 1.0f);\n"
//    "}\0";
const char *vertexShaderSource = 
    "#version 130\n"
    "in vec3 aPos;\n"
    "void main()\n"
    "{\n"
    "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
    "}\0";
const char *fragmentShaderSource = 
    "#version 130\n"
    "out vec4 FragColor;\n"
    "void main()\n"
    "{\n"
    "   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
    "}\n\0";

const char *fragmentShaderBlue = 
    "#version 130\n"
    "out vec4 FragColor;\n"
    "void main()\n"
    "{\n"
    "   FragColor = vec4(0.0f, 0.0f, 1.0f, 1.0f);\n"
    "}\n\0";

void firstProgram() {
        //For single trianlge
//    float vertices[] = {
//       -0.5f, -0.5f, 0.0f,
//        0.5f, -0.5f, 0.0f,
//        0.0f,  0.5f, 0.0f 
//    };
    
    //For Rectangle we should use EBO - Element Buffer Object to draw indexes.
    float vertices[] = {
        0.5f,  0.5f, 0.0f,  //top right
        0.5f, -0.5f, 0.0f,  //bottom right
       -0.5f, -0.5f, 0.0f,  //bottom left
       -0.5f,  0.5f, 0.0f   //bottom right
    };
    unsigned int indices[] = {
       0, 1, 3, //first triangle
       1, 2, 3  //second triangle
    };
    fprintf(
        stdout,
        "INFO: OpenGL Version: %s\n",
        glGetString(GL_VERSION)
        );
//    glutInitContextProfile(GLUT_CORE_PROFILE);
//    glutInitContextProfile(GLUT_CORE_PROFILE); 
//    glutInitContextVersion(3, 5); 
    // create the window
    sf::Window window(sf::VideoMode(800, 600), "OpenGL", sf::Style::Default, sf::ContextSettings(32));
    window.setVerticalSyncEnabled(true);

    // activate the window
    window.setActive(true);

    // load resources, initialize the OpenGL states, ...

    // run the main loop
    bool running = true;
    
    //Generating VAO - Vertex Array Object
    unsigned int VAO;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);
    
    unsigned int VBO;       //stands for vertex buffer object
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    /*
     * 
            GL_STATIC_DRAW: the data will most likely not change at all or very rarely.
            GL_DYNAMIC_DRAW: the data is likely to change a lot.
            GL_STREAM_DRAW: the data will change every time it is drawn.

     */
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    
    unsigned int EBO;       //stand for element buffer object.
    glGenBuffers(1, &EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
    
    /**
     * The vertex shader is one of the shaders that are programmable by people like us. 
     * Modern OpenGL requires that we at least set up a vertex and fragment shader 
     * if we want to do some rendering so we will briefly introduce shaders 
     * and configure two very simple shaders for drawing our first triangle. 
     * In the next tutorial we'll discuss shaders in more detail. 
     */
    //Vertex Shader //For Triangle vertices
    unsigned int vertexShader;
    vertexShader = glCreateShader(GL_VERTEX_SHADER);    //Since we create Vertex Shader we pass GL_VERTEX_SHADER as argument.
    //Next we attach the shader source code to the shader object and compile the shader:
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);
    
    //checking for errors
    int success;
    char infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if(!success) {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }
    //End error checking
    
    
    //Fragment Shader //For Triangle color
    unsigned int fragmentShader;
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);    //Since we create Fragment Shader we pass GL_FRAGMENT_SHADER as argument
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);
    //Error Checking
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if(!success) {
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
    }
    //end error checking for fragment shader.
    
    //shader program
    /**
     * A shader program object is the final linked version of multiple shaders combined.
     */
    unsigned int shaderProgram;
    shaderProgram = glCreateProgram();
    //attach shaders to the program
    glAttachShader(shaderProgram, vertexShader);        
    glAttachShader(shaderProgram, fragmentShader);
    // Setup Vertex Attributes  [NEW]
    glBindAttribLocation(shaderProgram, 0, "vertexPosition_modelspace");
    //link the program
    glLinkProgram(shaderProgram);
    
    //check for errors for shaderProgram.
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if(!success) {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::PROGRAMM::LINKED_FAILED\n";
    }
    
//    glUseProgram(shaderProgram);  - The result of our program now can be used in the game loop to draw.
    //we can now delete those shaders which are linked in the shaderProgram
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
    
    
    //Tell the OpenGL how to interpret data before rendering.
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    
    
    while (running)
    {
        // handle events
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                // end the program
                running = false;
            }
            else if (event.type == sf::Event::Resized)
            {
                // adjust the viewport when the window is resized
                glViewport(0, 0, event.size.width, event.size.height);
            }
        }

        // clear the buffers

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        // draw...
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);  //Draw only lines !Not Default option
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);  //Draw only lines Default option
        glUseProgram(shaderProgram);
        glBindVertexArray(VAO);
//        glDrawArrays(GL_TRIANGLES, 0, 3);     //For single trinagle
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        // end the current frame (internally swaps the front and back buffers)
        window.display();
    }
}

bool errorChecking(GLuint obj, GLenum pname) {
    int success;
    char infoLog[512];
    switch(pname) {
        case GL_COMPILE_STATUS:
            glGetShaderiv(obj, pname, &success);
            break;
        case GL_LINK_STATUS:
            glGetProgramiv(obj, pname, &success);
            break;
    }
    
    if(!success) {
        switch(pname) {
            case GL_COMPILE_STATUS:
                glGetShaderInfoLog(obj, 512, NULL, infoLog);
                break;
            case GL_LINK_STATUS:
                glGetProgramInfoLog(obj, 512, NULL, infoLog);
                break;
        }
        return false;
    }
    return true;
}

void exampleOne() {
    float firstTriangle[] = {
        //first triangle
        -0.8f, -0.8f, 0.0f,
        -0.2f, -0.8f, 0.0f,
        -0.5f,  0.1f, 0.0f,
        //second triangle
         0.8f,  0.8f, 0.0f,
         0.2f,  0.8f, 0.0f,
         0.5f,  -0.1f, 0.0f
    };

    
    sf::Window window(sf::VideoMode(800, 600), "OpenGL", sf::Style::Default, sf::ContextSettings(32));
    window.setVerticalSyncEnabled(true);
    window.setActive(true);
    
    GLuint VAO, VBO;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);
    
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(firstTriangle), firstTriangle, GL_STATIC_DRAW);
    
    //create Vertex, Fragment Shaders
    GLuint vertexShader, fragmentShader;
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);
    //Error check
    if(!errorChecking(vertexShader, GL_COMPILE_STATUS)) {
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n";
        return;
    }
    
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);
    //Error Check
    if(!errorChecking(fragmentShader, GL_COMPILE_STATUS)) {
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n";
        return;
    }
    //////////end vertex creations
    
    //Shader Program
    GLuint shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    //glBindAttribLocation() - needed because layout = 0 in GLSL is not avaible on the current version only version 330 or more can use layout
    glBindAttribLocation(shaderProgram, 0, "vertexPosition_modelspace");
    glLinkProgram(shaderProgram);
    //error check
    if(!errorChecking(shaderProgram, GL_LINK_STATUS)) {
        std::cout << "ERROR::SHADER::PROGRAM::LINK_FAILED\n";
        return;
    }
    
    //delete shaders
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
    
    //Tell OpenGL how to treat data before rendering
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    
    bool running = true;
    
    while (running)
    {
        // handle events
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                // end the program
                running = false;
            }
            else if (event.type == sf::Event::Resized)
            {
                // adjust the viewport when the window is resized
                glViewport(0, 0, event.size.width, event.size.height);
            }
        }

        // clear the buffers

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        // draw...
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);  //Draw only lines !Not Default option
//        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);  //Draw only lines Default option
        glUseProgram(shaderProgram);
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 6);     //For single trinagle
//        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        // end the current frame (internally swaps the front and back buffers)
        window.display();
    }
    
}

void exampleTwo() {
    float firstTriangle[] = {
        //first triangle
        -0.8f, -0.8f, 0.0f,
        -0.2f, -0.8f, 0.0f,
        -0.5f,  0.1f, 0.0f,
         
    };
    float secondTriangle[] = {
        0.8f,  0.8f, 0.0f,
        0.2f,  0.8f, 0.0f,
        0.5f,  -0.1f, 0.0f
    };
    
    sf::Window window(sf::VideoMode(800, 600), "OpenGL", sf::Style::Default, sf::ContextSettings(32));
    window.setVerticalSyncEnabled(true);
    window.setActive(true);
    
    GLuint VAO, VBO;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);
    
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(firstTriangle), firstTriangle, GL_STATIC_DRAW);
    //Tell OpenGL how to treat data before rendering
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    
    GLuint VAO2, VBO2;
    glGenVertexArrays(1, &VAO2);
    glBindVertexArray(VAO2);
    
    glGenBuffers(1, &VBO2);
    glBindBuffer(GL_ARRAY_BUFFER, VBO2);
    glBufferData(GL_ARRAY_BUFFER, sizeof(secondTriangle), secondTriangle, GL_STATIC_DRAW);
    //Tell OpenGL how to treat data before rendering
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    
    //create Vertex, Fragment Shaders
    GLuint vertexShader, fragmentShader;
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);
    //Error check
    if(!errorChecking(vertexShader, GL_COMPILE_STATUS)) {
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n";
        return;
    }
    
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);
    //Error Check
    if(!errorChecking(fragmentShader, GL_COMPILE_STATUS)) {
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n";
        return;
    }
    //////////end vertex creations
    
    //Shader Program
    GLuint shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    //glBindAttribLocation() - needed because layout = 0 in GLSL is not avaible on the current version only version 330 or more can use layout
    glBindAttribLocation(shaderProgram, 0, "vertexPosition_modelspace");
    glLinkProgram(shaderProgram);
    //error check
    if(!errorChecking(shaderProgram, GL_LINK_STATUS)) {
        std::cout << "ERROR::SHADER::PROGRAM::LINK_FAILED\n";
        return;
    }
    
    //delete shaders
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
    
    bool running = true;
    
    while (running)
    {
        // handle events
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                // end the program
                running = false;
            }
            else if (event.type == sf::Event::Resized)
            {
                // adjust the viewport when the window is resized
                glViewport(0, 0, event.size.width, event.size.height);
            }
        }

        // clear the buffers

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        // draw...
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);  //Draw only lines !Not Default option
//        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);  //Draw only lines Default option
        glUseProgram(shaderProgram);
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);     //For single trinagle
        glBindVertexArray(VAO2);
        glDrawArrays(GL_TRIANGLES, 0, 3);     //For single trinagle
//        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        // end the current frame (internally swaps the front and back buffers)
        window.display();
    }
}

void exampleThree() {
    float firstTriangle[] = {
        //first triangle
        -0.8f, -0.8f, 0.0f,
        -0.2f, -0.8f, 0.0f,
        -0.5f,  0.1f, 0.0f,
         
    };
    float secondTriangle[] = {
        0.8f,  0.8f, 0.0f,
        0.2f,  0.8f, 0.0f,
        0.5f,  -0.1f, 0.0f
    };
    
    sf::Window window(sf::VideoMode(800, 600), "OpenGL", sf::Style::Default, sf::ContextSettings(32));
    window.setVerticalSyncEnabled(true);
    window.setActive(true);
    
    GLuint VAO, VBO;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);
    
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(firstTriangle), firstTriangle, GL_STATIC_DRAW);
    //Tell OpenGL how to treat data before rendering
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    
    GLuint VAO2, VBO2;
    glGenVertexArrays(1, &VAO2);
    glBindVertexArray(VAO2);
    
    glGenBuffers(1, &VBO2);
    glBindBuffer(GL_ARRAY_BUFFER, VBO2);
    glBufferData(GL_ARRAY_BUFFER, sizeof(secondTriangle), secondTriangle, GL_STATIC_DRAW);
    //Tell OpenGL how to treat data before rendering
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    
    //create Vertex, Fragment Shaders
    GLuint vertexShader, fragmentShader, fragmentBlue;
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);
    //Error check
    if(!errorChecking(vertexShader, GL_COMPILE_STATUS)) {
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n";
        return;
    }
    
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);
    //Error Check
    if(!errorChecking(fragmentShader, GL_COMPILE_STATUS)) {
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n";
        return;
    }
    
    fragmentBlue = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentBlue, 1, &fragmentShaderBlue, NULL);
    glCompileShader(fragmentBlue);
    //ErrorCheck
    if(!errorChecking(fragmentBlue, GL_COMPILE_STATUS)) {
        std::cout << "ERROR::SHADER::FRAGMENT_BLUE::COMPILATION_FAILED\n";
        return;
    }
    //////////end vertex creations
    
    //Shader Program
    GLuint shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    //glBindAttribLocation() - needed because layout = 0 in GLSL is not avaible on the current version only version 330 or more can use layout
    glBindAttribLocation(shaderProgram, 0, "vertexPosition_modelspace");
    glLinkProgram(shaderProgram);
    //error check
    if(!errorChecking(shaderProgram, GL_LINK_STATUS)) {
        std::cout << "ERROR::SHADER::PROGRAM::LINK_FAILED\n";
        return;
    }
    
    GLuint shaderProgramBlue = glCreateProgram();
    glAttachShader(shaderProgramBlue, vertexShader);
    glAttachShader(shaderProgramBlue, fragmentBlue);
    glBindAttribLocation(shaderProgramBlue, 0, "vertexPosition_modelspace");
    glLinkProgram(shaderProgramBlue);
    //error check
    if(!errorChecking(shaderProgramBlue, GL_LINK_STATUS)) {
        std::cout << "ERROR::SHADER::PROGRAM_BLUE::LINK_FAILED\n";
        return;
    }
    
    //delete shaders
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
    glDeleteShader(fragmentBlue);
    
    bool running = true;
    
    while (running)
    {
        // handle events
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                // end the program
                running = false;
            }
            else if (event.type == sf::Event::Resized)
            {
                // adjust the viewport when the window is resized
                glViewport(0, 0, event.size.width, event.size.height);
            }
        }

        // clear the buffers

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        // draw...
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);  //Draw only lines !Not Default option
//        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);  //Draw only lines Default option
        glUseProgram(shaderProgram);
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);     //For single trinagle
        glUseProgram(shaderProgramBlue);
        glBindVertexArray(VAO2);
        glDrawArrays(GL_TRIANGLES, 0, 3);     //For single trinagle
//        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        // end the current frame (internally swaps the front and back buffers)
        window.display();
    }
}
#endif /* CH1_H */

