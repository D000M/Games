/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   MulthiMethods.h
 * Author: default
 *
 * Created on May 23, 2019, 4:04 PM
 */

#ifndef MULTHIMETHODS_H
#define MULTHIMETHODS_H

#include <iostream>
#include <typeindex>
#include <map>
#include <utility>

namespace MultiMethod {
    
    struct GameObject;
    
    void collide(GameObject& first, GameObject& second);
    
    struct GameObject {
        
        virtual std::type_index type() const = 0;
        
        virtual void collide(GameObject& other) {
            MultiMethod::collide(*this, other);
        }
    };
    
    //Curioslly recurring template pattern
    template<typename T>
    struct GameObjectImpl : GameObject {
        std::type_index type() const override {
            return typeid(T);
        }
    };
    
    struct Planet : GameObjectImpl<Planet> {};
    struct Asteroid : GameObjectImpl<Asteroid> {};
    struct Spaceship : GameObjectImpl<Spaceship> {};
    
    void spaseshipPlanet() { std::cout << "Spaceship lands on planet\n"; }
    void asteroidPlanet() { std::cout << "Asteroid burns up in the atmosphere\n"; }
    void asteroidSpaceship() { std::cout << "Asteroid hits and destroyes spaceship\n"; }
    
    /**
     * map with 
     * key std::pair<std::type_index, std::type_index>
     * value pointer to the void function with no arguments.
     */
    std::map<std::pair<std::type_index, std::type_index>, void(*)()> outcomes {
        {{typeid(Spaceship), typeid(Planet)}, spaseshipPlanet},
        {{typeid(Asteroid), typeid(Planet)}, asteroidPlanet},
        {{typeid(Asteroid), typeid(Spaceship)}, asteroidSpaceship}
    };
    
    void collide(GameObject& first, GameObject& second) {
        auto it = outcomes.find({first.type(), second.type()});
        if(it == outcomes.end()) {
            it = outcomes.find({second.type(), first.type()});
            if(it == outcomes.end()) {
                std::cout << "Object didnt collide!\n";
                return;
            }
        }
        it->second();   //Call the function pointer from the map
    }
    
    void testMulthimetod() {
        Asteroid asteroid;
        Planet planet;
        Spaceship ship;
        
        collide(planet, ship);
        collide(asteroid, planet);
        collide(asteroid, ship);
        collide(planet, asteroid);
        collide(planet, planet);
    }
}

#endif /* MULTHIMETHODS_H */

