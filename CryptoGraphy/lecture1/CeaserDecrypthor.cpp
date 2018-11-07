/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   CeaserDecrypthor.cpp
 * Author: default
 * 
 * Created on November 7, 2018, 12:11 PM
 */

#include "CeaserDecrypthor.h"

#include <iostream>
#include <sstream>

CeaserDecrypthor::CeaserDecrypthor(const std::string& f, int pos) {
    std::ifstream file{f};
    if(!file.is_open()) {
        std::cerr << "Error opening file: " << f << std::endl;
        return;
    }
    decryptedText = textToString(file);
    file.close();
    decryptor = pos;
}

std::string CeaserDecrypthor::textToString(std::ifstream& f) {
    return static_cast<std::stringstream const&>(std::stringstream() << f.rdbuf()).str();
}

void CeaserDecrypthor::saveDecrypredFile(const std::string& saveTo) {
        
    if(decryptedText == "") {
        std::cout << "There is nothing to decrypt.\n";
        return;
    }
    
    std::ofstream writeTo{saveTo};

    if(!writeTo.is_open()) {
        std::cerr << "Error opening file for writing: " << saveTo << std::endl;
        return;
    }
    
    writeTo << decryptedText;
    
}

void CeaserDecrypthor::decrypt() {
    for(int i = 0; i < decryptedText.length(); i++) {
        if(decryptedText.at(i) != '\n') {
            decryptedText.at(i) -= decryptor;
        }
    }
}
