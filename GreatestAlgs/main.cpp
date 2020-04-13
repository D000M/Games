/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: default
 *
 * Created on February 28, 2019, 5:09 PM
 */

#include <cstdlib>

#include "tests/TestSets.h"
#include "divideAndConquer/TestDAC.h"

using namespace std;

/*
 * 
 */
void testProportion() {
    float uhdWidth = 4096.0f;
    float uhdHeight = 2160.0f;
    float fhdWidth = 1920.0f;
    float fhdHeight = 1080.0f;
    float coeffX = uhdHeight / fhdHeight;
    float coeffY = uhdWidth / fhdWidth;
    
    std::cout << "x coeff: " << coeffX << ", t coeff: " << coeffY << std::endl; 
}

int main(int argc, char** argv) {
    
   testProportion();
    
    return 0;
}

