/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   DivideAndConquer.h
 * Author: default
 *
 * Created on February 22, 2019, 2:51 PM
 */

#ifndef DIVIDEANDCONQUER_H
#define DIVIDEANDCONQUER_H
#include <iostream>
#include <iterator>
#include <algorithm>
#include <vector>
#include <cstdlib>
#include <cstdio>
#include <cstring>
/**
 * Divide and conquer algorithm for finding inversions in an array
 * Example {1, 3, 5, 2, 4, 6}
 * 3-2
 * 5-2
 * 5-4
 * are not in order.
 */
/**
 * Version 1 Brute Force difficulty: On^2
 * @param arr
 * @param size
 */
void bruteForce(int arr[], int size) {
    int count = 0;
    for(int i = 0; i < size; i++) {
        for(int j = i + 1; j < size; j++) {
            if(arr[i] > arr[j]) {
                count++;
            }
        }
    }
    std::cout << "Total Inversions: " << count << std::endl;
}

/**
 * Version 2 Divide and conquer
 */
template <typename T>
long long mergeSortAndCountInversions(T* arr, int size)
{
    int m;

    if (size <= 1) {
        return 0;
    }

    m = size / 2;

    long long invCountA = 0, invCountB = 0, invCountC = 0;
    invCountA = mergeSortAndCountInversions(arr, m);
    invCountB = mergeSortAndCountInversions(arr + m, size - m);

    T* arrPartA = new T[m];
    T* arrPartB = new T[size - m];

    memcpy(arrPartA, arr, sizeof(T) * m);
    memcpy(arrPartB, arr + m, sizeof(T) * (size - m));

    int i = 0, j = 0, k = 0;

    while (k < size)
    {
            if (arrPartA[i] < arrPartB[j])
            {
                    arr[k] = arrPartA[i];
                    i++;

                    invCountC += j;
            }
            else
            {
                    arr[k] = arrPartB[j];
                    j++;

                    invCountC += 1;
            }

            k++;

            if (i >= m || j >= (size - m))
                    break;
    }

    invCountC -= j;

    while (i < m)
    {
            arr[k] = arrPartA[i];
            k++;
            i++;

            invCountC += j;
    }
    while (j < (size - m))
    {
            arr[k] = arrPartB[j];
            k++;
            j++;
    }

    delete []arrPartA;
    delete []arrPartB;

    return (invCountA + invCountB + invCountC);
}


int mergeAndCountInversions(int* arr, int size) {
    int middle;
    if(size <= 1) {
        return 0;
    }
    middle = size / 2;
    
    int countA = 0;
    int countB = 0;
    int countC = 0;
    
    countA = mergeAndCountInversions(arr, middle);
    countB = mergeAndCountInversions(arr + middle, size - middle);
    
    int* arrA = new int[middle];
    int* arrB = new int[size - middle];
    
    memcpy(arrA, arr, sizeof(int) * middle);
    memcpy(arrB, arr + middle, sizeof(int) * (size - middle));
    
    int i = 0; 
    int j = 0;
    int k = 0;
    
    while(k < size) {
        if(arrA[i] < arrB[j]) {
            arr[k] = arrA[i];
            i++;
            countC += j;
        }
        else {
            arr[k] = arrB[j];
            j++;
            countC += 1;
        }
        k++;
        if(i >= middle || j >= (size - middle)) {
            break;
        }
    }
    countC -= j;
    
    while( i < middle) {
        arr[k] = arrA[i];
        k++;
        i++;
        countC += j;
    }
    while(j < (size - middle)) {
        arr[k] = arrB[j];
        k++;
        j++;
    }
    delete [] arrA;
    delete [] arrB;
    return (countA + countB + countC);
}
#endif /* DIVIDEANDCONQUER_H */

