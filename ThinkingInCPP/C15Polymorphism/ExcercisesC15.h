/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   ExcercisesC15.h
 * Author: default
 *
 * Created on December 20, 2019, 1:26 PM
 */

#ifndef EXCERCISESC15_H
#define EXCERCISESC15_H

#include <iostream>

class ShapeC15 {
public:
    virtual void draw(){
        std::cout << "ShapeC15::draw() ";
    }
//    virtual void draw() = 0;
};
//void ShapeC15::draw() {
//    std::cout << "ShapeC15::draw() ";
//}
class Triangle : public ShapeC15 {
public:
    void draw() override {
        std::cout << "Triangle::draw()\n";
    }
};
class Circle : public ShapeC15 {
public: 
    void draw() override {
        std::cout << "Circle::draw()\n";
    }
    void testByValue() {
        std::cout << "Pass by value!\n";
    }
};
class Square : public ShapeC15 {
public:
    void draw() override {
        std::cout << "Square::draw()\n";
    }
};
void testEx01C15() {
    ShapeC15* arr[] = {new Triangle, new Circle, new Square};
    for (int i = 0; i < 3; i++) {
        arr[i]->draw();
        delete arr[i];
    }
//    ShapeC15 s;
    
}

void passByValueShape(ShapeC15 value) {
    
}
void testE03C15() {
    Circle c;
    passByValueShape(c);
}
#endif /* EXCERCISESC15_H */

