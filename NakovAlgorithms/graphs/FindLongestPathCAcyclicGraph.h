/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   FindLongestPathCAcyclicGraph.h
 * Author: default
 *
 * Created on January 14, 2019, 4:06 PM
 */

#ifndef FINDLONGESTPATHCACYCLICGRAPH_H
#define FINDLONGESTPATHCACYCLICGRAPH_H

#include "ExtremePathsCGraphs.h"


#ifdef __cplusplus
extern "C" {
#endif

    //Broi vyrhove v grafa
const unsigned n4 = 6;

//Matrica na teglata na grafa
const unsigned C[MAXN2][MAXN2] = {
    { 0, 12,  0,  0,  0,  0},
    { 0,  0, 40,  0, 17,  0},
    { 0,  0,  0,  0,  0,  0},
    { 0,  0,  0,  0, 30,  0},
    { 0,  0,  0,  0,  0, 20},
    { 0,  0, 20,  0,  0,  0}
};


int savePath[MAXN2];
int maxDist[MAXN2];

void longestPathDFS(unsigned i) {
    int max, d;
    unsigned j;
    if(maxDist[i] > 0) {
        return;
    }
    max = maxDist[i];
    
    for(j = 0; j < n4; j++) {
        if(C[i][j]) {
            longestPathDFS(j);
            d = maxDist[j] + C[i][j];
            if(d > max) {
                max = d;
                savePath[i] = j;
            }
        }
    }
    maxDist[i] = max;
}

void solveLongestPath() {
    unsigned i, maxi;
    
    //initialization.
    for(i = 0; i < n4; i++ ){
        maxDist[i] = 0;
        savePath[i] = -1;
    }
    for(i = 0; i < n4; i++) {
        if(maxDist[i] == 0) {
            longestPathDFS(i);
        }
    }
    maxi = 0;
    for(i = 0; i < n4; i++) {
        if(maxDist[i] > maxDist[maxi]) {
            maxi = i;
        }
    }
    printf("Duljinata na kritichniq put e %d\nPutqt e: ", maxDist[maxi]);
    while(savePath[maxi] >= 0){
        printf("%u ", maxi + 1);
        maxi = savePath[maxi];
    }
    
    printf("%d\n", maxi + 1);
}

void testLongestPath() {
    solveLongestPath();
}

#ifdef __cplusplus
}
#endif

#endif /* FINDLONGESTPATHCACYCLICGRAPH_H */

