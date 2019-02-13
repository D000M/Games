/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Tests.h
 * Author: default
 *
 * Created on February 12, 2019, 4:34 PM
 */

#ifndef TESTS_H
#define TESTS_H

int run() {
    if(/*someFunction(test1) != true*/) return 1;   //error 1st test
    if(/*someFunction(test2) != true*/) return 2;   //error 2nd test
    /*...*/                                         //error n-th test
    return 0; //if all test passed ok
}

#endif /* TESTS_H */

