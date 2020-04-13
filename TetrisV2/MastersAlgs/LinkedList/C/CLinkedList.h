/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   CLinkedList.h
 * Author: default
 *
 * Created on July 3, 2019, 2:17 PM
 */

#ifndef CLINKEDLIST_H
#define CLINKEDLIST_H

#include <stdlib.h>
#include <cstdio>
#include <iostream>
#include <climits>


struct CNode {
    int data;
    struct CNode* next;
}*first = nullptr, *last = nullptr;

void displayCNode(struct CNode* list) {
    while(list != nullptr) {
        printf("%d ", list->data);
        list = list->next;
    }
}

void displayCNodeRecursive(struct CNode* list) {
    if(list) {
        printf("%d ", list->data);  //forward
        displayCNodeRecursive(list->next);
//        printf("%d ", list->data);  //reverse
    }
}

struct CNode* createList(int arr[], int size) {
    struct CNode* list;
    list = (struct CNode*)malloc(sizeof(struct CNode));
    
    struct CNode *temp, *last;
    
    list->data = arr[0];
    list->next = nullptr;
    last = list;
    
    for(int i = 1; i < size; i++) {
        temp = (struct CNode*)malloc(sizeof(struct CNode*));
        temp->data = arr[i];
        temp->next = nullptr;
        last->next = temp;
        last = temp;
    }
    
    return list;
}

void createGlobalList(int arr[], int size) {
    
    struct CNode *temp, *last;
    first = (struct CNode*)malloc(sizeof(struct CNode));
    first->data = arr[0];
    first->next = nullptr;
    last = first;
    
    for(int i = 1; i < size; i++) {
        temp = (struct CNode*)malloc(sizeof(struct CNode*));
        temp->data = arr[i];
        temp->next = nullptr;
        last->next = temp;
        last = temp;
    }
    
}

void deleteLinkedList(struct CNode* list) {
    while(list) {
        free(list);
        list = list->next;
        std::cout << "Deleted!\n";
    }
}

int lengthIterative(struct CNode* list) {
    int size = 0;
    while(list) {
        size++;
        list = list->next;
    }
    return size;
}

int lengthRecursive(struct CNode* list) {
    if(list) {
        return lengthRecursive(list->next) + 1;
    }
    return 0;
}

int sumOfNodesIterative(struct CNode* list) {
    int sum = 0;
    while(list) {
        sum += list->data;
        list = list->next;
    }
    return sum;
}

int sumOfNodesRecursive(struct CNode* list) {
    if(list) {
        return sumOfNodesRecursive(list->next) + list->data;
    }
    return 0;
}

int maxIterative(struct CNode* list) {
    int max = list->data;
    while(list) {
        if(list->data > max) {
            max = list->data;
        }
        list = list->next;
    }
    return max;
}
int minIterative(struct CNode* list) {
    int min = list->data;
    while(list) {
        if(list->data < min) {
            min = list->data;
        }
        list = list->next;
    }
    return min;
}

int maxRecursive(struct CNode* list) {
    if(list) {
        int x = maxRecursive(list->next);
        return x > list->data ? x : list->data;
//        if(x > list->data) {
//            return x;
//        }
//        else {
//            return list->data;
//        }
    }
    return -37678;
}
int minRecursive(struct CNode* list) {
    if(list) {
        int x = minRecursive(list->next);
        return x < list->data ? x : list->data;
//        if(x < list->data) {
//            return x;
//        }
//        else {
//            return list->data;
//        }
    }
    return 37678;   
}

struct CNode* linearSearchIterative(struct CNode* list, int key) {
    while(list) {
        if(list->data == key) {
            return list;
        }
        list = list->next;
    }
    return nullptr;
}

struct CNode* linearSearchRecursive(struct CNode* list, int key) {
    if(list) {
        if(list->data == key) {
            return list;
        }
        return linearSearchRecursive(list->next, key);
    }
    return nullptr;
}

//Improved Linked List linear searchs move founded element at the front of the list
struct CNode* improvedLinearSearchIterative(struct CNode* list, int key) {
    struct CNode* previous = nullptr;
    struct CNode* start = list;
    
    while(start) {
        if(start->data == key) {
            previous->next = start->next;
            start->next = list;
            list = start;
            return list;
        }
        previous = start;
        start = start->next;
    }
    return nullptr;
}

void insertInCList(struct CNode* list, int element, int pos) {
    if(pos < 0) {
        return;
    }
    struct CNode* temp;
    if(pos == 0) {
        //Dont Work;
        temp = (struct CNode*)malloc(sizeof(struct CNode));
        temp->data = element;
        temp->next = first;
        first = temp;
        return;
    }
    else if(pos > 0) {
        if(pos > lengthRecursive(list) + 1) {
            pos = lengthRecursive(list);
        }
        
        int index = 0;
        temp = (struct CNode*)malloc(sizeof(struct CNode));
        
        while(list) {
            if(index == pos - 1) {
                temp->data = element;
                temp->next = list->next;
                list->next = temp;
                break;
            }
            index++;
            list = list->next;
        }
    }
}

