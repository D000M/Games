/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Bridge.h
 * Author: default
 *
 * Created on April 25, 2019, 10:12 AM
 */

#ifndef BRIDGE_H
#define BRIDGE_H

#include <iostream>


//Bridge example for rendering shapes
//Few Shapes - Circle, Square...
//Renderer - RasterRenderer, VectorRenderer...
namespace BridgeImpl {
    
    struct Renderer {
        virtual void circleRenderer(float x, float y, float radius) = 0;
    };
    struct RasterRenderer : Renderer {
        void circleRenderer(float x, float y, float radius) override {
            std::cout << "Rasterizing a circle radius: " << radius << std::endl;
        }
    };
    struct VectorRenderer : Renderer {
        void circleRenderer(float x, float y, float radius) override {
            std::cout << "Drawing a vector Circle of a radius: " << radius << std::endl;
        }
    };
    
    struct Shape {
        protected:
            Renderer& renderer;         //Our Bridge Design
            Shape(Renderer& renderer) 
                : renderer(renderer) {
            }
        public:
            virtual void draw() = 0;
            virtual void resize(float factor) = 0;
    };
    struct Circle : Shape {
        float x, y, radius;
        Circle(Renderer& renderer, float x, float y, float radius)  //We can accept Vector, Raster or some other Renderer
            : Shape(renderer), x(x), y(y), radius(radius) {
        }
        void draw() override {
            renderer.circleRenderer(x, y, radius);
        }
        void resize(float factor) override {
            radius *= factor;
        }

    };
    
    void testBridge() {
        RasterRenderer rr;
        Circle crcl{rr, 5, 5, 5};
        crcl.draw();
        crcl.resize(1.75);
        crcl.draw();
    }
}


#endif /* BRIDGE_H */

