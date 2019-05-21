/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   IteratorsInSTL.h
 * Author: default
 *
 * Created on May 17, 2019, 1:18 PM
 */

#ifndef ITERATORSINSTL_H
#define ITERATORSINSTL_H

#include <vector>
#include <string>
#include <iostream>


namespace STLIterators {
    void testSTLIterators() {
        std::vector<std::string> names {"john", "jane", "jill", "jack"};
        std::vector<std::string>::iterator it = names.begin();
        
        std::cout << "first name is: " << *it << std::endl;
        
        ++it;
        it->append(" goodall");
        std::cout << "second name is: " << *it << std::endl;
        
        while(++it != names.end()) {
            std::cout << "another name: " << *it << std::endl;
        }
        
        for(auto rIt = names.rbegin(); rIt != names.rend(); ++rIt) {
            std::cout << *rIt;
            if(rIt + 1 != names.rend()) {
                std::cout << ", ";
            }
        }
        std::cout << std::endl;
        
        std::vector<std::string>::const_reverse_iterator jack = names.crbegin();
        // *jack += std::string("some text"); forbidden jack is const iterator
        
        for(auto&& name : names ){
            std::cout << "name = " << name << std::endl; 
        }
    }
}

#endif /* ITERATORSINSTL_H */

