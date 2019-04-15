/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Prototype.h
 * Author: default
 *
 * Created on April 15, 2019, 3:22 PM
 */

#ifndef PROTOTYPE_H
#define PROTOTYPE_H

namespace Prototype {
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
            if(address != nullptr) {
                delete address;
                address = nullptr;
            }
        }      
        friend std::ostream& operator<<(std::ostream& os, const Contact& obj) {
            os << obj.name << " " << *obj.address;
            return os;
        }

    };
    
    
    void testContacts() {
        //Ptr problem
        Contact john("John Dow", new Address("Srelbishte", "Sofia", 46));
        Contact vanya{john};   //Deep Copy using copy constructors

        vanya.name = "Vanya Dimitrova";
        vanya.address->suite = 55;
        std::cout << john << std::endl << vanya << std::endl;
    }
}

#endif /* PROTOTYPE_H */

