/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include <fstream>
#include <iostream>
#include "C07Excercises.h"

Text::Text() {
    std::ifstream readFrom("C07FuncOverload/C07Excercises.cpp");
    if(!readFrom.is_open()) {
        throw ("ERROR Opening File! In Text()");
    }
    std::string line{};
    
    while(std::getline(readFrom, line)) {
        textContent += line + "\n";
    }
    if(readFrom.is_open()) {
        readFrom.close();
    }
}

Text::Text(const std::string& fileName) {
    std::ifstream readFrom(fileName);
    if(!readFrom.is_open()) {
        throw("ERROR Opening File! in Text(string)");
    }
    std::string line{};
    while(std::getline(readFrom, line)) {
        textContent += line + "\n";
    }
    if(readFrom.is_open()) {
        readFrom.close();
    }
}

const std::string Text::contains() const {
    return textContent;
}

void testText() {
    Text defaultText;
    std::cout << defaultText.contains();
    
    std::cout << "Use Non Default Constructor!\n";
    Text nonDefText{"C03CinCpp/MacrosDefinitions.h"};
    std::cout << nonDefText.contains();
}