/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   HandmadeFlyweight.h
 * Author: default
 *
 * Created on May 14, 2019, 12:33 PM
 */

#ifndef HANDMADEFLYWEIGHT_H
#define HANDMADEFLYWEIGHT_H

#include <stdint.h>
#include <boost/bimap.hpp>
#include <boost/flyweight.hpp>
#include <string>
#include <iostream>


namespace Handmade {
    
    using key = uint16_t;
    
    struct User {
        User(const std::string& first, const std::string& last) 
         : firstName{add(first)},
           lastName{add(last)} {}
           
        const std::string& getFirstName() const {
            return names.left.find(firstName)->second;
        }
        const std::string& getLastName() const {
            return names.left.find(lastName)->second;
        }
        friend std::ostream& operator<<(std::ostream& os, const User& obj) {
            // Write obj to stream
            os << "First Name: " << obj.getFirstName() << "(" << obj.firstName << ")" << ", Last Name: " << obj.getLastName() << "(" << obj.lastName << ")";
            return os;
        }

    protected:
        key firstName, lastName;
        //Map from boost which allows us to search from both sides, K -> V or V -> K
        static boost::bimap<key, std::string> names;    
        static key seed;
        
        static key add(const std::string& s) {
            auto it = names.right.find(s);
            if(it == names.right.end()) {   //The element was not found. Create new element and add it to the map.
                key id = ++seed;
                names.insert({seed, s});
                return id;
            }
            return it->second;
        }
        
        
    };
    
    key User::seed{0};
    boost::bimap<key, std::string> User::names{};
    
    void testHandmadeFlyweight() {
        User u{"John", "Smith"};
        User u2{"Jane", "Smith"};
        User u3{"John", "Dark"};
        std::cout << u << std::endl << u2 << std::endl << u3 << std::endl;
    }
    
    //Boost Flyweight
    struct User2 {
        User2(const std::string& firstName, const std::string& secondName)
        : firstName(firstName), 
          secondName(secondName) {
        }

        boost::flyweight<std::string> firstName, secondName;
    };
    void testBoostFlyweight() {
        User2 u{"John", "Smith"};
        User2 u2{"Jane", "Smith"};
        
        std::cout << u.firstName << std::endl;
        std::cout << std::boolalpha;
        std::cout << (&u.firstName.get() == &u2.firstName.get()) << std::endl;      //Get the pointer to the string not the actual string
        std::cout << (&u.secondName.get() == &u2.secondName.get()) << std::endl;    //So we compare the address of the strings.
    }
}

#endif /* HANDMADEFLYWEIGHT_H */

