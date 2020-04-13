/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   ObjectCounter.h
 * Author: default
 *
 * Created on December 21, 2019, 4:56 PM
 */

#ifndef OBJECTCOUNTER_H
#define OBJECTCOUNTER_H
#include <string>
#include <set>
#include <iostream>

class ObjectCounter {
    static int count;
    int id;
    std::string className;
    
    class CleanupCheck {
        std::set<ObjectCounter*> trace;
    public:
        ~CleanupCheck() {
            std::cout << "~CleanupCheck()\n";
        }
        void add(ObjectCounter* elem) {
            trace.insert(elem);
        }
        void remove(ObjectCounter* elem) {
            trace.erase(elem);
        }
    };
    
    static CleanupCheck verifier;
    
    ObjectCounter(const std::string& name) : id{count++}, className{""} {
        if(className == "") {
            className = name;
        }
        verifier.add(this);
        std::cout << "Class: " << className << " created [" << id << "]\n"; 
    }
    
    ObjectCounter(const ObjectCounter& obj);
    void operator = (const ObjectCounter&);
    
public:
    static ObjectCounter* create(const std::string& name) {
        return new ObjectCounter(name);
    }
    
    virtual ~ObjectCounter() {
        std::cout << "Class: " << className << " destroyed [" << id << "]\n";
        verifier.remove(this);
    }
    //Print both objects and pointers
    friend std::ostream& operator << (std::ostream& out, const ObjectCounter& obj) {
        return out << "ObjectCounter ref: " << obj.id;
    }
    friend std::ostream& operator << (std::ostream& out, const ObjectCounter* obj) {
        return out << "ObjectCounter ptr: " << obj->id;
    }
};

class TestObjectCounter {
    ObjectCounter* objects;
public:
    TestObjectCounter(const std::string& className = "TestObjectCounter") : objects{ObjectCounter::create(className)} {
        
    }
    virtual ~TestObjectCounter() {
        delete objects;
    }
};

void testObjectCounterExample();
#endif /* OBJECTCOUNTER_H */

