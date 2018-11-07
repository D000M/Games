/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   ViginerDecryptor.cpp
 * Author: default
 * 
 * Created on November 7, 2018, 4:09 PM
 */

#include <fstream>
#include <iostream>
#include <sstream>
#include "ViginerDecryptor.h"
//#include "utils.h"


std::string ViginerDecryptor::textToString(std::ifstream& f) {
    return static_cast<std::stringstream const&>(std::stringstream() << f.rdbuf()).str();
}

ViginerDecryptor::ViginerDecryptor(const std::string& f, const std::string& k) {
    std::ifstream file{f};
    
    if(!file.is_open()) {
        std::cerr << "Error opening file: " << f << std::endl; 
        return;
    }
    
    decryptedText = textToString(file);
    file.close();
    key = k;
}

void ViginerDecryptor::decrypt() {
    int length = key.length();
    int begin = 0;
    
    while(key.length() < decryptedText.length()) {
        key += key.at(begin);
        begin++;
        if(begin == length) {
            begin = 0;
        }
    }
    
    for(int i = 0; i < decryptedText.length(); i++) {
        int a = ((decryptedText.at(i) - key.at(i)) + 26) % 26;
        a += 'a';
        decryptedText.at(i) = a;
        std::cout << a << " " ;
    }
}

void ViginerDecryptor::saveDecrypted(const std::string& toF) {
    if(decryptedText == "") {
        return;
    }
//    std::cout << decryptedText << std::endl;
    std::ofstream writeTo{toF};
    if(!writeTo.is_open()) {
        std::cerr << "Error opening file: " << toF << std::endl;
        return;
    }
    
    writeTo << decryptedText;
    writeTo.close();
}
