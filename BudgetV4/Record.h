/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Record.h
 * Author: default
 *
 * Created on February 5, 2020, 5:06 PM
 */

#ifndef RECORD_H
#define RECORD_H

#include <string>
#include <ostream>
#include <map>
#include <iomanip>

class Record {
public:
    Record(const std::string& today);
    
    float getTotalOutcome() const;
    void setTotalOutcome();
    
    float getTotalIncome() const;
    void setTotalIncome();
    
    std::string getDay() const;
    void setDay(const std::string& d);
    
    void addOutcome(const std::string& type, float price);
    void addIncome(const std::string& type, float income);
    
    friend std::ostream& operator << (std::ostream& out, const Record& obj) {
        out << obj.day << "\n";
        for(auto it = obj.balance.begin(); it != obj.balance.end(); it++ ) {
            out << "\t" << std::setw(12) << it->second << "\t\t" << it->first << "\n";
        }
        out << std::endl;
        out << "Total Outcome: " << std::setw(5) << obj.totalOutcome << std::endl; 
        out << "Total Income: " << std::setw(5) << obj.totalIncome << std::endl;
        out << "END " << obj.day << " #######################\n";
        return out;
    }
    
private:
    std::string day;
    float totalOutcome;
    float totalIncome;
    std::map<std::string, float> balance;

};

#endif /* RECORD_H */

