/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: default
 *
 * Created on November 7, 2018, 11:37 AM
 */

#include <cstdlib>

#include "lecture1/CeaserCipher.h"
#include "lecture1/CeaserDecrypthor.h"
#include "lecture1/ViginerCipher.h"
#include "lecture1/ViginerDecryptor.h"

using namespace std;

/*
 * 
 */

void testCeaserEncrypt() {
    CeaserCipher text("files/TextToEncrypt.txt", 5);
    text.encryptFile();
    text.saveResult("files/EncryptedText5.txt");
}

void testCeaserDecryptor() {
    CeaserDecrypthor decrypt("files/EncryptedText5.txt", 5);
    decrypt.decrypt();
    decrypt.saveDecrypredFile("files/DecryptedText5.txt");
}

void testViginerCipher() {
    ViginerCipher vs{"files/vsTextToEncrypt.txt", "crypto"};
    vs.encrypt();
    vs.saveEncryptedFile("files/vsEncryptefFile.txt");
}

void testViginerDecryptor() {
    ViginerDecryptor vd{"files/vsEncryptefFile.txt", "crypto"};
    vd.decrypt();
    vd.saveDecrypted("files/vsDecryptedFile.txt");
}

int main(int argc, char** argv) {
    
    testViginerDecryptor();
    
    return 0;
}

