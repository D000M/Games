/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   TemplateArray.h
 * Author: default
 *
 * Created on December 20, 2019, 2:48 PM
 */

#ifndef TEMPLATEARRAY_H
#define TEMPLATEARRAY_H

#include <iostream>

template<class T>
class TemplateArray {
    enum {
        size = 100
    };
    T arr[size];
    
    public:
        //inline declaration
//        T& operator [] (int index) {
//            if(index < 0 || index >= size) {
//                throw ("Array index out of bounds");
//            }
//            return arr[index];
//        }
        T& operator [] (int index);
};
//non inline declaration
template<typename T>
T& TemplateArray<T>::operator [](int index) {
    if(index < 0 || index >= size) {
        throw ("Array index out of bounds");
    }
    return arr[index];
}
void testTemplateArray() {
    TemplateArray<int> intArr;
    TemplateArray<float> floatArr;
    for(int i = 0; i < 20; i++) {
        intArr[i] = i * i;
        floatArr[i] = float(i) * 1.414;
    }
    for(int i = 0; i < 20; i++ ) {
        std::cout << i << ": " << intArr[i] << ", " << floatArr[i] << std::endl;
    }
}
#endif /* TEMPLATEARRAY_H */

