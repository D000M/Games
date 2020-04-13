/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   StrasenSubcubic.h
 * Author: default
 *
 * Created on February 27, 2019, 2:06 PM
 */

#ifndef STRASENSUBCUBIC_H
#define STRASENSUBCUBIC_H


void multiple2Matrix() {
    int size = 32;
    int X[size][size];
    for(int i = 0; i < size; ++i) {
        for(int j = 0; j < size; ++j) {
            X[i][j] = i + j + 2;
        }
    }
    int Y[size][size];
    for(int i = 0; i < size; ++i) {
        for(int j = 0; j < size; ++j) {
            Y[i][j] = i * j + 3;
        }
    }
     int Z[size][size];
    int count = 0;
    for(int i = 0; i < size; ++i) {
        for(int j = 0; j < size; ++j) {
            Z[i][j] = 0;
            for(int k = 0; k < size; ++k) {
                Z[i][j] += X[i][k] * Y[k][j];
                count++;
            }
            std::cout << Z[i][j] << " ";
        }
        std::cout << std::endl;
    }
    std::cout << "Total iterations: " << count << std::endl;
}
void print2DimmArray2(int** arr, int size) {
    for(int i = 0; i < size; ++i) {
        for(int j = 0; j < size; ++j) {
            std::cout << arr[i][j] << " ";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

void matrixMult(int** A, int** B, int** C) {
    C[0][0] = (A[0][0] * B[0][0]) + (A[0][1] * B[1][0]);
    C[0][1] = (A[0][0] * B[0][1]) + (A[0][1] * B[1][1]);
    C[1][0] = (A[1][0] * B[0][0]) + (A[1][1] * B[1][0]);
    C[1][1] = (A[1][0] * B[0][1]) + (A[1][1] * B[1][1]);
}
int CCCC = 0;
int** matrixAdd(int** A, int** B, int size) {
    int** C = new int*[size];
    for(int i = 0; i < size; i++) {
        C[i] = new int[size];
        for(int j = 0; j < size; j++) {
            C[i][j] = A[i][j] + B[i][j];
            CCCC++;
        }
    }
    return C;
}
int** matrixSub(int** A, int** B, int size) {
    int** C = new int*[size];
    for(int i = 0; i < size; i++) {
        C[i] = new int[size];
        for(int j = 0; j < size; j++) {
            C[i][j] = A[i][j] - B[i][j];
        }
    }
    return C;
}

//Naive running time 0n^3 diffculty
void recursiveMultiply(int** A, int** B, int** C, int size) {

    if(size <= 2) {
        matrixMult(A, B, C);
    }
    else {
//        CCCC++;
        int middle = size / 2;
        int** A11 = new int*[middle];
        int** A12 = new int*[middle];
        int** A21 = new int*[middle];
        int** A22 = new int*[middle];
        int** B11 = new int*[middle];
        int** B12 = new int*[middle];
        int** B21 = new int*[middle];
        int** B22 = new int*[middle];
        
        for(int i = 0; i < middle; ++i) {
            CCCC++;
            A11[i] = new int[middle];
            A12[i] = new int[middle];
            A21[i] = new int[middle];
            A22[i] = new int[middle];
            
            B11[i] = new int[middle];
            B12[i] = new int[middle];
            B21[i] = new int[middle];
            B22[i] = new int[middle];
        }
        
        for(int i = 0; i < middle; i++) {
            for(int j = 0; j < middle; j++) {
//                CCCC++;
                A11[i][j] = A[i][j];
                A12[i][j] = A[i][j + middle];
                A21[i][j] = A[i + middle][j];
                A22[i][j] = A[i + middle][j + middle];
                
                B11[i][j] = B[i][j];
                B12[i][j] = B[i][j + middle];
                B21[i][j] = B[i + middle][j];
                B22[i][j] = B[i + middle][j + middle];
            }
        }
        int** first = new int*[middle];
        for(int i = 0; i < middle; ++i) {
//            CCCC++;
            first[i] = new int[middle];
        }
        int** second = new int*[middle];
        for(int i = 0; i < middle; ++i) {
//            CCCC++;
            second[i] = new int[middle];
        }
        int** upLeft = new int*[middle];
        for(int i = 0; i < middle; ++i) {
//            CCCC++;
            upLeft[i] = new int[middle];
        }
        int** upRight = new int*[middle];
        for(int i = 0; i < middle; ++i) {
//            CCCC++;
            upRight[i] = new int[middle];
        }
        int** downLeft = new int*[middle];
        for(int i = 0; i < middle; ++i) {
//            CCCC++;
            downLeft[i] = new int[middle];
        }
        int** downRight = new int*[middle];
        for(int i = 0; i < middle; ++i) {
//            CCCC++;
            downRight[i] = new int[middle];
        }
        recursiveMultiply(A11, B11, first, middle);
        recursiveMultiply(A12, B21, second, middle);
        upLeft = matrixAdd(first, second, middle);
        
        recursiveMultiply(A11, B12, first, middle);
        recursiveMultiply(A12, B22, second, middle);
        upRight = matrixAdd(first, second, middle);
        
        recursiveMultiply(A21, B11, first, middle);
        recursiveMultiply(A22, B21, second, middle);
        downLeft = matrixAdd(first, second, middle);
        
        recursiveMultiply(A21, B12, first, middle);
        recursiveMultiply(A22, B22, second, middle);
        downRight = matrixAdd(first, second, middle);
        
        for(int i = 0; i < middle; ++i) {
            for(int j = 0; j < middle; ++j) {
                CCCC++;
                C[i][j] = upLeft[i][j];
                C[i][j + middle] = upRight[i][j];
                C[i + middle][j] = downLeft[i][j];
                C[i + middle][j + middle] = downRight[i][j];
            }
        }
        for(int i = 0; i < middle; ++i) {
            CCCC++;
            delete[] A11[i];
            delete[] A12[i];
            delete[] A21[i];
            delete[] A22[i];
            delete[] B11[i];
            delete[] B12[i];
            delete[] B21[i];
            delete[] B22[i];
            delete[] upLeft[i];
            delete[] upRight[i];
            delete[] downLeft[i];
            delete[] downRight[i];
            delete[] first[i];
            delete[] second[i];
        }
        delete[] A11;
        delete[] A12;
        delete[] A21;
        delete[] A22;
        delete[] B11;
        delete[] B12;
        delete[] B21;
        delete[] B22;
        delete[] upLeft;
        delete[] upRight;
        delete[] downLeft;
        delete[] downRight;
        delete[] first;
        delete[] second;
    }
}
void printCCCC() {
    std::cout << "Total operations: " << CCCC << std::endl;
}
#endif /* STRASENSUBCUBIC_H */

