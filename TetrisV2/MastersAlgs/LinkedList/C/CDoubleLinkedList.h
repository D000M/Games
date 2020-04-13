/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   CDoubleLinkedList.h
 * Author: default
 *
 * Created on July 31, 2019, 1:06 PM
 */

#ifndef CDOUBLELINKEDLIST_H
#define CDOUBLELINKEDLIST_H

#include <stdlib.h>
#include <stdio.h>


#ifdef __cplusplus
extern "C" {
#endif

    struct CDNode {
        int data;
        struct CDNode* next;
        struct CDNode* prev;
    };
    
    struct CDNode* myList = NULL;
    
    void createCDLL(int arr[], int size) {
        struct CDNode *temp, *last;
        int i;
        
        myList = (struct CDNode*)malloc(sizeof(struct CDNode));
        myList->data = arr[0];
        myList->prev = NULL;
        myList->next = NULL;
        
        last = myList;
        
        for(i = 1; i < size; i++) {
            temp = (struct CDNode*)malloc(sizeof(struct CDNode));
            temp->data = arr[i];        //set the data of this NODE
            
            temp->next = last->next;    // Make this Node next, point to last next
            temp->prev = last;          //make this Node prev, point to the last
            
            last->next = temp;          // make last next point to the temp
            last = temp;
        }
        
    }   //end create
    
    void displayCDLL(struct CDNode* list) {
        while(list) {
            printf("%d ", list->data);
            list = list->next;
        }
        printf("\n");
    }   //end iterative display
    
    int lengthCDLL(struct CDNode* list) {
        int length = 0;
        
        while(list) {
            length++;
            list = list->next;
        }
        return length;
    }   //end iterative length
    
    void insertAtCDLL(int index, int elem) {
        struct CDNode* temp, *curr;
        if(index == 0) {
            temp = (struct CDNode*)malloc(sizeof(struct CDNode));
            temp->data = elem;
            temp->prev = NULL;
            temp->next = myList;
            myList->prev = temp;
            myList = temp;
        }
        else {
            curr = myList;
            for(int i = 0; i < index - 1 && curr->next; i++) {
                curr = curr->next;
            }
            temp = (struct CDNode*)malloc(sizeof(struct CDNode));
            temp->data = elem;
            
            temp->prev = curr;
            temp->next = curr->next;
            
            if(curr->next) {
                curr->next->prev = temp;
            }
            curr->next = temp;
        }
    }
    
    int deleteAtCDLL(int pos) {
        struct CDNode* temp;
        int elem;
        if(pos < 0) {
            return -1;  //Out of range
        }
        if(pos == 0) {
            temp = myList;
            myList = myList->next;
            elem = temp->data;
            std::cout << "Element: " << temp->data << " Deleted\n";
            free(temp);
            if(myList) {
                myList->prev = NULL;
            }
            return elem;
        }
        else {
            temp = myList;
            for(int i = 0; i < pos && temp->next; i++) {
                temp = temp->next;
            }
            elem = temp->data;
            temp->prev->next = temp->next;
            if(temp->next) {
                temp->next->prev = temp->prev;
            }
            std::cout << "Element: " << temp->data << " Deleted\n";
            free(temp);
            return elem;
        }
    }
    
    void reverseCDLL(struct CDNode* list) {
        struct CDNode* temp;
        while(list) {
            temp = list->next;
            list->next = list->prev;
            list->prev = temp;
            list = list->prev;
            if(list != NULL && list->next == NULL) {
                myList = list;
            } 
        }
    }
    
    void testCDLL() {
        int arr[] = { 1, 3, 5, 7, 9 };
        createCDLL(arr, 5);
        printf("\nLength is: %d\n", lengthCDLL(myList));
        displayCDLL(myList);
        insertAtCDLL(0, 100);
        printf("\nLength is: %d\n", lengthCDLL(myList));
        displayCDLL(myList);
        insertAtCDLL(2, 15);
        printf("\nLength is: %d\n", lengthCDLL(myList));
        displayCDLL(myList);
        insertAtCDLL(10, 155);
        printf("\nLength is: %d\n", lengthCDLL(myList));
        displayCDLL(myList);
        int elem = deleteAtCDLL(0);
        std::cout << "Element: " << elem << " returned\n";
        printf("\nLength is: %d\n", lengthCDLL(myList));
        displayCDLL(myList);
        int elem2 = deleteAtCDLL(15);
        std::cout << "Element: " << elem2 << " returned\n";
        printf("\nLength is: %d\n", lengthCDLL(myList));
        displayCDLL(myList);
        std::cout << "Reverse DLL: ";
        reverseCDLL(myList);
        displayCDLL(myList);
    }

#ifdef __cplusplus
}
#endif

#endif /* CDOUBLELINKEDLIST_H */

