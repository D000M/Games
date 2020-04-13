/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   TestSorts.h
 * Author: default
 *
 * Created on February 21, 2019, 12:54 PM
 */

#ifndef TESTSORTS_H
#define TESTSORTS_H

#include <vector>
#include <iostream>
#include <string>
#include "../../utils/RNGGenerator.h"
#include "Sorts.h"

void randomizeArray(int arr[], int size) {
    for(int i = 0; i < size; ++i) {
        arr[i] = getRandomInteger(1, 100);
    }
}
template<typename T>
void printArray(T arr[], int size, const std::string& msg) {
    std::cout << msg;
    for(int i = 0; i < size; ++i) {
        std::cout << arr[i] << " ";
    }
    std::cout << std::endl;
}

void testSelectionSort() {
    int arr[20];
    int size = std::size(arr);
    randomizeArray(arr, size);
    printArray(arr, size, "Before Sort: ");
    selectionSort(arr, size);
    printArray(arr, size, "After Sort: ");
}


void testInsertionSort() {
    int arr[30];
    int size = std::size(arr);
    randomizeArray(arr, size);
    printArray(arr, size, "Before sort: ");
    insertionSort(arr, size);
    printArray(arr, size, "After sort: ");
}

void testBubbleSort() {
    int arr[30];
    int size = std::size(arr);
    randomizeArray(arr, size);
    printArray(arr, size, "Before sort: ");
    bubbleSort(arr, size);
    printArray(arr, size, "After sort: ");
}


void testMergeSort() {
    int arr[6] = { 1, 3, 5, 2, 4, 6 };;
    int size = std::size(arr);
//    randomizeArray(arr, size);
    printArray(arr, size, "Before sort: ");
    mergeSort(arr, 0, size - 1);
    printArray(arr, size, "After sort: ");
}
#endif /* TESTSORTS_H */

