/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: default
 *
 * Created on January 29, 2020, 1:44 PM
 */

#include <cstdlib>
#include <iostream>
#include <string>
/*
 * 
 */
const char* arr[] = {
  "First",
  "Second"  
};

std::string strArr[] = {
    "str First",
    "str Second"
};
int main(int argc, char** argv) {

    for(auto&& elem : strArr) {
        std::cout << elem << "\n";
    }
    return 0;
}

