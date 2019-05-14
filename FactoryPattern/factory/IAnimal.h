/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   IAnimal.h
 * Author: default
 *
 * Created on March 14, 2019, 9:15 AM
 */

#ifndef IANIMAL_H
#define IANIMAL_H

#include <iostream>
#include <map>



class IAnimal {
public:
    virtual int GetAnimalLegs() const = 0;
    virtual void Speak() = 0;
    virtual void Free() = 0;
};

//typedef IAnimal* (*CreateAnimalFn)(void);

class Cat : public IAnimal {
public:
    int GetAnimalLegs() const override {return 4;}
    void Speak() override {std::cout << "Meow!\n";}
    void Free() override {delete this;}
    
//    static IAnimal* Create() {return new Cat();}
};

class Dog : public IAnimal {
public:
    int GetAnimalLegs() const override {return 4;}
    void Speak() override {std::cout << "Bau!\n";}
    void Free() override {delete this;}
    
//    static IAnimal* Create() {return new Dog();}
};

class Spider : public IAnimal {
public:
    int GetAnimalLegs() const override {return 8;}
    void Speak() override {std::cout << "hrhrhr!\n";
    }
    void Free() override {delete this;}
    
//    static IAnimal* Create() {return new Spider();}
};

class Horse : public IAnimal {
public:
    int GetAnimalLegs() const override {return 4;}
    void Speak() override { std::cout << "IUUU!\n";}
    void Free() override {delete this;};
    
//    static IAnimal* Create() {return new Horse();}
};

class AnimalFactory {
private:
    AnimalFactory();
    AnimalFactory(const AnimalFactory&);
    AnimalFactory &operator = (const AnimalFactory&) {return *this;}
    
    
    
public:
    ~AnimalFactory() {m_FactoryMap.clear();}
    
    static AnimalFactory *Get() {
        static AnimalFactory instance;
        return &instance;
    }
    
    template<typename T> 
    static IAnimal* CreateAnimal() {
        return new T;
    }
    
    template<typename T> 
    void Register(const std::string& animalName) {
        m_FactoryMap[animalName] = &CreateAnimal<T>;
    }
    
private:
    typedef IAnimal* (*PtrCreateFunc)();
    typedef std::map<std::string, PtrCreateFunc> FactoryMap;
    FactoryMap m_FactoryMap;
};

AnimalFactory::AnimalFactory() {

}

#endif /* IANIMAL_H */

