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

#include <cassert>
#include <cstdlib>
#include <cstdio>


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
        for(x = m[ind = i], j = i + 1; j < size; j++) {
            if(m[j].key < x.key) {
                x = m[ind = j];
                m[ind] = m[i];
                m[i] = x;
            }
        }
    }
}

/**
 * Heap Sort (Pyramid Sort)
 */
void sift(struct CElem m[], unsigned int left, unsigned int right) {
    unsigned int i = 1;
    unsigned int j = i + 1;
    
    struct CElem x = m[i];
    while(j <= right) {
        if(j < right && m[j].key < m[j + 1].key ) {
            j++;
        }
        if(x.key >= m[j].key) {
            break;
        }
        m[i] = m[j];
        i = j;
        j <<= 1;    //Pobitovo otmestvane na lqvo ekvivalentno na j *= 2;
    }
    m[i] = x;
}
void heapSort(struct CElem m[], unsigned int size) {
    unsigned int k;
    //Postroqvane na piramida
    for(k = size / 2 + 1; k > 1; --k) {
        sift(m, k - 1, size); 
    }
    //Postroqvane na sortirana posledovatelnost
    for(k = size; k > 1; k--) {
        swap(m + 1, m + k);
        sift(m, 1, k - 1);
    }
}

/**
 * Set Sort (Sortirane chrez mnojestva)
 */
#define MAX_VALUE 10
void setSort(unsigned int m[], unsigned int size) {
    char set[MAX_VALUE];
    unsigned int i, j;
    //1. Initizializirane na mnojestvoto
    for(i = 0; i < MAX_VALUE; i++) {
        set[i] = 0;
    }
    
    //2. Formirane na mnojestvoto
    for(j = 0; j < size; j++) {
        assert(m[j] >= 0 && m[j] < MAX_VALUE);
        assert(set[m[j]] == 0);
        set[m[j] == 1];
    }
    //3. Generirane na sortirana posledovatelnost
    for(i = j = 0; i < MAX_VALUE; i++) {
        if(set[i]) {
            m[j++] = 1;
        }
    }
    assert(j == size);
}

struct CSetE1 {
    char found;
    unsigned int index;
}mTwo[MAX];

#define NO_INDEX (unsigned int)(-1)
/**
 * Sortira masiv s izpolzvane na mnojestvo
 */
void setSortTwo(struct CElem m[], unsigned int size) {
    unsigned int indSet[MAX_VALUE]; //indeksno mnojestvo
    unsigned int i, j;
    
    //Inicializirane na mnojestvoto
    for(i = 0; i < MAX_VALUE; ++i) {
        indSet[i] = NO_INDEX;
    }
    //Formirane na mnojestvoto
    for(j = 0; j < size; j++) {
        assert(m[j].key >= 0 && m[j].key < MAX_VALUE);
        assert(indSet[m[j].key] == NO_INDEX);
        indSet[m[j].key] = j;
    }
    //Generirane na sortirana posledovatelnost
    for(i = j = 0; i < MAX_VALUE; i++) {
        if(NO_INDEX != indSet[i]) {
//            do4Elem(m[indSet[i]]);
        }
    }
}

//
void countSort(unsigned int m[], unsigned int size) {
    unsigned char cnt[MAX_VALUE];
    unsigned int i, j;
    
    for(i = 0; i < MAX_VALUE; i++) {
        cnt[i] = 0;
    }
    for(j = 0; j < size; j++) {
        assert(m[j] >= 0 && m[j] < MAX_VALUE);
        cnt[m[j]]++;
    }
    for(i = j = 0; i < MAX_VALUE; i++) {
        while(cnt[i]--) {
            m[j++] = i;
        }
    }
    assert(j == size);
}


//Побитово сортиране/
struct CList {
    struct CElem data;
    struct CList* next;
};
struct CList* init(unsigned int size) {
    struct CList* head, *p;
    unsigned int i;
    srand(time(NULL));
    for(head = nullptr, i = 0; i < size; i++) {
        p = (struct CList*) malloc(sizeof(struct CList));
        p->data.key = rand() % 1000;
        assert(p->data.key);
        p->next = head;
        head = p;
    }
    return head;
}
struct CList* bitSort(struct CList* head) {
    struct CList* zeroEnd;
    struct CList* oneEnd;
    struct CList* zero;
    struct CList* one;
    
    unsigned int maxBit;
    unsigned int bitPow2;
    
    //0. Opredelqne na maksimalnata bitova maska
    maxBit = 1 << (8 * sizeof(head->data.key) - 1);
    
    //1. Fiktiven element v nachaloto na spisycite
    zero = (struct CList*) malloc(sizeof(struct CList));
    one = (struct CList*) malloc(sizeof(struct CList));
    
