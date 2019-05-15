/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   PointerChain.h
 * Author: default
 *
 * Created on May 15, 2019, 10:07 AM
 */

#ifndef POINTERCHAIN_H
#define POINTERCHAIN_H

#include <string>

//Old example from Gang Of Four, we can use now linked list or vector
namespace PtrChain {
    
    struct Creature {
        std::string name;
        int attack, defense;
        
        Creature(std::string name, int attack, int defense)
            : name(name), attack(attack), defense(defense) {
        }
        friend std::ostream& operator<<(std::ostream& os, const Creature& obj) {
            os << "name: " << obj.name << ", attack: " << obj.attack << ", defense: " << obj.defense;
            return os;
        }

    };
    
    class CreatureModifier {
        CreatureModifier* next{nullptr};
    protected:
        Creature& creature;
    public:
        CreatureModifier(Creature& creature)
            : creature(creature) {
        }
        void add(CreatureModifier* cm) {
            if(next) {
                next->add(cm); 
            } 
            else {
                next = cm;
            }
        }
        virtual void handle() {
            if(next) {
                next->handle();
            }
        }
    };
    
    class DoubleAttackModifier : public CreatureModifier {
    public:
        DoubleAttackModifier(Creature& creature)
            : CreatureModifier(creature) {
        }

        void handle() override{
            creature.attack *= 2;
            CreatureModifier::handle(); //This allows us to walk through the chain of responsibility.
        }
    };
    class IncreaseDefenseModifier : public CreatureModifier {
    public:
        IncreaseDefenseModifier(Creature& creature)
            : CreatureModifier(creature) {
        }

        void handle() override{
            if(creature.attack <= 2) {
                creature.defense++;
            }
            CreatureModifier::handle(); //This allows us to walk through the chain of responsibility.
        }
    };
    
    class NoModifier : public CreatureModifier {
    public:
        NoModifier(Creature& creature)
            : CreatureModifier(creature) {
        }
        void handle() override {
            //Empty to cut the chain of responsibility, add it on begining.
        }
    };
    
    void testPtrChain() {
        Creature goblin{"goblin", 1, 1};
        CreatureModifier root{goblin};  //Start of the singly linked list
        DoubleAttackModifier r1{goblin};
        DoubleAttackModifier r1_2{goblin};
        IncreaseDefenseModifier r2{goblin};
        
        //Uncomment for test.
//        NoModifier curse{goblin};
//        root.add(&curse);
        root.add(&r1);
        root.add(&r1_2);
        root.add(&r2);
        root.handle();
        std::cout << goblin << std::endl;
    }
}

#endif /* POINTERCHAIN_H */

