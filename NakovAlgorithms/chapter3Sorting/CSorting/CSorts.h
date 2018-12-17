/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   CSorts.h
 * Author: default
 *
 * Created on December 15, 2018, 12:12 PM
 */

#ifndef CSORTS_H
#define CSORTS_H

#ifdef __cplusplus
extern "C" {
#endif


#define MAX_ELEM 100

struct CElem {
    int key;
    /**
     * some data corresponding to the key
     */
}m[MAX_ELEM];    

/**
 * Swap 2 elements
 * @param firstElem
 * @param secondElem
 */
void swap(struct CElem* firstElem, struct CElem* secondElem) {
    struct CElem tmp = *firstElem;
    *firstElem = *secondElem;
    *secondElem = tmp;
}



/**
 * C Insertion Sort
 * Usable for small amount of elements elemnentSize < ~20
 * Usable in practice
 * O(n * n) difficulty   much less than pyramidal or quick sort which are O(n * log2 * n)
 */

void straightInsertionSort(struct CElem m[], unsigned int size) {
    struct CElem x;
    unsigned int i;
    int j;
    for(i = 0; i < size; i++) {
        x = m[i];
        j = i - 1;
        while(j >= 0 && x.key < m[j].key) {
            m[j + 1] = m[j--];
        }
        m[j + 1] = x;
    }
}

void straightInsertionSortV2(struct CElem m[], unsigned int size) {
    unsigned int i, j;
    struct CElem x;
    for(i = 1; i <= size; i++) {
        x = m[i];
        m[0].key = x.key;
        for(j = i - 1; x.key < m[j].key; j--) {
            m[j + 1] = m[j];
        }
        m[j + 1] = x;
    }
}

void binaryInsertion(struct CElem m[], unsigned int size ) {
    struct CElem x;
    unsigned int i, med, right;
    int j, left;
    
    for(i = 1; i < size; i++) {
        x = m[i];
        left = 0;
        right = i - 1;
        
        //Dvoichno tursene
        while(left <= (int)right) {
            med = (left + right) / 2;
            if(x.key < m[med].key) {
                right = med - 1;
            }
            else {
                left = med + 1;
            }
        }
        
        //Mqstoto e namereno sledva vmukvane i izmestvane nadqsno
        for(j = i - 1; j >= left; j--) {
            m[j + 1] = m[j];
        }
        m[left] = x;
    }
}

/**
 * Shell Sort
 */
#define STEPS_COUNT 4
#define steps0 40
const unsigned steps[STEPS_COUNT] = {
    steps0, 13, 4, 1
};

void shellSort(struct CElem m[], unsigned int size) {
    int i, j, k, s;
    unsigned int stepInd;
    struct CElem x;
    
    for(stepInd = 0; stepInd < STEPS_COUNT; stepInd++) {
        s = -(k = steps[stepInd]);      //Ogranichitel.
        for(i = k + 1; i <= (int)size; i++) {
            x = m[i];
            j = i - k;
            if(s == 0) {
                s = -k;
            }
            m[++s] = x;
            while(x.key < m[j].key) {
                m[j + k] = m[j];
                j -= k;
            }
            m[j + k] = x;
        }
    }
}
void shellSortV2(struct CElem m[], unsigned left, unsigned right) {
    static unsigned int incs[16] = {
       1391376, 463792, 198768, 86961, 33936, 13776, 4592, 1968, 861, 336, 112, 48, 21, 7, 3, 1  
    };
    
    unsigned int i, j, k, h;
    struct CElem v;
    for(k = 0; k < 16; k++) {
        for(h = incs[k], i = left + h; i <= right; i++) {
            v = m[i];
            j = i;
            while(j > h && m[j - h].key > v.key) {
                m[j] = m[j - h];
                j -= h;
            }
            m[j] = v;
        }
    }
}

/**
 * Bubble Sort Most used sort and less effective
 * 
 */
void bubbleSortV1(struct CElem m[], unsigned int size) {
    unsigned int i, j;
    for(i = 1; i < size; i++) {
        for(j = size - 1; j >= i; j--) {
            if(m[j - 1].key > m[j].key) {
                swap(m + j - 1, m + j);
            }
        }
    }
}

//Improved bubble sort
void bubbleSortV2(struct CElem m[], unsigned int size) {
    unsigned i, j, k;
    for(i = size; i > 0; i = k) {
        for(k = j = 0; j < i; j++) {
            if(m[j].key > m[j + 1].key) {
                swap(m + j, m + j + 1);
                k = j;
            }
        }
    }
}

//Used all bubble sort algorithms we can make shakeSort
void shakerSort(struct CElem m[], unsigned int size) {
    unsigned int k = size;
    unsigned int right = size - 1;
    unsigned int left = 1;
    unsigned int j;
    
    do {
        for(j = right; j >= left; j--){
            if(m[j - 1].key > m[j].key) {
                swap(m + j - 1, m + j);
                k = j;
            }
        }
        
        left = k + 1;
        for(j = left; j <= right; j++) {
            if(m[j - 1].key < m[j].key) {
                swap(m + j - 1, m + j);
                k = j;
            }
        }
        right = k - 1;
    }
    while(left <= right);
}


/**
 * Quick Sort by Hoop Method.
 * Izpolzva se globalen masiv tui kato methoda razdelqsht masiva na polovina e rekursiven
 * po tozi nachin se pesti mqsto v stack-a.
 */

int partition(int left, int right) {
    int num, j, x;
    num = left - 1;
    x = m[right].key;
    
    for(j = left; j <= right; j++) {
        if(m[j].key <= x) {
            num++;
            swap(m + num, m + j);
        }
    }
    if(num == right) {
        num--;
    }
    return num;
}
int partitionV2(int left, int right) {
    unsigned i, j, x;
    i = left;
    j = right;
    x = m[left].key;
    
    do{
        while(x > m[i].key) {
            i++;
        }
        while(x < m[j].key) {
            j--;
        }
        if(i <= j) {
            swap(m + i, m + j);
            i++;
            j--;
        }
    }
    while(j >= i);
    return j;
}
void quickSort(int left, int right) {
    int num, j, x;
    num = left - 1;
    x = m[right].key;
    
    for(j = left; j <= right; j++) {
        if(m[j].key <= x) {
            num++;
            swap(m + num, m + j);
        }
    }
    if(num == right) {
        num--;
    }
    if(left < num) {
        quickSort(left, num);
    }
    if((num + 1) < right) {
        quickSort(num + 1, right);
    }
}
void quickSortPartV2(int left, int right) {
    unsigned i, j, x;
    i = left;
    j = right;
    x = m[left].key;
    
    do{
        while(x > m[i].key) {
            i++;
        }
        while(x < m[j].key) {
            j--;
        }
        if(i <= j) {
            swap(m + i, m + j);
            i++;
            j--;
        }
    }
    while(j >= i);
    if(j > left) {
        quickSortPartV2(left, j);
    }
    if(i < right) {
        quickSortPartV2(i, right);
    }
}

void quickSortV3(void) {
    int i, j, l, r, s, x;
    
    struct {
        int left, right;
    }stack[MAX_ELEM];
    
    stack[s = 0].left = 0;
    stack[0].right = MAX_ELEM - 1;
    
    for(;;) {
        l = stack[s].left;
        r = stack[s].right;
        if(0 == s--) {
            break;
        }
        
        do{
            i = l;
            j = r;
            x = m[(l + r) / 2].key;
            do {
                while(m[i].key < x) {
                    i++;
                }
                while(m[j].key > x) {
                    j--;
                }
                if(i <= j) {
                    swap(m + i, m + j);
                    i++;
                    j--;
                }
            }
            while(i <= j);
            
            if(i < r) {
                stack[++s].left = i;
                stack[s].right = r;
            }
            r = j;
        }
        while(l < r);
    }
}


/**
 * Method of turtules and rabbits
 * very fast O(n * log2 * n) difficulty
 */
void combSortC(struct CElem m[], unsigned int size) {
    unsigned s, i, j, gap = size;
    do{
        s = 0;
        gap = (unsigned) (gap/1.3);
        if(gap < 1) {
            gap = 1;
        }
        for(i = 0; i < size - gap; i++) {
            j = i + gap;
            if(m[i].key > m[j].key) {
                swap(m + i, m + j);
                s++;
            }
        }
    }
    while(s != 0 || gap > 1);
}


/**
 * Straight Selection Sort
 * O(n * n) difficult
 */
void straightSelectionSort(struct CElem m[], unsigned int size) {
    unsigned i, j;
    for(i = 0; i < size - 1; i++) {
        for(j = i + 1; j <= size; j++) {
            if(m[i].key > m[j].key) {
                swap(m + i, m + j);
            }
        }
    }
}
void straightSelectionSortV2(struct CElem m[], unsigned int size) {
    unsigned i, j, ind;
    struct CElem x;
    for(i = 0; i < size - 1; i++) {
        for(x = m[ind = i], j = i + 1; j < n; j++) {
            if(m[j].key < x.key) {
                x = m[ind = j];
                m[ind] = m[i];
                m[i] = x;
            }
        }
    }
}
#ifdef __cplusplus
}
#endif

#endif /* CSORTS_H */

