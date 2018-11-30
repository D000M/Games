/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include <cstring>
#include <sstream>
#include <iostream>

const char* roman1_9[] = {
    "", "A", "AA", "AAA", "AB", "B", "BA", "BAA", "BAAA", "AC"
};

const char* romanDigits[] = {
    "IVX", "XLC", "CDM", "M"  
};

void getRomanDigits(char* rslt, char x, unsigned char power) {
    const char *pch;
    for(pch = roman1_9[x]; *pch != '\0'; pch++) {
        *rslt++ = romanDigits[power][*pch - 'A'];
    }
    *rslt = '\0';
}

#define MAX_ROMAN_LENGTH 100

char* decimalToRoman(char* rslt, unsigned int x) {
    unsigned char power;
    char buf[10];
    char oldRslt[MAX_ROMAN_LENGTH];
    
    for(*rslt = '\0', power = 0; x > 0; power++, x /= 10) {
        getRomanDigits(buf, (char)(x % 10), power);
        strcpy(oldRslt, rslt);
        strcpy(rslt, buf);
        strcat(rslt, oldRslt);
    }
    return rslt;
}
std::string toStr(int x) {
    std::stringstream ss;
    ss << x;
    return ss.str();
}
void testDecimalToRoman(int n) {
    char rslt[MAX_ROMAN_LENGTH];
    const char* roman = decimalToRoman(rslt, n);    
    std::cout << roman << std::endl;
}