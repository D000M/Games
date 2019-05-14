/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Rational.h
 * Author: default
 *
 * Created on March 22, 2019, 5:41 PM
 */

#ifndef RATIONAL_H
#define RATIONAL_H

#include <ostream>
#include <iostream>


class Rational {
private:
    int numerator;
    int denominator;
public:
    Rational() {
        numerator = 1;
        denominator = 1;
    }
    Rational(int n, int d) {
        numerator = n;
        denominator = d;
    }
    Rational(const Rational& obj) {
        numerator = obj.numerator;
        denominator = obj.denominator;
    }
    
    void setNumerator(int n) {
        if(numerator == 0) {
            numerator = 1;
        }
        else {
            numerator = n;
        }
    }
    int getNumerator() const {
        return numerator;
    }
    void setDenominator(int n) {
        if(denominator == 0) {
            denominator = 1;
        }
        else {
            denominator = n;
        }
    }
    int getDenominator() const {
        return denominator;
    }
    
    Rational operator + (const Rational& obj) {
        Rational temp;
        temp.numerator = (numerator * obj.denominator) + (obj.numerator * denominator);
        temp.denominator = denominator * obj.denominator;
        return temp;
    }
    friend Rational operator + (const Rational& left, const Rational right);
    friend std::ostream& operator << (std::ostream& out, const Rational& obj); 
};
std::ostream& operator << (std::ostream& out, const Rational& obj) {
    out << obj.numerator << "/" << obj.denominator << std::endl;
    return out;
}
Rational operator + (const Rational& left, const Rational& right) {
    Rational temp;
    temp.setNumerator((left.getNumerator() * right.getDenominator()) + (right.getNumerator() * left.getDenominator()));
    temp.setDenominator((left.getDenominator() * right.getDenominator()));
    return temp;
}
#endif /* RATIONAL_H */

