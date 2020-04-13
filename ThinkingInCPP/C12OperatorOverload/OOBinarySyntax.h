/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   OOBinarySyntax.h
 * Author: default
 *
 * Created on December 7, 2019, 1:27 PM
 */

#ifndef OOBINARYSYNTAX_H
#define OOBINARYSYNTAX_H
#include <iostream>

class IntegerV3 {
    long value;
public:
    IntegerV3(long val = 0) : value{val} {}
    //Operators that creates new modified value
    friend const IntegerV3 operator + (const IntegerV3& left, const IntegerV3& right);
    friend const IntegerV3 operator - (const IntegerV3& left, const IntegerV3& right);
    friend const IntegerV3 operator * (const IntegerV3& left, const IntegerV3& right);
    friend const IntegerV3 operator / (const IntegerV3& left, const IntegerV3& right);
    friend const IntegerV3 operator % (const IntegerV3& left, const IntegerV3& right);
    friend const IntegerV3 operator ^ (const IntegerV3& left, const IntegerV3& right);
    friend const IntegerV3 operator & (const IntegerV3& left, const IntegerV3& right);
    friend const IntegerV3 operator | (const IntegerV3& left, const IntegerV3& right);
    friend const IntegerV3 operator << (const IntegerV3& left, const IntegerV3& right);
    friend const IntegerV3 operator >> (const IntegerV3& left, const IntegerV3& right);
    
    //Assignments modify return value
    friend IntegerV3& operator += (IntegerV3& left, const IntegerV3& right);
    friend IntegerV3& operator -= (IntegerV3& left, const IntegerV3& right);
    friend IntegerV3& operator *= (IntegerV3& left, const IntegerV3& right);
    friend IntegerV3& operator /= (IntegerV3& left, const IntegerV3& right);
    friend IntegerV3& operator %= (IntegerV3& left, const IntegerV3& right);
    friend IntegerV3& operator ^= (IntegerV3& left, const IntegerV3& right);
    friend IntegerV3& operator &= (IntegerV3& left, const IntegerV3& right);
    friend IntegerV3& operator |= (IntegerV3& left, const IntegerV3& right);
    friend IntegerV3& operator >>= (IntegerV3& left, const IntegerV3& right);
    friend IntegerV3& operator <<= (IntegerV3& left, const IntegerV3& right);
    
    //Conditional operators returns true/false
    friend int operator == (const IntegerV3& left, const IntegerV3& right);
    friend int operator != (const IntegerV3& left, const IntegerV3& right);
    friend int operator < (const IntegerV3& left, const IntegerV3& right);
    friend int operator > (const IntegerV3& left, const IntegerV3& right);
    friend int operator <= (const IntegerV3& left, const IntegerV3& right);
    friend int operator >= (const IntegerV3& left, const IntegerV3& right);
    friend int operator && (const IntegerV3& left, const IntegerV3& right);
    friend int operator || (const IntegerV3& left, const IntegerV3& right);
    
    //write the contents to the ostream
    void print(std::ostream& out) const {
        out << value;
    }
};

#endif /* OOBINARYSYNTAX_H */

