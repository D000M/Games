/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   BoostIteratorFacade.h
 * Author: default
 *
 * Created on May 17, 2019, 3:29 PM
 */

#ifndef BOOSTITERATORFACADE_H
#define BOOSTITERATORFACADE_H

#include <string>
#include <boost/iterator/iterator_facade.hpp>
#include <algorithm>
#include <iostream>

namespace BoostIteratorFacade {
    
    struct Node {
        std::string value;
        Node* next{nullptr};
        
        Node(std::string value) : value(value) {}
        
        Node(std::string value, Node* parent) :value(value) {
            parent->next = this;
        }

    };
    
    struct ListIterator 
        : boost::iterator_facade<ListIterator, Node, boost::forward_traversal_tag> {
        Node* current{ nullptr };
        
        ListIterator() {}
        ListIterator(Node* current) : current(current) {}
        
    private:
        friend class boost::iterator_core_access;
        
        void increment() {
            current = current->next;
        }
        
        bool equal(const ListIterator& other) const {
            return other.current == current;
        }
        
        Node& dereference() const {
            return *current;
        }
    };
    
    void testBoostIterator() {
        Node alpha{"alpha"};
        Node beta{ "beta", &alpha };
        Node gamma{ "gamma", &beta };
        
        std::for_each(ListIterator{&alpha}, ListIterator{}, [](const Node& n) {
           std::cout << n.value << std::endl; 
        });
    }
    
}

#endif /* BOOSTITERATORFACADE_H */

