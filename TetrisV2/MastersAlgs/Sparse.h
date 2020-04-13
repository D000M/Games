/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Sparse.h
 * Author: default
 *
 * Created on July 2, 2019, 3:45 PM
 */

#ifndef SPARSE_H
#define SPARSE_H

#include <iosfwd>


class Elem {
    int row;
    int col;
    int value;
public:
//    Elem();
//    
//    Elem(int row, int col, int value);
    
    int getCol() const {
        return col;
    }

    void setCol(int col) {
        this->col = col;
    }

    int getRow() const {
        return row;
    }

    void setRow(int row) {
        this->row = row;
    }

    int getValue() const {
        return value;
    }

    void setValue(int value) {
        this->value = value;
    }
};

class Sparse {
public:
    Sparse(int rows, int cols, int size);

    Sparse(const Sparse& orig);
    virtual ~Sparse();
    
    void readData();
    void displayData();
    
    Sparse* operator + (const Sparse& s);
    
    friend std::istream& operator >> (std::istream& is, Sparse& obj);
    
    friend std::ostream& operator << (std::ostream& os, const Sparse& obj);
    
    
private:
    
    int rows;
    int cols;
    int size;
    Elem* elem;
    
};

#endif /* SPARSE_H */

