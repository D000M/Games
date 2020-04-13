/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   OperatorNewAndDeleteMemberForArrays.h
 * Author: default
 *
 * Created on December 11, 2019, 4:07 PM
 */

#ifndef OPERATORNEWANDDELETEMEMBERFORARRAYS_H
#define OPERATORNEWANDDELETEMEMBERFORARRAYS_H

#include <new>
#include <fstream>

std::ofstream trace("ArrayOperatorNew.out");

class Widget {
    enum {
        size = 10
    };
    int i[size];
public:
    Widget() {
        trace << "*";
    }
    ~Widget() {
        trace << "~";
    }
    
    void* operator new(size_t s) {
        trace << "Widget::new: " << s << " bytes " << std::endl;
        return ::new char[s];   //call global new, used just to implement print to file
    }
    void operator delete(void* objectMemory) {
        trace << "Widget::delete" << std::endl;
        ::delete []objectMemory;    //call global delete, used just to implement print to file
    }
    void* operator new[] (size_t s) {
        trace << "Widget::new[]: " << s << " bytes " << std::endl;
        return ::new char[s];
    }
    void operator delete[] (void* objectMemory) {
        trace << "\nWidget::delete[]" << std::endl;
        ::delete [] objectMemory;
    } 
};

void testOpNewDelForArray() {
    trace << "new Widget\n";
    Widget* w = new Widget();
    trace << "\nDelete Widget\n";
    delete w;
    trace << "\nnew Widget[25]\n";
    Widget* wArr = new Widget[25];
    trace << "\nDelete Widget[25]\n";
    delete [] wArr;
}
#endif /* OPERATORNEWANDDELETEMEMBERFORARRAYS_H */

