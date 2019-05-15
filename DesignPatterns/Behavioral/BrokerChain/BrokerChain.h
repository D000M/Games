/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   BrokerChain.h
 * Author: default
 *
 * Created on May 15, 2019, 10:35 AM
 */

#ifndef BROKERCHAIN_H
#define BROKERCHAIN_H

#include <boost/signals2.hpp>
#include <iostream>
//Much more sophisticated chain of responsibility pattern
//Using boost::signal2
//Event Broker = different design patterns, chain of responsibility + observer(signals2) + command query separation(Splitting commands and query) 
namespace Broker {
    
    struct Query {  //Request some information about the creature.
        std::string creatureName;
        enum Argument { attack, defense} argument;  //Define and declare variable argument
        int result;
        Query(const std::string& creatureName, Argument argument, int result)
            : creatureName(creatureName), argument(argument), result(result) {
        }

    };
    
    struct Game {   //Mediator (design pattern)
        boost::signals2::signal<void(Query&)> queries;
    };
    
    class Creature {
        Game& game;
        std::string name;
        int attack, defense;
    public:
        Creature(Game& game, const std::string& name, int attack, int defense)
            : game(game), name(name), attack(attack), defense(defense) {
        }
        
        int getAttack() const {
            Query q{name, Query::Argument::attack, attack}; //Query
            game.queries(q);
            return q.result;
        }
        int getDefense() const {
            Query q{name, Query::Argument::defense, defense};
            game.queries(q);
            return q.result;
        }
        std::string getName() const {
            return name;
        }
        friend std::ostream& operator<<(std::ostream& os, const Creature& obj) {
            // Write obj to stream
            os << "name: " << obj.name << ", attack: " << obj.getAttack() << ", defense: " << obj.getDefense();
            return os;
        }
    };
    
    class CreatureModifier {
        Game& game;
        Creature& creature;
    public:
        CreatureModifier(Game& game, Creature& creature)
            : game(game), creature(creature) {
        }
        virtual ~CreatureModifier() = default;
    };
    class DoubleAttackModifier : public CreatureModifier {
        boost::signals2::connection conn;
    public:
        DoubleAttackModifier(Game& game, Creature& creature)
            : CreatureModifier(game, creature) {
                //Using game queries whenenever someone asks for attack value.
                conn = game.queries.connect([&](Query& q) {
                    if(q.creatureName == creature.getName() &&
                            q.argument == Query::Argument::attack) {
                        q.result *= 2;
                    }
                });
        }
            
        ~DoubleAttackModifier() {
            conn.disconnect();
        }

    };
    
    void testBrokerChain() {
        Game game;
        Creature goblin{game, "Strong Goblin", 2, 2};
        std::cout << goblin << std::endl;
        
        {
            DoubleAttackModifier dam{game, goblin};
            std::cout << goblin << std::endl;
        }
        std::cout << goblin << std::endl;
    }
}

#endif /* BROKERCHAIN_H */

