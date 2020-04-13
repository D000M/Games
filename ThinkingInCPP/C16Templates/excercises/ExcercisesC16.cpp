/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "ExcercisesC16.h"

void testFibonaciTemplate() {
    for(int i = 0; i < 10; i++) {
        double d = double(i) * 3.14;
        //effective: 1 3 13 55 233 987 4181 17711 121393 514229 2.17831e+06 9.22746e+06 3.90882e+07 
        //effective: 1.6558e+08 7.01409e+08 5.1256e+08 -1.10983e+09 3.68225e+08 3.63076e+08 1.82053e+09 ~CleanupCheck

        std::cout << fibonaciTemplate(d) << " ";
    }
}