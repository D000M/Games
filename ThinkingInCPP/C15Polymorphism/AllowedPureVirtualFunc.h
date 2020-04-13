/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   AllowedPureVirtualFunc.h
 * Author: default
 *
 * Created on December 20, 2019, 10:34 AM
 */

#ifndef ALLOWEDPUREVIRTUALFUNC_H
#define ALLOWEDPUREVIRTUALFUNC_H
#include <string>
class Pet {
public:
    virtual void speak() const = 0;
    virtual void eat() const = 0;
//    virtual void sleep() = 0 {}   //cant declare pure virtual function inline, but we can declare it like a normal func in the interface
};
void Pet::eat() const {
    std::cout << "Pet::eat()\n";
}
void Pet::speak() const {
    std::cout << "Pet::speak()\n";
}

class Hamster : public Pet {
public:
    //use the common pet code
    void speak() const override {
        //add new functionality
        Pet::speak();   //use base class code
        //add new functionality
    }
    void eat() const override {
        //add new functionality
        Pet::eat(); //use base class code
        //add new functionality
    }
};

void testPureVirt() {
    Hamster sigma;
    sigma.eat();
    sigma.speak();
}
#endif /* ALLOWEDPUREVIRTUALFUNC_H */

