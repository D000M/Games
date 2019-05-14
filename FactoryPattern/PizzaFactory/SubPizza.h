/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   SubPizza.h
 * Author: default
 *
 * Created on March 14, 2019, 11:11 AM
 */

#ifndef SUBPIZZA_H
#define SUBPIZZA_H

#include "Pizza.h"


class HamAndMushroomPizza : public Pizza {
    public:
        int getPrice() override { return 9;}
        virtual ~HamAndMushroomPizza() {std::cout << "~HamAndMushroomPizza()\n";};
};

class DeluxPizza : public Pizza {
public:
    int getPrice() override {return 6;}
    virtual ~DeluxPizza() {std::cout << "~DeluxPizza()\n";};
};

class HawaiianPizza : public Pizza {
public:
    int getPrice() override {return 12;}
    virtual ~HawaiianPizza() {std::cout << "~HawaiianPizza()\n";};
};
#endif /* SUBPIZZA_H */

