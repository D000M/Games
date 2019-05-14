/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Items.h
 * Author: default
 *
 * Created on March 27, 2019, 4:38 PM
 */

#ifndef ITEMS_H
#define ITEMS_H

#include <string>
#include <iostream>
#include <fstream>


class Item {
    std::string m_name;
    float m_price;
    int m_quantity;
public:
    Item(const std::string& n = "", float p = 0, int q = 0) 
        : m_name{n},
          m_price{p},
          m_quantity{q} { 
              std::cout << "Item " << m_name << " Created!\n";
    }
          ~Item() {
              std::cout << "Item " << m_name << " Destroyed!\n";
          }
    friend std::ostream& operator << (std::ostream& out, const Item& obj);
    friend std::ofstream& operator << (std::ofstream& out, const Item& obj);
    friend std::istream& operator >> (std::istream& in, Item& obj);
    friend std::ifstream& operator >> (std::ifstream& in, Item& obj);
};

std::ostream& operator << (std::ostream& out, const Item& obj) {
    return out << "Name: " << obj.m_name << " Price: " << obj.m_price << " Quantity: " << obj.m_quantity << std::endl; 
}
std::ofstream& operator << (std::ofstream& out, const Item& obj) {
    out << obj.m_name << " ";
    out << obj.m_price << " ";
    out << obj.m_quantity << std::endl;
    return out;
}
std::istream& operator >> (std::istream& in, Item& obj) {
    std::cout << "Input Name: ";
    in >> obj.m_name;
    std::cout << "Input Price: ";
    in >> obj.m_price;
    std::cout << "Input Quantity: ";
    in >> obj.m_quantity;
    return in;
}
std::ifstream& operator >> (std::ifstream& in, Item& obj) {
    in >> obj.m_name;
    in >> obj.m_price;
    in >> obj.m_quantity;
    return in;
}
#endif /* ITEMS_H */

