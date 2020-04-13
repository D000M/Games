/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Record.cpp
 * Author: default
 * 
 * Created on February 5, 2020, 5:06 PM
 */

#include "Record.h"

Record::Record(const std::string& d) 
    : day{d} {
    totalIncome = 0;
    totalOutcome = 0;
}

void Record::addIncome(const std::string& type, float income) {
    std::map<std::string, float>::iterator it = balance.find(type);
    if(it != balance.end()) {
        it->second += income;
    }
    else {
        balance[type] = income;
    }
    totalIncome += income;
}

void Record::addOutcome(const std::string& type, float price) {
    auto it = balance.find(type);
    if(it != balance.end()) {
        it->second -= price;
    }
    else {
        balance[type] = price;
    }
    totalOutcome += price;
}

std::string Record::getDay() const {
    return day;
}

void Record::setDay(const std::string& d) {
    balance.clear();
    totalOutcome = 0;
    totalIncome = 0;
    day = d;
}

float Record::getTotalIncome() const {
    return totalIncome;
}

float Record::getTotalOutcome() const {
    return totalOutcome;
}


