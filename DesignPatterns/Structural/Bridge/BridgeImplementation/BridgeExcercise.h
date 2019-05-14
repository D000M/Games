/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   BridgeExcercise.h
 * Author: default
 *
 * Created on April 25, 2019, 10:45 AM
 */

#ifndef BRIDGEEXCERCISE_H
#define BRIDGEEXCERCISE_H
#include <string>
#include <iostream>

namespace BridgeExcercise {
    
    struct Renderer2 {
        virtual std::string what_to_render_as(std::string name) const = 0;
    };
    struct VectorRenderer2 : Renderer2 {
        std::string what_to_render_as(std::string name) const override {
            return "Drawing " + name +  " as lines";
        }
    };
    struct RasterRenderer2 : Renderer2 {
        std::string what_to_render_as(std::string name) const override {
            return "Drawing " + name + " as pixels"; 
        }
        
    };
    
    struct Shape2
    {   
        const Renderer2& render;
        std::string name;
        Shape2(const Renderer2& render)
            : render(render) {
        }

    };

    struct Triangle : Shape2
    {
        Triangle(const Renderer2& rend) : Shape2(rend)
        {
            name = "Triangle";
        }
        std::string str() const {
            return render.what_to_render_as(name);
        }
    };

    struct Square : Shape2
    {
        Square(const Renderer2& rend) : Shape2(rend)
        {
            name = "Square";
        }
        std::string str() const {
            return render.what_to_render_as(name);
        }
    };

    struct VectorSquare : Square
    {
        std::string str() const
        {
            return "Drawing " + name + " as lines";
        }
    };

    struct RasterSquare : Square
    {
        std::string str() const
        {
            return "Drawing " + name + " as pixels";
        }
    };
    
    
    
    void testBrdigeEx( ) {
        std::cout << Triangle(RasterRenderer2()).str();
    }
}

#endif /* BRIDGEEXCERCISE_H */

