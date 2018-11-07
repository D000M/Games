/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   CeaserDecrypthor.h
 * Author: default
 *
 * Created on November 7, 2018, 12:11 PM
 */

#ifndef CEASERDECRYPTHOR_H
#define CEASERDECRYPTHOR_H

#include <fstream>


class CeaserDecrypthor {
    
public:
    
    CeaserDecrypthor(const std::string& f, int pos);
    
    void decrypt();
    void saveDecrypredFile(const std::string& saveTo);
    
    std::string textToString(std::ifstream& f);
private:
    
    std::string decryptedText;
    int decryptor;
};

#endif /* CEASERDECRYPTHOR_H */

