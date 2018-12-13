/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Recursive.h
 * Author: default
 *
 * Created on November 28, 2018, 1:05 PM
 */

#ifndef RECURSIVE_H
#define RECURSIVE_H

class Recursive {
    static int constexpr MAX_FIB = 10000;
    //Use this to avoid sqrt(5) reducing the operations in the equation.
    static constexpr float SQUARE_OF_FIVE = 2.23607;
    int fibNext[MAX_FIB];
    int tribNext[MAX_FIB];
private:
    
    
    
public:
    static unsigned long factoriel(int n);
    static unsigned long naturalNumsSum(int n);
    static unsigned long naturalNumsSumFrom(int start, int n);
    static unsigned long fib(int n);
    
    //Non recursive method for finging Nth fibonaci number. Effective for N >>> 0.
    static unsigned long moaverFib(int n);
    
    static unsigned long GCD(int first, int second);
    static unsigned long NOK(int numbers[], int next);
    static void cutDrobs(int a, int b);
    
    
    static void printN(int n);
    
    //Recursion with global variables. Doesnt use stack memory.
    static unsigned long factoriel2();
    static void testFactoriel2();
    
    /////////////////
    static void printRed(int k, long result); 
    
    /**
     * Fibonaci with memorization.
     */
    unsigned long fibMem(int n);
    void testFibMem();
    
    //Ex 1.168
    /**
     * Числа на трибоначи.
     */
    static unsigned long tribonaci(unsigned long n);
    unsigned long tribMem(unsigned long n);
    void testTribMem();
    
    //Ex 1.169
    static unsigned long fibFromRow(unsigned int row, unsigned long n);
    
    
    //Ex 1.177
    static unsigned int palindrome(int n);
    static void testPalindrom(int n);
    
    //Ex 1.182
    static void printPiramid(int n, int stop);
    
    static int initArray(int n, int size);
    static void testRecInitArray();
};

#endif /* RECURSIVE_H */

