/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   PersonAddressBuilder.h
 * Author: default
 *
 * Created on April 11, 2019, 5:39 PM
 */

#ifndef PERSONADDRESSBUILDER_H
#define PERSONADDRESSBUILDER_H

#include "PersonBuilder.h"

class PersonAddressBuilder : public PersonBuilderBase {
    
    using self = PersonAddressBuilder;
    
    public:
    explicit PersonAddressBuilder(BuilderFacets::Person& person)
        : PersonBuilderBase(person) {
    }
        
    self& atStreet(const std::string& streetAddress) {
        person.setStreetAddress(streetAddress);
        return *this;
    }  
    self& inCity(const std::string& city) {
        person.setCity(city);
        return *this;
    }    
    self& withPostCode(const std::string& postCode) {
        person.setPostCode(postCode);
        return *this;
    }    
};

#endif /* PERSONADDRESSBUILDER_H */

