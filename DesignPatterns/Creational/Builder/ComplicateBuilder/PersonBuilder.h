/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   PersonBuilder.h
 * Author: default
 *
 * Created on April 11, 2019, 5:19 PM
 */

#ifndef PERSONBUILDER_H
#define PERSONBUILDER_H

#include <deque>

#include "Person.h"

class PersonAddressBuilder;
class PersonJobBuilder;

class PersonBuilderBase {
protected:
    BuilderFacets::Person& person;  //reference to person
public:
    PersonBuilderBase(BuilderFacets::Person& person);
    
    //Cast operator
    operator BuilderFacets::Person() const{
        return std::move(person);
    }
    
    PersonAddressBuilder lives() const;
    PersonJobBuilder works() const;
};  //End of PersonBuilderBase class

class PersonBuilder : public PersonBuilderBase {
    BuilderFacets::Person p;    //Actual object
public:
    PersonBuilder();
};  //End of PersonBuilder

#endif /* PERSONBUILDER_H */

