/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Set.h
 * Author: default
 *
 * Created on February 28, 2019, 5:10 PM
 */

#ifndef SET_H
#define SET_H

#include <vector>

class Set {
    std::vector<int> vertices;
public:
    Set(std::vector<int> v);
    virtual ~Set();
    bool find(int element);
    void unionSets(const Set& other);
    void printSet();
private:
    void setup(std::vector<int> v);
    
};

#endif /* SET_H */