struct CNode* insertFront(struct CNode* list, int element) {
    struct CNode* temp;
    temp = (struct CNode*)malloc(sizeof(struct CNode));
    temp->data = element;
    temp->next = list;
    list = temp;
    return list;
}

void insertAtPos(struct CNode* list, int element, int pos) {
    struct CNode* temp;
    temp = (struct CNode*)malloc(sizeof(CNode));
    temp->data = element;
    int index = 0;
    
    while(list) {
        if(index == pos - 1) {
            temp->next = list->next;
            list->next = temp;
            break;
        }
        index++;
        list = list->next;
    }
}

void insertAtEnd(int element) {
    struct CNode* temp = (struct CNode*)malloc(sizeof(struct CNode));
    temp->data = element;
    temp->next = nullptr;
    
    if(first == nullptr) {
        first = last = temp;
    }
    else {
        last->next = temp;
        last = temp;
    }
}

void sortedInsert(struct CNode* list, int element) {
    struct CNode* previous = nullptr;

    struct CNode* temp = (struct CNode*)malloc(sizeof(struct CNode));
    temp->data = element;
    temp->next = nullptr;
    
    if(first == nullptr) {
        first = temp;
    }
    else {
        while(list && list->data < element) {
            previous = list;
            list = list->next;
        }
        
        if(list == first) {
            temp->next = first;
            first = temp;
        }
        else {
            temp->next = previous->next;
            previous->next = temp;
        }
    }
 
//    if(!previous) {
//        previous = curr;
//        temp->next = list;
//        list = temp;
//    }
//    else {
//        temp->next = previous->next;
//        previous->next = temp;
//    }
//    first = curr;
}

int deleteElement(int pos) {
    
    struct CNode* temp = nullptr;
    int element = -1;
    if(pos == 0) {
        temp = first;
        first = first->next;
        element = temp->data;
//        delete temp;
        free(temp);
        temp = nullptr;
    }
    else {

        struct CNode* curr = first;
        
        for(int i = 0; i <= pos - 1 && curr; i++) {
            temp = curr;
            curr = curr->next;
        }
        if(curr) {
            temp->next = curr->next;
            element = curr->data;
            free(curr);
        }
    }
    
    return element;
}

//Recursive
bool checkIfListIsSorted(struct CNode* list, int value) {
    static bool isSorted = true;
    static int count = 0;
    count++;
    std::cout << "Count: " << count << std::endl;
    if(list && isSorted) {
        if(list->data < value) {
            isSorted = false;
        }
        else {
            checkIfListIsSorted(list->next, list->data);
        }
    }
    return isSorted;
}

//Iterative
bool checkIfListIsSortedIterative(struct CNode* list) {
    int min = INT_MIN;
    while(list) {
        if(list->data < min) {
            return false;
        }
        min = list->data;
        list = list->next;
    }
    return true;
}

void removeDuplicatesIter(struct CNode* list) {
    struct CNode* curr = list;
    struct CNode* next = list->next;
    
    while(next) {
        if(curr->data != next->data) {
            curr = next;
            next = next->next;
        }
        else {
            curr->next = next->next;
            free(next);
            next = curr->next;
        }
    }
}

void removeDuplicatesRec(struct CNode* curr, struct CNode* next) {
    if(next) {
        if(curr->data != next->data) {
//            curr = next;
//            next = next->next;
            removeDuplicatesRec(next, next->next);
        }
        else {
            curr->next = next->next;
            free(next);
            next = curr->next;
            removeDuplicatesRec(curr, next);
        }
    }
}

//Reverse Elements not links
void reverseLinkedList(struct CNode* list) {
    int listSize = lengthRecursive(list);
    int arr[listSize];
    
    int index = 0;
    
    while(list) {
        arr[index] = list->data;
        list = list->next;
        index++;
    }

    for(auto&& elem : arr) {
        std::cout << elem << " ";
    }
    std::cout << std::endl;
    struct CNode* rewrite = first;
    
    while(rewrite) {
        rewrite->data = arr[--index];
        rewrite = rewrite->next;
    }
    displayCNode(first);
}

//Reverse Links 
void reverseLinkedListPtrs() {
    struct CNode* p = first;
    struct CNode* q = nullptr;
    struct CNode* r = nullptr;
    
    //Sliding pointers.
    while(p != nullptr) {
        r = q;
        q = p;
        p = p->next;
        q->next = r;
    }
    first = q;
}

