/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   ViginerDecryptor.h
 * Author: default
 *
 * Created on November 7, 2018, 4:09 PM
 */

#ifndef VIGINERDECRYPTOR_H
#define VIGINERDECRYPTOR_H

#include <string>


class ViginerDecryptor {
public:
    ViginerDecryptor(const std::string& f, const std::string& keyWord);

    void decrypt();
    void saveDecrypted(const std::string& toF);
    
    std::string textToString(std::ifstream& f);
private:
    
    std::string decryptedText;
    std::string key;
    
};

#endif /* VIGINERDECRYPTOR_H */

