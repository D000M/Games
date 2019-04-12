/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   LiskovExample.h
 * Author: default
 *
 * Created on April 11, 2019, 1:04 PM
 */

#ifndef LISKOVEXAMPLE_H
#define LISKOVEXAMPLE_H

#include <iostream>


namespace Liskov {

    class Rectangle {
    protected:
        int width, height;
    public:
        Rectangle(int width, int height) :
            width(width), height(height) {
        }

        
        int getHeight() const {
            return height;
        }

        int getWidth() const {
            return width;
        }
        virtual void setHeight(int height) {
            this->height = height;
        }

        virtual void setWidth(int width) {
            this->width = width;
        }

        int area() const {return width * height;}
    };  //end Rectangle
    
    class Square : public Rectangle {
    public:
        Square(int side) :
            Rectangle(side, side) {
        }
        void setHeight(int height) override { this->width = this->height = height; }
        void setWidth(int width) override { this->width = this->height = width; }

    };

    class RectangleFactory {
    public:
        static Rectangle createRectangle(int w, int h);
        static Rectangle createSquare(int side);
    };
    
    void process(Rectangle& rect) {
        int w = rect.getWidth();
        rect.setHeight(10);

        std::cout << "exptected area: " << (w * 10) 
                  << ", got " << rect.area() << std::endl;
    }

    void simpleTestOne() {
        Rectangle r{3, 4};
        process(r);
        
        //Now we have problem, we should have factory for a this kind of stuff
        Square sq{5};
        process(sq);
    }
    
}   //End of namespace Liskov

#endif /* LISKOVEXAMPLE_H */

