/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   MergeSort.h
 * Author: default
 *
 * Created on February 21, 2019, 12:44 PM
 */

#ifndef MERGESORT_H
#define MERGESORT_H

#include <vector>


template<typename T>
void swap(T& first, T& second) {
    T temp = first;
    first = second;
    second = temp;
}

/**
 * Algorithms Not Discused in the course
 * Selection sort,
 * Insertion sort,
 * Bubble sort, 
 */

/**
 * Selection sort - difficulty: On^2
 *  Намира най-малкия елемент в списъка като сравнява първият елемент с всички останали
    Разменя го с елемента на първа позиция
    Повтаря горните две стъпки за всеки следващ елемент
 */
template<typename T>
void selectionSort(T arr[], T size) {
    for(int i = 0; i < size - 1; ++i) {
        for(int j = i + 1; j < size; ++j) {
            if(arr[i] > arr[j]) {
                swap(arr[i], arr[j]);
            }
        }
    }
}

/**
 * Insertion sort - difficulty: On^2
 * 
    Списъкът с елементи, които ще бъдат сортирани се разделя на две части: частта със сортираните елементи и частта с несортираните
    При всяка стъпка се взема първият елемент от несортирания списък и се вмъква на правилната позиция в сортираната част от списъка
    Сортирането продължава докато елементите от несортираната част на списъка се изчерпят
 */
template<typename T>
void insertionSort(T arr[], int size) {
    for(int i = 1; i < size; ++i) {
        T next = arr[i];
        int j = i;
        while(j > 0 && arr[j - 1] > next) {
            arr[j] = arr[j - 1];
            j--;
        }
        arr[j] = next;
    }
}


/**
 * Bubble Sort - difficulty: On^2
 */
template<typename T>
void bubbleSort(T arr[], int size) {
    for(int i = 0; i < size - 1; ++i) {
        for(int j = 0; j < size - i - 1; ++j) {
            if(arr[j] > arr[j + 1]) {
                swap(arr[j], arr[j + 1]);
            }
        }
    }
}
/**
 * MergeSort pseudo code
 * Divide and Conquer algorithm
 * Steps
 * - recursive call 1st half of the array
 * - recursive call 2nd half of the array
 * - Merge two sorted sublist in one.
 * base case if size <= 1
 */
void merge(int arr[], int left, int middle, int right) {
    int i, j, k;
    int leftSize = middle - left + 1;
    int rightSize = right - middle;
    
    int leftArr[leftSize];
    int rightArr[rightSize];
    
       /* Copy data to temp arrays L[] and R[] */
    for (i = 0; i < leftSize; i++) {
        leftArr[i] = arr[left + i]; 
    }
    for (j = 0; j < rightSize; j++) {
        rightArr[j] = arr[middle + 1 + j]; 
    }
    
    i = 0;
    j = 0;
    k = left;
    
    while(i < leftSize && j < rightSize) {
        if(leftArr[i] <= rightArr[j]) {
            arr[k] = leftArr[i];
            i++;
        }
        else {
//            if(rightArr[j] > 0) {
                arr[k] = rightArr[j];
                j++;
//            }
        }
        k++;
    }
    
     /* Copy the remaining elements of leftArr[], if there 
       are any */
    while (i < leftSize) 
    { 
        arr[k] = leftArr[i]; 
        i++; 
        k++; 
    } 
  
    /* Copy the remaining elements of rightArr[], if there 
       are any */
    while (j < rightSize) 
    { 
        arr[k] = rightArr[j]; 
        j++; 
        k++; 
    } 
}
void mergeSort(int arr[], int left, int right) {
    if(left < right) {
        int middle = left + (right - left) / 2;
        mergeSort(arr, left, middle);
        mergeSort(arr, middle + 1, right);
        
        merge(arr, left, middle, right);
    }
}

#endif /* MERGESORT_H */

