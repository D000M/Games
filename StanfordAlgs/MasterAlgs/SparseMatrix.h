/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   SparseMatrix.h
 * Author: default
 *
 * Created on June 27, 2019, 3:34 PM
 */

#ifndef SPARSEMATRIX_H
#define SPARSEMATRIX_H

#include <stdio.h>
#include <stdlib.h>


struct Element {
    int row;
    int col;
    int value;
};

struct SparseMatrix {
    int totalRow;
    int totalCol;
    int totalElements;
    struct Element* e;
};

void createSparse(struct SparseMatrix* s) {
    int i;
    printf("Enter Dimmensions, Rows and Cols: ");
    scanf("%d%d", &s->totalRow, &s->totalCol);
    printf("Enter Number of Non-Zero elements: ");
    scanf("%d", &s->totalElements);
    
    s->e = (struct Element*)malloc(s->totalElements * (struct Element));
    printf("Enter All Elements: ");
    for(i = 0; i < s->totalElements; i++) {
        scanf("%d%d%d", &s->e[i].row, &s->e[i].col, &s->e[i].value);
    }
}

void testSparce() {
    struct SparseMatrix s;
    createSparse(&s);
    
    free((struct Element)s->e);
}

#endif /* SPARSEMATRIX_H */

