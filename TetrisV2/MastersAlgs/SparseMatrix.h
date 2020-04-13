/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   SparseMatrix.h
 * Author: default
 *
 * Created on June 27, 2019, 3:45 PM
 */

#ifndef SPARSEMATRIX_H
#define SPARSEMATRIX_H


#include <stdio.h>
#include <stdlib.h>
#include <iostream>

#include "Sparse.h"


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
    
    s->e = (Element*)malloc(s->totalElements * sizeof(struct Element));
    printf("Enter All Elements: ");
    for(i = 0; i < s->totalElements; i++) {
        scanf("%d%d%d", &s->e[i].row, &s->e[i].col, &s->e[i].value);
    }
}
void displaySparse(struct SparseMatrix s) {
    int row, col, k = 0;
    for(row = 0; row < s.totalRow; row++) {
        for(col = 0; col < s.totalCol; col++) {
            if(row == s.e[k].row && col == s.e[k].col) {
                printf("%d ", s.e[k++].value);
            }
            else {
                printf("0 ");
            }
        }
        printf("\n");
    }
}

struct SparseMatrix* addSparse(struct SparseMatrix* first, struct SparseMatrix* second) {
    if(first->totalRow != second->totalRow || first->totalCol != second->totalCol) {
        return nullptr;
    }
    struct SparseMatrix* sum;
    sum = (SparseMatrix*)malloc(sizeof(struct SparseMatrix));
    sum->totalRow = first->totalRow;
    sum->totalCol = first->totalCol;
    sum->e = (struct Element*)malloc((first->totalElements + second->totalElements) * sizeof(struct Element));
    
    int i = 0, j = 0, k = 0;
    
    while(i < first->totalElements && j < second->totalElements) {
        if(first->e[i].row < second->e[j].row) {
            sum->e[k].row = first->e[i].row;
            sum->e[k].col = first->e[i].col;
            sum->e[k].value = first->e[i].value;
            k++;
            i++;
        }
        else if(first->e[i].row > second->e[j].row) {
            sum->e[k].row = second->e[j].row;
            sum->e[k].col = second->e[j].col;
            sum->e[k].value = second->e[j].value;
            k++;
            j++;
        }
        else {  //rows are equal
            if(first->e[i].col < second->e[j].col) {
                sum->e[k].row = first->e[i].row;
                sum->e[k].col = first->e[i].col;
                sum->e[k].value = first->e[i].value;
                k++;
                i++;
            }
            else if(first->e[i].col > second->e[j].col) {
                sum->e[k].row = second->e[j].row;
                sum->e[k].col = second->e[j].col;
                sum->e[k].value = second->e[j].value;
                k++;
                j++;
            }
            else {
                sum->e[k].row = first->e[i].row;
                sum->e[k].col = first->e[i].col;
                sum->e[k].value = first->e[i].value + second->e[j].value;
                k++;
                i++;
                j++;
            }
        }
    }
    
    for( ; i < first->totalElements; i++) {
        sum->e[k].row = first->e[i].row;
        sum->e[k].col = first->e[i].col;
        sum->e[k].value = first->e[i].value;
        k++;
    }
    for( ; j < second->totalElements; j++) {
        sum->e[k].row = second->e[j].row;
        sum->e[k].col = second->e[j].col;
        sum->e[k].value = second->e[j].value;
        k++;
    }
    
    return sum;
}
void testSparce() {
    struct SparseMatrix s;
    createSparse(&s);
    
    
    struct SparseMatrix s2;
    createSparse(&s2);
    
    std::cout << "Result: \n\n";
    displaySparse(s);
    std::cout << std::endl;
    displaySparse(s2);
    std::cout << std::endl;
    struct SparseMatrix* result = addSparse(&s, &s2);
    std::cout << "Third Result: \n";
    displaySparse(*result);
    free(result->e);
    free(result);
    free(s.e);
    free(s2.e);
}

void testSparseCplus() {
    Sparse s1(3, 3, 3);
    Sparse s2(3, 3, 3);
//    s1.readData();
//    s1.displayData();
    
    std::cin >> s1;
    std::cin >> s2;
    
    Sparse* resultMatrix = s1 + s2;
    std::cout << "First Matrix: \n";
    std::cout << s1;
    std::cout << "Second Matrix: \n";
    std::cout << s2;
    std::cout << "Result Matrix: \n";
    std::cout << *resultMatrix;
    delete resultMatrix;
}

#endif /* SPARSEMATRIX_H */

