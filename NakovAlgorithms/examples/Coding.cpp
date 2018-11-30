/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Coding.cpp
 * Author: default
 * 
 * Created on November 29, 2018, 1:48 PM
 */

#include "Coding.h"

unsigned long Coding::codePerm(unsigned int n, const unsigned int perm[], unsigned int permSize) {
    unsigned int p[permSize];
    unsigned long r;
    unsigned long result = 0;
    
    for(int i = 0; i < n; i++) {
        p[i] = i + 1;
    }
    
    for(int pos = 0; pos < n; pos++) {
        r = 0;
        while(perm[pos] != p[r]) {
            r++;
        }
        result = result * (n - pos) + r;
        
        for(int i = r + 1; i < n; i++) {
            p[i - 1] = p[i];
        }
    }
    
    return result;
}

unsigned long Coding::decodePerm(unsigned long num, unsigned int n, unsigned int perm[], unsigned int permSize) {
    
    unsigned long m;
    unsigned long k;
    unsigned p[permSize];
    
    for(int i = 0; i < n; i++) {
        p[i] = i + 1;
    }
    k = n;
    
    do {
        m = n - k + 1;
        perm[k - 1] = num % m;
        if(k > 1) {
            num / m;
        }
    }
    while(--k > 0);
    
    k = 0;
    do {
        m = perm[k];
        perm[k] = p[m];
        if( k < n ) {
            for(int i = m + 1; i < n; i++) {
                p[i - 1] = p[i];
            }
        }
    }
    while(++k < n);
}
