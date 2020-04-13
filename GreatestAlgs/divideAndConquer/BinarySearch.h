/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   BinarySearch.h
 * Author: default
 *
 * Created on March 1, 2019, 3:46 PM
 */

#ifndef BINARYSEARCH_H
#define BINARYSEARCH_H

/**
 * Binary Search worked only for sorted collections
 * 
 *  1  2  3   4   5   6   7   8   9   10  11  12   13   14  15   16
 * [3][8][14][23][26][29][35][44][55][67][88][99][105][112][115][120]  << our collection
 *  ^                          ^                                  ^  
 * low                        middle                             high
 * 
 * search for key = 105
 * 
 * we take LOW and HIGH    and create MIDDLE where MIDDLE is (LOW + HIGH) / 2
 * our middle is (1 + 16) / 2 = 8
 * element on index 8 is 44 
 * so 105 > 44 
 * change low = middle + 1
 * low = 9
 * high = 15
 * middle = (low + high) / 2   = (9 + 15) / 2 = 12
 */


/**
 * Iterative Binary Search
 * @param arr
 * @param size
 * @param value
 * @return 
 */
int iterativeBinarySearch(int arr[], int size, int value) {

    int low = 0;
    int high = size;

    while(low <= high) {
        int middle = (low + high) / 2;
        if(value == arr[middle]) {
            std::cout << "Element " << value << " found at position: " << middle << std::endl;
            return middle;
        }
        else if(value > arr[middle]) {
            low = middle + 1;
        }
        else if(value < arr[middle]) {
            high = middle - 1;
        }
    }
}

/**
 * Recursive Binary Sort
 * T(n) = { 1       low == high
 *        { T(n / 2) + 1    -->  O(logn)
 * @param arr
 * @param low
 * @param high
 * @param element
 * @return 
 */
int recursiveBinarySearch(int arr[], int low, int high, int element) {
    if(low >= high) {
        if(element == arr[low]) {
            return low;
        }
        else {
            return -1;
        }
    }
    else {
        int middle = (low + high) / 2;
        if(element == arr[middle]) {
            return middle;
        }
        if(element < arr[middle]) {
            return recursiveBinarySearch(arr, low, middle - 1, element);
        }
        else if(element > arr[middle]) {
            return recursiveBinarySearch(arr, middle + 1, high, element);
        }
    }
}

#endif /* BINARYSEARCH_H */

