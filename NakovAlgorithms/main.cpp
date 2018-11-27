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
#include <iostream>

using namespace std;

/*
 * 
 */


int main(int argc, char** argv) {

    testBinaryToOct("10001");
    testBinaryToHex("10001");
    decToBinary(17);
    decToOctal(17);
    decToHex(17);
    decToBinary(-17);
    decToOctal(-17);
    decToHex(10);
    
    decToPTypeSystem(17, 2);
    decToPTypeSystem(17, 8);
    decToPTypeSystem(10, 16);
    std::cout << "---------\n";
    decToPTypeSystem(10, 3);
    decToPTypeSystem(10, 5);
    decToPTypeSystem(10, 7);
    decToPTypeSystem(10, 14);
    
    std::cout << "-----------\n";
    FromDecimal number(10, 3);
    std::cout << number << std::endl;
    number.setSystem(10, 5);
    std::cout << number << std::endl;
    
    std::cout << "------------\n";
    ToDecimal decNumber("FFF", 16);
    std::cout << decNumber << std::endl;
    decNumber.setNumber("20", 5);
    std::cout << decNumber << std::endl;
    return 0;
}

