/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Shapes.h
 * Author: default
 *
 * Created on December 21, 2019, 3:45 PM
 */

#ifndef SHAPES_H
#define SHAPES_H

#include <iostream>

class IShape {
public:
    virtual void draw() = 0;
    virtual void erase() = 0;
    virtual ~IShape() {}
};

class ConcreteCirle : public IShape {
public:
    ConcreteCirle() {
        std::cout << "ConcreteCircle::ConcreteCircle()\n";
    }
    ~ConcreteCirle() {
        std::cout << "ConcreteCircle::~ConcreteCircle()\n";
    }
    void draw() override {
        std::cout << "ConcreteCircle::draw()\n";
    }
    void erase() override {
        std::cout << "ConcreteCircle::erase()\n";
    }
};

class ConcreteSquare : public IShape {
public:
    ConcreteSquare() {
        std::cout << "ConcreteSquare::ConcreteSquare()\n";
    }
    ~ConcreteSquare() {
        std::cout << "ConcreteSquare::~ConcreteSquare()\n";
    }
    void draw() override {
        std::cout << "ConcreteSquare::draw()\n";
    }
    void erase() override {
        std::cout << "ConcreteSquare::erase()\n";
    }
};

class ConcreteLine : public IShape {
public:
    ConcreteLine() {
        std::cout << "ConcreteLine::ConcreteLine()\n";
    }
    ~ConcreteLine() {
        std::cout << "ConcreteLine::~ConcreteLine()\n";
    }
    void draw() override {
        std::cout << "ConcreteLine::draw()\n";
    }
    void erase() override {
        std::cout << "ConcreteLine::erase()\n";
    }
};
#endif /* SHAPES_H */

