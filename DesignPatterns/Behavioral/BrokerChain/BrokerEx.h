/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   BrokerEx.h
 * Author: default
 *
 * Created on May 15, 2019, 12:13 PM
 */

#ifndef BROKEREX_H
#define BROKEREX_H

#include <vector>
#include <string>
#include <iostream>
#include <boost/signals2.hpp>
/**
Chain of Responsibility Coding Exercise

You are given a game scenario with classes Goblin  and GoblinKing . Please implement the following rules:

    A goblin has base 1 attack/1 defense (1/1), a goblin king is 3/3.
    When the Goblin King is in play, every other goblin gets +1 Attack.
    Goblins get +1 to Defense for every other Goblin in play (a GoblinKing is a Goblin!).

Example:

    Suppose you have 3 ordinary goblins in play. Each one is a 1/3 (1/1 + 0/2 defense bonus).
    A goblin king comes into play. Now every ordinary goblin is a 2/4 (1/1 + 0/3 defense bonus from each other + 1/0 from goblin king)
    Meanwhile, the goblin king itself is 3/6 (3/3 + 0/3 defense bonus from other goblins)

Here is an example of the kind of test that will be run on the system:

    Game game;
    Goblin goblin(game);
    game.creatures.push_back(&goblin);
    ASSERT_EQ(1, goblin.get_attack());
    ASSERT_EQ(1, goblin.get_defense());
 */
namespace BrokerEx {
    struct Creature;
        
    struct StatQuery {
        enum Statistic { attack, defense } statistic;
        int result;
        StatQuery(Statistic statistic, int result)
            : statistic(statistic), result(result) {
        }

    };
    
    struct Game {
        std::vector<Creature*> creatures;
    };
    
    struct Creature {
    protected:
        Game& game;
        int baseAttack, baseDefense;
        bool bIsKing;
    public:
        Creature(Game& game, int baseAttack, int baseDefense, bool isKing) 
            : game(game), baseAttack(baseAttack), baseDefense(baseDefense), bIsKing{isKing} {
                game.creatures.push_back(this);
        }
            
        virtual int getAttack() = 0;
        virtual int getDefense() = 0;
        
        bool getIsKing() const {
            return bIsKing;
        }
        friend std::ostream& operator<<(std::ostream& os, const Creature& obj) {
            // Write obj to stream
            os << "attack: " << obj.baseAttack << ", defense:" << obj.baseDefense;
            return os;
        }

    };
    
    class Goblin : public Creature {
    public:
        Goblin(Game& game, int baseAttack, int baseDefense, bool bIsKing)
            : Creature(game, baseAttack, baseDefense, bIsKing) {}
        Goblin(Game& game) 
            : Creature{game, 1, 1, false} {}
            
        int getAttack() override {
            StatQuery q{StatQuery::Statistic::attack, baseAttack};
            int addExtraAttack = 0;
            for(const auto& elem : game.creatures) {
                if(elem->getIsKing()) {
                    addExtraAttack++;
                }
            }
            return q.result + addExtraAttack;
        }
        int getDefense() override {
            StatQuery q{StatQuery::Statistic::defense, baseDefense};
            return q.result + game.creatures.size() - 1;
        }
        friend std::ostream& operator<<(std::ostream& os, Goblin& obj) {
            os << "Goblin: Attack: " << obj.getAttack() << ", Defense: " << obj.getDefense();
            return os;
        }

    };
    
    class GoblinKing : public Goblin {
    public:
        GoblinKing(Game& game) 
            : Goblin{game, 3, 3, true} {}
            
        int getAttack() override {
            StatQuery q{StatQuery::Statistic::attack, baseAttack};
            return q.result;
        }
        
        friend std::ostream& operator<<(std::ostream& os, GoblinKing& obj) {
            // Write obj to stream
            os << "Goblin King: Attack: " << obj.getAttack() << ", Defense: " << obj.getDefense();
            return os;
        }

    };
    
    void testBrokerEx() {
        Game game;
        Goblin goblin{game};
//        GoblinKing goblinKing{game};
//        game.creatures.push_back(&goblin);
//        game.creatures.push_back(&goblinKing);
        Goblin goblin2{game};
        Goblin goblin3{game};
        GoblinKing king{game};
//        Goblin goblin4{game};
        GoblinKing king2{game};
        std::cout << goblin << std::endl;
        std::cout << goblin2 << std::endl;
        std::cout << goblin3 << std::endl;        
        std::cout << king << std::endl;
        std::cout << king2 << std::endl;

    }
}

#endif /* BROKEREX_H */

