/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   DivideAndConquer.h
 * Author: default
 *
 * Created on March 1, 2019, 12:37 PM
 * 
 * Topics
 * 1. Binary Search
 * 2. Finding Maximum and Minimum
 * 3. Merge Sort
 * 4. Quick Sort
 * 5. Strassen's Matrix multiplication
 * 
 */

#ifndef DIVIDEANDCONQUER_H
#define DIVIDEANDCONQUER_H

#include <vector>


//Merge Sort Iterative.
void mergeSortIterative(std::vector<int>& first, std::vector<int>& second, std::vector<int>& result) {
    int firstIndex = 0; 
    int secondIndex = 0;
    
    while(firstIndex < first.size() && secondIndex < second.size()) {
        if(first.at(firstIndex) < second.at(secondIndex)) {
            result.push_back(first.at(firstIndex));
            firstIndex++;
        }
        else {
            result.push_back(second.at(secondIndex));
            secondIndex++;
        }
    }
    while(firstIndex < first.size()) {
        result.push_back(first.at(firstIndex));
        firstIndex++;
    }
    while(secondIndex < second.size()) {
        result.push_back(second.at(secondIndex));
        secondIndex++;
    }
}

// Merges two subarrays of arr[]. 
// First subarray is arr[l..m] 
// Second subarray is arr[m+1..r] 

void merge(int arr[], int left, int middle, int right) {
    int i, j, k;
    int n1 = middle - left + 1;
    int n2 = right - middle;

    /* create temp arrays */
    int L[n1], R[n2];

    /* Copy data to temp arrays L[] and R[] */
    for (i = 0; i < n1; i++)
        L[i] = arr[left + i];
    for (j = 0; j < n2; j++)
        R[j] = arr[middle + 1 + j];

    /* Merge the temp arrays back into arr[l..r]*/
    i = 0; // Initial index of first subarray 
    j = 0; // Initial index of second subarray 
    k = left; // Initial index of merged subarray 
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        }
        else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    /* Copy the remaining elements of L[], if there 
       are any */
    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }

    /* Copy the remaining elements of R[], if there 
       are any */
    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
} 

void mergeSort(int A[], int left, int right) {
    
    if (left < right) 
    { 
        // Same as (l+r)/2, but avoids overflow for 
        // large l and h 
        int middle = left + (right - left)/2; 
  
        // Sort first and second halves 
        mergeSort(A, left, middle); 
        mergeSort(A, middle + 1, right); 
  
        merge(A, left, middle, right); 
    } 
}


/**
 * Quick Sort
 * 
 */
void swap(int& first, int& second) {
    int temp = first;
    first = second;
    second = temp;
}
int partition(int low, int high, int arr[]) {
    int pivot = arr[low];
    int i = low;
    int j = high;
    
    while(i < j) {
        
        do {
            i++;
        }while(arr[i] <= pivot);
        
        do {
            j--;
        }while(arr[j] > pivot);
        
        if(i < j) {
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[low], arr[j]);
    return j;
}

void quickSort(int low, int high, int arr[]) {
    if(low < high) {
        int sorted = partition(low, high, arr);
        quickSort(low, sorted, arr);
        quickSort(sorted + 1, high, arr);
    }
}
#endif /* DIVIDEANDCONQUER_H */

