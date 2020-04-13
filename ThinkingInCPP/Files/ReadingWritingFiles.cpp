/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include <fstream>
#include <iostream>
#include <vector>
#include "ReadingWritingFiles.h"

void copyFromAtoB() {
    
    std::ifstream readFrom("Files/ReadingWritingFiles.cpp");
    std::ofstream writeTo("Files/result/ReadingWritingFiles2.txt");
    std::string line{};
    
    while(std::getline(readFrom, line)) {
        writeTo << line << "\n";
    }
}

void readEntireFileIntoAString() {
    std::ifstream readFrom("Files/ReadingWritingFiles.cpp");
    std::string file{};
    std::string line{};
    while(std::getline(readFrom, line)) {
        file += line + "\n";
    }
    std::cout << file;
}

void readFromFileAndAddToVector() {
    std::ifstream readFrom("Files/ReadingWritingFiles.cpp");
    std::string line{};
    std::vector<std::string> lines;
    
    while(std::getline(readFrom, line)) {
        lines.emplace_back(line);
    }
    for(auto&& line : lines) {
        static int lineRow = 1;
        std::cout << lineRow++ << ": " << line << "\n";
    }
}

void readFromFileAndGetWords() {
    std::ifstream readFrom("Files/ReadingWritingFiles.cpp");
    std::string word{};
    std::vector<std::string> words;
    while(readFrom >> word) {
        words.emplace_back(word);
    }
    for(auto&& word : words) {
        std::cout << word << "\n";
    }
    std::cout << "Total Words: " << words.size() << std::endl;
}