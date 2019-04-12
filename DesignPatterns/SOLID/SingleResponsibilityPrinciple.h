/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   SingleResponsibilityPrinciple.h
 * Author: default
 *
 * Created on April 10, 2019, 3:49 PM
 */

#ifndef SINGLERESPONSIBILITYPRINCIPLE_H
#define SINGLERESPONSIBILITYPRINCIPLE_H

#include <string>
#include <vector>
#include <fstream>
#include <boost/lexical_cast.hpp>


struct Journal {
    std::string title;
    std::vector<std::string> entries;
    
    Journal(const std::string& lTitle) : title{lTitle} {}
    
    void addEntry(const std::string& lEntry) {
        static int count = 1;
        //lexical_cast boost library lexical_cast
        entries.push_back(boost::lexical_cast<std::string>(count++) + ": " + lEntry);
    }
    
    //Wrong way to have method to safe our journal in to the file
//    void save(const std::string& fileName) {
//        std::ofstream ofs{fileName};
//        for(auto& e : entries) {
//            ofs << e << std::endl;
//        }
//    }
    /**
     * Now if we have lots of journals, all of those objects will have save method
     * which is not actually of a journal importance and we break Single Responsibility Principle of a class.
     * we should use another object for saving in files.
     */
    //////////////////
};

//Our manager for files of journal
//We can now add other methods for our Classes in Persistance Manager.
//This way we will avoid Single Responsibility principle which means our class should do only stuff that are dependent.
//of our class.
struct PersistanceManager {
    static void saveToFile(const Journal& j, const std::string& fileName) {
        std::ofstream ofs{fileName};
        for(auto& e : j.entries) {
            ofs << e << std::endl;
        }
    }
};

void JournalOne() {
    Journal journal("My Journal");
    journal.addEntry("First Line");
    journal.addEntry("Second Line");
    PersistanceManager::saveToFile(journal, "SOLID/files/SolidResposibility.txt");
}
#endif /* SINGLERESPONSIBILITYPRINCIPLE_H */

