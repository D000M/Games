/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   VariantAndStdVisitor.h
 * Author: default
 *
 * Created on May 23, 2019, 4:33 PM
 */

#ifndef VARIANTANDSTDVISITOR_H
#define VARIANTANDSTDVISITOR_H

#include <boost/variant.hpp>
#include <boost/variant/apply_visitor.hpp>
#include <boost/log/attributes/value_visitation.hpp>
#include <string>
#include <iostream>

namespace BoostVariantAndVisitor {
    
   
    struct AddressPrinter : public boost::static_visitor<> {
        //need to overload function call operator operator()() for every single type of attributes in boost::variant
        template<typename T>
        void operator() (const T& t) const {
            std::cout << "A house with name: " << t << std::endl;
        }
    };
    
    void testSTDVariantAndVisitor() {
        boost::variant<int, std::string> house;
        //Only one of those can be assign in boost::variant , replace union in C
        house = 123;
        //house = "Mansion";
        
        AddressPrinter ap;
        boost::apply_visitor(ap, house);
    }
}

#endif /* VARIANTANDSTDVISITOR_H */

