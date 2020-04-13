/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   CCircularDoubleLinkedList.h
 * Author: default
 *
 * Created on July 31, 2019, 3:31 PM
 */

#ifndef CCIRCULARDOUBLELINKEDLIST_H
#define CCIRCULARDOUBLELINKEDLIST_H

#include <stdlib.h>
#include <stdio.h>
#include <iostream>


#ifdef __cplusplus
extern "C" {
#endif

    struct CCDNode {
        int data;
        CCDNode* next;
        CCDNode* prev;
    };
    
    struct CCDNode* myCDLLhead;
    
    void createCCDLL(int arr[], int size) {
        
        struct CCDNode* current;
        
        myCDLLhead = (struct CCDNode*)malloc(sizeof(struct CCDNode));
        myCDLLhead->data = arr[0];
        myCDLLhead->prev = myCDLLhead;
        myCDLLhead->next = myCDLLhead;
        
        int i;
        
        struct CCDNode* last = myCDLLhead;
        
        for(i = 1; i < size; i++) {
            current = (struct CCDNode*)malloc(sizeof(struct CCDNode));
            current->data = arr[i];
            
            current->next = last->next;
            current->prev = last;
            
            last->next = current;
            last = current;
        }
        myCDLLhead->prev = last;
        last->next = myCDLLhead;
    }
    
    void displayCCDLL(struct CCDNode* list) {
        do {
            printf("%d ", list->data);
            list = list->next;
        }
        while(list != myCDLLhead);
    }
    
    void displayCCDLLThreeTimes(struct CCDNode* list) {
        int count = 0;
        while(list) {
            if(count == 3) {
                break;
            }
            printf("%d ", list->data);
            list = list->next;
            if(list == myCDLLhead) {
                count++;
            }
        }
    }
    
    void insertAtCCDLL(struct CCDNode* current, int pos, int elem) {

        struct CCDNode* temp;
        
        if(pos == 0) {
            temp = (struct CCDNode*)malloc(sizeof(struct CCDNode));
            temp->data = elem;
            
            temp->prev = current->prev;
            temp->next = current;
            current->prev->next = temp;
            current->prev = temp;
            myCDLLhead = temp;
        }
        else {
            for(int i = 0; i < pos - 1; i++) {
                current = current->next;
            }
            temp = (struct CCDNode*)malloc(sizeof(struct CCDNode));
            temp->data = elem;

            temp->prev = current;
            temp->next = current->next;

            current->next->prev = temp;
            current->next = temp;
        }
    }
    
    void testCircularDoubleLL() {
        int arr[] = {1, 2, 3, 4, 5};
        createCCDLL(arr, 5);
        std::cout << "Displaying: ";
        displayCCDLL(myCDLLhead);
        std::cout << std::endl;
        
        insertAtCCDLL(myCDLLhead, 3, 100);
        std::cout << "Displaying: ";
        displayCCDLLThreeTimes(myCDLLhead);
        std::cout << std::endl;
        
        insertAtCCDLL(myCDLLhead, 0, 55);
        std::cout << "Displaying: ";
        displayCCDLLThreeTimes(myCDLLhead);
        std::cout << std::endl;
        
        std::cout << "Displaying: ";
        insertAtCCDLL(myCDLLhead, 12, 222);
        displayCCDLL(myCDLLhead);
        std::cout << std::endl;
    }

#ifdef __cplusplus
}
#endif

#endif /* CCIRCULARDOUBLELINKEDLIST_H */

