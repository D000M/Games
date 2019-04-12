/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   PersonBuilder.cpp
 * Author: default
 * 
 * Created on April 11, 2019, 5:19 PM
 */

#include "PersonBuilder.h"
#include "PersonAddressBuilder.h"
#include "PersonJobBuilder.h"

PersonBuilderBase::PersonBuilderBase(BuilderFacets::Person& person) 
    : person{person} {
}

PersonBuilder::PersonBuilder()
        : PersonBuilderBase{p}{
}
        
PersonAddressBuilder PersonBuilderBase::lives() const {
    return PersonAddressBuilder{person};
}

PersonJobBuilder PersonBuilderBase::works() const {
    return PersonJobBuilder{person};
}


        