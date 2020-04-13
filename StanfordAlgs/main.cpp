/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: default
 *
 * Created on February 20, 2019, 3:09 PM
 */

#include <cstdlib>

#include "mystuff/Multiply.h"
#include "mystuff/sorts/TestSorts.h"
#include "mystuff/divideAndConquer/TestDivideAndConquer.h"
#include "mystuff/divideAndConquer/testStrasen.h"
#include "MasterAlgs/SparseMatrix.h"

using namespace std;

/*
 * 
 */

int main(int argc, char** argv) {
    
//    testSimpleMultiply();       // Total operations: 32768

    testSparce();
    
    return 0;
}

