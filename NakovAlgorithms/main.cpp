/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: default
 *
 * Created on November 23, 2018, 10:31 AM
 */

#include <cstdlib>
#include "examples/Externs.h"
#include "examples/FromDecimal.h"
#include "examples/ToDecimal.h"
#include "examples/Recursive.h"
#include "examples/Combinatorics.h"
#include "examples/Coding.h"
#include "chapter2/Examples.h"
#include "chapter3Sorting/CSorting/CExamples.h"
#include "containers/ContExamples.h"
#include "searchAlgs/Searching.h"
#include "CPPSorts/CPPSorts.h"
#include "CPPSearching/CPPSearchs.h"
#include "graphs/CGraphs.h"
#include "graphs/TestGraphs.h"
#include "graphs/ExtremePathsCGraphs.h"
#include "graphs/FindLongestPathCAcyclicGraph.h"
#include "SearchWithReturns/CppAlgs/HorseMoving.h"
#include "SearchWithReturns/CppAlgs/EightQueen.h"
#include <iostream>
#include <complex>
#include <iterator>

using namespace std;

/*
 * 
 */

#define MAXN 100

void testCoding() {
    const unsigned int n = 6;
    const unsigned int perm[MAXN] = {
      5, 3, 6, 4, 2, 1  
    };
    const unsigned long code = 551;
    unsigned int dPerm[MAXN];
    
    Coding c;
    std::cout << "Дадената пермутациа се кодира като: " << c.codePerm(n, perm, n) << std::endl;
    std::cout << "Декодираме пермутациата отговаряща на числото: " << code << "\n";
    c.decodePerm(code, n, dPerm, n);
    for(int i = 0; i < n; i++) {
        std::cout << dPerm[i] << " ";
    }
}
/**
 *  Zaplata 2017: 3771.01
    Zaplata 2018: 4148.12
    Zaplata 2019: 4417.74

 */
extern int tribCount;


void simpleSwap(int a, int b) {
    int temp = a;
    a = b;
    b = temp;
}
int testCnt = 0;
void myPermSort(int arr[], int size) {
    for(int i = 0; i < 20; i++) {
        while(arr[i] != i) {
            testCnt++;
            swap(arr[i], arr[arr[i]]);
        }
    }
}

void testPermSort() {
    int arr[] = {
       5, 10, 6, 2, 3, 8, 1, 15, 17, 19, 4, 7, 18, 0, 9, 11, 14, 16, 12, 13  
    };
    std::copy(arr, arr + 20, std::ostream_iterator<int>(std::cout, " "));
    myPermSort(arr, 20);
    std::cout << std::endl;
    std::copy(arr, arr + 20, std::ostream_iterator<int>(std::cout, " "));
    std::cout << "\n" << "Total Swaps: " << testCnt << std::endl;
}

constexpr int TT = 20;
int myArr[TT] = {};

void printArray() {
    std::cout << std::endl;
    for(int i = 0; i < TT; i++) {
        std::cout << myArr[i] << " ";
    }
}

void initArray(int arr[], int count) {
    if(count < TT) {
        printArray();
        
    }
    else if(count == TT) {
        printArray();
        return;
    }
    arr[count] = count;
    initArray(arr, count + 1);
} 

double percent(double from, double to) {
    return ((to - from) / from) * 100;
}

int main(int argc, char** argv) {
    
    
//    constexpr unsigned int max = -1;
//    std::cout << max << std::endl;

//    testQueens();
    
//    initArray(myArr, 0);
    
    double currIncr = percent(1280, 1324);
    std::cout << "Percent: " << currIncr << "%"; 
    
    size_t a = -5;
    std::cout << a << std::endl;

    return 0;
}

