/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Pizza.h
 * Author: default
 *
 * Created on March 14, 2019, 11:08 AM
 */

#ifndef PIZZA_H
#define PIZZA_H

#include <memory>
#include <iostream>

class Pizza {
public:
    virtual int getPrice() = 0;
    virtual ~Pizza() { std::cout << "~Pizza()\n"; };
};


class PizzaFactory {
public:
    enum class PizzaType {
        HamMushroom,
        Deluxe,
        Hawaiian
    };
public:
    static std::unique_ptr<Pizza> createPizza(PizzaType type);
};
#endif /* PIZZA_H */

