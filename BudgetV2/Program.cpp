/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Program.cpp
 * Author: default
 * 
 * Created on March 19, 2019, 1:43 PM
 */

#include <iostream>
#include <fstream>
#include <cstring>
#include <sstream>
#include "Program.h"

Program::Program(const std::string& d) 
    : currRecord{d} {
    totalIncome = 0;
    totalOutcome = 0;
}

void Program::setRecord(const std::string& type, float price) {
    currRecord.addOutcome(type, price);
}

void Program::setIncome(const std::string& type, float income) {
    currRecord.addIncome(type, income);
}

void Program::outputRecord() {
    std::cout << currRecord;
}

void Program::writeToFile(const std::string& writeTo) {
    std::ofstream file;
    file.open(writeTo, std::ios::out | std::ios::app);
    
    if(file.fail()) {
        throw std::ios_base::failure(std::strerror(errno));
    }
    file << currRecord << std::endl;
    file.close();
}

void Program::setDay(const std::string& day) {
    currRecord.setDay(day);
}

void Program::readFromFile(const std::string& readFrom) {
    std::ifstream file{readFrom};
    if(!file.is_open()) {
        std::cout << "Cant open file: " << readFrom << std::endl;
        return;
    }
    std::string line{};
    while(std::getline(file, line)) {
        std::stringstream ss;
        ss << line;
        std::string type;
        ss >> type;
        if(type == "Date" || type == "END") {
            continue;
        }
        
        double price{};
        if(type != "" && type != "Total") {
            price = std::stof(type);
        }
        std::string item{};
        while(!ss.eof()) {
            
            ss >> type;
            
            if(type != "Total" && type != "Income:" && type != "Outcome:") {
                item.append(type + " ");
            }
            if(type == "Outcome:") {
                ss >> type;
                totalOutcome += std::stof(type);
            }
            if(type == "Income:") {
                ss >> type;
                totalIncome += std::stof(type);
            }
            
        }
        
        auto it = allItems.find(item); 
       
        if(it != allItems.end()) {
            if(price != 0) {
                allItems[item] += price;
            }
        }
        else {
            
            if(price != 0) {
                allItems[item] = price;
            }
        }
    }
    
}

void Program::getMontlyOutcome(const std::string& readFrom, const std::string& month) {
    std::ifstream file(readFrom);
    if(!file.is_open()) {
        std::cout << "Cant open file!\n";
        return;
    }
    std::string line{};
}

float Program::getTotalDifference() {
    return totalIncome + totalOutcome;
}

void Program::printAllItems() {
//    float sum{};
    std::map<float, std::string> sortedList;
    
    for(auto it = allItems.begin(); it != allItems.end(); ++it) {
        sortedList[it->second] = it->first;
    }
    for(auto it = sortedList.begin(); it != sortedList.end(); it++) {
        std::cout << it->first << ": " << it->second << std::endl;
    }
//    std::cout << "TOTAL SUM: " << sum << std::endl;
}

void Program::printAveragePerDay(const std::string& readFrom) {
    std::ifstream file{readFrom};
    if(!file.is_open()) {
        std::cout << "File cant be open: " << readFrom << std::endl;
        return;
    }
    std::string line;
    
    int countDays = 0;
    double totalOutcome = 0;
    double totalIncome{};
    while(std::getline(file, line)) {
        std::stringstream ss;
        ss << line;
        std::string type;
        ss >> type;
        double outcome{};
        double income{};
//        while(ss >> type) {
        if(type == "Total") {
            ss >> type;
            if(type == "Outcome:") {
                ss >> outcome;
                totalOutcome += outcome;
            }
            if(type == "Income:") {
                ss >> income;
                totalIncome += income;
            }
        }
        if(type != "Date") {
            continue;
        }
        countDays++;
//        std::cout << countDays << std::endl;
//        }
    }
    std::cout << "Average Outcome Per Day: " << totalOutcome / countDays << std::endl;
    std::cout << "Average Income Per Day: " << totalIncome / countDays << std::endl;
}

float Program::getTotalIncome() const {
    return totalIncome;
}

float Program::getTotalOutcome() const {
    return totalOutcome;
}

float Program::getDayIncome() const {
    return currRecord.getTotalIncome();
}

float Program::getDayOutcome() const {
    return currRecord.getTotalOutcome();
}

void Program::printDailyExpenses() {
    std::cout << "Изхарчени пари за " << currRecord.getDay() << " април: " << getDayOutcome() << "лева." << std::endl;
    std::cout << "Получени пари за " << currRecord.getDay() << " април: " << getDayIncome() << "лева." << std::endl;
}
