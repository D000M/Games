/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Polynomial.h
 * Author: default
 *
 * Created on July 2, 2019, 4:51 PM
 */

#ifndef POLYNOMIAL_H
#define POLYNOMIAL_H

#include <stdio.h>
#include <stdlib.h>
#include <complex>


struct CTerm {
    int coeff;
    int exp;
};

struct CPoly {
    int size;
    struct CTerm* term;
};

int sumOfPolynome(struct CPoly poly, int x) {
    int resX = x;
    int sum = 0;
    for(int i = 0; i < poly.size; i++) {
        sum += poly.term[i].coeff * std::pow(resX, poly.term[i].exp);
        std::cout << sum << std::endl;
    }
    return sum;
}

void addTwoPolynoms(struct CPoly first, struct CPoly second) {
    
    int i = 0, j = 0, k = 0;
    struct CPoly* result = (struct CPoly*)malloc(sizeof(struct CPoly));
    result->size = first.size + second.size;
    result->term = (struct CTerm*)malloc(result->size * sizeof(struct CTerm));
    
    while( i < first.size && j < second.size) {
        if(first.term[i].exp > second.term[j].exp) {
            result->term[k].coeff = first.term[i].coeff;
            result->term[k].exp = first.term[i].exp;
            k++;
            i++;
        }
        else if(first.term[i].exp < second.term[j].exp) {
            result->term[k].coeff = second.term[j].coeff;
            result->term[k].exp = second.term[j].exp;
            k++;
            j++;
        }
        else {
            result->term[k].coeff = first.term[i].coeff + second.term[j].coeff;
            result->term[k].exp = first.term[i].exp + second.term[j].exp;
            k++;
            j++;
            i++;
        }
    }
    for(; i < first.size; i++) {
        result->term[k].coeff = first.term[i].coeff;
        result->term[k].exp = first.term[i].coeff;
        k++;
        i++;
    }
    for(; j < second.size; j++) {
        result->term[k].coeff = second.term[j].coeff;
        result->term[k].exp = second.term[j].exp;
        k++;
        j++;
    }
    
    int sumOfPolynoms = sumOfPolynome(*result, 2);
    std::cout << sumOfPolynoms << std::endl;
    free(result->term);
    free(result);
}

void testPolynomial() {
    struct CPoly polynome;
    
    printf("Enter Size of the polynome: ");
    scanf("%d", &polynome.size);
    polynome.term = (struct CTerm*)malloc(polynome.size * sizeof(struct CTerm));
    
    printf("Enter Polynomial terms coeff and exponent: ");
    for(int i = 0; i < polynome.size; i++) {
        printf("Term #: %d, coeff: exp: ", i + 1);
        scanf("%d%d", &polynome.term[i].coeff, &polynome.term[i].exp);
    }
    int result = sumOfPolynome(polynome, 1);
    std::cout << "Polynomial result: " << result << std::endl;
    
    
    free(polynome.term);
}

void testAddPolynoms() {
    struct CPoly first;
    struct CPoly second;
    
    printf("Enter Size of the polynome1: ");
    scanf("%d", &first.size);
    first.term = (struct CTerm*)malloc(first.size * sizeof(struct CTerm));
    
    printf("Enter Polynomial terms coeff and exponent: ");
    for(int i = 0; i < first.size; i++) {
        printf("Term #: %d, coeff: exp: ", i + 1);
        scanf("%d%d", &first.term[i].coeff, &first.term[i].exp);
    }
    
    printf("Enter Size of the polynome2: ");
    scanf("%d", &second.size);
    second.term = (struct CTerm*)malloc(second.size * sizeof(struct CTerm));
    
    printf("Enter Polynomial terms coeff and exponent: ");
    for(int i = 0; i < second.size; i++) {
        printf("Term #: %d, coeff: exp: ", i + 1);
        scanf("%d%d", &second.term[i].coeff, &second.term[i].exp);
    }
    addTwoPolynoms(first, second);
    
    free(first.term);
    free(second.term);
}

#endif /* POLYNOMIAL_H */

