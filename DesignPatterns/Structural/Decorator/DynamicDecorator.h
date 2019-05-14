/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   DynamicDecorator.h
 * Author: default
 *
 * Created on May 9, 2019, 12:45 PM
 */

#ifndef DYNAMICDECORATOR_H
#define DYNAMICDECORATOR_H

#include <string>
#include <iostream>


namespace DynamicDecorator {

    struct Shape {
        virtual std::string toStr() const = 0;
    };
    
    struct Circle : public Shape {
        
        float radius;
        
        Circle() {}
        
        Circle(float radius) : radius{radius} {}
        
        void resize(float scale) {
            radius *= scale;
        }
        
        std::string toStr() const override {
            std::ostringstream oss;
            oss << "A circle of radius: " << radius;
            return oss.str();
        }

    };
    
    struct Square : Shape {
        float side;
        Square() {}
        Square(float side) : side{side} {}
        
        std::string toStr() const override {
            std::ostringstream oss;
            oss << "A square with side: " << side;
            return oss.str();
        }
    };
    
    //Dynamic Decorator for runtime when we need some decorator. We cant use member functions of concrete classes... We have to use
    //Static Decorator for that purpose
    
    struct ColoredShape : Shape {
        Shape& shape;
        std::string color;
        
        ColoredShape(Shape& shape, const std::string& color) : shape{shape}, color{color} {}
        
        std::string toStr() const override{
            std::ostringstream oss;
            oss << shape.toStr() << " has the color: " << color;
            return oss.str();
        }

    };
    struct TransparentShape : Shape {
        Shape& shape;
        int transparency;
        
        TransparentShape(Shape& shape, int transparency) :
            shape(shape), transparency(transparency) {
        }
        
        std::string toStr() const override {
            std::ostringstream oss;
            oss << shape.toStr() << " has " 
                                 << static_cast<float>(transparency) / 255.f * 100.f  //return transparency in percent
                                 << "%";  
            return oss.str();
        }

    };
    
    void testDynamicDecorator() {
        Square square{5};
        ColoredShape redSquare{square, "RED"};
        
        std::cout << square.toStr() << std::endl;
        std::cout << redSquare.toStr() << std::endl;
        
        TransparentShape mySquare{redSquare, 51};
        std::cout << mySquare.toStr() << std::endl;
    }
    
    
    //Static Decorator
    template<typename T>
    struct ColoredShape2 : T {      //Inherit from template class
        //Way to be sure that the template argument is desired class in our case Shape is base of T
        //We should use static assert with std::is_base_of<> method
        static_assert(std::is_base_of<Shape, T>::value, "Template Argument Must be Shape");
        
        //Functionality
        std::string color;
        ColoredShape2() {}
        
        //For able to use TransparentShape2<ColoredShape2<Square>> sq{10, "color", 52}; //size, color, transparent
        template<typename ...Args>
        ColoredShape2(const std::string& color, Args ...args)       //next call the base class T
            : T(std::forward<Args>(args)...)
              ,color{color} {} 
        
        std::string toStr() const override {
            std::ostringstream oss;
            oss << T::toStr() << " has the color: " << color;
            return oss.str();
        }
    };
    //Static Decorator
    template<typename T>
    struct TransparentShape2 : T {      //Inherit from template class
        //Way to be sure that the template argument is desired class in our case Shape is base of T
        //We should use static assert with std::is_base_of<> method
        static_assert(std::is_base_of<Shape, T>::value, "Template Argument Must be Shape");
        
        //Functionality
        int transparency;
        TransparentShape2() {}
        
        //For able to use TransparentShape2<ColoredShape2<Square>> sq{10, "color", 52}; //size, color, transparent
        template<typename ...Args>
        TransparentShape2(const int transparency, Args ...args)       //next call the base class T
            : T(std::forward<Args>(args)...)
              ,transparency{transparency} {} 
        
        std::string toStr() const override {
            std::ostringstream oss;
            oss << T::toStr() << " has " 
                              << static_cast<float>(transparency) / 255.f * 100.f  //return transparency in percent
                              << "%";
            return oss.str();
        }
    };
    
    void testStaticDecorator() {
        ColoredShape2<Circle> greenCircle("Green", 5);
        //We can now use Circle member resize, with dynamic decorator we cant
        greenCircle.resize(10);
        std::cout << greenCircle.toStr() << std::endl;
        
        TransparentShape2<ColoredShape2<Square>> square{70, "Red", 7};
        std::cout << square.toStr() << std::endl;
    }
}

#endif /* DYNAMICDECORATOR_H */

