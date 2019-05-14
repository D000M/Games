/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Toy.h
 * Author: default
 *
 * Created on March 14, 2019, 10:16 AM
 */

#ifndef TOY_H
#define TOY_H

#include <iostream>


class Toy {
protected:
    std::string name;
    float price;
public:
    virtual void prepareParts() = 0;
    virtual void combineParts() = 0;
    virtual void assembleParts() = 0;
    virtual void applyLabel() = 0;
    virtual void showProduct() = 0;
};
class Car : public Toy {
    void prepareParts() override {std::cout << "Preparing CAR parts" << std::endl;}
    void combineParts() override {std::cout << "Combining CAR parts" << std::endl;}
    void assembleParts() override {std::cout << "Assembling CAR parts" << std::endl;}
    void applyLabel() override {std::cout << "Applying CAR label" << std::endl; name = "CAR"; price = 145.6f;}
    void showProduct() override {std::cout << "Name: " << name << std::endl << "Price: " << price << std::endl;}
};
class Bike : public Toy {
    void prepareParts() override {std::cout << "Preparing BIKE parts" << std::endl;}
    void combineParts() override {std::cout << "Combining BIKE parts" << std::endl;}
    void assembleParts() override {std::cout << "Assembling BIKE parts" << std::endl;}
    void applyLabel() override {std::cout << "Applying BIKE label" << std::endl; name = "BIKE"; price = 45.6f;}
    void showProduct() override {std::cout << "Name: " << name << std::endl << "Price: " << price << std::endl;}
};
class Plane : public Toy {
    void prepareParts() override {std::cout << "Preparing PLANE parts" << std::endl;}
    void combineParts() override {std::cout << "Combining PLANE parts" << std::endl;}
    void assembleParts() override {std::cout << "Assembling PLANE parts" << std::endl;}
    void applyLabel() override {std::cout << "Applying PLANE label" << std::endl; name = "PLANE"; price = 123.5f;}
    void showProduct() override {std::cout << "Name: " << name << std::endl << "Price: " << price << std::endl;}
};


#endif /* TOY_H */

