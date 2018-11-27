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

#endif /* EXTERNS_H */

