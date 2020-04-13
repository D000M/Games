/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   RealStack.h
 * Author: default
 *
 * Created on December 21, 2019, 12:42 PM
 */

#ifndef REALSTACK_H
#define REALSTACK_H

#include <string>
#include <fstream>
#include "../utils/require.h"
#include <iostream>

//Stack with nested iterator

template<class T>
class Stack {
    
    struct Link {
        T* data;
        Link* next;
        Link(T* dat, Link* nxt) : data{dat}, next{nxt} {}
    }*head;
    
    public:
        Stack() : head{nullptr} {}
        ~Stack();
        
        void push(T* elem) {
            head = new Link(elem, head);
        }
        T* peek() const {
            return head ? head->data : 0;
        }
        T* pop();
        
//        class iterator;
//        friend class iterator;
        class iterator {
            Stack::Link* p;
        public:
            iterator(const Stack<T>& t1) : p(t1.head) {}
            //Copy constructor
            iterator(const iterator& t1) : p{t1.p} {}
            iterator() : p(nullptr) {}
            
            //operator ++ returns boolean indicating the end
            bool operator ++ () {
                if(p->next) {
                    p = p->next;
                }
                else {
                    p = nullptr;
                }
                return bool(p);
            }
            bool operator ++ (int) {
                return operator ++ ();
            }
            
            T* current() const {
                if(!p) {
                    return nullptr;
                }
                return p->data;
            }
            
            //Pointer derefernce operator
            T* operator -> () const {
                require(p != nullptr, "Stack::iterator::operator->() returns null");
                return current();
            }
            T* operator * () const {
                return current();
            }
            
            //bool conversion for conditional test
            operator bool() const {
                return bool(p);
            }
            
            //comparision to test for end
            bool operator == (const iterator& rv) {
                return p == nullptr;
            } 
            bool operator != (const iterator& rv) {
                return p != nullptr;
            } 
        };  //end class iterator
        
        iterator begin() const {
            return iterator(*this);
        }
        iterator end() const {
            return iterator();
        }
};

template<class T>
Stack<T>::~Stack() {
    while(head) {
        delete pop();
    }
}
template<class T>
T* Stack<T>::pop() {
    if(head == nullptr) {
        return nullptr;
    }
    T* result = head->data;
    Link* oldHead = head;
    head = head->next;
    delete oldHead;
    return result;
}
void testStacksss() {
    std::ifstream file("C16Templates/RealStack.h");
    assure(file, "C16Templates/RealStack.h");
    Stack<std::string> textLines;
    std::string line;
    while(std::getline(file, line)) {
        textLines.push(new std::string{line});
    }
    
    int i = 0;
    Stack<std::string>::iterator it = textLines.begin();
    Stack<std::string>::iterator* it2 = nullptr;
    
    while(it != textLines.end()) {
        std::cout << it->c_str() << std::endl;
        it++;
        if(++i == 11) {
            it2 = new Stack<std::string>::iterator(it);
        }
    }
    std::cout << (*it2)->c_str() << std::endl;
    delete it2;
    
}
#endif /* REALSTACK_H */

