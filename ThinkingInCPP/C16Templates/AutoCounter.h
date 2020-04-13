/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   AutoCounter.h
 * Author: default
 *
 * Created on December 21, 2019, 11:08 AM
 */

#ifndef AUTOCOUNTER_H
#define AUTOCOUNTER_H

#include <set>
#include "../utils/require.h"
#include <iostream>
#include <ostream>

class AutoCounter {
    static int count;
    int id;
    
    class CleanupCheck {
            std::set<AutoCounter*> trace;
        public:
            ~CleanupCheck() {
                std::cout << "~CleanupCheck" << std::endl;
                require(trace.size() == 0, "All AutoCounter objects not cleanup");
            }
            void add(AutoCounter* ac) {
                trace.insert(ac);
            }
            void remove(AutoCounter* ac) {
                require(trace.erase(ac) == 1, "Attempt to delete AutoCounter twice"); 
            }
        
    };  //end of class CleanupCheck
    
    static CleanupCheck verifier;
    
    //Make the constructor private, use singleton pattern
    AutoCounter() : id{count++} {
        verifier.add(this);     //Register itself
        std::cout << "created [" << id << "]\n";
    }
    
    //Prevent assignment and copy constructions
    AutoCounter(const AutoCounter&);
    void operator = (const AutoCounter&);
    
public:
    //You can only create objects with this
    static AutoCounter* create() {
        return new AutoCounter;
    }
    ~AutoCounter() {
        std::cout << "destroying[" << id << "]\n";
        verifier.remove(this);
    }
    //Print both objects and pointers
    friend std::ostream& operator << (std::ostream& out, const AutoCounter& obj) {
        return out << "AutoCoutner ref: " << obj.id;
    }
    friend std::ostream& operator << (std::ostream& out, const AutoCounter* obj) {
        return out << "AutoCounter ptr: " << obj->id;
    }
};

#endif /* AUTOCOUNTER_H */

