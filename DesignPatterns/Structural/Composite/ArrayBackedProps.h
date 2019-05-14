/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   ArrayBackedProps.h
 * Author: default
 *
 * Created on May 8, 2019, 2:46 PM
 */

#ifndef ARRAYBACKEDPROPS_H
#define ARRAYBACKEDPROPS_H

#include <array>
#include <numeric>
#include <algorithm>
#include <iostream>
#include <vector>


namespace ArrayBackedProperties {
    class Creature {
        enum eAbilities {str, agl, intl, count};
        std::array<int, count> abilities;
        
    public:
        void setStrength(int value) { abilities[str] = value; }
        int getStrength() const { return abilities[str]; }
        
        void setAgility(int value) { abilities[agl] = value; }
        int getAgility() const { return abilities[agl]; }
        
        void setInteligence(int value) { abilities[intl] = value; }
        int getInteligence() const { return abilities[intl]; }
        
        int sum() const {
            return std::accumulate(abilities.cbegin(), abilities.cend(), 0);
        }
        
        double average() const {
            return sum() / double(count);
        }
        
        int maxStat() const {
            return *std::max_element(abilities.cbegin(), abilities.cend());
        }
    };
    
    void testCreature() {
        Creature orc;
        orc.setStrength(16);
        orc.setAgility(11);
        orc.setInteligence(9);
        std::cout << "Orc has an average stats of: "
                << orc.average()
                << " and a maximum stat of: " 
                << orc.maxStat() << std::endl;
    }
    
    
    
    //////Exercise My Solution
    class ContainsIntegers : public std::vector<int> {
    public:
        virtual int getSum() const = 0;
    };
    
    class SingleValue : public ContainsIntegers {
    public:
        SingleValue(int elem) {
            emplace_back(elem);
        }
        int getSum() const {
            return at(0);
        }
    };
    
    class ManyValues : public ContainsIntegers {
    public:
        void add(int elem) {
            emplace_back(elem);
        }
        int getSum() const {
            return std::accumulate(cbegin(), cend(), 0);
        }
    };
    
    //Provided By WebSite
//    struct ContainsIntegers {
//        public:
//        virtual int getSum() const = 0;
//    };
//
//    struct SingleValue : public ContainsIntegers
//    {
//      int value{ 0 };
//
//      SingleValue() = default;
//
//      explicit SingleValue(const int value)
//        : value{value}
//      {
//      }
//
//      // TODO
//      int getSum() const {
//          return value;
//      }
//    };
//
//    struct ManyValues : std::vector<int>, ContainsIntegers
//    {
//      void add(const int value)
//      {
//        push_back(value);
//      }
//      int getSum() const {
//          return accumulate(cbegin(), cend(), 0);
//      }
//    };

    int sum(const std::vector<ContainsIntegers*> items)
    {
    // TODO
        int totalSum = 0;
        for(auto vecs : items) {
            totalSum += vecs->getSum();
        }
        return totalSum;
    }
    
    void testExcercise() {
        SingleValue single_value{1};
        ManyValues many_values;
        many_values.add(2);
        many_values.add(3);
        int total = sum({&single_value, &many_values});
//        int total = single_value.getSum();
        std::cout << "Total Sum: " << total << std::endl;
    }
}

#endif /* ARRAYBACKEDPROPS_H */

