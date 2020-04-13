/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Set.cpp
 * Author: default
 * 
 * Created on February 28, 2019, 5:10 PM
 */

#include "Set.h"
#include <iostream>

Set::Set(std::vector<int> v) {
    setup(v);
}

Set::~Set() {
}

void Set::setup(std::vector<int> v) {
    for(int i = 0; i < v.size(); i++) {
        vertices.push_back(v.at(i));
    }
}

bool Set::find(int element) {
    
    if(vertices.empty()) {
        return false;
    }
    
    for(int i = 0; i < vertices.size(); i++) {
        if(vertices.at(i) == element) {
            return true;
        }
    }
    return false;
}

void Set::unionSets(const Set& other) {
    if(&other == this) {
        return;
    }
    
    if(other.vertices.empty()) {
        return;
    }
    for(int i = other.vertices.size(); i < other.vertices.size() * 2; i++ ) {
        vertices.push_back(other.vertices.at(i - other.vertices.size()));
    }
}

void Set::printSet() {
    for(int i = 0; i < vertices.size(); i++) {
        std::cout << vertices.at(i) << " ";
    }
}
