/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   ObserverEx.h
 * Author: default
 *
 * Created on May 21, 2019, 1:50 PM
 */

#ifndef OBSERVEREX_H
#define OBSERVEREX_H

#include <vector>
#include <iostream>
#include <algorithm>


/**
 * Observer Coding Exercise

    Imagine a game where one or more rats can attack a player. 
  * Each individual rat has an attack  value of 1. 
 *  However, rats attack as a swarm, so each rat's attack  
 *  value is equal to the total number of rats in play.

     Given that a rat enters play through the constructor and leaves play (dies)
 *   via its destructor, please implement the Game  and Rat  classes so that, 
 *   at any point in the game, the attack  value of a rat is always consistent.
 */
namespace ObserverEx {
    
    struct Rat;
    
    struct IRat {
        virtual void increaseAttack(int increase) = 0;
    };
    
    struct Game {
        //todo
        std::vector<IRat*> observers;
        
        void notify() {
            for(auto elem : observers) {
                elem->increaseAttack(observers.size());
            }
        }
        
        void unsubscribe(IRat& rat) {
            observers.erase(std::remove(observers.begin(), observers.end(), &rat), observers.end());
            notify();
        }
        
    };
    
    struct Rat : IRat {
        Game& game;
        int attack{1};
        
        Rat(Game& game) : game{game} {
            //todo obviously
            std::cout << "Rat Created!\n";
            game.observers.emplace_back(this);
            game.notify();
        }
        
        ~Rat() {
            // rat dies here.
            std::cout << "Rat Destroyed!\n";
            game.unsubscribe(*this);
        }
        
        void increaseAttack(int increase) override {
            attack = increase;
        }

        friend std::ostream& operator<<(std::ostream& os, const Rat& obj) {
            // Write obj to stream
            os << "Rat attack: " << obj.attack;
            return os;
        }

    };
    
    void testObserverEx() {
        Game game;
        Rat *r1 = new Rat{game};
        std::cout << *r1 << std::endl;
        Rat *r2 = new Rat{game};
        std::cout << *r1 << ", " << *r2 << std::endl;
        Rat *r3 = new Rat{game};
        delete r2;
        r2 = nullptr;
        delete r1;
        r1 = nullptr;
        std::cout << *r3 << std::endl;
        Rat *r4 = new Rat{game};
        std::cout << *r3 << ", " << *r4 << std::endl;
        delete r3;
        delete r4;
    }
}

#endif /* OBSERVEREX_H */

