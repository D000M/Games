/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Person.h
 * Author: default
 *
 * Created on April 11, 2019, 5:09 PM
 */

#ifndef PERSON_H
#define PERSON_H

#include <string>
#include <iostream>

class PersonBuilder;    //Forward declaration

namespace BuilderFacets {
    
    
    
    class Person {
        //address information for AddressBuilder
        std::string streetAddress, postCode, city;
        // employment   for Employment Builder
        std::string companyName, position;
        int annualIncome{0};

    public:
        static PersonBuilder create();
        
        friend class PersonBuilder;
        friend class PersonJobBuilder;
        friend class PersonAddressBuilder;
        
    public:
        void setAnnualIncome(const int annualIncome);

        void setCity(const std::string& city);

        void setCompanyName(const std::string& companyName);

        void setPosition(const std::string& position);

        void setPostCode(const std::string& postCode);

        void setStreetAddress(const std::string& streetAddress);

        friend std::ostream& operator<<(std::ostream& os, const Person& obj) {
            os << "Street Address: " << obj.streetAddress << "\nPost Code: " << obj.postCode
                    << "\nCity: " << obj.city << "\nCompany Name: " << obj.companyName << "\nPosition: " << obj.position
                    << "\nAnnual Income: " << obj.annualIncome << std::endl;
            return os;
        }

    };  //end of class Person
    
}   //end of namespace BuilderFacets

#endif /* PERSON_H */

