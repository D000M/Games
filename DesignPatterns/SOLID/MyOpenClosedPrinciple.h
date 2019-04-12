/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   MyOpenClosedPrinciple.h
 * Author: default
 *
 * Created on April 11, 2019, 11:18 AM
 */

#ifndef MYOPENCLOSEDPRINCIPLE_H
#define MYOPENCLOSEDPRINCIPLE_H

#include <string>
#include <vector>

#include "OpenClosedPrTemplates.h"


enum class BeerType {
    WEISS,
    DOPELBOK,
    IPA,
    ALE,
    LAGER
};

enum class Country {
    GERMAN,
    CZECH,
    BELGIUM,
    ENGLAND
};

class Beer {
    std::string mName;
    BeerType mType;
    Country mCountry;
    
public:
    Beer(const std::string& lName, const BeerType& lType, const Country& lCountry);
    
    BeerType getType() const;
    Country getCountry() const;
    std::string getBeerName() const;
};
Beer::Beer(const std::string& lName, const BeerType& lType, const Country& lCountry) 
    : mName{lName},
      mType{lType},
      mCountry{lCountry} {}
      
BeerType Beer::getType() const {
    return mType;
}
Country Beer::getCountry() const {
    return mCountry;
}
std::string Beer::getBeerName() const {
    return mName;
}
      
//Create a Better Filter
class MyBetterFilter : public IMyFilter<Beer> {
    
public:
    //Override Filter function to desired object
    std::vector<Beer*> filterItems(const std::vector<Beer*> vBeers, const IMySpecification<Beer>& specification) override {
        std::vector<Beer*> result;
        for(auto& beer : vBeers) {
            if(specification.isSatisfied(beer)) {
                result.push_back(beer);
            }
        }
        return result;
    }

};


//Now create Specifications  for a beer filter
class BeerTypeSpec : public IMySpecification<Beer> {
    BeerType mType;
public:
    explicit BeerTypeSpec(const BeerType& lType) : mType{lType} {}
    
    bool isSatisfied(Beer* obj) const override {
        return obj->getType() == mType;
    }

};

class BeerCountrySpec : public IMySpecification<Beer> {
    Country mCountry;
public:
    explicit BeerCountrySpec(const Country& lCountry) : mCountry{lCountry} {}
    
    bool isSatisfied(Beer* obj) const override {
        return obj->getCountry() == mCountry;
    }

}; 




///TEST METHOD
void testMyOpenClosedSpec() {
    Beer staropramen("Staropramen", BeerType::LAGER, Country::CZECH);
    Beer stela("Stela", BeerType::LAGER, Country::BELGIUM);
    Beer krombaher("Krombaher", BeerType::WEISS, Country::GERMAN);
    Beer bohemiaRegent("Bohemia Regent", BeerType::LAGER, Country::CZECH);
    Beer krushovice("Krushovice", BeerType::LAGER, Country::CZECH);
    Beer guiness("Guiness", BeerType::DOPELBOK, Country::ENGLAND);
    Beer hubgoblin("Hubgoblin", BeerType::DOPELBOK, Country::ENGLAND);
    Beer trooper("The Trooper", BeerType::LAGER, Country::ENGLAND);
    
    std::vector<Beer*> beers {&staropramen, &stela, &krombaher, &bohemiaRegent, &krushovice, &guiness, &hubgoblin, &trooper};
    
    MyBetterFilter mbf; //Beer Filter.
    
    BeerTypeSpec lagerType{BeerType::LAGER};
    for(auto& beer : mbf.filterItems(beers, lagerType)) {
        std::cout << beer->getBeerName() << " is lager beer." << std::endl;
    }
    
    BeerCountrySpec fromEngland{Country::ENGLAND};
    for(auto& beer : mbf.filterItems(beers, fromEngland)) {
        std::cout << beer->getBeerName() << " is from england." << std::endl;
    }
    
    MyAndSpecification<Beer> fromEnglandAndLager{lagerType, fromEngland};
    for(auto& beer : mbf.filterItems(beers, fromEnglandAndLager)) {
        std::cout << beer->getBeerName() << " is from england and is lager beer." << std::endl;
    }
    
    auto opAnd = lagerType && fromEngland;  //return object of a type MyAndSpecification{lagerType, fromEngland}; using operator &&
    for(auto& beer : mbf.filterItems(beers, opAnd)) {
        std::cout << beer->getBeerName() << " is from england and is lager beer. Using operator &&" << std::endl;
    }
    
    
    auto opOr = lagerType || fromEngland;
    for(auto& beer : mbf.filterItems(beers, opOr)) {
        std::cout << beer->getBeerName() << " is lager or from England. Using operator ||" << std::endl;
    }
}

#endif /* MYOPENCLOSEDPRINCIPLE_H */

