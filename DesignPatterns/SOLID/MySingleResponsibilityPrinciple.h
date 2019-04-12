/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   MySingleResponsibilityPrinciple.h
 * Author: default
 *
 * Created on April 11, 2019, 10:01 AM
 */

#ifndef MYSINGLERESPONSIBILITYPRINCIPLE_H
#define MYSINGLERESPONSIBILITYPRINCIPLE_H

#include <string>
#include <vector>
#include <boost/lexical_cast.hpp>


class Book {
    std::string mTitle;
    std::vector<std::string> mPage;
    
public:
    Book(const std::string& lTitle) : mTitle{lTitle} {}
    void addPage(const std::string& lPage);
    std::vector<std::string> getPages() const;
};

void Book::addPage(const std::string& lPage) {
    static int pageCount = 1;
    mPage.push_back(boost::lexical_cast<std::string>(pageCount++) + ": " + lPage);
}

std::vector<std::string> Book::getPages() const {
    return mPage;
}

class UtilityMgr {
public:
    static void writeBookToFile(const Book& lBook, const std::string& fileName);
};

void UtilityMgr::writeBookToFile(const Book& lBook, const std::string& fileName) {
    std::ofstream writeToFile{fileName};
    for(auto& page : lBook.getPages()) {
        writeToFile << page << std::endl;
    }
}

void testBookSRP() {
    Book myBook{"My Life"};
    myBook.addPage("Childhood\nSome Text\n More Text\n");
    myBook.addPage("School\nYears in School\nEnd of School\n");
    myBook.addPage("End Of Life\nDeath Awaits\n");
    UtilityMgr::writeBookToFile(myBook, "SOLID/files/MyLife.txt");
}
#endif /* MYSINGLERESPONSIBILITYPRINCIPLE_H */

