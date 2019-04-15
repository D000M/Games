/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   RecordKeeping.h
 * Author: default
 *
 * Created on April 15, 2019, 3:02 PM
 */

#ifndef RECORDKEEPING_H
#define RECORDKEEPING_H

#include <string>
#include <iostream>

namespace RecordKeeping {
    struct Address {
        std::string street, city;
        int suite;
        
        Address(const std::string& street, const std::string& city, int suite)
            : street(street), city(city), suite(suite) {
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

        friend std::ostream& operator<<(std::ostream& os, const Contact& obj) {
            os << obj.name << " " << *obj.address;
            return os;
        }

    };
    
    
    void testContacts() {
        //Problems when we use Address* instead of Address copy object.
//        Contact john{"John Dow", Address{"Strelbishte", "Sofia", 46}};
//        Contact vanya{"Vanya Dimitrova", Address{"Strelbishte", "Sofia", 45}};
//        std::cout << john << std::endl << vanya << std::endl;
//        
//        //We can do something like that
//        Contact eli = john;
//        eli.name = "Elinna";
//        eli.address.suite = 55;
//        std::cout << eli << std::endl;
        
        //////////////////////^^^^^^^^ this up there work because of using Address address; .Stop working when we use Address* ptrAddress;
        
        //Ptr problem
        Contact john("John Dow", new Address("Srelbishte", "Sofia", 46));
        Contact vanya = john;   //shallow copy, if we want Address* to work we need deep copy approach -->Check Prototype folder

        vanya.name = "Vanya Dimitrova";
        vanya.address->suite = 55;
        std::cout << john << std::endl << vanya << std::endl;
        //When we derefernce the ptrAddress, we have the same suite for both persons because john address is now the same as vanya.
    }
}

#endif /* RECORDKEEPING_H */

