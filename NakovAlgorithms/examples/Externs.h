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
extern void iterativeVariant(int n);

//Ex 1.165
extern void printLuckyNumbers(int n, int steps);

//Ex 1.168
//Iterative tribonaci
extern void printTribonaci(int n);
extern void printFibFromRow(unsigned int row, unsigned long n);


//Ex 1.170
extern void sumOfSquares(int n);

//Ex 1.174
extern void sumInInterval(int n);

//Ex 1.178
extern void pitagorNumbers(int n);

//Ex 1.182
extern void printIterPyramid(int n, bool bType = false);

//Ex 1.183
extern void printIterKare(int n);

//Ex 1.184
extern void magicSquare(int n);

//Ex 1.187
extern void transpondMatrix();
#endif /* EXTERNS_H */

