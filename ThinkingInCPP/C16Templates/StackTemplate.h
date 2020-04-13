/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   StackTemplate.h
 * Author: default
 *
 * Created on December 21, 2019, 9:58 AM
 */

#ifndef STACKTEMPLATE_H
#define STACKTEMPLATE_H

#include <iostream>
#include <fstream>
#include <string>

template<class T>
class StackT {
    struct Link {
        T* data;
        Link* next;
        Link(T* dat, Link* nxt) : data{dat}, next{nxt} {}
    }*head;
    
    public:
        StackT() : head{nullptr} {}
        ~StackT() {
            while(head) {
                delete pop();
            }
        }
        void push(T* elem) {
            head = new Link(elem, head);
        }
        T* peek() const {
            return head ? head->data : nullptr;
        }
        T* pop() {
            if(head == nullptr) {
                return nullptr;
            }
            T* result = head->data;
            Link* oldHead = head;
            head = head->next;
            delete oldHead;
            return result;
        }
};

class TestX {
public:
    TestX() {
        std::cout << "Constructor TestX()\n";
    }
    virtual ~TestX() {
        std::cout << "Destructor ~TestX()\n";
    }
};
void testStackTemplate2() {
    std::ifstream file("C16Templates/StackTemplate.h");
    StackT<std::string> lines;
    std::string line;
    while(std::getline(file, line)) {
        lines.push(new std::string{line});
    }
    
    //Pop some strings from the stack
    std::string* str;
    for(int i = 0; i < 10; i++) {
        if((str = (std::string*)lines.pop()) == nullptr) {
            break;
        }
        std::cout << *str << std::endl;
        delete str;
    }   //Destructor deletes the other strings
    StackT<TestX> testStack;
    for(int i = 0; i < 10; i++) {
        testStack.push(new TestX());
    }
}
#endif /* STACKTEMPLATE_H */

