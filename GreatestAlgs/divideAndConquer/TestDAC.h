/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   TestDAC.h
 * Author: default
 *
 * Created on March 1, 2019, 12:42 PM
 */

#ifndef TESTDAC_H
#define TESTDAC_H

#include <vector>
#include <iterator>

#include "RecurrenceRelations.h"
#include "BinarySearch.h"
#include "DivideAndConquer.h"


void testRRtest() {
    printSquareOfTwo(1);
}

void testIterativeBinarySearh() {
    int arr[] = {
        3, 8, 14, 23, 26, 29, 35, 44, 55, 67, 88, 99, 105, 112, 115, 120  
    };
    iterativeBinarySearch(arr, 16, 35);
}
void testRecursiveBinarySearch() {
    int arr[] = {
        3, 8, 14, 23, 26, 29, 35, 44, 55, 67, 88, 99, 105, 112, 115, 120  
    };
    for(int element = 0; element < 125; ++element) {
        int index = recursiveBinarySearch(arr, 0, std::size(arr), element);
        if(index != -1) {
            std::cout << "Element " << element <<" found at index: " << index << std::endl;
        }
        else {
            std::cout << "Element " << element << " was not found!\n";
        }
    }
}



void testMergeSortIterative() {
    std::vector<int> first = {2, 3, 5, 7, 9, 10, 20, 21};
    std::vector<int> second = {1, 3, 3, 3, 4, 6, 8, 12, 14, 15, 16};
    std::vector<int> result;
    mergeSortIterative(first, second, result);
    
    std::copy(result.begin(), result.end(), std::ostream_iterator<int>(std::cout, " "));
    
}
void printArray(int A[], int size) 
{ 
    int i; 
    for (i=0; i < size; i++) 
        printf("%d ", A[i]); 
    printf("\n"); 
} 

void testMergeSort() {
    int arr[] = {23, 52, 12, 56, 1, 4, 8, 9, 12};
    int arrSize = sizeof(arr)/sizeof(arr[0]);
    printArray(arr, arrSize);
    std::cout << std::endl;
    mergeSort(arr, 0, arrSize - 1);
    printArray(arr, arrSize);
}


void testQuickSort() {
    int arr[] = {23, 52, 12, 56, 1, 2, 2, 3, 3, 3, 3, 3, 3, 2, 2, 2, 1, 1, 1, 15, 18, 4, 4, 4, 8, 9, 12};
    int arrSize = sizeof(arr)/sizeof(arr[0]);
    printArray(arr, arrSize);
    std::cout << std::endl;
    quickSort(0, arrSize, arr);
    printArray(arr, arrSize);
}
#endif /* TESTDAC_H */

