/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Combinatorics.h
 * Author: default
 *
 * Created on November 28, 2018, 3:18 PM
 */

#ifndef COMBINATORICS_H
#define COMBINATORICS_H

class Combinatorics {
public:
    
    Combinatorics();
    
    void print();
    void permute(int i);
    void testPermutation();
    
    /**
     * 1 2 3 4 5 6 7 8 9
     * 1 + 2 + 3 + 4 + 5  = 10
     */
    void print2(int i);
    void variate(int i);
    void testWithRepeat();
private:
    static constexpr int MAX = 100;
    int n;
    int k;
    bool used[MAX];
    int permutation[MAX];
    int taken[MAX];
};

#endif /* COMBINATORICS_H */

