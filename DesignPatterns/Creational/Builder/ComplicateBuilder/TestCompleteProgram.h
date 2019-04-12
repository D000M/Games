/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   TestCompleteProgram.h
 * Author: default
 *
 * Created on April 12, 2019, 10:17 AM
 */

#ifndef TESTCOMPLETEPROGRAM_H
#define TESTCOMPLETEPROGRAM_H

#include <iostream>

#include "Person.h"
#include "PersonBuilder.h"
#include "PersonAddressBuilder.h"
#include "PersonJobBuilder.h"


void createPerson() {
    BuilderFacets::Person p = BuilderFacets::Person::create()
            .lives()
                .atStreet("Ekzarh Antim I")
                .withPostCode("8400")
                .inCity("Karnobat")
            .works()
                .inCompany("EGT")
                .onPosition("Programmer")
                .earns(33000);
    
    std::cout << p << std::endl;
}

#endif /* TESTCOMPLETEPROGRAM_H */

