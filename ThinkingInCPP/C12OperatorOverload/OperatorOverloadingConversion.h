/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   OperatorOverloadingConversion.h
 * Author: default
 *
 * Created on December 7, 2019, 5:02 PM
 */

#ifndef OPERATOROVERLOADINGCONVERSION_H
#define OPERATOROVERLOADINGCONVERSION_H

class Three {
    int value;
public:
    Three(int v = 0, int = 0) : value{v} {}
};
class Four {
    int x;
public:
    Four(int xx) : x{xx} {}
    operator Three() const {
        return Three(x);
    }
};

void funcThree(Three) {}

void testOperatorConversion() {
    Four four{10};
    funcThree(four);
    funcThree(100);     //Calls Three(100, 0);
}
#endif /* OPERATOROVERLOADINGCONVERSION_H */

