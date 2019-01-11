/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   CPPSorts.h
 * Author: default
 *
 * Created on January 4, 2019, 2:08 PM
 */

#ifndef CPPSORTS_H
#define CPPSORTS_H

#include <iostream>
#include <algorithm>
#include <iterator>


namespace SORTS {

template<typename T> 
void printSequence(T arr[], int size, const std::string& msg) {
    std::cout << msg;
    std::copy(arr, arr + size, std::ostream_iterator<T>(std::cout, " "));
    std::cout << std::endl;
}
    
template<typename T>    
void swap(T& elemOne, T& elemTwo) {
    T temp = elemOne;
    elemOne = elemTwo;
    elemTwo = temp;
}

/**
 * Insertion Sort
 * Effective with small amount of elements array size less than 20
 */
template<typename T>
void straightInsertionSort(T arr[], const unsigned int size) {
    for(int i = 0; i < size; i++) {
        T temp = arr[i];
        int index = i - 1;
        while(index >= 0 && temp < arr[index]) {
            arr[index + 1] = arr[index--];
        }
        arr[index + 1] = temp;
    }
}

/**
 * Insertion Sort V2
 * Ne Raboti?!?
 */
template<typename T>
void straightInsertionSortV2(T arr[], const unsigned int size) {
    int j;
    for(int i = 1; i <= size; i++) {
        T temp = arr[i];
        arr[0] = temp;
        for(j = i - 1; temp < arr[j]; j--) {
            arr[j + 1] = arr[j];
        }
        arr[j + 1] = temp;
    }
}

template<typename T>
void binaryInsertionSort(T arr[], const unsigned int size) {
    
    unsigned int middle = 0;
    for(int i = 1; i < size; i++) {
        T temp = arr[i];
        int left = 0;
        int right = i - 1;
        
        //Binary search
        while(left <= right) {
            middle = (left + right) / 2;
            if(temp < arr[middle]) {
                right = middle - 1;
            }
            else {
                left = middle + 1;
            }
        }
        
        //The spot is found, insert the element here.
        for(int j = i - 1; j >= left; j--) {
            arr[j + 1] = arr[j];
        }
        arr[left] = temp;
    }
    
}

template<typename T>
void shellSort(T arr[], unsigned int left, unsigned int right) {
    constexpr static int TOTAL = 16;
    static unsigned int steps[TOTAL] {
        1391376, 463792, 198768, 86961, 33936, 13776, 4592, 1968, 861, 336, 112, 48, 21, 7, 3, 1
    };
    unsigned int k, h, i, j;
    T temp;
    for(k = 0; k < TOTAL; k++) {
        for(h = steps[k], i = left + h; i <= right; i++) {
            temp = arr[i];
            
            j = i;
            while(j > h && arr[j - h] > temp) {
                arr[j] = arr[j - h];
                j -= h;
            }
            arr[j] = temp;
        }
    }
}

template<typename T>
void bubbleSort(T arr[], const unsigned int size) {
    unsigned int i, j, k;
    for(i = size - 1; i > 0; i = k) {
        for(k = j = 0; j < i; j++) {
            if(arr[j] > arr[j + 1]) {
                swap(arr[j], arr[j + 1]);
                k = j;
            }
        }
    }
}

template<typename T>
void shakerSort(T arr[], unsigned int size) {
    int bottom = 0;
    int top = size - 1;
    bool swapped = true;
    
    while(swapped == true) {    // if no elements have been swapped, then the list is sorted
        swapped = false;
        for(int i = bottom; i < top; i++) {
            if(arr[i] > arr[i + 1]) {
                swap(arr[i], arr[i + 1]);
                swapped = true;
            }
        }
        // decreases top the because the element with the largest value in the unsorted
        // part of the list is now on the position top 
        top = top - 1;
        for(int i = top; i > bottom; i--) {
            if(arr[i] < arr[i + 1]) {
                swap(arr[i], arr[i - 1]);
                swapped = true;
            }
        }
    }
    
}

//Simple QuickSort
template<typename T>
void quickSortRecursive(T arr[], int start, int end) {
    if(start >= end) {
        return; 
    }
    T mid = arr[end];
    int left = start;
    int right = end - 1;
    
    while(left < right) {
        while(arr[left] < mid && left < right) {
            left++;
        }
        while(arr[right] >= mid && left < right) {
            right--;
        }
        swap(arr[left], arr[right]);
    }
    if(arr[left] >= arr[end]) {
        swap(arr[left], arr[end]);
    }
    else {
        left++;
    }
    quickSortRecursive(arr, start, left - 1);
    quickSortRecursive(arr, left + 1, end);
}
template<typename T>
void quickSort(T arr[], unsigned int length) {
    quickSortRecursive(arr, 0, length - 1);
}
////////////////End of QuickSort Algorithm

//CombSort
template<typename T>
void combSort(T arr[], int length) {
    double shrinkFaktor = 0.8;
    int gap = length;
    bool swapped = true;
    int i;
    
    while(gap > 1 || swapped) {
        if(gap > 1) {
            gap = (int)((double)gap * shrinkFaktor);
        }
        swapped = false;
        for(i = 0; gap + i < length; i++) {
            if(arr[i] > arr[i + gap]) {
                swap(arr[i], arr[i + gap]);
                swapped = true;
            }
        }
    }
}
///End Comb Sort

//Heap Sort
template<typename T>
void maxHeapify(T arr[], int start, int end) {
    int dad = start;
    int son = dad * 2 + 1;
    while(son <= end) {
        if(son + 1 <= end && arr[son] < arr[son + 1]) {
            son++;
        }
        if(arr[dad] > arr[son]) {
            return;
        }
        else {
            swap(arr[dad], arr[son]);
            dad = son;
            son = dad * 2 + 1;
        }
    }
}
template<typename T> 
void heapSort(T arr[], int length) {
    for(int i = length / 2 - 1; i >= 0; i--) {
        maxHeapify(arr, i, length - 1);
    }
    for(int i = length - 1; i > 0; i--) {
        swap(arr[0], arr[i]);
        maxHeapify(arr, 0, i - 1);
    }
}
//End heap sort


void testProgram() {
    int arr[] = {
       5, 10, 6, 2, 3, 8, 1, 15, 17, 19, 4, 7, 18, 0, 9, 11, 14, 16, 12, 13  
    };
    printSequence(arr, 20, "Before: ");
    heapSort(arr, 20);
    printSequence(arr, 20, "After: ");

}

} //End of namespace SORTS

#endif /* CPPSORTS_H */

