/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   ExtremePathsCGraphs.h
 * Author: default
 *
 * Created on January 11, 2019, 2:45 PM
 */

#ifndef EXTREMEPATHSCGRAPHS_H
#define EXTREMEPATHSCGRAPHS_H

#include <stdio.h>


#ifdef __cplusplus
extern "C" {
#endif

namespace CGRAPHS {
    
    #define MAXN2 150   //Maksimalen broi na vurhove v grafa
    #define MAX_VALUE 10000 
    
    const unsigned int n2 = 4; //Broi vyrhove v grafa.
    
    //Matrica na teglata na grafa za naglednost kadeto nqmame rebra A[i][j] = 0, po kysno shte zadadem A[i][j] = MAX_VALUE
    unsigned int A2[MAXN2][MAXN2] = {
       // 1   2   3   4   5   6   7   8   9   10 
//        { 0, 23,  0,  0,  0,  0,  0,  8,  0,  0}, //1 
//        {23,  0,  0,  3,  0,  0, 34,  0,  0,  0}, //2 
//        { 0,  0,  0,  6,  0,  0,  0, 25,  0,  7}, //3
//        { 0,  3,  6,  0,  0,  0,  0,  0,  0,  0}, //4
//        { 0,  0,  0,  0,  0, 10,  0,  0,  0,  0}, //5
//        { 0,  0,  0,  0, 10,  0,  0,  0,  0,  0}, //6
//        { 0, 34,  0,  0,  0,  0,  0,  0,  0,  0}, //7
//        { 8,  0, 25,  0,  0,  0,  0,  0,  0, 30}, //8
//        { 0,  0,  0,  0,  0,  0,  0,  0,  0,  0}, //9
//        { 0,  0,  7,  0,  0,  0,  0, 30,  0,  0}  //10
       //A  B  C  D 
        {0, 0, 6, 2}, //A
        {0, 0, 0, 0}, //B
        {0, 1, 0, 0}, //C
        {0, 0, 2, 0}  //D
        
    };
    
    /**
     * Namira duljinata na minimalnia put mejdu vsqka dvoika vurhove 
     * Algorithm na Floyd
     */
    void floydAlgorithm(void) {
        unsigned i, j, k;
        //Stoinostite 0 se promenqt na MAX_VALUE
        for(i = 0; i < n2; i++) {
            for(j = 0; j < n2; j++) {
                if(A2[i][j] == 0) {
                    A2[i][j] = MAX_VALUE;
                }
            }
        } //end of outer for
        
        /*Algorithm na Floyd*/
        for(k = 0; k < n2; k++) {
            for(i = 0; i < n2; i++) {
                for(j = 0; j < n2; j++) {
                    if(A2[i][j] > (A2[i][k] + A2[k][j])) {
                        A2[i][j] = A2[i][k] + A2[k][j];
                    }
                }
            }
        }
        for(i = 0; i < n2; i++) {
            A2[i][i] = 0;
        }
        
    }   //End of floydAlgorithm(void)
    
    void printMinPaths(void) {
        unsigned i, j;
        printf("Matricata na teglata sled izpulnenieto na algorithma na Floyd: \n");
        for(i = 0; i < n2; i++) {
            for(j = 0; j < n2; j++) {
                printf("%3d ", (A2[i][j] == MAX_VALUE ? 0 : A2[i][j]));
            }
            printf("\n");                    
        }
    }
    
    void testFloyd() {
        printMinPaths();
        printf("\n#########################\n");
        floydAlgorithm();
        printMinPaths();
    }
    
    ////Small Improvements of Floyd Algs
    int max(int first, int second) {        
        return first > second ? first : second;
    }
    void improvedFloyd(void) {
        unsigned i, j, k;
        //Stoinostite 0 se promenqt na MAX_VALUE
        for(i = 0; i < n2; i++) {
            for(j = 0; j < n2; j++) {
                if(A2[i][j] == 0 && (i != j)) {
                    A2[i][j] = MAX_VALUE;
                }
            }
        } //end of outer for
        
        /*Algorithm na Floyd*/
        for(k = 0; k < n2; k++) {
            for(i = 0; i < n2; i++) {
                for(j = 0; j < n2; j++) {
                    if((i != j) && (i != k) && (k != j)) {
                        if(A2[i][j] > (A2[i][k] + A2[k][j])) {
                            A2[i][j] = A2[i][k] * A2[k][j];
                        }
                    }
                }
            }
        }
    }
    void testImprovedFloyd(void) {
        printMinPaths();
        improvedFloyd();
        printMinPaths();
    }
    
} //end of CGRAPHS


#ifdef __cplusplus
}
#endif

#endif /* EXTREMEPATHSCGRAPHS_H */

