/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   C07Excercises.h
 * Author: default
 *
 * Created on December 5, 2019, 4:05 PM
 */

#ifndef C07EXCERCISES_H
#define C07EXCERCISES_H

#include <string>

class Text {
    std::string textContent;
public:
    Text();
    Text(const std::string& fileName);
    const std::string contains() const; 
};


extern void testText();
#endif /* C07EXCERCISES_H */

