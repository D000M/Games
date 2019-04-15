/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Serialization.h
 * Author: default
 *
 * Created on April 15, 2019, 4:14 PM
 */

#ifndef SERIALIZATION_H
#define SERIALIZATION_H

//Use boost serialization
//#include <boost/serialization/serialization.hpp>
//#include <boost/archive/text_iarchive.hpp>
//#include <boost/archive/text_oarchive.hpp>
#include <sstream>
#include <boost/serialization/access.hpp>
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>

namespace PrototypeSerialization {
    
    struct Address {
        std::string street, city;
        int suite;
        
        Address() {}
        
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

    private:
        friend class boost::serialization::access;
        
        template<typename T>
        void serialize(T& archive, const unsigned int version) {
            archive& street;
            archive& city;
            archive& suite;
        }
    };
    struct Contact {
        std::string name;
        Address* address;
        
        Contact() {}
        
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
    private:
        friend class boost::serialization::access;
        
        template<typename T>
        void serialize(T& archive, const unsigned int version) {
            archive& name;
            archive& address;
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
        //lambda
        auto clone = [](const Contact& c) {
            //Serialize
            std::ostringstream oss;
            boost::archive::text_oarchive oa{oss};
            oa << c;
            std::string s = oss.str();
            std::cout << s << std::endl;
            
            //Deserialize
            std::istringstream iss{s};
            boost::archive::text_iarchive ia{iss};
            Contact result;
            ia >> result;
            return result;
        };  //end of lambda
        
        auto john = EmployeeFactory::newMainOfficeEmployee("John", 55);
        auto vanya = clone(*john);
        vanya.name = "Vanya";
        std::cout << *john << std::endl << vanya << std::endl;
    }
}


#endif /* SERIALIZATION_H */

