/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   CopyingWithPointers.h
 * Author: default
 *
 * Created on December 7, 2019, 4:20 PM
 */

#ifndef COPYINGWITHPOINTERS_H
#define COPYINGWITHPOINTERS_H

#include <string>
#include <iostream>
#include <ostream>

class Dog {
    std::string name;
public:
    Dog(const std::string& nm) : name{nm} {
        std::cout << "Creating Dog: " << *this << std::endl;
    }
    //Sentisyzed copy constructor and operator = are correct
    
    Dog(const Dog* dogPtr, const std::string& msg) 
        : name{dogPtr->name + msg} {
        std::cout << "Copied Dog: " << *this << " from " << *dogPtr << std::endl;
    }
    ~Dog() {
        std::cout << "Deleting dog: " << *this << std::endl;
    }
    void rename(const std::string& newName) {
        name = newName;
        std::cout << "Dog renamed to: " << *this << std::endl;
    }
    const std::string getName() const {
        return name;
    }
    friend std::ostream& operator << (std::ostream& os, const Dog& obj) {
        return os << "[" << obj.name << "]";
    }
};

class DogHouse {
    Dog* dogPtr;
    std::string houseName;
public:
    DogHouse(Dog* dog, const std::string& houseNm) 
     : dogPtr{dog}, houseName{houseNm} {   
    }
     
    DogHouse(const DogHouse& dh) 
        : dogPtr{ new Dog(dh.dogPtr, " copy-constructed") },
          houseName{dh.houseName + " copy-constructed"} {
        
    } 
    DogHouse& operator = (const DogHouse& dh) {
        //Check for self assignment
        if(this != &dh) {
            dogPtr = new Dog(dh.dogPtr, " assigned");
            houseName = dh.houseName + " assigned";
        }
        return *this;
    }      
    void renameHouse(const std::string& newName) {
        houseName = newName;
    }
    
    Dog* getDog() const {
        return dogPtr;
    }
    ~DogHouse() {
        //std::cout << dogPtr->getName() << " Deleted!\n";
        delete dogPtr;
    }
    
    friend std::ostream& operator << (std::ostream& os, const DogHouse& obj) {
        return os << "[" << obj.houseName << "] contains: " << *obj.dogPtr;
    }
};

void testDogHouse() {
    DogHouse fidos(new Dog("Fido"), "FidoHouse");
    std::cout << fidos << std::endl;
    DogHouse otherDog = fidos;      //Copy construction
    std::cout << otherDog << std::endl;
    otherDog.getDog()->rename("Spot");
    otherDog.renameHouse("SpotHouse");
    std::cout << otherDog << std::endl;
    fidos = otherDog;
    std::cout << fidos << std::endl;
    fidos.getDog()->rename("MadMax");
    fidos.renameHouse("MadMaxHouse");
}
#endif /* COPYINGWITHPOINTERS_H */

