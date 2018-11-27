/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include <iostream>
//#include <X11/Xlibint.h>
#include <algorithm>
#include <valarray>

#include "Externs.h"


void digitsOfNumber(int n) {
    std::cout << "The number: " << n << " has ";
    int digits = 0;
    for(; n > 0; n /= 10, digits++);
    std::cout << digits << " digits." << std::endl;
}

void calculateDivisionAndMod(int n, int m) {
    std::cout << n << " / " << m << " = ";
    std::cout << (n / m) << std::endl;
    std::cout << n << " % " << m << " = ";
    std::cout << (n % m) << std::endl;
}

int recSum(int n) {
    if(n == 0) {
        return 0;
    }
    return recSum(n - 1) + n;
}

void sumOfFirstNNumbers(int n) {
    int res = recSum(n);
    std::cout << "S = " << res << std::endl;
}

int NOD(int m, int n) {
    if(n == 0) {
        return m;
    }
    return NOD(n, m % n);
}

void binoms() {
    const int MAXN = 1000;
    const int n = 10;
    const int k = 3;
    
    long lastLine[MAXN + 1];
    
    lastLine[0] = 1;
    std::cout << lastLine[0] << std::endl;
    for(int i = 1; i <= n; i++ ) {
        lastLine[i] = 1;
        std::cout << lastLine[i] << "\t";
        for(int j = i - 1; j >= 1; j--) {
            lastLine[j] += lastLine[j - 1];
            std::cout << lastLine[j] << "\t";
        }
        std::cout << lastLine[i] << "\t";
        std::cout << std::endl;
    }
//    printf("C(%u,%u) = %lu\n", n, k, lastLine[k]);
}

bool isBinary(const std::string& str) {
    for(int i = 0; i < str.length(); i++) {
        if(str.at(i) != '0' && str.at(i) != '1') {
            return false;
        }
    }
    return true;
}

char returnHex(const std::string& fourBits) {
    int result = 0;
    if(fourBits.at(0) == '1') {
        result += 8;
    }
    if(fourBits.at(1) == '1') {
        result += 4;
    }
    if(fourBits.at(2) == '1') {
        result += 2;
    }
    if(fourBits.at(3) == '1') {
        result += 1;
    }
    
    switch(result) {
        case 0: return '0';
        case 1: return '1';
        case 2: return '2';
        case 3: return '3'; 
        case 4: return '4'; 
        case 5: return '5'; 
        case 6: return '6'; 
        case 7: return '7'; 
        case 8: return '8'; 
        case 9: return '9'; 
        case 10: return 'A'; 
        case 11: return 'B';
        case 12: return 'C'; 
        case 13: return 'D';
        case 14: return 'E'; 
        case 15: return 'F'; 
    }
}

void binaryToHex(const std::string& binary) {
    
    std::string result = binary;
    if(!isBinary(result)) {
        std::cerr << "The input isnt binary number! exit\n";
        return;
    }
    
    while(result.length() % 4 != 0) {
        result = "0" + result;
    }
    int symbols = result.length() / 4;
    
    std::string hexResult = "";
    
    for(int i = 0; i < symbols; i++) {
        std::string temp = "";
        for(int j = i * 4; j < i * 4 + 4; j++ ) {
            temp += result.at(j);
        }
        hexResult += returnHex(temp);
    }
    hexResult.erase(0, hexResult.find_first_not_of('0'));
    std::cout << hexResult << std::endl;
}

void testBinaryToHex(const std::string& number) {
    binaryToHex(number);
}

char returnOct(const std::string& binary) {
    int result = 0;
    if(binary.at(0) == '1') {
        result += 4;
    }
    if(binary.at(1) == '1') {
        result += 2;
    }
    if(binary.at(2) == '1') {
        result += 1;
    }
    switch(result) {
        case 0: return '0';
        case 1: return '1';
        case 2: return '2';
        case 3: return '3';
        case 4: return '4';
        case 5: return '5';
        case 6: return '6';
        case 7: return '7';
    }
}

void binaryToOctal(const std::string& binary) {
    std::string result = binary;
    
    while(result.length() % 3 != 0) {
        result = "0" + result;
    }
    
    int symbols = result.length() / 3;
    std::string octReslt = "";
    
    for(int i = 0; i < symbols; i++) {
        std::string temp = "";
        for(int j = i * 3; j < i * 3 + 3; j++) {
            temp += result.at(j);
        }
        octReslt += returnOct(temp);
    }
    octReslt.erase(0, octReslt.find_first_not_of('0'));
    std::cout << octReslt << std::endl;
}

void testBinaryToOct(const std::string& number) {
    binaryToOctal(number);
}

void decToBinary(int decimal) {
    std::string result = "";
    bool addMinus = false;
    if(decimal < 0) {
        addMinus = true;
        decimal = abs(decimal);
    }
    else if(decimal == 0) {
        result = "0";
    }
    while(decimal > 0) {
        int bin = decimal % 2;
        decimal = decimal / 2;
        result += std::to_string(bin);
    }
    std::reverse(result.begin(), result.end());
    if(addMinus) {
        result = "-" + result;
    }
    std::cout << result << std::endl;
}

void decToOctal(int number) {
    std::string result = "";
    bool addMinus = false;
    if(number < 0) {
        addMinus = true;
        number = abs(number);
    }
    else if(number == 0) {
        result = "0";
    }
    while(number > 0) {
        int octal = number % 8;
        number = number / 8;
        result += std::to_string(octal);
    }
    std::reverse(result.begin(), result.end());
    if(addMinus) {
        result = "-" + result;
    }
    std::cout << result << std::endl;
}

char getChar(char n) {
    return (n < 10) ? (n + '0') : (n + 'A' - 10);
}

void decToHex(int number) {
    std::string result = "";
    bool addMinus = false;
    if(number < 0) {
        addMinus = true;
        number = abs(number);
    }
    else if(number == 0) {
        result = "0";
    }
    while(number > 0) {
        result += getChar((char)(number % 16));
        number = number / 16;
        
    }
    std::reverse(result.begin(), result.end());
    if(addMinus) {
        result = "-" + result;
    }
    std::cout << result << std::endl;
}

void decToPTypeSystem(int number, int base) {
    std::string result = "";
    bool addMinus = false;
    if(number < 0) {
        addMinus = true;
        number = abs(number);
    }
    else if(number == 0) {
        result = "0";
    }
    
    while(number > 0) {
        result += getChar((char)(number % base));
        number = number / base;
    }
    std::reverse(result.begin(), result.end());
    if(addMinus) {
        result = "-" + result;
    }
    std::cout << result << std::endl;
}