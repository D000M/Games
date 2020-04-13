/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   OperatorOverloadingAndInheritance.h
 * Author: default
 *
 * Created on December 20, 2019, 1:03 PM
 */

#ifndef OPERATOROVERLOADINGANDINHERITANCE_H
#define OPERATOROVERLOADINGANDINHERITANCE_H
#include <iostream>
//virtual operator overloading
//Polymorphism with OO

class Matrix;
class Scalar;
class Vector;

class Math {
public:
    virtual ~Math() {
        std::cout << "~Math Destructor\n";
    }
    virtual Math& operator * (Math& rightVal) = 0;
    virtual Math& multiply(Matrix*) = 0;
    virtual Math& multiply(Scalar*) = 0;
    virtual Math& multiply(Vector*) = 0;
    
};

class Matrix : public Math {
public:
    virtual ~Matrix() {
        std::cout << "~Matrix Destructor\n";
    }
    Math& operator * (Math& rightVal) {
        return rightVal.multiply(this); //2nd dispatch
    }
    Math& multiply(Matrix*) {
        std::cout << "Matrix * Matrix\n";
        return *this;
    }
    Math& multiply(Scalar*) {
        std::cout << "Scalar * Matrix\n";
        return *this;
    }
    Math& multiply(Vector*) {
        std::cout << "Vector * Matrix\n";
        return *this;
    }
};

class Scalar : public Math {
public:
    virtual ~Scalar() {
        std::cout << "~Scalar Destructor\n";
    }
    Math& operator * (Math& rightVal) {
        return rightVal.multiply(this); //2nd dispatch
    }
    Math& multiply(Matrix*) {
        std::cout << "Matrix * Matrix\n";
        return *this;
    }
    Math& multiply(Scalar*) {
        std::cout << "Scalar * Matrix\n";
        return *this;
    }
    Math& multiply(Vector*) {
        std::cout << "Vector * Matrix\n";
        return *this;
    }
};

class Vector : public Math {
public:
    virtual ~Vector() {
        std::cout << "~Vector Destructor\n";
    }
    Math& operator * (Math& rightVal) {
        return rightVal.multiply(this); //2nd dispatch
    }
    Math& multiply(Matrix*) {
        std::cout << "Matrix * Matrix\n";
        return *this;
    }
    Math& multiply(Scalar*) {
        std::cout << "Scalar * Matrix\n";
        return *this;
    }
    Math& multiply(Vector*) {
        std::cout << "Vector * Matrix\n";
        return *this;
    }
};

void testMultiply() {
//    Matrix m;
//    Vector v;
//    Scalar s;
    Math* arr[] = {new Matrix, new Vector, new Scalar};
    
    for(int i = 0; i < 3; i++) {
        for(int j = 0; j < 3; j++){
            Math& m1 = *arr[i];
            Math& m2 = *arr[j];
            m1 * m2;
        }
    }
    for(int i = 0; i < 3; i++) {
        delete arr[i];
    }
}
#endif /* OPERATOROVERLOADINGANDINHERITANCE_H */

