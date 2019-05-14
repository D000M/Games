/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   SingletonImplementation.h
 * Author: default
 *
 * Created on April 17, 2019, 3:42 PM
 */

#ifndef SINGLETONIMPLEMENTATION_H
#define SINGLETONIMPLEMENTATION_H

#include <string>
#include <map>
#include <iostream>
#include <boost/lexical_cast.hpp>
#include <vector>
#include <fstream>
#include <memory>

namespace SingletonImplementation {
    
    
    class DataBase {
    public:
        virtual int getPopulation(const std::string& name) = 0;
    }; //End DataBase
    //For unit test. 
    class DummyDataBase : public DataBase {
        std::map<std::string, int> capitals;
    public:
        DummyDataBase() {
            capitals["alpha"] = 1;
            capitals["beta"] = 2;
            capitals["gamma"] = 3;
        }
        int getPopulation(const std::string& name) override {
            return capitals[name];
        }
    }; //End DummyDataBase
    
    struct ConfigurableRecordFinder {
        DataBase& db;      
        ConfigurableRecordFinder(DataBase& db)
            : db(db) {
        }

        int totalPopulation(std::vector<std::string> names) {
            int result{0};
            for (auto& city : names) {
                result += db.getPopulation(city);
            }
            return result;
        }
        
    };
    
    class SingletonDB : public DataBase{
        //Make constructor private so only 1 object can be created via static function. Forbid copy constructor and assignment operator
        SingletonDB() {
            std::cout << "DataBase Created!\n";
            std::ifstream ifs{"Creational/Singleton/files/capitals.txt"};
            std::string city, pop;
            while(std::getline(ifs, city)) {    //Take one line
                std::getline(ifs, pop);         //Take next line
                
                int population = boost::lexical_cast<int>(pop);
                capitals[city] = population;
            }
        }
        std::map<std::string, int> capitals;
    public:
        //Assure nobody can create another DB object via copy constructor or assignment
        SingletonDB(const SingletonDB&) = delete;           //Delete copy constructor
        void operator = (const SingletonDB&) = delete;      //Delete copy assignment
        
        static SingletonDB& get() {
            static SingletonDB db;
            return db;
        }
        
        int getPopulation(const std::string& cityName) override {
            return capitals[cityName];
        }
    };
    
    void testSingletonDB() {
        std::string cityName = "Delhi";
        std::cout << cityName << " has population: " << SingletonDB::get().getPopulation(cityName) << std::endl;
        cityName = "Tokyo";
        std::cout << cityName << " has population: " << SingletonDB::get().getPopulation(cityName) << std::endl;
    }
    
    struct SingletonDBRecordFinder {
        int totalPopulation(std::vector<std::string> names) {
            int result{0};
            for(auto& city : names) {
                result += SingletonDB::get().getPopulation(city);
            }
            return result;
        }
    };
    
    void testSingletonDBRF() {
        SingletonDBRecordFinder rf;
        std::vector<std::string> names{"Tokyo", "Delhi", "Mexico City"};
        int totalPop = rf.totalPopulation(names);
        std::cout << "Total Pop: " << totalPop << std::endl;
    }
    
    
    //Dependancy Injection Singleton using boost
    struct IFoo {
        virtual string name() = 0;
    }; 
    struct Foo : IFoo {
        static int id;
        Foo() {
            ++id;
        }
        string name() override {
            return "Foo " + boost::lexical_cast<std::string>(id); 
        }
    };
    int Foo::id = 0;
    
    struct Bar {
        std::shared_ptr<IFoo> foo;
    };
    
    void testDISingleton() {
         
    }
}

#endif /* SINGLETONIMPLEMENTATION_H */

