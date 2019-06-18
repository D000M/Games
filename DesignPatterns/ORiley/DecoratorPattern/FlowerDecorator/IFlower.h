/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   IFlower.h
 * Author: default
 *
 * Created on June 14, 2019, 12:51 PM
 */

#ifndef IFLOWER_H
#define IFLOWER_H

#include <string>
#include <iostream>


class IFlower {
public:
    virtual std::string toStr() const = 0;
    virtual float cost() const = 0;
};

//Concrete Component
class Azalea : public IFlower {
public:
    std::string toStr() const override {
        return "Azalea";
    }
    float cost() const override {
        return 11.5f;
    }
};

//Concrete Component
class Begonia : public IFlower {
public:
    std::string toStr() const override {
        return "Begonia";
    }
    float cost() const override {
        return 13.6f;
    }
};

//Concrete Component
class Dahlia : public IFlower {
public: 
    std::string toStr() const override {
        return "Dahlia";
    }
    float cost() const override {
        return 10.8f;
    }
};

//Decorators
class RedFlowerDecorator : public IFlower {
    const IFlower& component;
public:
    RedFlowerDecorator(const IFlower& t)
        : component{t} {
    }
    
    template<typename... Args>
    RedFlowerDecorator(IFlower& t, Args... args) 
        : component{t},
          IFlower{std::forward<Args>(args)...}{
    }
          
    std::string toStr() const override {
        return component.toStr() + " is red ";
    }
    float cost() const override {
        return component.cost() + 2.5f;
    }
};

class BlueFlowerDecorator : public IFlower {
    const IFlower& component;
public:
    
    BlueFlowerDecorator(const IFlower& t)
        : component{t} {
    }
    
    template<typename... Args>
    BlueFlowerDecorator(IFlower& t, Args... args) 
        : component{t},
          IFlower{std::forward<Args>(args)...}{
    }
        
    std::string toStr() const override {
        return component.toStr() + " is blue ";
    }
    float cost() const override {
        return component.cost() + 4.7f;
    }
};

void testFlowerDecorator() {
//    Azalea flower{RedFlowerDecorator{}};
    RedFlowerDecorator redAzalea{RedFlowerDecorator{BlueFlowerDecorator{RedFlowerDecorator{Dahlia{}}}}};
    std::cout << redAzalea.toStr() << " Price: " << redAzalea.cost() << std::endl;
    
    IFlower* redBegonia = new RedFlowerDecorator{BlueFlowerDecorator{Begonia{}}};
    std::cout << redBegonia->toStr() << " Price: " << redBegonia->cost() << std::endl;
    delete redBegonia;
    
}
#endif /* IFLOWER_H */