    //2. Sortirane
    for(bitPow2 = 1; bitPow2 < maxBit; bitPow2 <<= 1) {
        //2.1 Razpredelqne po spisyci
        for(zeroEnd = zero, oneEnd = one; head != NULL; head = head->next) {
            if(!(head->data.key & bitPow2)) {
                zeroEnd->next = head;
                zeroEnd = zeroEnd->next;
            }
            else {
                oneEnd->next = head;
                oneEnd = oneEnd->next;
            }
        }
        //2.2 Obedinenie na spisycite
        oneEnd->next = NULL;
        zeroEnd->next = one->next;
        head = zero->next;
    }
    //3. Osvobojdavane na pametta
    free(zero);
    free(one);
    
    return head;
}
void print(struct CList* head) {
    for(; head != NULL; head = head->next) {
        printf("%8d", head->data.key);
    }
    printf("\n");
}
void check(struct CList* head) {
    if(head == NULL) {
        return;
    }
    for(; head->next != NULL; head = head->next) {
        assert(head->data.key <= head->next->data.key);
    }
}
void clear(struct CList* head) {
    while(head != NULL) {
        free(head);
        head = head->next;
    }
}

void testBitSort() {
    struct CList* head;
    head = init(MAX_VALUE);
    printf("Before: ");
    print(head);
    std::cout << std::endl;
    printf("After: ");
    head = bitSort(head);
    print(head);
    check(head);
    clear(head);
}

// Recursive bit sort po burz za silno razburkan masiv sravnim i po dobur po nqkoga ot quicksort
void bitSort2(int left, int right, unsigned int bitMask) {
    int i, j;
    if(right > left && bitMask > 0) {
        i = left;
        j = right;
        while(i != j) {
            while(!(m[i].key & bitMask) && i < j) {
                i++;
            }
            while((m[j].key & bitMask) && j > i) {
                j--;
            }
            swap(&m[i], &m[j]);
        }
        if(!(m[right].key & bitMask)) {
            j++;
        }
        bitSort2(left, j - 1, bitMask >> 1);
        bitSort2(j, right, bitMask >> 1);
    }
}
void printCElem(const std::string& msg) {
    int count = 0;
    std::cout << msg;
    while(count < MAX_ELEM) {
        std::cout << m[count].key << " ";
        count++;
    }
    std::cout << std::endl;
}
void testBitSort2() {
    srand(time(NULL));
    for(int i = 0; i < MAX_ELEM; i++) {
        m[i].key = rand() % 1000;
    }
    printCElem("Before: ");
    std::cout << std::endl;
    bitSort2(0, MAX_ELEM - 1, 1 << 8 * sizeof(m[0].key) - 1);
    printCElem("After: ");
}


/**
 * Radix Sort /Metod na broinite sistemi.
 */
#define BASE 16     //Osnova na broinata sistema
#define POW2 4      // *16 = 1 << 4
#define DIG_CNT 8   //Broi cifri

struct CList* radixSort(struct CList* head) {
    struct {
        struct CList* st;
        struct CList* en;
    }mod[BASE];
    
    unsigned int i, dig, mask, shrM;
    
    //1. Initializirane
    for(i = 0; i < BASE; i++) {
        mod[i].st = (struct CList*) malloc(sizeof(struct CList));
    }
    
    //2. Sortirane
    mask = BASE - 1;
    shrM = 0;
    
    for(dig = 1; dig <= DIG_CNT; dig++) {
        //2.1 Initializirane
        for(i = 0; i < BASE; i++) {
            mod[i].en = mod[i].st;
        }
        //2.2 Razpredelqne na elementite po spisaci
        while(head != NULL) {
            //2.2.1 Namirane na i-tata cifra v BASE-ichniq zapis na chisloto
            i = (head->data.key & mask) >> shrM;
            //2.2.2 Vkluchvane na chisloto v suotvetniq spisuk
            mod[i].en->next = head;
            mod[i].en = mod[i].en->next;
            
            head = head->next;
        }
        
        //2.3 Obedinqvane na spisycite
        mod[BASE - 1].en->next = NULL;
        for(i = BASE - 1; i > 0; i--) {
            mod[i - 1].en->next = mod[i].st->next;
        }
        head = mod[0].st->next;
        
        //2.4 Izchislqvane na novite Maski
        shrM += POW2;
        mask <<= POW2;
    }
    //3 Osvobojdavane na pameta
    for(i = 0; i < BASE; i++) {
        free(mod[i].st);
    }
    return head;
}

void testRadixSort() {
    struct CList* head;
    head = init(MAX_ELEM);
    printf("Before sort: ");
    print(head);
    std::cout << std::endl;
    printf("After sort: ");
    head = radixSort(head);
    print(head);
    check(head);
    clear(head);
}

//Permutation Sort
void permSort(struct CElem m[], unsigned int n) {
    unsigned int i;
    for(i = 0; i < n; i++) {
        while(m[i].key != (int)i) {
            swap(&m[i], &m[m[i].key]);
        }
    }
}
#ifdef __cplusplus
}
#endif

#endif /* CSORTS_H */

