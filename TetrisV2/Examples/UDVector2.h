/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   UDVector2.h
 * Author: default
 *
 * Created on June 7, 2019, 1:29 PM
 */

#ifndef UDVECTOR2_H
#define UDVECTOR2_H

template<typename T>
struct UDVector2 {
    T x;
    T y;
    
    UDVector2(const T& l_x, const T& l_y) 
        : x{l_x},
          y{l_y} {}
};

struct UDVector2i : UDVector2<int> {
    UDVector2i(const int& l_x, const int& l_y) : UDVector2(l_x, l_y) {}
};

struct UDVector2f : UDVector2<float> {
    UDVector2f(const float& l_x, const float& l_y) : UDVector2(l_x, l_y) {}
};
#endif /* UDVECTOR2_H */

