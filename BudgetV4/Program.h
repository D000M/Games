/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Program.h
 * Author: default
 *
 * Created on February 5, 2020, 5:06 PM
 */

#ifndef PROGRAM_H
#define PROGRAM_H

#include <vector>

#include "Record.h"


class Program {
public:
    Program(const std::string& d);
    
    void setRecord(const std::string& type, float price);
    void setIncome(const std::string& type, float income);
    void outputRecord();
    void setDay(const std::string& day);
    void writeToFile(const std::string& writeTo);
    
    void readFromFile(const std::string& readFrom);
    void printTotalOutcome();
    
    void getMontlyOutcome(const std::string& readFrom, const std::string& month);
    float getTotalDifference();
    float getTotalOutcome() const;
    float getTotalIncome() const;
    float getDayOutcome() const;
    float getDayIncome() const;
    void printAllItems();
    void printDailyExpenses();
    void printAveragePerDay(const std::string& readFrom);
    
private:
    Record currRecord;
    float totalOutcome;
    float totalIncome;
    std::map<std::string, float> allItems;
};

#endif /* PROGRAM_H */

