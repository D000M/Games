/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   ByteMemberBinaryOO.h
 * Author: default
 *
 * Created on December 7, 2019, 2:05 PM
 */

#ifndef BYTEMEMBERBINARYOO_H
#define BYTEMEMBERBINARYOO_H


//Member functions operator overload implicit this
class ByteV2 {
    unsigned char value;
public:
    ByteV2(unsigned char val = 0) : value{val} {}
    //No side effect const member functions
    const ByteV2 operator + (const ByteV2& right) const {
        return ByteV2(value + right.value);
    }
    const ByteV2 operator - (const ByteV2& right) const {
        return ByteV2(value - right.value);
    }
    const ByteV2 operator * (const ByteV2& right) const {
        return ByteV2(value * right.value);
    }
    const ByteV2 operator / (const ByteV2& right) const {
        if(right.value == 0) {
            throw ("ERROR Division by 0");
        }
        return ByteV2(value / right.value);
    }
    const ByteV2 operator % (const ByteV2& right) const {
        if(right.value == 0) {
            throw ("ERROR Modulus by 0");
        }
        return ByteV2(value % right.value);
    }
    const ByteV2 operator ^ (const ByteV2& right) const {
        return ByteV2(value ^ right.value);
    }
    const ByteV2 operator & (const ByteV2& right) const {
        return ByteV2(value & right.value);
    }
    const ByteV2 operator | (const ByteV2& right) const {
        return ByteV2(value | right.value);
    }
    const ByteV2 operator << (const ByteV2& right) const {
        return ByteV2(value << right.value);
    }
    const ByteV2 operator >> (const ByteV2& right) const {
        return ByteV2(value >> right.value);
    }
    
    //Assignment modify and return value
    //operator = can only be a member function
    ByteV2& operator = (const ByteV2& right) {
        //Handle self assignment
        if(this == &right) {
            return *this;
        }
        value = right.value;
        return *this;
    }
    
    ByteV2& operator += (const ByteV2& right) {
        if(this == &right){
            //Self assignment
        }
        value += right.value;
        return *this;
    }
    ByteV2& operator -= (const ByteV2& right) {
        if(this == &right){
            //Self assignment
        }
        value -= right.value;
        return *this;
    }
    ByteV2& operator *= (const ByteV2& right) {
        if(this == &right){
            //Self assignment
        }
        value *= right.value;
        return *this;
    }
    ByteV2& operator /= (const ByteV2& right) {
        if(this == &right){
            throw("ERROR Divide by 0");
        }
        value /= right.value;
        return *this;
    }
    ByteV2& operator %= (const ByteV2& right) {
        if(this == &right){
            throw("ERROR Modulus by 0");
        }
        value %= right.value;
        return *this;
    }
    ByteV2& operator ^= (const ByteV2& right) {
        if(this == &right){
            
        }
        value ^= right.value;
        return *this;
    }
    ByteV2& operator &= (const ByteV2& right) {
        if(this == &right){
            
        }
        value &= right.value;
        return *this;
    }
    ByteV2& operator |= (const ByteV2& right) {
        if(this == &right){
            
        }
        value |= right.value;
        return *this;
    }
    ByteV2& operator >>= (const ByteV2& right) {
        if(this == &right){
            
        }
        value >>= right.value;
        return *this;
    }
    ByteV2& operator <<= (const ByteV2& right) {
        if(this == &right){
            
        }
        value <<= right.value;
        return *this;
    }
    
    //Conditionals operators returns true/false.
    int operator == (const ByteV2& right) const {
        return value == right.value;
    }
    int operator != (const ByteV2& right) const {
        return value != right.value;
    }
    int operator < (const ByteV2& right) const {
        return value < right.value;
    }
    int operator > (const ByteV2& right) const {
        return value > right.value;
    }
    int operator <= (const ByteV2& right) const {
        return value <= right.value;
    }
    int operator >= (const ByteV2& right) const {
        return value >= right.value;
    }
    int operator && (const ByteV2& right) const {
        return value && right.value;
    }
    int operator || (const ByteV2& right) const {
        return value || right.value;
    }
    
    void print(std::ostream& out) const {
        out << int(value) << std::dec;
    }
};

#endif /* BYTEMEMBERBINARYOO_H */

