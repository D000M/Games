/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   ClassicStateMachine.h
 * Author: default
 *
 * Created on May 21, 2019, 3:07 PM
 */

#ifndef CLASSICSTATEMACHINE_H
#define CLASSICSTATEMACHINE_H

#include <iostream>


namespace ClassicStateMachine {
    
    struct LightSwitch;
    
    struct State {
        
        virtual void on(LightSwitch* ls) {
            std::cout << "Light is Already ON\n";
        }
        virtual void off(LightSwitch* ls) {
            std::cout << "Light is Already OFF\n";
        }
        
    };
    
    struct OnState : State {
        OnState() {
            std::cout << "OnState Created!\n";
            std::cout << "Light is turn on!\n";
        }
        ~OnState() {
            std::cout << "OnState Destroyed!\n";
        }
        void off(LightSwitch* ls) override;

    };
    
    struct OffState : State {
        OffState() {
            std::cout << "OffState Created!\n";
            std::cout << "Light is turn off!\n";
        }
        ~OffState() {
            std::cout << "OffState Destroyed!\n";
        }
        void on(LightSwitch* ls) override;

    };
    
    class LightSwitch {
        State* state;
    public:
        LightSwitch() {
            std::cout << "LightSwitch Created!\n";
            state = new OffState();
        }
        ~LightSwitch() {
            std::cout << "LightSwitch Destroyed!\n";
        }
        void setState(State* state) {
            this->state = state;
        }
        
        void on() {
            state->on(this);
        }
        void off() {
            state->off(this);
        }
    };
    
    void OnState::off(LightSwitch* ls) {
        std::cout << "Switching Light OFF...\n";
        ls->setState(new OffState());
        delete this;
    }
    void OffState::on(LightSwitch* ls) {
        std::cout << "Switching Light ON...\n";
        ls->setState(new OnState());
        delete this;
    }
    
    void testClassicSM() {
        LightSwitch ls;
        ls.on();
        ls.off();
        ls.off();
    }
}

#endif /* CLASSICSTATEMACHINE_H */

