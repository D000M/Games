/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Person.cpp
 * Author: default
 * 
 * Created on April 11, 2019, 5:09 PM
 */

#include "Person.h"
#include "PersonBuilder.h"

namespace BuilderFacets {
    

    PersonBuilder Person::create() {
        return PersonBuilder();
    }

    void Person::setAnnualIncome(const int annualIncome) {
            this->annualIncome = annualIncome;
    }

    void Person::setCity(const std::string& city) {
        this->city = city;
    }

    void Person::setCompanyName(const std::string& companyName) {
        this->companyName = companyName;
    }

    void Person::setPosition(const std::string& position) {
        this->position = position;
    }

    void Person::setPostCode(const std::string& postCode) {
        this->postCode = postCode;
    }

    void Person::setStreetAddress(const std::string& streetAddress) {
        this->streetAddress = streetAddress;
    }
        
}
