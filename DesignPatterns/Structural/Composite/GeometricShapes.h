/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   GeometricShapes.h
 * Author: default
 *
 * Created on April 25, 2019, 1:12 PM
 */

#ifndef GEOMETRICSHAPES_H
#define GEOMETRICSHAPES_H

#include <iostream>
#include <vector>


namespace GeoShapes {
    
    struct GraphicObject {
        virtual void draw() = 0;
    };
    struct Circle : GraphicObject {
        int circleId;
        Circle() {
            static int id = 0;
            circleId = id;
            id++;
        }
        void draw() override {
            std::cout << "Circle " << circleId << "\n";
        }
    };
    struct Group : GraphicObject {
        std::string name;
        std::vector<GraphicObject*> objects;
        
        Group(const std::string& name)
            : name(name) {
        }
        void draw() override {
            std::cout << "Group: " << name.c_str() << " contains: " << std::endl;
            for(auto&& obj : objects) {
                obj->draw();
            }
            std::cout << std::endl;
        }

    };
    
    void testComposite() {
        Group root("Root Group");
        Circle c1, c2, c3;
        root.objects.emplace_back(&c1);
        root.objects.emplace_back(&c2);
        std::cout << "Root:\n";
        root.draw();
        Group subGroup("Sub Group");
        subGroup.objects.emplace_back(&c3);
        std::cout << "Sub:\n";
        subGroup.draw();
        root.objects.emplace_back(&subGroup);
        std::cout << "Root + Sub:\n";
        root.draw();
        
    }
}

#endif /* GEOMETRICSHAPES_H */

