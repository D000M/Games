/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   FactoryExcercise.h
 * Author: default
 *
 * Created on April 12, 2019, 4:58 PM
 */

#ifndef FACTORYEXCERCISE_H
#define FACTORYEXCERCISE_H

#include <string>


namespace AbstractFactory {
    struct Person {
        int id;
        std::string name;
        
        friend std::ostream& operator<<(std::ostream& os, const Person& obj) {
            os << obj.name << " " << obj.id;
            return os;
        }

    };
    class PersonFactory {
    public:
        static Person create_person(const std::string& name) {
            static int id = 0;
            return {id++, name};
        }
    };
    
    void testPersons() {
        Person p0 = PersonFactory::create_person("First");
        Person p1 = PersonFactory::create_person("Second");
        Person p2 = PersonFactory::create_person("Third");
        
        std::cout << p0 << std::endl << p1 << std::endl << p2 << std::endl;
    }
}


#endif /* FACTORYEXCERCISE_H */

