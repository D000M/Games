/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   HandMadeStateMachine.h
 * Author: default
 *
 * Created on May 21, 2019, 4:46 PM
 */

#ifndef HANDMADESTATEMACHINE_H
#define HANDMADESTATEMACHINE_H

#include <iosfwd>
#include <vector>
#include <map>
#include <iostream>


namespace HandMadeStateMachine {
    
    enum class State {
        offHook,
        connecting,
        connected,
        onHold,
        onHook
    };
    inline std::ostream& operator << (std::ostream& os, const State& obj) {
        switch(obj) {
            case State::offHook:
                os << "of the hook";
                break;
            case State::connecting:
                os << "connecting";
                break;
            case State::connected:
                os << "connected";
                break;
            case State::onHold:
                os << "on hold";
                break;
            case State::onHook:
                os << "on the hook";
                break;
            default:
                break;
        }
        return os;
    }
    
    enum class Trigger {
        callDialed,
        hungUp,
        callConnected,
        placedOnHold,
        takenOffHold,
        leftMessage,
        stopUsingPhone
    };
    
    inline std::ostream& operator << (std::ostream& os, const Trigger& obj) {
        switch(obj) {
            case Trigger::callDialed:
                os << "call dialed";
                break;
            case Trigger::hungUp:
                os << "hung up";
                break;
            case Trigger::callConnected:
                os << "call connected";
                break;
            case Trigger::placedOnHold:
                os << "placed on hold";
                break;
            case Trigger::takenOffHold:
                os << "taken off hold";
                break;
            case Trigger::leftMessage:
                os << "left message";
                break;
            case Trigger::stopUsingPhone:
                os << "putting phone on hook";
                break;
            default:
                break;
        }
        return os;
    }
    
    void testHandMadeSM() {
        std::map<State, std::vector<std::pair<Trigger, State>>> rules;
        
        rules[State::offHook] = {
            { Trigger::callDialed, State::connecting },
            { Trigger::stopUsingPhone, State::onHook }
        };
        
        rules[State::connecting] = {
            { Trigger::hungUp, State::offHook },
            { Trigger::callConnected, State::connected }
        };
        
        rules[State::connected] = {
            { Trigger::leftMessage, State::offHook },
            { Trigger::hungUp, State::offHook },
            { Trigger::placedOnHold, State::onHold }
        };
        
        rules[State::onHold] = {
            { Trigger::takenOffHold, State::connected },
            { Trigger::hungUp, State::offHook }
        };
        
        State currentState{ State::offHook };
        State exitState{ State::onHook };
        
        
        while(true) {
            std::cout << "The Phone is currently: " << currentState << "\n";
            
        selectTrigger:  //goto functionality
            std::cout << "Select Trigger:\n";
            int i = 0;
            for(auto item : rules[currentState]) {
                std::cout << i++ << ". " << item.first << "\n";
            }
            int input;
            std::cin >> input;
            if(input < 0 || (input + 1) > rules[currentState].size()) {
                std::cout << "Incorrect Option: Try Again!\n";
                goto selectTrigger; //back to selectTrigger label.
            }
            
            currentState = rules[currentState][input].second;
            if(currentState == exitState) {
                break;
            }
        }
        
        std::cout << "We are done using the phone.\n";
    }
}


#endif /* HANDMADESTATEMACHINE_H */

