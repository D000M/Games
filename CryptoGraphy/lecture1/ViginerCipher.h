/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   ViginerCipher.h
 * Author: default
 *
 * Created on November 7, 2018, 3:13 PM
 */

#ifndef VIGINERCIPHER_H
#define VIGINERCIPHER_H

class ViginerCipher {
public:
    ViginerCipher(const std::string& readFrom, const std::string& keyWord);
    
    void encrypt();
    void saveEncryptedFile(const std::string& writeTo);
private:
    std::string textToEncrypt;
    std::string key;
};

#endif /* VIGINERCIPHER_H */

