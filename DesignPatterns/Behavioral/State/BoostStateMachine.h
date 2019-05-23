/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   BoostStateMachine.h
 * Author: default
 *
 * Created on May 22, 2019, 10:29 AM
 */

#ifndef BOOSTSTATEMACHINE_H
#define BOOSTSTATEMACHINE_H
//msm - meta state machine
//Back end
//Defined structures of the state machine
#include <boost/msm/back/state_machine.hpp>

//Front end part that actually executes the state machine
#include <boost/msm/front/state_machine_def.hpp>
#include <boost/msm/front/functor_row.hpp>
#include <vector>
#include <string>
#include <iostream>

namespace msm = boost::msm;
namespace mpl = boost::mpl;     //Meta Programming library
using namespace msm::front;

namespace BoostSM {
    
    std::vector<std::string> stateNames {
      "off hook"s,
      "connecting"s,
      "connected"s,
      "on hold"s,
      "destroyed"s
    };
    
    //Triggers
    struct CallDialed { };
    struct HungUp { };
    struct CallConnected { };
    struct PlacedOnHold { };
    struct TakenOffHold { };
    struct LeftMessage { };
    struct PhoneThrownIntoWall { };
    
    //Inherit from state_machine_def which needs CRP (Curiosly Recurring pattern)
    struct PhoneStateMachine : state_machine_def<PhoneStateMachine> {
        
        bool angry{true};
        
        //States will be here
        struct OffHook : state<> {};    //End OffHook state
        
        struct Connecting : state<> {
            
            //Method from state<>
            template<typename Event, typename FSM>
            void on_entry(const Event& event, FSM& fsm) {
                std::cout << "We are connecting...\n";
            }
            
        }; //End Connecting State
        
        struct Connected : state<> {};  //End Connected state
        struct OnHold : state<> {};     //End OnHold state
        struct PhoneDestroyed : state<> {}; //End PhoneDestroyed state
        
        //ACTION for the state PhoneDestroyed
        struct PhoneBeingDestroyed {
            template<class EVT, class FSM, class SourceState, class TriggerState>
            void operator () (EVT const&, FSM&, SourceState&, TriggerState&) {
                std::cout << "Phone breaks into million piece's" << std::endl;
            }
        };
        
        //Guard condition what can happen if we destroy the phone
        struct CanDestroyPhone {
            template<class EVT, class FSM, class SoureState, class TriggerState>
            bool operator () (EVT const&, FSM& fsm, SoureState&, TriggerState) {
                return fsm.angry;
            }
        };
        //Using boost::mpl (meta programming library)
        //Building a vector of rows of type list.
        //start, event, target, action, guard
        //This struct should be called exactly as it is transition_table and must inherit mpl::vector
        struct transition_table : mpl::vector <
            //Row<class SOURCE, class EVENT, class TARGET, class ACTION = none, class GUARD = none>
            //OffHook - starting state, 
            //CallDialed(what happens, whats the trigger) CallDialed<<trigger,
            //Connecting, final, the outcome state. our Result.
            Row<OffHook, CallDialed, Connecting>,   
            Row<Connecting, CallConnected, Connected>, 
            Row<Connected, PlacedOnHold, OnHold>, 
            Row<OnHold, PhoneThrownIntoWall, PhoneDestroyed, PhoneBeingDestroyed, CanDestroyPhone>
        > { };  //End struct TransitionTable
        
        typedef OffHook initial_state;
        template<class FSM, class Event>
        void no_transition(Event const& e, FSM&, int state) {
            std::cout << "No transition from state: " << stateNames[state]
                    << " on event: " << typeid(e).name() << std::endl;
        }
    };
    
    
    
    void testBoostSM() {
        msm::back::state_machine<PhoneStateMachine> phone;
        
        auto info = [&]() {
            auto i = phone.current_state()[0];
            std::cout << "The Phone is currently: " << stateNames[i] << "\n";
        };
        
        info();
        phone.process_event(CallDialed{});
        info();
        phone.process_event(CallConnected{});
        info();
        phone.process_event(PlacedOnHold{});
        info();
        phone.process_event(PhoneThrownIntoWall{});
        info();
        
        //No transition from the state PhoneThrownIntoWall, so guard call function no_transition() is called.
        phone.process_event(CallDialed{});
    }

}

#endif /* BOOSTSTATEMACHINE_H */

