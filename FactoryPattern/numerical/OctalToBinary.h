/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   OctalToBinary.h
 * Author: default
 *
 * Created on April 10, 2019, 12:22 PM
 */

#ifndef OCTALTOBINARY_H
#define OCTALTOBINARY_H

#include <cstdio>
#include <string>


const int OCTAL = 8; 

const std::string octalDigits[OCTAL] = {
    "000",
    "001",
    "010",
    "011",
    "100",
    "101",
    "110",
    "111"
};  

std::string convertToOctal(const std::string& temp) {
    if(temp == "000") {
        return "0";
    }
    else if(temp == "001") {
        return "1";
    }
    else if(temp == "010") {
        return "2";
    }
    else if(temp == "011") {
        return "3";
    }
    else if(temp == "100") {
        return "4";
    }
    else if(temp == "101") {
        return "5";
    }
    else if(temp == "110") {
        return "6";
    }
    else if(temp == "111") {
        return "7";
    }
    return "";
}

void convertOctalToBinary(const int& octalNumber) {
    int num = octalNumber;
    std::string result = "";
    while(num > 0) {
        int digit = num % 10;
        result = octalDigits[digit] + result;
        num = num / 10;
    }
//    int pos = result.find("1");
//    std::cout << pos << std::endl;
//    for(std::size_t i = 0; i < result.length(); i++) {
//        if(i == pos) {
//            break;
//        }
//        if(i < pos) {
//            std::cout << i << std::endl;
//            result.replace(0, 1, "");
//        }
//
//    }
    std::cout << "Octal Number: " << octalNumber << ", is equal to: " << result << ", in binary.\n";
}

void convertBinaryToOctal(const std::string& binary) {
    std::string bin = binary;

    
    std::string::iterator it = bin.end();
    std::string tempRes = "";
    int count = 0;
    std::string result = "";
    while(it != bin.begin()) {
        
        tempRes = *it + tempRes;
        
        if(count % 3 == 0) {
            result = convertToOctal(tempRes) + result;
            tempRes = "";
            count = 0;
        }
        count++;
        it--;
        
    }
    tempRes = *it + tempRes;
    result = convertToOctal(tempRes) + result;
    std::cout << "The binary number: " << binary << " , is in octal: " << result <<std::endl;
}
#endif /* OCTALTOBINARY_H */

