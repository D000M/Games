/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   IterStackTemplate.h
 * Author: default
 *
 * Created on December 21, 2019, 12:21 PM
 */

#ifndef ITERSTACKTEMPLATE_H
#define ITERSTACKTEMPLATE_H

#include "../utils/require.h"
#include "IntStack.h"
#include <ostream>
#include <iostream>
#include <fstream>
#include <string>

template<typename T, int ssize = 1000>
class TheStack {
    T stack[ssize];
    int top;
    public:
    TheStack() : top{0} {}
    void push(const T& elem) {
        require(top < ssize, "Too many pushes!\n");
        stack[top++] = elem;
    }
    T pop() {
        require(top > 0, "Too many pops()\n");
        return stack[--top];
    }
        
//        class iterator;
//        friend class iterator;
        class iterator {
            TheStack& s;
            int index;
        public:
            iterator(TheStack& ts) : s{ts}, index{0} {}
            iterator(TheStack& ts, bool) : s{ts}, index{s.top} {}
            
            T operator * () const{
                return s.stack[index];
            }
            //Prefix
            T operator ++ () {
                require(index < s.top, "iterator moved out of range");
                return s.stack[++index];
            }
            T operator ++ (int) {
                require(index < s.top, "iterator moved out of range");
                return s.stack[index++];
            }
            //Jump an iterator forward
            iterator& operator += (int amount) {
                require(index + amount < s.top, "TheStack::iterator::operator += () moved out of range");
                index += amount;
                return *this;
            }
            //to see if you are at the end
            bool operator == (const iterator& rv) const {
                return index == rv.index;
            }
            bool operator != (const iterator& rv) const {
                return index != rv.index;
            }
            friend std::ostream& operator << (std::ostream& os, const iterator& obj) {
                return os << *obj;
            }
        };  //end of class iterator
        
        
    iterator begin() {
        return iterator(*this);
    }
    //Create the end sentinel
    iterator end() {
        return iterator(*this, true);
    }
};


void testIterStackTemplate() {
    TheStack<int> is;
    for(int i = 0; i < 20; i++) {
        is.push(fibonaci(i));
    }
    std::cout << "Traverse the whole stack with iterator\n";
    TheStack<int>::iterator it = is.begin();
    while(it != is.end()) {
        std::cout << it++ << " ";
    }
    
    std::cout << "\nTravers a portion\n";
    TheStack<int>::iterator start = is.begin();
    TheStack<int>::iterator end = is.begin();
    start += 5;
    end += 15;
    while(start != end) {
        std::cout << start++ << " ";
    }
    std::cout << std::endl;
    std::ifstream file("C16Templates/IterStackTemplate.h");
    assure(file, "C16Templates/IterStackTemplate.h");
    std::string line;
    TheStack<std::string> ss;
    while(std::getline(file, line)) {
        ss.push(line);
    }
    TheStack<std::string>::iterator sb = ss.begin(), se = ss.end();
    while(sb != se) {
        static int lineNum = 1;
        std::cout << lineNum++ << ": " << sb++ << std::endl;
    }
}

#endif /* ITERSTACKTEMPLATE_H */

