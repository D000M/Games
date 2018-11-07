/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   ViginerCipher.cpp
 * Author: default
 * 
 * Created on November 7, 2018, 3:14 PM
 */

#include <string>
#include <fstream>
#include <iostream>
#include <sstream>
#include "ViginerCipher.h"
//#include "utils.h"

std::string textToString(std::ifstream& f) {
    return static_cast<std::stringstream const&>(std::stringstream() << f.rdbuf()).str();
}

ViginerCipher::ViginerCipher(const std::string& f, const std::string& keyWord)
    : key{keyWord} {
    
    std::ifstream file{f};
    
    if(!file.is_open()) {
        std::cerr << "Error opening file: " << f << std::endl;
        return;
    }
    textToEncrypt = textToString(file);
    file.close();
}

void ViginerCipher::encrypt() {
    
    int length = key.length();
    std::cout << "Key Length: " << length << std::endl;
    int begin = 0;

    while(key.length() < textToEncrypt.length()) {
        key += key.at(begin);
        begin++;
        if(begin == length) {
            begin = 0;
        }
    }
    std::string result = "";
    for(int i = 0; i < textToEncrypt.length(); i++) {
        int a = (textToEncrypt.at(i) + key.at(i)) % 26;
        a += 'a';
        textToEncrypt.at(i) = a;
        std::cout << textToEncrypt.at(i) << " ";
    }
}

void ViginerCipher::saveEncryptedFile(const std::string& writeTo) {
    if(textToEncrypt == "") {
        return;
    }
    std::ofstream file{writeTo};
    if(!file.is_open()) {
        std::cerr << "Error opening file: " << writeTo << std::endl;
        return;
    }
    
    file << textToEncrypt;
    file.close();
}
