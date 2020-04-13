/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   CCircularLinkedList.h
 * Author: default
 *
 * Created on July 30, 2019, 3:48 PM
 */

#ifndef CCIRCULARLINKEDLIST_H
#define CCIRCULARLINKEDLIST_H

#include <stdlib.h>
#include <stdio.h>


#ifdef __cplusplus
extern "C" {
#endif

    struct CNode2 {
        int data;
        struct CNode2* next;
    }*head; //Global variable, same as CNode* head;

    CNode2* secHead;

    void createCList2(int arr[], int size) {
        int i;
        struct CNode2* temp, *last;
        head = (struct CNode2*)malloc(sizeof(struct CNode2));
        head->data = arr[0];
        head->next = head;  //next points to head.
        
        last = head;
        
        for(i = 1; i < size; i++) {
            temp = (struct CNode2*)malloc(sizeof(struct CNode2));
            temp->data = arr[i];
            temp->next = last->next;
            last->next = temp;
            last = temp;
        }
    }
    
    int lengthCLL(struct CNode2* list) {
        int len = 0;
        do {
            len++;
            list = list->next;
        }
        while(list != head);
        return len;
    }
    int lengthCLLRec(struct CNode2* list) {
        static int flag = 0;
        if(list != head || flag == 0) {
            flag = 1;
            return lengthCLLRec(list->next) + 1;            
        }
        flag = 0;
        return 0;
    }
    
    void displayCircularLL(struct CNode2* list) {
        do {
            printf("%d ", list->data);
            list = list->next;
        }while(list != head);
        printf("\n");
    }
    
    void displayCircularLLRecursive(struct CNode2* list) {
        static int flag = 0;
        if(list != head || flag == 0) {
            flag = 1;
            printf("%d ", list->data);
            displayCircularLLRecursive(list->next);
        }
        flag = 0;
    }
    
    void insertInCircularLL(struct CNode2* list, int pos, int elem) {
        int i;
        struct CNode2* temp;
        struct CNode2* currPtr = list;
        
        if(pos < 0 || pos > lengthCLL(list)) {
            return;
        }
        
        if(pos == 0) {
            temp = (struct CNode2*)malloc(sizeof(struct CNode2));
            temp->data = elem;
            if(head == NULL) {
                head = temp;
                head->next = head;
            }
            else {
                temp->next = head;
                while(currPtr->next != head) {
                    currPtr = currPtr->next;
                }
                currPtr->next = temp;
                head = temp;
            }
        }
        else {
            for(i = 0; i < pos - 1; i++) {
                currPtr = currPtr->next;
            }

            temp = (struct CNode2*)malloc(sizeof(struct CNode2));
            temp->data = elem;
            temp->next = currPtr->next;
            currPtr->next = temp;
        }
    }
    
    CNode2* deleteAtCLL(int pos) {
        int i;
        struct CNode2* prev = head;
        struct CNode2* removed;
        if(pos == 0) {
            while(prev->next != head) {
                prev = prev->next;
            }
            prev->next = head->next;
            removed = head;
            head = prev->next;
        }
        else {
            for(i = 0; i < pos - 1; i++) {
                prev = prev->next;
            }
            removed = prev->next;
            prev->next = removed->next;
        }
        return removed;
    }
    void freeResources() {
        struct CNode2* temp = head;
        do {
            std::cout << "Element: " << temp->data << " Removed!\n";
            free(temp);
            temp = temp->next;
        }while(temp != head);
    }
    void testCircularLL() {
        int arr[] = {1, 3, 5, 7, 9};
        createCList2(arr, 5);
        insertInCircularLL(head, 3, 6);
        displayCircularLLRecursive(head);
        std::cout << std::endl;
        insertInCircularLL(head, 0, 20);
        displayCircularLL(head);
        std::cout << std::endl;
        insertInCircularLL(head, -5, 22);
        displayCircularLL(head);
        std::cout << std::endl;
        insertInCircularLL(head, 15, 25);
        displayCircularLL(head);
        std::cout << "Length Iterative: " << lengthCLL(head) << std::endl;
        std::cout << "Length Recursive: " << lengthCLLRec(head) << std::endl;
        
        struct CNode2* elemPtr = deleteAtCLL(1);
        std::cout << "Element: " << elemPtr->data << " removed!\n";
        free(elemPtr);
        displayCircularLLRecursive(head);
        struct CNode2* elemPtr2 = deleteAtCLL(0);
        std::cout << std::endl;
        std::cout << "Element: " << elemPtr2->data << " removed!\n";
        free(elemPtr2);
        displayCircularLLRecursive(head);
        std::cout << std::endl;
        freeResources();
//        displayCircularLL(head);
    }
#ifdef __cplusplus
}
#endif

#endif /* CCIRCULARLINKEDLIST_H */

