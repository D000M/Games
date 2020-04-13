/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Sparse.cpp
 * Author: default
 * 
 * Created on July 2, 2019, 3:45 PM
 */

#include <iostream>

#include "Sparse.h"


Sparse::Sparse(int rows, int cols, int size)
    : rows(rows), cols(cols), size(size) {
    
    elem = new Elem[size];
}

Sparse::Sparse(const Sparse& orig) {
}

Sparse::~Sparse() {
    delete [] elem;
}

void Sparse::readData() {
    std::cout << "Enter Non-Zero Elements: ";
    for(int i = 0; i < size; i++) {
        int r, c, data;
        std::cin >> r >> c >> data;
        elem[i].setRow(r);
        elem[i].setCol(c);
        elem[i].setValue(data);
    }
}

void Sparse::displayData() {
    int index = 0;
    for(int row = 0; row < rows; row++) {
        for(int col = 0; col < cols; col++) {
            if(elem[index].getRow() == row && elem[index].getCol() == col) {
                std::cout << elem[index++].getValue() << " ";
            }
            else {
                std::cout << "0 ";
            }
        }
        std::cout << std::endl;
    }
}

std::istream& operator >> (std::istream& is, Sparse& obj) {
    std::cout << "Enter Non-Zero Elements: ";
    for(int i = 0; i < obj.size; i++) {
        int r, c, data;
        is >> r >> c >> data;
        obj.elem[i].setRow(r);
        obj.elem[i].setCol(c);
        obj.elem[i].setValue(data);
    }
    return is;
}

std::ostream& operator << (std::ostream& os, const Sparse& obj) {
    int index = 0;
    for(int row = 0; row < obj.rows; row++) {
        for(int col = 0; col < obj.cols; col++) {
            if(obj.elem[index].getRow() == row && obj.elem[index].getCol() == col) {
                os << obj.elem[index++].getValue() << " ";
            }
            else {
                os << "0 ";
            }
        }
        os << std::endl;
    }
    return os;
}

Sparse* Sparse::operator + (const Sparse& s) {
    if(this->rows != s.rows || this->cols != s.cols) {
        return nullptr;
    }
    Sparse* sum = new Sparse(this->rows, this->cols, this->size + s.size);
    int i = 0, j = 0, k = 0;
    
    while(i < this->size && j < s.size) {
        if(this->elem[i].getRow() < s.elem[j].getRow()) {
            sum->elem[k].setRow(this->elem[i].getRow());
            sum->elem[k].setCol(this->elem[i].getCol());
            sum->elem[k].setValue(this->elem[i].getValue());
            k++;
            i++;
        }
        else if(this->elem[i].getRow() > s.elem[j].getRow()) {
            sum->elem[k].setRow(s.elem[j].getRow());
            sum->elem[k].setCol(s.elem[j].getCol());
            sum->elem[k].setValue(s.elem[j].getValue());
            k++;
            j++;
        }
        else {  //rows are equal
            if(this->elem[i].getCol() < s.elem[j].getCol()) {
                sum->elem[k].setRow(this->elem[i].getRow());
                sum->elem[k].setCol(this->elem[i].getCol());
                sum->elem[k].setValue(this->elem[i].getValue());
                k++;
                i++;
            }
            else if(this->elem[i].getCol() > s.elem[j].getCol()) {
                sum->elem[k].setRow(s.elem[j].getRow());
                sum->elem[k].setCol(s.elem[j].getCol());
                sum->elem[k].setValue(s.elem[j].getValue());
                k++;
                j++;
            }
            else {
                sum->elem[k].setRow(this->elem[i].getRow());
                sum->elem[k].setCol(this->elem[i].getCol());
                sum->elem[k].setValue(this->elem[i].getValue() + s.elem[j].getValue());
                k++;
                i++;
                j++;
            }
        }
    }
    
    for( ; i < this->size; i++) {
        sum->elem[k].setRow(this->elem[i].getRow());
        sum->elem[k].setCol(this->elem[i].getCol());
        sum->elem[k].setValue(this->elem[i].getValue());
        k++;
    }
    for( ; j < s.size; j++) {
        sum->elem[k].setRow(s.elem[j].getRow());
        sum->elem[k].setCol(s.elem[j].getCol());
        sum->elem[k].setValue(s.elem[j].getValue());
        k++;
    }
    
    return sum;
}
