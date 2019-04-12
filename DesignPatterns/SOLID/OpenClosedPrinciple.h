/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   OpenClosedPrinciple.h
 * Author: default
 *
 * Created on April 10, 2019, 4:09 PM
 */



/**
 * 
 * Open-Closed Principle
 * Open for extension, closed for modification. 
 */



#ifndef OPENCLOSEDPRINCIPLE_H
#define OPENCLOSEDPRINCIPLE_H

#include <string>
#include <vector>
#include <iostream>

enum class Color { red, green, blue };
enum class Size { small, medium, large };

struct Product {
    std::string name;
    Color color;
    Size size;
    
    Product(const std::string& lName, const Color& lColor, const Size& lSize) 
            : name{lName},
              color{lColor},
              size{lSize} {}
};



/**
 * Wrong way
 * What if our boss say the client wants now to find items by Color and Size?
 * We make another method this time with arguments color and size
 * so we have 3 method for only 2 properties
 * what if we have 3 properties in our class?
 * we will must create 8 methods with almost same code.
 * This lead to Open-Close Principle
 */
//Filter product
struct ProductFilter {
    /**
     * Filter Products by color
     * @param items vector from where to check colors of the products
     * @param color search for particular color in the items vector
     * @return result vector
     */
    std::vector<Product*> byColor(std::vector<Product*> items, const Color& lColor) {
        std::vector<Product*> result;
        for(auto& i : items) {
            if(i->color == lColor) {
                result.push_back(i);
            }
        }
        return result;
    }
    
    /**
     * Filter Products by size
     * @param items vector from where to check size of the products
     * @param lSize search for particular size in the items vector
     * @return result vector
     */
    std::vector<Product*> bySize(std::vector<Product*> items, const Size& lSize) {
        std::vector<Product*> result;
        for(auto& i : items) {
            if(i->size == lSize) {
                result.push_back(i);
            }
        }
        return result;
    }
    
    /**
     * Filter Product by size and color
     * @param items vector from where to check size and color of the products
     * @param lSize search for particular size in the items vector
     * @param lColor search for particular color in the items vector
     * @return result vector
     */
    std::vector<Product*> bySizeAndColor(std::vector<Product*> items, const Size& lSize, const Color& lColor) {
        std::vector<Product*> result;
        for(auto& i : items) {
            if(i->size == lSize && i->color == lColor) {
                result.push_back(i);
            }
        }
        return result;
    }
};

void productFilterOne() {
    Product apple("Apple", Color::green, Size::small);
    Product tree("Tree", Color::green, Size::large);
    Product house("House", Color::blue, Size::large);
    
    std::vector<Product*> items{&apple, &tree, &house};
    
    ProductFilter pf;
    auto greenColorItems = pf.byColor(items, Color::green);
    for(auto& item : greenColorItems) {
        std::cout << item->name << " is green\n";
    }
}
/////////////////////////////////////////// WRONG APROACH

/**
 * Open-Closed Principle
 * We declare 2 interfaces
 */
//Specification Interface
/**
 * We will make it template so to can work on another products not only on our Product
 */
template<typename T> 
struct ISpecification {
    virtual bool isSatisfied(T* item) const = 0;
    
    /** Not working
    AndSpecification<T> operator && (ISpecification<T>&& other) {
        return AndSpecification<T>(*this, other);   //Return AndSpecification constructed of itself and other 
    } */
};

//Filter Interface
template<typename T>
struct IFilter {
    virtual std::vector<T*> filterItems(std::vector<T*> items, ISpecification<T>& spec) = 0;
};

//Now we can construct a better Filter
struct BetterFilter : IFilter<Product> {
    
    std::vector<Product*> filterItems(std::vector<Product*> items, ISpecification<Product>& spec) override {
        std::vector<Product*> result;
        for(auto& item : items) {
            if(spec.isSatisfied(item)) {
                result.push_back(item);
            }
        }
        return result;
    }
   
};

//Now we have to implement the specification
//Lets use Color specification
struct ColorSpecification : ISpecification<Product> {
    Color color;
    ColorSpecification(const Color& lColor) : color{lColor} {}
    
    bool isSatisfied(Product* item) const override {
        return item->color == color;
    }

};

struct SizeSpecification : ISpecification<Product> {
    
    Size size;
    
    explicit SizeSpecification(const Size& lSize) : size{lSize} {}
    
    bool isSatisfied(Product* item) const override {
        return item->size == size;
    }

};

//And Generic Structure to can use both specification for Color and Size
template<typename T>
struct AndSpecification : ISpecification<T> {
    const ISpecification<T>& first;
    const ISpecification<T>& second;
    
    AndSpecification(const ISpecification<T>& f, const ISpecification<T>& s) 
        : first{f}, second{s} {}
    
    bool isSatisfied(T* item) const override {
        return first.isSatisfied(item) && second.isSatisfied(item);
    }

};

//To use operator && for Delcared Specification
template<typename T> 
AndSpecification<T> operator && (const ISpecification<T>& first, const ISpecification<T>& second) {
    return {first, second};
}

//Now we can use our better filter
void betterFilterOne() {
    Product apple("Apple", Color::green, Size::small);
    Product tree("Tree", Color::green, Size::large);
    Product house("House", Color::blue, Size::large);
    
    std::vector<Product*> items{&apple, &tree, &house};
    
    BetterFilter bf;
    ColorSpecification green{Color::green};
    for(auto& item : bf.filterItems(items, green)) {
        std::cout << item->name << " is green\n";
    }
    
    SizeSpecification large{Size::large};
    for(auto& item : bf.filterItems(items, large)) {
        std::cout << item->name << " is large\n";
    }
    
    //Now we can Combine both Color and Size
    AndSpecification<Product> greenAndLarge{green, large};
    for(auto& item : bf.filterItems(items, greenAndLarge)) {
        std::cout << item->name << " is green and large\n";
    }
    
    //To avoid lots of variables we can do overload operator &&
    auto spec = green && large;
    for(auto& item : bf.filterItems(items, spec)) {
        std::cout << item->name << " is green and large operator &&\n";
    }
    
}
#endif /* OPENCLOSEDPRINCIPLE_H */

