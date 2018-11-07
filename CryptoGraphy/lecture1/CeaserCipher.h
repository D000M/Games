/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   CeaserCipher.h
 * Author: default
 *
 * Created on November 7, 2018, 11:39 AM
 */

#ifndef CEASERCIPHER_H
#define CEASERCIPHER_H

#include <string>
#include <fstream>

class CeaserCipher {

public:
    CeaserCipher();
    CeaserCipher(const std::string& filePath, int pos);
//    CeaserCipher(const CeaserCipher& orig);
//    virtual ~CeaserCipher();
    
    void openFile(const std::string& filePath);
    void openFile(const std::string& filePath, int pos);
    void setEncriptionNum(int pos);
    
    void saveResult(const std::string& saveTo);
    
    void encryptFile();
    
    std::string textToString(std::ifstream& f);
private:
    std::ifstream file;
    int encryptionNum;
    std::string encryptedText;
};

#endif /* CEASERCIPHER_H */