//Reverse Links recursive
void reverseLinkedListPtrsRecursive(struct CNode* tail, struct CNode* head) {
    if(head != nullptr) {
        reverseLinkedListPtrsRecursive(head, head->next);
        head->next = tail;
    }
    else {
        first = tail;
    }
}

void concatLinkedList(struct CNode* listOne, struct CNode* listTwo) {
    while(listOne->next != nullptr) {
        listOne = listOne->next;
    }
    listOne->next = listTwo;
    listTwo = nullptr;
}

struct CNode* mergeLinkedLists(struct CNode* listOne, struct CNode* listTwo) {
    
    struct CNode* third = nullptr;
    struct CNode* last = nullptr;
    
    if(listOne->data < listTwo->data) {
        third = last = listOne;
        listOne = listOne->next;
        last->next = nullptr;
    }
    else {
        third = last = listTwo;
        listTwo = listTwo->next;
        last->next = nullptr;
    }
    
    while(listOne && listTwo) {
        if(listOne->data < listTwo->data) {
            last->next = listOne;
            last = listOne;
            listOne = listOne->next;
            last->next = nullptr;
        }
        else {
            last->next = listTwo;
            last = listTwo;
            listTwo = listTwo->next;
            last->next = nullptr;
        }
    }
    
    if(listOne != nullptr) {
        last->next = listOne;
    }
    else {
        last->next = listTwo;
    }
    return third;
}

//Check For Loop in List
bool isLoopInList(struct CNode* list) {
    struct CNode* tail; 
    struct CNode* head;
    tail = head = list;
    
    do {
        tail = tail->next;
        head = head->next;
        head = head != nullptr ? head->next : nullptr; 
    }
    while((tail && head) && (tail != head));    //Both Pointers are not nullptr.
    
    return (tail == head ? true : false);
}

void checkForLoopInList() {
    int arr[] = {3, 5, 7, 10, 15, 55};
    struct CNode* listOne = createList(arr, 6);
    
    struct CNode* ptrOne = listOne->next->next;
    struct CNode* ptrTwo = listOne->next->next->next->next->next;
    ptrTwo->next = ptrOne;
    
    if(isLoopInList(listOne)) {
        std::cout << "There is Loop in the list!\n";
    }
    else {
        std::cout << "There is NO Loop in the list!\n";
    }
}

void testMerginLists() {
    int arr[] = {3, 5, 7, 10, 15, 55};
    int arr2[] = {2, 45, 48, 66};
    struct CNode* listOne = createList(arr, 6);
    struct CNode* listTwo = createList(arr2, 4);
    
    std::cout << "First List: ";
    displayCNodeRecursive(listOne);
    std::cout << std::endl << "Second List: ";
    displayCNodeRecursive(listTwo);

    
    struct CNode* result = mergeLinkedLists(listOne, listTwo);
    std::cout << std::endl << "Result List: ";
    displayCNodeRecursive(result);
}

void testConcatList() {
    
    int arr[] = {3, 5, 7, 10, 15, 55};
    int arr2[] = {122, 45, 1, -7};
    struct CNode* listOne = createList(arr, 6);
    struct CNode* listTwo = createList(arr2, 4);
    
    std::cout << "First List: ";
    displayCNodeRecursive(listOne);
    std::cout << std::endl << "Second List: ";
    displayCNodeRecursive(listTwo);
    concatLinkedList(listOne, listTwo);
    std::cout << "\nConcat Lists: ";
    displayCNodeRecursive(listOne);
    std::cout << std::endl << "Second List: ";
    displayCNodeRecursive(listTwo);
}
void testReverseList() {
    int arr[] = {3, 5, 5, 5, 4, 10, 10, 20, 25};
    createGlobalList(arr, 9);
    reverseLinkedList(first);
    std::cout << "\nPrint Reverse Pointrs in List\n";
    reverseLinkedListPtrs();
    displayCNode(first);
    std::cout << "\nPrint Reverse Pointrs in List Recursive\n";
    reverseLinkedListPtrsRecursive(nullptr, first);
    displayCNodeRecursive(first);
}

