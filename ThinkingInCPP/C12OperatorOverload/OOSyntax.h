/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   OOSyntax.h
 * Author: default
 *
 * Created on December 7, 2019, 12:40 PM
 */

#ifndef OOSYNTAX_H
#define OOSYNTAX_H

#include <iostream>


class Integer {
    int value;
public:
    Integer(int val = 0) : value{val} {}
    
    const Integer operator + (const Integer& rightVal) const {
        std::cout << "Operator + used\n";
        return Integer(value + rightVal.value);
    }
    Integer& operator += (const Integer& rightVal) {
        std::cout << "Operator += used\n";
        value += rightVal.value;
        return *this;
    }
};


void testOperatorOInteger() {
    Integer first{1}, second{2}, third{3};
    third += first + second;
}

//Unary operators overloading using friend functions (non-member functions)
class IntegerV2 {
    long value;
    IntegerV2* This() { return this; }
public:
    IntegerV2(int val = 0) : value{val} {}
    
    //No side effects takes const&
    friend const IntegerV2& operator + (const IntegerV2& rightVal);
    friend const IntegerV2 operator - (const IntegerV2& rightVal);
    friend const IntegerV2 operator ~ (const IntegerV2& rightVal);
    friend IntegerV2* operator & (IntegerV2& rightVal);
    friend int operator ! (const IntegerV2& rightVal);
    
    //Side effects have non-const& argument.
    friend const IntegerV2& operator ++ (IntegerV2& rightVal);          //Postfix
    friend const IntegerV2 operator ++ (IntegerV2& rightVal, int);      //Prefix
    friend const IntegerV2& operator -- (IntegerV2& rightVal);          //Postfix
    friend const IntegerV2 operator -- (IntegerV2& rightVal, int);      //Prefix
};
//Global operators for IntegerV2
const IntegerV2& operator + (const IntegerV2& rightVal) {
    std::cout << "operator + used: ";
    return rightVal;
}
const IntegerV2 operator - (const IntegerV2& rightVal) {
    std::cout << "operator - used: ";
    return IntegerV2(-rightVal.value);
}
const IntegerV2 operator ~ (const IntegerV2& rightVal) {
    std::cout << "operator ~ used: ";
    return IntegerV2(~rightVal.value);
}
IntegerV2* operator & (IntegerV2& rightVal) {
    std::cout << "operator & used: ";
    return rightVal.This();
} 
int operator ! (const IntegerV2& rightVal) {
    std::cout << "operator ! used: ";
    return !rightVal.value;
}
//Prefix return incremented value
const IntegerV2& operator ++ (IntegerV2& rightVal) {
    std::cout << "operator ++rightVal used: ";
    rightVal.value++;
    return rightVal;
}

//Postfix return the value before increment
const IntegerV2 operator ++ (IntegerV2& rightVal, int) {
    std::cout << "operator rightVal++ used: ";
    IntegerV2 before(rightVal.value);
    rightVal.value++;
    return before;
}
//Prefix return decremented value
const IntegerV2& operator -- (IntegerV2& rightVal) {
    std::cout << "operator --rightVal used: ";
    rightVal.value--;
    return rightVal;
}

//Postfix return the value before decrement
const IntegerV2 operator -- (IntegerV2& rightVal, int) {
    std::cout << "operator rightVal-- used: ";
    IntegerV2 before(rightVal.value);
    rightVal.value--;
    return before;
}
void testIntegerV2(IntegerV2 myInt) {
    std::cout << "\n############# IntegerV2 Test!\n";
    +myInt;
    std::cout << std::endl;
    -myInt;
    std::cout << std::endl;
    ~myInt;
    std::cout << std::endl;
    IntegerV2* myIntPtr = &myInt;
    std::cout << std::endl;
    !myInt;
    std::cout << std::endl;
    ++myInt;
    std::cout << std::endl;
    myInt++;
    std::cout << std::endl;
    --myInt;
    std::cout << std::endl;
    myInt--;
    std::cout << std::endl;
}


//Operator overload member functions
class Byte {
    unsigned char value;
public:
    Byte(unsigned char val = 0) : value{val} {}
    //No Side effects const member functions
    const Byte& operator + () const {
        std::cout << "operator + used: ";
        return *this;
    }
    const Byte operator - () const {
        std::cout << "operator - used: ";
        return Byte(-value);
    }
    const Byte operator ~ () const {
        std::cout << "operator ~ used: ";
        return Byte(~value);
    }
    Byte operator ! () const {
        std::cout << "operator ! used: ";
        return Byte(!value);
    }
    Byte* operator & () {
        std::cout << "operator & used: ";
        return this;
    }
    // Side effects non-const member functions
    //Prefix
    const Byte& operator ++ () {
        std::cout << "operator ++value used: ";
        value++;
        return *this;
    }
    //Postfix
    const Byte operator ++ (int) {
        std::cout << "operator value++ used: ";
        Byte before{value};
        value++;
        return before;
    }
    //Prefix
    const Byte& operator -- () {
        std::cout << "operator --value used: ";
        value--;
        return *this;
    }
    //Postfix
    const Byte operator -- (int) {
        std::cout << "operator value-- used: ";
        Byte before{value};
        value--;
        return before;
    }
}; //end class Byte

void testMemberOverload(Byte b) {
    std::cout << "\n############# Byte Test!\n";
    +b;
    std::cout << std::endl;
    -b;
    std::cout << std::endl;
    ~b;
    std::cout << std::endl;
    Byte* bp = &b;
    std::cout << std::endl;
    !b;
    std::cout << std::endl;
    ++b;
    std::cout << std::endl;
    b++;
    std::cout << std::endl;
    --b;
    std::cout << std::endl;
    b--;
    std::cout << std::endl;
}

void testIntandByte() {
    IntegerV2 myInt;
    testIntegerV2(myInt);
    Byte myBt;
    testMemberOverload(myBt);
}

#endif /* OOSYNTAX_H */

