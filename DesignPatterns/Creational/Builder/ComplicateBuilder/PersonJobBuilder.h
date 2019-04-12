/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   PersonJobBuilder.h
 * Author: default
 *
 * Created on April 12, 2019, 9:59 AM
 */

#ifndef PERSONJOBBUILDER_H
#define PERSONJOBBUILDER_H

#include "PersonBuilder.h"

class PersonJobBuilder : public PersonBuilderBase {
    
    using self = PersonJobBuilder;
    
    public:
    explicit PersonJobBuilder(BuilderFacets::Person& person)
        : PersonBuilderBase(person) {
    }

    self& inCompany(const std::string& company) {
        person.setCompanyName(company);
        return *this;
    }
    self& onPosition(const std::string& position) {
        person.setPosition(position);
        return* this;
    }
    self& earns(const int salary) {
        person.setAnnualIncome(salary);
        return *this;
    }
};

#endif /* PERSONJOBBUILDER_H */

