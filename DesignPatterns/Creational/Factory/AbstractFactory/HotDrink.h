/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   HotDrink.h
 * Author: default
 *
 * Created on April 12, 2019, 4:06 PM
 */

#ifndef HOTDRINK_H
#define HOTDRINK_H

#include <iostream>
#include <memory>


namespace AbstractFactory {
    
    struct HotDrink {
        virtual ~HotDrink() = default;
        virtual void prepare(int volume) const = 0; 
    };
    
    struct Tea : HotDrink {
        void prepare(int volume) const override {
            std::cout << "Take a tea bag, boil water, pour " << volume
                    << "ml, add some lemon\n";
        }
    };
    struct Coffee : HotDrink {
        void prepare(int volume) const override {
            std::cout << "Grind some beans, boil water, pour " << volume
                    << "ml, add some cream, enjoy!\n";
        }
    };
    
}

#endif /* HOTDRINK_H */

