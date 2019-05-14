/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Person.h
 * Author: default
 *
 * Created on April 18, 2019, 5:00 PM
 */

#ifndef PERSON_H
#define PERSON_H

#include <string>

class Person2 {
public:
    std::string name;

    class PersonImpl;
    PersonImpl* impl;
    
    Person2();
    ~Person2();

    void greet();


private:

};


#endif /* PERSON_H */

