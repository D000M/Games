/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   C12Excercises.h
 * Author: default
 *
 * Created on December 9, 2019, 3:25 PM
 */

#ifndef C12EXCERCISES_H
#define C12EXCERCISES_H
#include <iostream>
#include <string>
#include <ostream>

class SimpleOpPlusPlus {
    std::string name;
public:
    SimpleOpPlusPlus(const std::string& setName) : name{setName} {}
    
    const SimpleOpPlusPlus& operator ++ () {
        std::cout << "PreFix operator ++ used\n";
        name = "Pre " + name;
        return *this;
    }
    const SimpleOpPlusPlus operator ++ (int) {
        std::cout << "PostFix operator ++ used\n";
        SimpleOpPlusPlus before(name);
        name = name + " postfix";
        return before;
    }
    friend std::ostream& operator << (std::ostream& out, const SimpleOpPlusPlus& obj) {
        out << obj.name << std::endl;
        return out;
    }
};
void testEx1C12() {
    SimpleOpPlusPlus preTest{"Vanya"};
    ++preTest;
    std::cout << "PreFix operator: " << preTest;
    SimpleOpPlusPlus postFix{"Elina"};
    std::cout << "PostFix operator: " << postFix++;
    std::cout << "After PostFix operator: " << postFix << std::endl;
}

class Ex2C12 {
    int value;
public:
    Ex2C12(int v = 0) : value{v} {}
    const Ex2C12& operator + (const Ex2C12& rightVal) {
        std::cout << "Operator + used: ";
        value += rightVal.value;
        return *this;
    }
    Ex2C12 operator - (const Ex2C12& rightVal) const {
        std::cout << "Operator - used: ";
        return Ex2C12(value - rightVal.value);
    }
    const Ex2C12& operator ++ () {
        value++;
        return *this;
    }
    const Ex2C12 operator ++ (int) {
        Ex2C12 before{value};
        value++;
        return before;
    }
    const Ex2C12& operator -- () {
        value--;
        return *this;
    }
    const Ex2C12 operator -- (int) {
        Ex2C12 before{value};
        value--;
        return before;
    }
    void print(std::ostream& out) {
        out << value << std::endl;
    }
};

void testEx2C12() {
    Ex2C12 v1{10};
    Ex2C12 v2{15};
    Ex2C12 v3{20};
    v1 = v1 + v2 - v3;
    v1.print(std::cout);
    v1++;
    v1.print(std::cout);
    ++v1;
    v1.print(std::cout);
    v1--;
    v1.print(std::cout);
//    --v1.print(std::cout);
    --v1;
    v1.print(std::cout);
   
}

class MyNumber {
    double value;
public:
    MyNumber(const double& val = 0) : value{val} {
        std::cout << "MyNumber Constructor used\n";
    }
    
    const MyNumber& operator + (const MyNumber& rightVal){
        value += rightVal.value;
        return *this;
    }
    MyNumber operator - (const MyNumber& rightVal) const {
        
        return MyNumber(value - rightVal.value);
    }
    const MyNumber& operator * (const MyNumber& rightVal) {
        value *= rightVal.value;
        return *this;
    }
    const MyNumber& operator / (const MyNumber& rightVal) {
        value /= rightVal.value;
        return *this;
    }
    
    operator MyNumber () const {
        std::cout << "Operator () used!\n";
        return MyNumber(value);
    }
    
    friend std::ostream& operator << (std::ostream& out, const MyNumber& obj) {
        out << obj.value << std::endl;
        return out;
    }
    
};

void testAutoConversion(MyNumber) {
    
}

void testMyNumber() {
    MyNumber v1{15.5};
    MyNumber v2{23.25};
    MyNumber v3{5.75};
    v1 = v1 + v2 * v3 - v2;
    std::cout << v1 << v2 << v3 <<std::endl;
    MyNumber testAutoConv{10};
    testAutoConversion(testAutoConv);
    testAutoConversion(50);
}
#endif /* C12EXCERCISES_H */

