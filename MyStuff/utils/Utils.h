/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Utils.h
 * Author: default
 *
 * Created on February 7, 2019, 5:09 PM
 */

#ifndef UTILS_H
#define UTILS_H

#include <cmath>


// return true if the difference between a and b is less than absEpsilon, 
// or within relEpsilon percent of the larger of a and b
bool approximatelyEqualAbsRel(double a, double b, double absEpsilon, double relEpsilon) {
    // Check if the numbers are really close -- needed when comparing numbers near zero.
    double diff = fabs(a - b);
    std::cout << diff << std::endl;
    if(diff <= absEpsilon) {
        return true;
    }
    
    // Otherwise fall back to Knuth's algorithm
    return diff <= ((fabs(a) < fabs(b) ? fabs(b) : fabs(a)) * relEpsilon);
}

#endif /* UTILS_H */

