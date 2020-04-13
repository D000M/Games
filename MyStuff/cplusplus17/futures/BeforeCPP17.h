/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   BeforeCPP17.h
 * Author: default
 *
 * Created on February 15, 2019, 12:53 PM
 */

#ifndef BEFORECPP17_H
#define BEFORECPP17_H

#include <utility>
#include <iostream>

std::pair<int, int> divideRemainder(int divident, int div) {
    std::pair<int, int> result;
    result.first = divident / div;
    result.second = divident % div;
    return result;
}
void printPair() {
    const auto result(divideRemainder(13, 4));
    std::cout << result.first << " with remainder: " << result.second << std::endl;
}
#endif /* BEFORECPP17_H */

