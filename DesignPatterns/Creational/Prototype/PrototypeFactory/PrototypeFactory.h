/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   PrototypeFactory.h
 * Author: default
 *
 * Created on April 15, 2019, 3:46 PM
 */

#ifndef PROTOTYPEFACTORY_H
#define PROTOTYPEFACTORY_H

#include <memory>


namespace PrototypeFactory {
    struct Address {
        std::string street, city;
        int suite;
        
        Address(const std::string& street, const std::string& city, int suite)
            : street(street), city(city), suite(suite) {
        }
        Address(const Address& other)
            : street{other.street},
              city{other.city},
              suite{other.suite} {         
        }
        ~Address() {
            std::cout << "Addres: " << suite << " Destroyed!\n";
        }      
        friend std::ostream& operator<<(std::ostream& os, const Address& obj) {
            os << obj.city << " " << obj.street << " " << obj.suite; 
            return os;
        }

    };
    struct Contact {
        std::string name;
        Address* address;
        Contact(std::string name, Address* address)
            : name(name), address(address) {
        }
        Contact(const Contact& other)
            : name{other.name},
              address{new Address{*other.address}} {        
        }
        ~Contact() {
            std::cout << "Contact: " << name << " Destroyed!\n";
            delete address;
        }      
        friend std::ostream& operator<<(std::ostream& os, const Contact& obj) {
            os << obj.name << " " << *obj.address;
            return os;
        }

    };
    
    //Factory
    class EmployeeFactory {
    public:
        static std::unique_ptr<Contact> newMainOfficeEmployee(const std::string& name, const int suite) {
            //our prototype
            static Contact p{"", new Address{"Strelbishte", "Sofia", 0}};
            return newEmployee(name, suite, p);
        }
    private:
        static std::unique_ptr<Contact> newEmployee(const std::string& name, const int suite, const Contact& prototype) {
            auto result = std::make_unique<Contact>(prototype);
            result->name = name;
            result->address->suite = suite;
            return result;
        }
    };
    
    void testContacts() {
        auto john = EmployeeFactory::newMainOfficeEmployee("John", 55);
        auto vanya = EmployeeFactory::newMainOfficeEmployee("Vanya", 102);
        std::cout << *john << std::endl << *vanya << std::endl;
    }
}

#endif /* PROTOTYPEFACTORY_H */

