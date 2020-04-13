/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   C08ConstExamples.h
 * Author: default
 *
 * Created on December 5, 2019, 5:00 PM
 */

#ifndef C08CONSTEXAMPLES_H
#define C08CONSTEXAMPLES_H

void constPointersDifference() {    
    const int* ptrOne;  //ptrOne is a pointer which points to the const int
    int const* ptrTwo;  //ptrTwo is ordinary pointer which points to int that happens to be const. same as ptrOne.
    
    //To make pointer itself const
    //Compiler requires the pointer to point to a object
    int d = 1;
    int* const constPtr = &d;   //To make the pointer const which mean the pointer cannot point to another object not. but we can change the value of the object
    *d = 2;
}

#endif /* C08CONSTEXAMPLES_H */

