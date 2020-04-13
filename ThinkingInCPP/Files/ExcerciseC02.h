/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   ExcerciseC02.h
 * Author: default
 *
 * Created on December 2, 2019, 3:38 PM
 */

#ifndef EXCERCISEC02_H
#define EXCERCISEC02_H

#include <string>
#include <fstream>
#include <vector>
#include <iostream>
#include "../utils/RNGGenerator.h"
//C02.Excercise 04
void countWordOccurence(const std::string& readFrom, const std::string& searchedWord) {
    std::ifstream file(readFrom);
    std::string word;
    int count{};
    while(file >> word) {
        if(word == searchedWord) {
            count++;
        }
    }
    std::cout << "Total Occurences of word: " << searchedWord << ": " << count << std::endl;
}

//C02.Excercise 05
void printVectorBackwards() {
    std::ifstream readFrom{"Files/ReadingWritingFiles.cpp"};
    std::vector<std::string> lines;
    std::string line{};
    while(std::getline(readFrom, line)) {
        static int count = 0;
        std::cout << count++ << ": " << line << std::endl;
        lines.emplace_back(line);
    }
    for(int i{lines.size() - 1}; i >= 0; i--) {
        std::cout << i << ": " << lines.at(i) << "\n";
    }
}

//C02.Excercise 07
void printLineByLine() {
    std::ifstream readFrom{"Files/ExcerciseC02.h"};
    std::string line{};
    while(std::getline(readFrom, line)) {
        int a;
        std::cin.get();
        std::cout << line;
    }
}

//C02.Excercise 08
void addFloatsToVector() {
    std::vector<float> v1;
    for(int i = 0; i < 25; i++) {
        v1.emplace_back(getRandomDouble(10, 100));
    }
    for(auto&& elem : v1) {
        std::cout << elem << "\n";
    }
}

//C02.Excercise 09
void addVectors() {
    std::vector<float> v1;
    std::vector<float> v2;
    std::vector<float> result;
    for(int i = 0; i < 25; i++) {
        v1.emplace_back(getRandomDouble(10, 100));
        v2.emplace_back(getRandomDouble(10, 100));
        result.emplace_back(v1.at(i) + v2.at(i));
    }
    for(int i = 0; i < result.size(); i++) {
        std::cout << v1.at(i) << " + " << v2.at(i) << " = " << result.at(i) << "\n";
    }
}

//C02.Excercise 10
void modifyVector() {
    std::vector<float> result;
    for(int i = 0; i < 25; i++) {
        result.emplace_back(getRandomInteger(10, 30));
    }
    for(auto&& elem : result) {
        std::cout << elem << " * " << elem << " = " << (elem * elem) << std::endl;
        elem *= elem;
    }
    for(const auto elem : result) {
        std::cout << elem << "\n";
    }
}
#endif /* EXCERCISEC02_H */

