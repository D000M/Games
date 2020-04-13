/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   StringToCChar.h
 * Author: default
 *
 * Created on December 7, 2019, 5:12 PM
 */

#ifndef STRINGTOCCHAR_H
#define STRINGTOCCHAR_H

#include <string>
#include <string.h>

//Class to use cpp string in any char* c library
class StringToCChar {
    std::string str;
public:
    StringToCChar(const std::string& msg = "") : str{msg} {}
    operator const char * () const {
        return str.c_str();
    }
};

void testStringToCChar() {
    StringToCChar str1{"bba"};
    StringToCChar str2{"bbc"};
    
    std::cout << strcmp(str1, str2) << std::endl;
}
#endif /* STRINGTOCCHAR_H */

