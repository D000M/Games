/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Person.cpp
 * Author: default
 * 
 * Created on April 18, 2019, 5:00 PM
 */

#include <iostream>

#include "Person2.h"

class Person2::PersonImpl {
public:
    void greet(Person2* p);

};
void Person2::PersonImpl::greet(Person2* p) {
    std::cout << "Hello: " << p->name << std::endl;
}

Person2::Person2() 
    : impl{new PersonImpl} {

}

Person2::~Person2() {
    delete impl;
}

void Person2::greet() {
    impl->greet(this);
}

