/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   ProprtyProxy.h
 * Author: default
 *
 * Created on May 14, 2019, 4:16 PM
 */

#ifndef PROPRTYPROXY_H
#define PROPRTYPROXY_H

#include <iostream>


namespace Property {
    
    template<typename T>
    struct Property {
        T value;
        
        Property(T val) {
            *this = val;    //Calls operator = 
        }
        
        //Get Property
        operator T() {
            return value;
        }
        
        //Set Property
        T operator = (T val) {
            std::cout << "Assignemnt\n";
            return value = val;
        }
    };
    
    struct Creature {
        Property<int> strength{10};
        Property<int> agility{5};
    };
    
    void testProperty() {
        Creature c;
        c.strength = 11;
        int x = c.agility;
    }
}


#endif /* PROPRTYPROXY_H */

