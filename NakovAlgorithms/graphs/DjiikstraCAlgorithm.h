/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   DjiikstraCAlgorithm.h
 * Author: default
 *
 * Created on January 14, 2019, 3:00 PM
 */

#ifndef DJIIKSTRACALGORITHM_H
#define DJIIKSTRACALGORITHM_H

#include "ExtremePathsCGraphs.h"
#include "CGraphs.h"


#ifdef __cplusplus
extern "C" {
#endif

#define NO_PARENT (unsigned)(-1)

    //Broi vyrhove v grafa
const unsigned n3 = 10;
const unsigned s = 1;

//Matrica na teglata na grafa
const unsigned B[MAXN2][MAXN2] = {
    { 0, 23,  0,  0,  0,  0,  0,  8,  0,  0},
    {23,  0,  0,  3,  0,  0, 34,  0,  0,  0},
    { 0,  0,  0,  6,  0,  0,  0, 25,  0,  7},
    { 0,  3,  6,  0,  0,  0,  0,  0,  0,  0},
    { 0,  0,  0,  0,  0, 10,  0,  0,  0,  0},
    { 0,  0,  0,  0, 10,  0,  0,  0,  0,  0},
    { 0, 34,  0,  0,  0,  0,  0,  0,  0,  0},
    { 8,  0, 25,  0,  0,  0,  0,  0,  0, 30},
    { 0,  0,  0,  0,  0,  0,  0,  0,  0,  0},
    { 0,  0,  7,  0,  0,  0,  0, 30,  0,  0}
};
    
char T[MAXN2];
unsigned d[MAXN2];
//int pred[MAXN2];
/**
 * Algorithm na Dijkstra minimalen put S do ostanalite vyrhove
 * @param s
 */
void dijkstraPath(unsigned s) {
    unsigned i;
    for(i = 0; i < n3; i++) {   //Inizializirame: d[i] = B[s][i], (i E V), i != s;
        if(B[s][i] == 0) {
            d[i] = MAX_VALUE;
            CGRAPHS::pred[i] = NO_PARENT;
        }
        else {
            d[i] = B[s][i];
            CGRAPHS::pred[i] = s;
        }
    }
    for(i = 0; i < n3; i++) {   //T sudurja vsichki vyrhove
        T[i] = 1;
    }
    T[s] = 0;
    CGRAPHS::pred[s] = NO_PARENT;        //ot grafa, s ickluchenie na s. 
    
    while(true) {   //Dokato T sudurja i: d[i] < MAX_VALUE/
        //Izbirane na vyrha j ot T, za koito d[j] e minimalno.
        unsigned j = NO_PARENT;
        unsigned di = MAX_VALUE;
        
        for(i = 0; i < n3; i++) {
            if(T[i] && d[i] < di) {
                di = d[i];
                j = i;
            }
        }
        if(j == NO_PARENT) {    //d[i] = MAX_VALUE, za vsichki i: EXIT. 
            break;
        }
        T[j] = 0;   //Izkluchvame j ot T
        
        //Za vsqko it ot T izpulnqvame D[i] = min(d[i], d[j] + A[j][i]) izpulnqvame
        for(i = 0; i < n3; i++) {
            if(T[i] && B[j][i] != 0) {
                if(d[i] > d[j] + B[j][i]) {
                    d[i] = d[j] + B[j][i];
                    CGRAPHS::pred[i] = j;
                }
            }
        }
    }
}

void printDijkstraPath(unsigned s, unsigned j) {
    if(CGRAPHS::pred[j] != s) {
        printDijkstraPath(s, CGRAPHS::pred[j]);
    }
    printf("%u ", j + 1);
}

void printDijkstraResult(unsigned s) {
    unsigned i;
    for(i = 0; i < n3; i++) {
        if(i != s) {
            if(d[i] == MAX_VALUE) {
                printf("Nqma put mejdu vurhovete %u i %u\n ", s + 1, i + 1 );
            }
            else {
                printf("Minimalen put ot vryh %u do %u:   %u ", s + 1, i + 1, s + 1);
                printDijkstraPath(s, i);
                printf(", Duljina na putq: %u\n", d[i]);
            }
        }
    }
}

void testDijkstra() {
    dijkstraPath(s - 1);
    printDijkstraResult(s - 1);
}

#ifdef __cplusplus
}
#endif

#endif /* DJIIKSTRACALGORITHM_H */

