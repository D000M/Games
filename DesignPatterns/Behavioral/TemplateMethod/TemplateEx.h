/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   TemplateEx.h
 * Author: default
 *
 * Created on May 22, 2019, 4:46 PM
 */

#ifndef TEMPLATEEX_H
#define TEMPLATEEX_H

#include <iostream>
#include <vector>
#include <complex>
#include <tuple>
using namespace std;


/**
Template Method Coding Exercise


 * Imagine a typical collectible card game which has cards representing creatures. 
 * Each creature has two values: Attack and Health. 
 * Creatures can fight each other, 
 * dealing their Attack damage, 
 * thereby reducing their opponent's health.


 * The class CardGame implements the logic for two creatures fighting one another. 
 * However, the exact mechanics of how damage is dealt is different:

    
 * TemporaryCardDamage : 
 * In some games (e.g., Magic: the Gathering), 
 * unless the creature has been killed, 
 * its health returns to the original value at the end of combat.
    
 * PermanentCardDamage : 
 * In other games (e.g., Hearthstone), 
 * health damage persists.


 * You are asked to implement classes TemporaryCardDamageGame  
 * and PermanentCardDamageGame  
 * that would allow us to simulate combat between creatures.


 * Some examples:

    
 * With temporary damage, creatures 1/2 and 1/3 can never kill one another. 
 * With permanent damage, second creature will win after 2 rounds of combat.
    
 * With either temporary or permanent damage, 
 * two 2/2 creatures kill one another.
 */

namespace TemplateEx {
    struct Creature {
        
        int attack, health;
        
        Creature(int attack, int health)
            : attack(attack), health(health) {
        }

    };
    
    struct CardGame {
        vector<Creature> creatures;
        
        CardGame(const vector<Creature>& creatures)
            : creatures(creatures) {
        }
        
        // return the index of the creature that won (is a live)
        // example:
        // - creature1 alive, creature2 dead, return creature1
        // - creature1 dead, creature2 alive, return creature2
        // - no clear winner: return -1
        int combat(int creature1, int creature2) {
            //todo
            hit(creatures[creature1], creatures[creature2]);
            
            if(creatures[creature1].health <= 0 && creatures[creature2].health <= 0) {
                return -1;
            }
            if(creatures[creature1].health > 0 && creatures[creature2].health > 0) {
                return -1;
            }
            else if(creatures[creature1].health > 0) {
                return creature1;
            }
            else {
                return creature2;
            }
            
        }
        
        virtual void hit(Creature& attacker, Creature& other) = 0;
    }; //end struct CardGame
    
    struct TemporaryCardDamageGame : CardGame {
        
        TemporaryCardDamageGame(const vector<Creature>& creatures)
            : CardGame(creatures) {
        }
        
        void hit(Creature& attacker, Creature& other) override {
            //todo
            attacker.health -= other.attack;
            other.health -= attacker.attack;
        }
    };
    
    struct PermanentCardDamageGame : CardGame {
        bool winner{false};
        PermanentCardDamageGame(const vector<Creature>& creatures)
            : CardGame(creatures) {
        }

        void hit(Creature& attacker, Creature& other) override {
            //todo
                attacker.health -= other.attack;
                other.health -= attacker.attack;
            
        }
    };
    
    void testTemplateEx() {
        std::vector<Creature> creatures{ { Creature(1, 2)}, {Creature(1, 3) } };
        TemporaryCardDamageGame tempGame{creatures};
        std::cout << "TempDamage: " <<tempGame.combat(0, 1) << std::endl;
        
        PermanentCardDamageGame permGame{creatures};
        std::cout << "PermDamage: " <<permGame.combat(0, 1);
    }
}

#endif /* TEMPLATEEX_H */

