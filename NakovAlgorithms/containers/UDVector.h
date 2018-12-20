/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   UDVector.h
 * Author: default
 *
 * Created on December 18, 2018, 10:35 AM
 */

#ifndef UDVECTOR_H
#define UDVECTOR_H

#include <iostream>
#include <typeinfo>
#include <algorithm>


#define COUT(x) std::cout << #x << std::endl

/**
 * Class simulating stl c++ vector
 */
template<typename T>
class UDVector {
    size_t size;           //current size of the vector
    T* element;         //pointer to the element of type T
    size_t space;          //reserved space in the vector
    
    static constexpr size_t SPACE = 10;
public:
    
    UDVector() 
        : size{0},
          element{nullptr},
          space{0} {
              COUT("Default UDVector Constructor!");
              std::cout << "Type: " << typeid(T).name() << std::endl;
    }
          
    explicit UDVector(size_t newSize) 
        : size{newSize},
          element{new T[newSize]},
          space{newSize} {
              COUT("UDVector Constructor with custom size!");
              std::cout << "Type: " << typeid(T).name() << ", size: " << newSize << std::endl;
    }
          
    UDVector(std::initializer_list<T> initList) 
        : size{initList.size()},
          element{new T[size]},
          space{initList.size()}{
              COUT("UDVector Constructor with initializer list!");
              std::cout << "Type: " << typeid(T).name() << std::endl;
              std::copy(initList.begin(), initList.end(), element);
    }
          
    UDVector(const UDVector& orig) 
        : size{orig.size},
          element{new T[orig.size]},
          space{orig.space} {
        COUT("UDVector Copy Constructor");
        std::copy(orig.element, orig.element + orig.size, element);
    }
    UDVector& operator = (const UDVector& orig) {
        COUT("UDVector Assignment operator");
        if(this == &orig) {
            COUT("Refere to self");
            return *this;
        }
        if(orig.size <= space) {
            COUT("No need to create space");
            for(int i = 0; i < orig.size; ++i) {
                element[i] = orig.element[i];
                size = orig.size;
            } 
            return *this;
        }
        T* newElements = new T[orig.size];
        for(int i = 0; i < orig.size; i++) {
            newElements[i] = orig.element[i];
        }
        delete [] element;
        space = size = orig.size;
        element = newElements;
        return *this;
    }
    
    UDVector(UDVector&& orig) 
        : size{orig.size},
          element{orig.element},
          space{orig.space} {
              orig.size = 0;
              orig.element = nullptr;
              orig.space = 0;
    }      
    UDVector& operator = (UDVector&& orig) {
        COUT("UDVector Move Assignment operator");
        delete [] element;
        element = orig.element;
        size = orig.size;
        space = orig.space;
        orig.size = 0;
        orig.element = nullptr;
        orig.space = 0;
        return *this;
    }      
          
          
    virtual ~UDVector() {
        COUT("UDVector Destructor!");
        std::cout << "Destructor type: " << typeid(T).name() << std::endl;
        delete [] element;
        size = 0;
        space = 0;
    }      
    
    
    //Functions
    void reserve(int newAlloc) {
        if(newAlloc <= space) {
            return;
        }
        T* newElements = new T[newAlloc];
        std::copy(element, element + size, newElements);
        delete [] element;
        element = newElements;
        space = newAlloc;
    }
    void resize(int newSize) {
        reserve(newSize);
        for(int i = size; i < newSize; ++i) {
            element[i] = nullptr;
        }
        size = newSize;
    }
    void pushBack(T newElem) {
        if(space == 0) {
            reserve(SPACE);
        }
        else if(size == space) {
            reserve(2 * space);
        }
        element[size] = newElem;
        ++size;
    }
    size_t getSize() const {
        return size;
    }
    size_t getReserveSpace() const {
        return space;
    }
    T& operator [] (int index) {
        return element[index];
    }
    const T operator [] (int index) const {
        return element[index];
    }
};



#endif /* UDVECTOR_H */

