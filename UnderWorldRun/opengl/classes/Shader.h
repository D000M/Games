/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Shader.h
 * Author: default
 *
 * Created on September 28, 2018, 11:32 AM
 */

#ifndef SHADER_H
#define SHADER_H

#define GL_GLEXT_PROTOTYPES     //Define GL_GLTEXT_PROTOTYPES for gl to work.

#include <SFML/OpenGL.hpp>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

/**
 Shade Class use like this
 * Shader ourShader("path/to/shaders/shader.vs", "path/to/shaders/shader.fs");
 * 
 * while(...) {
 *      ourShader.use();
 *      ourShader.setFloat("someUniform", 1.0f);
 *      DrawStuff();
 *}
 */

class Shader {
public:
    //the program ID
    unsigned int ID;
    
    //constructor reads and build shader
    Shader(const GLchar* vertexPath, const GLchar* fragmentPath);

    //use/activate the shader
    void use();
    
    //utility uniform functions.
    void setBool(const std::string &name, bool value) const;
    void setInt(const std::string& name, int value) const;
    void setFloat(const std::string& name, float value) const;
    
private:

};

#endif /* SHADER_H */

