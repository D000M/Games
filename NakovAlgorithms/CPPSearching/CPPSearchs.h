/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   CPPSearchs.h
 * Author: default
 *
 * Created on January 8, 2019, 2:46 PM
 */

#ifndef CPPSEARCHS_H
#define CPPSEARCHS_H

#include <iostream>
#include <complex>


namespace SEARCH {
    
//Sequence Search     
template<typename T>
bool sequenceSearch(T* arr, const T element) {
//    std::cout << sizeof(arr) / sizeof(*arr) << std::endl;
    for(int i = 0; i < sizeof(arr) / sizeof(*arr); i++) {
        if(arr[i] == element) {
            return true;
        }
    }
    return false;
}
//End Sequence Search

//Search with step. Quadratic Search
//The Collection must be sorted.
template<typename T>
T* seqSearch(T* arr, int left, int right, T element) {
    while(left <= right) {
        if(arr[left++] == element) {
            return &arr[left - 1];
        }
    }
    return nullptr;
}
template<typename T>
T* jumpSearch(T* arr, T element, int step, int length) {
    unsigned int index;
    for(index = 0; index < length && arr[index] < element; index += step);
    
    return seqSearch(arr, index + 1 < step ? 0 : index + 1 - step, length < index ? length : index, element); 
}
int steps(int length) {
    return 2 * sqrt(length) + 1;
}
//End of Jump Search

//Binary Search
//1. Recursive
template<typename T>
T* binarySearchRecursive(T* arr, T element, int left, int right) {
    if(left > right) {
        return nullptr;
    }
    
    int middle = (left + right) >> 1;    //use ((left + right) >> 1) instead of ((left + right) / 2) because slow division operation
    
    if(element < arr[middle]) {
        return binarySearchRecursive(arr, element, left, middle - 1);
    }
    else if(element > arr[middle]) {
        return binarySearchRecursive(arr, element, middle + 1, right);
    }
    else {
        return &arr[middle];
    }
}
//2. Iterative binarySearch
template<typename T> 
T* binarySearchIterative(T* arr, T element, int arrLength) {
    int left = 0;
    int right = arrLength - 1;
    int middle;
    
    while(left <= right) {
        
        middle = (left + right) >> 1;       //use ((left + right) >> 1) instead of ((left + right) / 2) because slow division operation
        
        if(element < arr[middle]) {
            right = middle - 1;
            
        }
        else if(element > arr[middle]) {
            left = middle + 1;
        }
        else {
            return &arr[middle];
        }
        
    }

    return nullptr;
}

//3. Iterative Binary Search with offset power of 2
unsigned int getMaxPow2(unsigned int k) {
    unsigned int pow2;
    for(pow2 = 1; pow2 <= k; pow2 <<= 1);
    return pow2 >> 1;
}
template<typename T>
T* binarySearchIterativeV2(T* arr, T element, int arrLength) {
    unsigned int i = getMaxPow2(arrLength);
    unsigned int left = (arr[i] >= element) ? 0 : arrLength - i + 1;
    unsigned int index;
    while(i > 0) {
        i = i >> 1;
        index = left + i;
        if(arr[index] == element) {
            return &arr[index];
        }
        else if(arr[index] < element) {
            left = index;
        }
    }
    return nullptr;
}
//End of Binary Search

//Interpolation Search very effective log2(log2n). Example log2(log2(1000000000)) < 5;
//The Elements must have int keys otherwise this search cant be used.
template<typename T>
int interpolationSearch(T* arr, T element, int arrLength) {
    unsigned int middle;
    unsigned int low = 0;
    unsigned int high = arrLength - 1;

    while( (arr[high] != arr[low]) && (element >= arr[low] && element < arr[high])) {
        middle = low + ((element - arr[low])) * (high - low) / (arr[high] - arr[low]);
        
        if(arr[middle] < element) {
            low = middle + 1;
        }
        else if(element < arr[middle]) {
            high = middle - 1;
        }
        else {
            return middle;
        }
    }
    if(element == arr[low]) {
        return low;
    }
    else {
        return -1;
    }
}

void testInterpolationSearch() {
    int arr[] = {
       5, 10, 6, 2, 3, 8, 1, 15, 17, 19, 4, 7, 18, 0, 9, 11, 14, 16, 12, 13,
       105, 110, 106, 102, 103, 108, 101, 115, 117, 119, 104, 107, 118, 100, 109, 111, 114, 116, 112, 113
    };
    SORTS::quickSort(arr, 40);
    SORTS::printSequence(arr, 40, "Sorted: ");
    int a = interpolationSearch(arr, 105, 40);
    if(a == -1) {
        std::cout << "Element NOT FOUND!\n";
    }
    else {
        std::cout << "Element FOUND!\n";
        std::cout << "At Position: " << a << std::endl;
    }
}

void testBinaryRecSearch() {
    
    int arr[] = {
       5, 10, 6, 2, 3, 8, 1, 15, 17, 19, 4, 7, 18, 0, 9, 11, 14, 16, 12, 13,
       105, 110, 106, 102, 103, 108, 101, 115, 117, 119, 104, 107, 118, 100, 109, 111, 114, 116, 112, 113
    };
    SORTS::quickSort(arr, 40);
    SORTS::printSequence(arr, 40, "Sorted: ");
    //Recursive
    int* a = binarySearchRecursive(arr, 19, 0, 40);
    if(a == nullptr) {
        std::cout << "Element NOT FOUND!\n";
    }
    else {
        std::cout << "Element FOUND!\n";
    }
    //Iterative
    a = binarySearchIterative(arr, 50, 40);
    if(a == nullptr) {
        std::cout << "Element NOT FOUND!\n";
    }
    else {
        std::cout << "Element FOUND!\n";
    }
    //Iterative 2
    a = binarySearchIterativeV2(arr, 5, 40);
    if(a == nullptr) {
        std::cout << "Element NOT FOUND!\n";
    }
    else {
        std::cout << "Element FOUND!\n";
    }
}

void testJumpSearch() {
    int arr[] = {
       5, 10, 6, 2, 3, 8, 1, 15, 17, 19, 4, 7, 18, 0, 9, 11, 14, 16, 12, 13,
       105, 100, 106, 102, 103, 108, 101, 115, 117, 119, 104, 107, 118, 100, 109, 111, 114, 116, 112, 113
    };
    SORTS::quickSort(arr, 40);
    SORTS::printSequence(arr, 40, "Sorted: ");
    int* a = jumpSearch(arr, 101, steps(40), 40);
    if(a == nullptr) {
        std::cout << "Element NOT FOUND!\n";
    }
    else {
        std::cout << "Element FOUND!\n";
    }
}

void testProgram() {
    int arr[] = {
       5, 10, 6, 2, 3, 8, 1, 15, 17, 19, 4, 7, 18, 0, 9, 11, 14, 16, 12, 13  
    };
    
    int a = 12;
    
    if(sequenceSearch(arr, a)) {
        std::cout << "Element " << a << " FOUND!\n";
    }
    else {
        std::cout << "Element " << a << " NOT FOUND!\n";
    }

}

} //end of namespace SEARCH
#endif /* CPPSEARCHS_H */

