/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   StateEx.h
 * Author: default
 *
 * Created on May 22, 2019, 11:39 AM
 */

#ifndef STATEEX_H
#define STATEEX_H

/**
State Coding Exercise

A combination lock is a lock that opens after the right digits have been entered. 
A lock is preprogrammed with a combination (e.g., 12345 ) and the user is expected to enter this combination to unlock the lock.

The lock has a status  field that indicates the state of the lock. The rules are:

    If the lock has just been locked (or at startup), the status is LOCKED.
    If a digit has been entered, that digit is shown on the screen. As the user enters more digits, they are added to Status.
    If the user has entered the correct sequence of digits, the lock status changes to OPEN.
    If the user enters an incorrect sequence of digits, the lock status changes to ERROR.

Please implement the CombinationLock  class to enable this behavior. Be sure to test both correct and incorrect inputs.

Here is an example unit test for the lock:

    CombinationLock cl({1,2,3});
    ASSERT_EQ("LOCKED", cl.status);
    cl.enter_digit(1);
    ASSERT_EQ("1", cl.status);
    cl.enter_digit(2);
    ASSERT_EQ("12", cl.status);
    cl.enter_digit(3);
    ASSERT_EQ("OPEN", cl.status);
 */

#include <iostream>
#include <vector>
#include <string>
#include <iosfwd>
#include <sstream>
using namespace std;


namespace StateEx {

    enum class State {
        locked,     //startup or just lock state.
        open,
        error
    };
    
    inline std::ostream& operator << (std::ostream& os, const State& obj) {
        switch(obj) {
            case State::locked:
                os << "LOCKED";
                break;
            case State::open:
                os << "OPEN";
                break;
            case State::error:
                os << "ERROR";
                break;
        }
        return os;
    }

    class CombinationLock
    {
        vector<int> combination;
        int pos{0};
    public:
        string status;
        std::ostringstream oss;
        State currentState { State::locked };
        
        CombinationLock(const vector<int> &combination) : combination(combination) {
            oss << currentState;
            status = oss.str();
            pos = 0;
        }

        void enter_digit(int digit)
        {
          // TODO
            if(pos == 0) {
                status = "";
            }
            if(currentState == State::locked) {
                oss.str("");
                oss.clear();
                oss << digit;
                status.append(oss.str());
                if(digit == combination.at(pos)) {
                    if(pos == combination.size() - 1) {
                        currentState = State::open;
                    }
                    else {
                        pos++;
                    }
                }
                else {
                    currentState = State::error;
                }
            }
            if(currentState == State::open) {
                reset();
                oss << State::open;
                status.append(oss.str());
                currentState = State::locked;
            }
            if(currentState == State::error) {
                reset();
                oss << State::error;
                status.append(oss.str());
                currentState = State::locked;
            }
         }  //end enter_digit()
        
        void reset() {
            pos = 0;
            status = "";
            oss.str("");
            oss.clear();
        }
    };
    
    void testStateEx() {
        CombinationLock cl({1, 2, 3});
        std::cout << cl.status << std::endl;
        cl.enter_digit(1);
        std::cout << cl.status << std::endl;
        cl.enter_digit(3);
        std::cout << cl.status << std::endl;
        cl.enter_digit(3);    
        std::cout << cl.status << std::endl;
        cl.enter_digit(1);
        std::cout << cl.status << std::endl;
        cl.enter_digit(2);
        std::cout << cl.status << std::endl;
        cl.enter_digit(3);
        std::cout << cl.status << std::endl;
    }
}

#endif /* STATEEX_H */

