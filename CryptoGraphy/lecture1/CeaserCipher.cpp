/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   CeaserCipher.cpp
 * Author: default
 * 
 * Created on November 7, 2018, 11:39 AM
 */



#include <iostream>
#include <sstream>

#include "CeaserCipher.h"

CeaserCipher::CeaserCipher() 
    : file{},
      encryptionNum{},
      encryptedText{} {
}

CeaserCipher::CeaserCipher(const std::string& filePath, int pos) 
    : file{filePath}, 
      encryptionNum{pos}, 
      encryptedText{""} {
        if(!file.is_open()) {
            std::cerr << "File: " << filePath << ", cannot be opened for reading!\n";
            return;
        }
        encryptedText = textToString(file);
}

void CeaserCipher::openFile(const std::string& filePath) {
    
    file.open(filePath);
    
    if(!file.is_open()) {
        std::cerr << "File: " << filePath << ", cannot be opened for reading!\n";
        return;
    }
    encryptedText = textToString(file);
}

void CeaserCipher::openFile(const std::string& filePath, int pos) {
    file.open(filePath);
    
    if(!file.is_open()) {
        std::cerr << "File: " << filePath << ", cannot be opened for reading!\n";
        return;
    }
    encryptedText = textToString(file);
    encryptionNum = pos;
    
}

void CeaserCipher::saveResult(const std::string& saveTo) {
    
    if(!file.is_open()) {
        std::cerr << "File: " << saveTo << ", cannot be opened for reading!\n";
        return;
    }

    if(encryptedText == "") {
        return;
    }
        
    std::ofstream writeTo{saveTo};
    
    if(!writeTo.is_open()) {
        std::cerr << "File: " << saveTo << ", cannot be opened for writing!\n";
        return;
    }
    writeTo << encryptedText;
    file.close();
    writeTo.close();
}

void CeaserCipher::encryptFile() {
    std::cout << "Before: \n" << encryptedText << std::endl;
    for(int i = 0; i < encryptedText.length(); i++) {
        if(encryptedText.at(i) != '\n') {
            encryptedText.at(i) += encryptionNum;
        }
    }
    std::cout << "After: \n" << encryptedText << std::endl;
}

void CeaserCipher::setEncriptionNum(int pos) {
    encryptionNum = pos;
}

std::string CeaserCipher::textToString(std::ifstream& f) {
    return static_cast<std::stringstream const&>(std::stringstream() << f.rdbuf()).str();
}

    

