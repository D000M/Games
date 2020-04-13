/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   IntStack.h
 * Author: default
 *
 * Created on December 20, 2019, 2:06 PM
 */

#ifndef INTSTACK_H
#define INTSTACK_H
#include <iostream>
#include <string>
#include <fstream>
#include "../utils/require.h"

class IntStack {
    enum {
        size = 100
    };
    int stack[size];
    int top;
public:
    IntStack() : top{0} {}
    void push(int i) {
        if(top > size - 1) {
            throw("Error to many pushes!\n");
        }
        stack[top++] = i;
    }
    int pop() {
        if(top < 0) {
            throw("Error to many pop's\n");
        }
        return stack[--top];
    }
    
    friend class IntStackIter;
    //using nested class for iterator
    //can be commented?!?
//    class iterator;
//    friend class iterator;
    class iterator {
        IntStack& s;
        int index;
    public:
        iterator(IntStack& is) : s{is}, index{0} {}
        //to create "the end sentinel" iterator
        iterator(IntStack& is, bool) : s{is}, index{s.top} {}
        
        int current() const {
            return s.stack[index];
        }
        int operator ++ () {
            require(index < s.top, "iterator moved out of range");
            return s.stack[++index];
        }
        int operator ++ (int) {
            require(index < s.top, "iterator moved out of range");
            return s.stack[index++];
        }
        
        //Jump an iterator forward
        iterator& operator += (int amount) {
            require(index + amount < s.top, "IntStack::iterator::operator += () tried to move out of bounds");
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
            return os << obj.current();
        }
    };  //end class iterator
    
    iterator begin() {
        return iterator(*this);
    }
    //Create the end sentinel
    iterator end() {
        return iterator(*this, true);
    }
};
//An iterator is like an smart pointer
class IntStackIter {
    IntStack& s;
    int index;
public:
    IntStackIter(IntStack& is) : s{is}, index{0} {}
    
    //Prefix
    int operator ++ () {
        require(index < s.top, "iterator moved out of range");
        return s.stack[++index];
    }
    //Postfix
    int operator ++ (int) {
        require(index < s.top, "iterator moved out of range");
        return s.stack[index++];
    }
};

int fibonaci(int n) {
    if(n == 0) {
        return 0;
    }
    else if(n <= 2) {
        return 1;
    }
    return fibonaci(n - 1) + fibonaci(n - 2);
}
//effective fibonacci
int effectiveFib(int n) {
    const int size = 100;
    if(n >= 100) {
        throw("To big fibonacci number error\n");
    } 
    static int fibArr[size];
    fibArr[0] = fibArr[1] = 1;
    
    int i;
    for(i = 0; i < size; i++) {
        if(fibArr[i] == 0) {
            break;
        }
    }
    while(i <= n) {
        fibArr[i] = fibArr[i - 1] + fibArr[i - 2];
        i++;
    }
    return fibArr[n];
}

void testIntStackIter() {
    IntStack is;
    for(int i = 0; i < 20; i++) {
        is.push(effectiveFib(i));
    }
    
    //Traverse with iterator
    IntStackIter it(is);
    for(int i = 0; i < 20; i++) {
        std::cout << it++ << std::endl;
    }
}
void testIntStack() {
    IntStack is;
    for(int i = 0; i < 20; i++) {
        is.push(effectiveFib(i));
    }
    for(int k = 0; k < 20; k++) {
        std::cout << is.pop() << " ";
    }
}

void testIntStackNestedIterator() {
    IntStack is;
    for(int i = 0; i < 20; i++) {
        is.push(effectiveFib(i));
    }
    std::cout << "Traverse the whole int stack\n";
    IntStack::iterator it = is.begin();
    while(it != is.end()) {
        std::cout << it++ << " ";
    }
    std::cout << "\nTraverse a portion of the IntStack\n";
    IntStack::iterator start = is.begin();
    IntStack::iterator end = is.begin();
    start += 5;
    end += 15;
    std::cout << "start: " << start << std::endl;
    std::cout << "end: " << end << std::endl;
    while(start != end) {
        std::cout << start++ << " ";
    }
}
//IntStack as template
template<typename T>
class StackTemplate {
    enum {
        sizes = 100
    };
    T arr[sizes];
    int top;
public:
    StackTemplate() : top{0} {}
    void push(const T& elem) {
        if(top >= sizes) {
            throw("Error out of bounds");
        }
        arr[top++] = elem;
    }
    T pop() {
        if(top < 0) {
            throw("Error empty stack");
        } 
        return arr[--top];
    }
    int size() const {
        return top;
    }
};

void testStackTemplate() {
    StackTemplate<int> intStack;
    for(int i = 0; i < 20; i++ ){
        intStack.push(fibonaci(i));
    }
    while(intStack.size() > 0) {
        std::cout << intStack.pop() << " ";
    }
    std::ifstream in("C16Templates/TemplateArray.h");
    std::string line;
    StackTemplate<std::string> lines;
    while(std::getline(in, line)) {
        lines.push(line);
    }
    while(lines.size() > 0) {
        std::cout << lines.pop() << std::endl;
    }
}
#endif /* INTSTACK_H */