void testSortedInsert() {
    int arr[] = {3, 5, 5, 5, 4, 10, 10, 20, 25};
    createGlobalList(arr, 9);
    int lengthList = lengthRecursive(first);
    std::cout << "Size: " << lengthList << std::endl;
    std::cout << "Elements: ";
    displayCNodeRecursive(first);
    std::cout << std::endl;
    
    std::cout << "Recursive Check If List is Sorted: " << checkIfListIsSorted(first, INT_MIN);
    std::cout << std::endl;
    std::cout << "Iterative Check If List is Sorted: " << checkIfListIsSortedIterative(first);
    std::cout << std::endl;
    
    std::cout << "Remove Recursive:\n";
    removeDuplicatesRec(first, first->next);
    displayCNodeRecursive(first);
    std::cout << std::endl;
    std::cout << "After Insert: ";
    sortedInsert(first, 8);
    displayCNodeRecursive(first);
    std::cout << std::endl;
    std::cout << std::endl;
    std::cout << "After Insert: ";
    sortedInsert(first, 22);
    displayCNodeRecursive(first);
    std::cout << std::endl;
    std::cout << std::endl;
    std::cout << "After Insert: ";
    sortedInsert(first, 1);
    displayCNodeRecursive(first);
    std::cout << std::endl;
    
    std::cout << "Delete Element at index 0: " << deleteElement(0) << std::endl;
    displayCNodeRecursive(first);
    std::cout << std::endl;
    std::cout << "Delete Element at index 7: " << deleteElement(7) << std::endl;
    displayCNodeRecursive(first);
    std::cout << std::endl;
    deleteLinkedList(first);
}

void testCNode() {

    
    //CPLUS PLUS
    // list = new CNode;
    int arr[] = {3, 5, 7, 10, 15, 55, 122, 45, 1, -7};
    struct CNode* list = createList(arr, 10);
    int lengthList = lengthRecursive(list);
    std::cout << "List Size: " << lengthList << std::endl;
    std::cout << "Sum of Nodes Iter: " << sumOfNodesIterative(list) << std::endl;
    std::cout << "Sum of Nodes Recursive: " << sumOfNodesRecursive(list) << std::endl;
    std::cout << "Max Element Iterative: " << maxIterative(list) << std::endl;
    std::cout << "Min Element Iterative: " << minIterative(list) << std::endl;
    std::cout << "Max Element Recursive: " << maxRecursive(list) << std::endl;
    std::cout << "Min Element Recursive: " << minRecursive(list) << std::endl;
    if(struct CNode* res = linearSearchIterative(list, 46)) {
        std::cout << "Element was found! " << res->data << "\n";
    }
    else {
        std::cout << "Element was NOT found!\n";
    }
    if(struct CNode* res = linearSearchRecursive(list, 122)) {
        std::cout << "Element was found! " << res->data << "\n";
    }
    else {
        std::cout << "Element was NOT found!\n";
    }
    struct CNode* res;
    if(res = improvedLinearSearchIterative(list, 45)) {
        std::cout << "Element was found! " << res->data << "\n";
    }
    else {
        std::cout << "Element was NOT found!\n";
    }
    
    
    displayCNodeRecursive(list);
    std::cout << std::endl;
//    deleteLinkedList(list);
    list = res;
    displayCNodeRecursive(list);
    struct CNode* newList = insertFront(list, -5);
    list = newList;
    std::cout << std::endl;
    displayCNodeRecursive(list);
    std::cout << std::endl;
    lengthList = lengthRecursive(list);
    std::cout << "New List Size: " << lengthList << std::endl;
    
    insertAtPos(list, 88, 11);
    std::cout << std::endl;
    displayCNodeRecursive(list);
    std::cout << std::endl;
    lengthList = lengthRecursive(list);
    std::cout << "New List Size: " << lengthList << std::endl;
    
    insertInCList(list, 335, 5);
    std::cout << std::endl;
    displayCNodeRecursive(list);
    std::cout << std::endl;
    lengthList = lengthRecursive(list);
    std::cout << "New List Size: " << lengthList << std::endl;
    
    deleteLinkedList(list);
    
    
    std::cout << "Insert From begining\n";
    
    insertInCList(first, 10, 0);
    insertInCList(first, 20, 0);
    insertInCList(first, 30, 0);
    insertInCList(first, 40, 0);
    insertInCList(first, 50, 1);
    insertInCList(first, 60, 2);
    insertInCList(first, 70, 3);
    insertInCList(first, 71, 15);
    insertInCList(first, 72, 17);
    displayCNode(first);
    std::cout << std::endl;
    deleteLinkedList(first);
    
    std::cout << "Insert Last\n";
    first = nullptr;
    insertAtEnd(1);
    insertAtEnd(2);
    insertAtEnd(3);
    insertAtEnd(4);
    insertAtEnd(5);
    displayCNodeRecursive(first);
    std::cout << std::endl;
    deleteLinkedList(first);
}

struct CNode* middleOfLL(struct CNode* list) {
    int length = lengthRecursive(list);
    for(int i = 0; i < length / 2; i++) {
        list = list->next;
    }
    return list;
}



void testFindAMiddleOfLL() {
    int arr[] = {3, 5, 7, 10, 15, 22, 122, 45, 1, -7, 15, 100};
    struct CNode* list = createList(arr, 12);
    struct CNode* result = middleOfLL(list);
    std::cout << "Middle Element is: " << result->data << std::endl;
}

#endif /* CLINKEDLIST_H */

