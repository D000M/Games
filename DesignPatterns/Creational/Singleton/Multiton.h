/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Multiton.h
 * Author: default
 *
 * Created on May 27, 2019, 3:47 PM
 */

#ifndef MULTITON_H
#define MULTITON_H

#include <string>
#include <memory>
#include <map>
#include <iostream>

namespace Multi {
    
    enum class Importance {
        primary,
        secondary,
        tertiary
    };
    
    template<typename T, typename Key = std::string>
    class Multiton {
        protected:
            Multiton() = default;
            virtual ~Multiton() = default;
            //We can delete copy assignment and copy constructor.
        public:
            static std::shared_ptr<T> get(const Key& key) {
                const auto it = instances.find(key);
                if(it != instances.end() ) {        
                       return it->second;
                }
                auto instance = std::make_shared<T>();
                instances[key] = instance;
                return instance;
            }
            
        private:
            static std::map<Key, std::shared_ptr<T>> instances;  
    };
    
    template<typename T, typename Key>
    std::map<Key, std::shared_ptr<T>> Multiton<T, Key>::instances;  //Initializing of static map
    
    
    class Printer {
    public:
        Printer() {
            ++Printer::totalInstanceCount;
            std::cout << totalInstanceCount << " instances created so far\n";
        }
        static int totalInstanceCount;
    };
    
    int Printer::totalInstanceCount = 0;
    
    void testMultiton() {
        typedef Multiton<Printer, Importance> mt;
        auto mainPrinter = mt::get(Importance::primary);
        auto auxPrinter = mt::get(Importance::secondary);
        auto auxPrinter2 = mt::get(Importance::secondary);
    }
}


#endif /* MULTITON_H */

