/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   MyAbstractFactory.h
 * Author: default
 *
 * Created on April 15, 2019, 2:11 PM
 */

#ifndef MYABSTRACTFACTORY_H
#define MYABSTRACTFACTORY_H

#include <iostream>
#include <functional>
#include <memory>
#include <string>
#include <map>


namespace MonsterFctry {
    struct Monster {
        virtual ~Monster() {
            std::cout << "Monster Destroyed!\n";
        }
        virtual void createMonster(int health) = 0;
    };
    
    struct Troll : Monster {
        void createMonster(int health) override {
            std::cout << "Troll Created with health: " << health << ".\n";
        }
    };
    struct Goblin : Monster {
        void createMonster(int health) override {
            std::cout << "Goblin Created with health: " << health << ".\n";
        }
    };
    
    class MonsterFactory {
        std::map<std::string, std::function<std::unique_ptr<Monster>() > > monsterFactory;
    public:
        MonsterFactory() {
            
            monsterFactory["Troll"] = []() {
                auto troll = std::make_unique<Troll>();
                troll->createMonster(250);
                return troll;
            };
            
            monsterFactory["Goblin"] = []() {
                auto goblin = std::make_unique<Goblin>();
                goblin->createMonster(55);
                return goblin;
            };
        }
        
        //public method to return monster from the factory
        std::unique_ptr<Monster> create(const std::string& monsterType) {
            return monsterFactory[monsterType]();
        }
    };
    
    void testMonsterFactory() {
        MonsterFactory mfcry;
        auto troll = mfcry.create("Troll");
        auto goblin = mfcry.create("Goblin");
    }
}

#endif /* MYABSTRACTFACTORY_H */

