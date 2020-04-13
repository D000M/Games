/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   ConstantsInTemplates.h
 * Author: default
 *
 * Created on December 20, 2019, 3:24 PM
 */

#ifndef CONSTANTSINTEMPLATES_H
#define CONSTANTSINTEMPLATES_H
//Create Array with default size 100
template<class T, int size = 100>
class ConstantArray {
    T array[size];
public:
    T& operator [] (int index) {
        if(index < 0 || index >= size) {
            throw("Error out of bounds\n");
        }
        return array[index];
    }     
    int length() const {
        return size;
    }
};
class Number {
    float f;
public:
    Number(float ff = 0.0f) : f{ff} {}
    Number& operator = (const Number& n) {
        f = n.f;
        return *this;
    }
    operator float () const {
        return f;
    }
    friend std::ostream& operator << (std::ostream& os, const Number& obj) {
        return os << obj.f;
    }
};
template<typename T, int size = 20>
class Holder {
    ConstantArray<T, size>* nPtr;
public:
    Holder() : nPtr{nullptr} {}
    T& operator [] (int index) {
        if(index < 0 || index >= size) {
            throw ("Error out of bounds");
        }
        if(nPtr == nullptr) {
            nPtr = new ConstantArray<T, size>;
        }
        return nPtr->operator [](index);
    }
    int length() const {
        return size;
    }
    ~Holder() {
        delete nPtr;
    }
};
void testTemplateConstants() {
    Holder<Number> h;
    for(int i = 0; i < 20; i++) {
        h[i] = i;
    }
    for(int i = 0; i < 20; i++) {
        std::cout << h[i] << " ";
    }
}
#endif /* CONSTANTSINTEMPLATES_H */

