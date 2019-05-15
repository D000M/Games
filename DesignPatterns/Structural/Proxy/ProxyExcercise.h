/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   ProxyExcercise.h
 * Author: default
 *
 * Created on May 15, 2019, 9:46 AM
 */

#ifndef PROXYEXCERCISE_H
#define PROXYEXCERCISE_H

#include <string>
#include <ostream>


namespace ProxyEx {
    class Person {
        friend class ResponsiblePerson;
        int age;
    public:
        Person(int age) : age{age} {}
        
        int getAge() const {
            return age;
        }
        void setAge(int val) {
            this->age = val;
        }
        
        std::string drink() const { return "drinking"; }
        std::string drive() const { return "driving"; }
        std::string drinkAndDrive() const { return "driving while drunk"; }
    };
    
    class ResponsiblePerson {
        Person person;
    public:
        ResponsiblePerson(const Person& person) : person{person} {}
        
        std::string drink() const {
            if(person.getAge() < 18) {
                return "too young";
            }
            return person.drink();
        }
        std::string drive() const {
            if(person.getAge() < 16) {
                return "too young";
            }
            return person.drive();
        }
        std::string drinkAndDrive() const {
            return "dead";
        }
        int getAge() const {
            return person.getAge();
        }
        void setAge(int val) {
            person.setAge(val);
        }
    };
    
    void testPerson() {
        Person p{15};
        ResponsiblePerson rp{p};
        std::cout << rp.drink() << std::endl
                  << rp.drive() << std::endl
                  << rp.drinkAndDrive() << std::endl;
        
        rp.setAge(20);
        std::cout << rp.drink() << std::endl
                  << rp.drive() << std::endl
                  << rp.drinkAndDrive() << std::endl;
    }
}

#endif /* PROXYEXCERCISE_H */

