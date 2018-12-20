/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   ContExamples.h
 * Author: default
 *
 * Created on December 18, 2018, 10:40 AM
 */

#ifndef CONTEXAMPLES_H
#define CONTEXAMPLES_H

#include "UDVector.h"

template <typename T>
void printUDVector(const std::string& msg, UDVector<T>& vec) {
    std::cout << msg;
    for(int i = 0; i < vec.getSize(); i++) {
        std::cout << vec[i] << " ";
    }
    std::cout << std::endl;
}

template<typename T>
UDVector<T> fillVec() {
    UDVector<int> result{10, 20, 30, 40, 50};
    return result;
}

void testUDVector() {
    UDVector<int> myIntVec{1, 2, 3, 4, 5};
    printUDVector("myIntVec: ", myIntVec);
    UDVector<int> vecCopy{myIntVec};
    printUDVector("vecCopy: ", vecCopy);
    UDVector<int> vecAssignment(10);
    vecAssignment = vecCopy;
    printUDVector("vecAssignment: ", vecAssignment);
    
    UDVector<int> moveAssignmentVec;
    moveAssignmentVec = fillVec<int>();
    printUDVector("moveAssignmentVec: ", moveAssignmentVec);
    
    UDVector<int> moveCtrctrVec(fillVec<int>());
    printUDVector("moveCtrctrVec: ", moveCtrctrVec);
}


#endif /* CONTEXAMPLES_H */

