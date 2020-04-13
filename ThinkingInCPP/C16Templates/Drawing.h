/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Drawing.h
 * Author: default
 *
 * Created on December 21, 2019, 3:48 PM
 */

#ifndef DRAWING_H
#define DRAWING_H

#include "RealStash.h"
#include "Shapes.h"
#include "RealStack.h"
#include <vector>

//A drawing is primariy container of shape
class Drawing : public Stash<IShape> {
    public:
        ~Drawing() {
            std::cout << "~Drawing()\n";
        }
};

class Plan : public Stack<IShape> {
public:
    ~Plan() {
        std::cout << "~Plan()\n";
    }
};

//A schematic is different container of IShape, using std::vector
class Schematic : public std::vector<IShape*> {
public:
    ~Schematic() {
        std::cout << "~Schematic()\n";
    }
};

//A function template
template<class Iter>
void drawAll(Iter start, Iter end) {
    while(start != end) {
        (*start)->draw();
        start++;
    }
}

void testDrawing() {
    //Each type of container has different interface
    Drawing d;
    d.add( new ConcreteCirle);
    d.add( new ConcreteSquare);
    d.add( new ConcreteLine);
    
    Plan p;
    p.push(new ConcreteLine);
    p.push(new ConcreteSquare);
    p.push(new ConcreteCirle);
    
    Schematic s;
    s.emplace_back(new ConcreteSquare());
    s.emplace_back(new ConcreteCirle());
    s.emplace_back(new ConcreteLine());
    
    IShape* shapeArr[] = {
        new ConcreteCirle, new ConcreteSquare, new ConcreteLine
    };
    
    //iterators and the template function allow them to be treated generically
    std::cout << "\nDrawing d\n";
    drawAll(d.begin(), d.end());
    std::cout << "\nPlan p\n";
    drawAll(p.begin(), p.end());
    std::cout << "\nSchematic s\n";
    drawAll(s.begin(), s.end());
    std::cout << "\nArray shapeArr\n";
    //Even works with array pointers
    drawAll(shapeArr, shapeArr + sizeof(shapeArr) / sizeof(*shapeArr));
    for(int i = 0; i < sizeof(shapeArr) / sizeof(*shapeArr); i++) {
        delete shapeArr[i];
        shapeArr[i] = nullptr;
    }

    for(int i = 0; i < s.size(); i++) {
        delete s.at(i);
    }
    std::cout << "\nEnd Of Test\n";
}
#endif /* DRAWING_H */

