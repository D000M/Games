/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   MediatorEx.h
 * Author: default
 *
 * Created on May 20, 2019, 2:39 PM
 */

#ifndef MEDIATOREX_H
#define MEDIATOREX_H

#include <vector>
#include <iostream>


namespace MediatorEx {
    
    
    
    struct IParticipant {
        virtual void addToValue(int val) = 0;
    };
    struct PartMediator {
        std::vector<IParticipant*> participants;
    };
    struct Participant : IParticipant {
        int value{0};
        PartMediator& mediator;
        
        Participant(PartMediator& mediator)
            : mediator(mediator) {
            mediator.participants.push_back(this);
        }

        void say(int value) {
            for(int i = 0; i < mediator.participants.size(); i++) {
                if(this != mediator.participants.at(i)) {
                    std::cout << "i: " << i << " ";
                    mediator.participants.at(i)->addToValue(value);
                }
            }
            std::cout << std::endl;
        }
        void addToValue(int val) override {
            value += val;
        }

    };
    
    void testMediatorEx() {
        PartMediator mediator;
        Participant p1{mediator};
        Participant p2{mediator};
        Participant p3{mediator};
        Participant p4{mediator};
        Participant p5{mediator};
        p1.say(5);
        for(int i = 0; i < mediator.participants.size(); i++) {
            Participant* pPtr = reinterpret_cast<Participant*>(mediator.participants.at(i));
            if(pPtr) {
                std::cout << i << ": " << pPtr->value << std::endl;
            }
        }
        p2.say(10);
        for(int i = 0; i < mediator.participants.size(); i++) {
            Participant* pPtr = dynamic_cast<Participant*>(mediator.participants.at(i));
            if(pPtr) {
                std::cout << i << ": " << pPtr->value << std::endl;
            }
        }
        p3.say(15);
        for(int i = 0; i < mediator.participants.size(); i++) {
            Participant* pPtr = dynamic_cast<Participant*>(mediator.participants.at(i));
            if(pPtr) {
                std::cout << i << ": " << pPtr->value << std::endl;
            }
        }
//        p4.say(20);
//        p5.say(25);
    }
}


#endif /* MEDIATOREX_H */

