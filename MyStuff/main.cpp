/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: default
 *
 * Created on February 7, 2019, 10:10 AM
 */

#include <cstdlib>
#include <iostream>

#include "vairables/chapterDQuizz.h"
#include "utils/Bits.h"
#include "vairables/enumStructs.h"
#include <experimental/filesystem>
using namespace std;

/*
 * 
 */

double percent(double from, double to) {
    return ((to - from) / from) * 100;
}

int main(int argc, char** argv) {

    bubbleSort();
    
    return 0;
}

