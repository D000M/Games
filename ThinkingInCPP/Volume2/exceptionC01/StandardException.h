/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   StandardException.h
 * Author: default
 *
 * Created on January 7, 2020, 3:28 PM
 */

#ifndef STANDARDEXCEPTION_H
#define STANDARDEXCEPTION_H

#include <stdexcept>
#include <iostream>

class MyException : public std::runtime_error {
    public:
        MyException(const std::string& msg = "") 
                : std::runtime_error{"throw MyException: " + msg} {}
};
void testMyException();
#endif /* STANDARDEXCEPTION_H */

