/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Computer.h
 * Author: default
 *
 * Created on March 14, 2019, 11:00 AM
 */

#ifndef COMPUTER_H
#define COMPUTER_H

#include <string>


class Computer {
public:
    virtual void run() = 0;
    virtual void stop() = 0;
    
    virtual ~Computer() {};  //without this we do not call subclasses destructors
};

class Laptop : public Computer {
public:
    void run() override {bHibernating = true;}
    void stop() override {bHibernating = false;}
    virutal ~Laptop() {};   //because of virtual functions we have need virtual destructor
private:
    bool bHibernating;
};

class Desktop : public Computer {
public:
    void run() override {mOn = true;}
    void stop() override {mOn = false;}
    virtual ~Desktop() {}
private:
    bool mOn;
};


class ComputerFactory {
public:
    static Computer* NewComputer(const std::string& type) {
        if(type == "Laptop") {
            return new Laptop;
        }
        else if(type == "Desktop") {
            return new Desktop;
        }
        return nullptr;
    }
};
#endif /* COMPUTER_H */

