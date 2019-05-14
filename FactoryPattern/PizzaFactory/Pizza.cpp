/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "Pizza.h"
#include "SubPizza.h"


std::unique_ptr<Pizza> PizzaFactory::createPizza(PizzaType type) {
    switch(type) {
        case PizzaType::HamMushroom: {
            return std::make_unique<HamAndMushroomPizza>();
        }
        case PizzaType::Deluxe: {
            return std::make_unique<DeluxPizza>();
        }
        case PizzaType::Hawaiian: {
            return std::make_unique<HawaiianPizza>();
        }
        throw "Invalid Pizza Type!\n";
    }
}