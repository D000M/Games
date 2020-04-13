/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   FileNameExample.h
 * Author: default
 *
 * Created on December 19, 2019, 1:58 PM
 */

#ifndef FILENAMEEXAMPLE_H
#define FILENAMEEXAMPLE_H
#include <fstream>
#include <string>
#include <iostream>
#include <sstream>
//Class to open file and remembe its name

//Using composition
class FName1 {
    std::ifstream file;
    std::string fileName;
    bool named;
    
public:
    FName1() : named{false} {}
    FName1(const std::string& fname) : fileName{fname}, file{fname.c_str()} {
        named = true;
    } 
    
    const std::string getFileName() const {
        return fileName;
    }
    void setFileName(const std::string& fname) {
        if(named) { //if file has name dont overwrite
            return; 
        }
        fileName = fname;
        named = true;
    }
    operator std::ifstream& () {
        return file;
    }
    const std::string getFileInfo() const {
        std::stringstream ss;
        ss << file.rdbuf();
        return ss.str();
    }
    
    void closeFile() {
        file.close();
    }
    
};


void testNamedFile() {
    FName1 file("C14InheritanceAndComposition/FileNameExample.h");
    std::cout << file.getFileName() << std::endl;
    std::cout << file.getFileInfo() << std::endl;
}

//Using Inheritance
class FName2 : public std::ifstream {
    std::string fileName;
    bool named;
    
public:
    FName2() : named{false} {}
    FName2(const std::string& fname) 
        : std::ifstream(fname.c_str()), fileName(fname) {
        named = true;
    }
    const std::string getFileName() const {
        return fileName;
    }
    void setFileName(const std::string& fname) {
        if(named) {
            return;
        }
        fileName = fname;
        named = true;
    }
};

void testFNameInheritance() {
    FName2 file("C14InheritanceAndComposition/FileNameExample.h");
    //using used defined member functions for FName2
    std::cout << "fileName: " << file.getFileName() << std::endl;
    std::string s;
    // Using std::ifstream interface
    std::cout << file.rdbuf() << std::endl;
//    std::getline(file, s);
//    file.seekg(-200, std::ios::end);
    file.close();
}
#endif /* FILENAMEEXAMPLE_H */

