/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   GLSLhelp.h
 * Author: default
 *
 * Created on September 19, 2018, 4:08 PM
 */

#ifndef GLSLHELP_H
#define GLSLHELP_H

#include <SDL2/SDL_opengl.h>
#include <GL/glext.h>
#include <SFML/System/Time.hpp>
#include <SFML/System/Clock.hpp>
#include <valarray>


//Typical shader structure
/*
  
#version version_number
in type in_variable_name;
in type in_variable_name;

out type out_variable_name;
  
uniform type uniform_name;
  
void main()
{
  // process input(s) and do some weird graphics stuff
  ...
  // output processed stuff to output variable
  out_variable_name = weird_stuff_we_processed;
}

*/

//check Maximum vertex attributes for given platform.
void checkMaxShaders() {
    int maxAttributes;
    glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &maxAttributes);
    std::cout << "Maximum vertex attributes for this platform: " << maxAttributes << std::endl;
}



const char *vertexShaderSource2 = {
        "#version 130\n"
        "in vec3 aPos;\n"
        "out vec4 vertexColor;\n"
        "void main()\n"
        "{\n"
        "   gl_Position = vec4(aPos, 1.0);\n"
        "   vertexColor = vec4(0.5, 0.0, 0.0, 1.0);\n"  //set to dark-red color.
        "}\0"
};

const char *fragmentShaderSource2 = {
      "#version 130\n"
      "out vec4 FragColor;\n"
          "in vec4 vertexColor;\n"  //the input variable from vertexShader (same name and same type)
          "void main()\n"
          "{\n"
          "     FragColor = vertexColor;"
          "}\0"
};

const char *vertexShaderSource3 = {
        "#version 130\n"
        "in vec3 aPos;\n"
        "in vec3 aColor;\n"
        "out vec3 ourColor;\n"
        "void main()\n"
        "{\n"
        "   gl_Position = vec4(aPos, 1.0);\n"
        "   ourColor = aColor;\n"
        "}\0"
};
//uniforms
const char *fragmentColorSource = {
    "#version 130\n"
    "out vec4 FragColor;\n"
    "in vec3 ourColor;\n"
    "void main()\n"
    "{\n"
    "   FragColor = vec4(ourColor, 1.0f);\n"
    "}\n\0"
};

void testDarkColor() {
            //For single trianlge
    float vertices[] = {
       -0.5f, -0.5f, 0.0f,
        0.5f, -0.5f, 0.0f,
        0.0f,  0.5f, 0.0f 
    };
    
    //For Rectangle we should use EBO - Element Buffer Object to draw indexes.
//    float vertices[] = {
//        0.5f,  0.5f, 0.0f,  //top right
//        0.5f, -0.5f, 0.0f,  //bottom right
//       -0.5f, -0.5f, 0.0f,  //bottom left
//       -0.5f,  0.5f, 0.0f   //bottom right
//    };
//    unsigned int indices[] = {
//       0, 1, 3, //first triangle
//       1, 2, 3  //second triangle
//    };
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
    
//    unsigned int EBO;       //stand for element buffer object.
//    glGenBuffers(1, &EBO);
//    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
//    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
    
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
    glShaderSource(vertexShader, 1, &vertexShaderSource2, NULL);
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
    glShaderSource(fragmentShader, 1, &fragmentShaderSource2, NULL);
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
    glBindAttribLocation(shaderProgram, 1, "vertexPosition_modelspace");
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
    //position attributes
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    
    //color attributes
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    
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
        glDrawArrays(GL_TRIANGLES, 0, 3);     //For single trinagle
//        glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0);
        // end the current frame (internally swaps the front and back buffers)
        window.display();
    }
}

void testUniform() {
    float vertices[] = {
        //positions        //colors     
       -0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f,         //bottom left
        0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f,         //bottom right
        0.0f,  0.5f, 0.0f, 0.0f, 0.0f, 1.0f          //top
    };
        
    //For Rectangle we should use EBO - Element Buffer Object to draw indexes.
//    float vertices[] = {
//        0.5f,  0.5f, 0.0f,  //top right
//        0.5f, -0.5f, 0.0f,  //bottom right
//       -0.5f, -0.5f, 0.0f,  //bottom left
//       -0.5f,  0.5f, 0.0f   //bottom right
//    };
//    unsigned int indices[] = {
//       0, 1, 3, //first triangle
//       1, 2, 3  //second triangle
//    };
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
    
//    unsigned int EBO;       //stand for element buffer object.
//    glGenBuffers(1, &EBO);
//    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
//    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
    
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
    glShaderSource(vertexShader, 1, &vertexShaderSource3, NULL);
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
    glShaderSource(fragmentShader, 1, &fragmentColorSource, NULL);
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
    glBindAttribLocation(shaderProgram, 1, "vertexPosition_modelspace");
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
    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // color attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    
    sf::Clock clock;
    glUseProgram(shaderProgram);
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
//        sf::Time myTime = clock.getElapsedTime();
//        float timeValue = myTime.asSeconds();
//        float greenValue = sin(timeValue) / 2.0f + 0.5f;
//        float redValue = sin(timeValue) / 2.0f + 0.35f;
//        float blueValue = sin(timeValue) / 2.0f + 0.25f;
//        int vertexColorLocation = glGetUniformLocation(shaderProgram, "ourColor");
//        glUseProgram(shaderProgram);
//        glUniform4f(vertexColorLocation, redValue, 0.0f, blueValue, 1.0f);
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);     //For single trinagle
//        glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0);
        // end the current frame (internally swaps the front and back buffers)
        window.display();
    }
}
#endif /* GLSLHELP_H */

