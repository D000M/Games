/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Externs.h
 * Author: default
 *
 * Created on November 23, 2018, 11:34 AM
 */

#ifndef EXTERNS_H
#define EXTERNS_H

#include <string>

extern void digitsOfNumber(int n);
extern void calculateDivisionAndMod(int n, int m);
extern void sumOfFirstNNumbers(int n);
extern int NOD(int m, int n);
extern void binoms();
extern void testBinaryToHex(const std::string& number);
extern void binaryToHex(const std::string& binary);
extern void testBinaryToOct(const std::string& number);
extern void decToBinary(int decimal);
extern void decToOctal(int number);
extern void decToHex(int number);

extern void decToPTypeSystem(int number, int base);

//Roman digits
extern void testDecimalToRoman(int n);

//Excercises
//Ex 1.157
extern void testEx1();
//Ex 1.158
extern void sievePrimes(int size);
//Ex 1.161
extern void testEx1161(int n);

//Ex 1.162
extern void testEx1162(const std::string& s);
#endif /* EXTERNS_H */

