/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   CList.h
 * Author: default
 *
 * Created on December 4, 2018, 3:40 PM
 */

#ifndef CLIST_H
#define CLIST_H

#include <stdlib.h>
#include <stdio.h>


typedef int dataL;
typedef int keyType;

struct list {
    keyType key;
    dataL info;
    struct list* next;
};

/**
 * Insert element at the begining of the list
 * @param L
 * @param key
 * @param x
 */
void insertBegin(struct list** L, keyType key, dataL x ) {
    struct list* temp;
    temp = (struct list*) malloc(sizeof(*temp));
    
    if(temp == NULL) {
        fprintf(stderr, "Not enough memory for new element! \n");
        return;
    }
    
    temp->next = *L;
    (*L) = temp;
    (*L)->key = key;
    (*L)->info = x;
}

void insertAfter(struct list** L, keyType key, dataL x) {
    struct list* temp;
    
    if(*L == NULL) {    //Chasten sluchai ako spisyka e prazen.
        insertBegin(L, key, x);
        return;
    }
    
    temp = (struct list*) malloc(sizeof(*temp));
    if(temp == NULL) {
        fprintf(stderr, "Nqma dostatuchno mqsto za nov element! \n");
        return;
    }
    temp->key = key;
    temp->info = x;
    temp->next = (*L)->next;
    (*L)->next = temp;
}

void insertBefore(struct list** L, keyType key, dataL x) {
    struct list* temp;
    
    if(*L == NULL) {
        insertBegin(L, key, x);
        return;
    }
    
    temp = (struct list*) malloc(sizeof(*temp));
    if(temp == NULL) {
        fprintf(stderr, "Nqma dostatuchno mqsto za nov element! \n");
        return;
    }
    
    *temp = **L;
    (*L)->next = temp;
    (*L)->key = key;
    (*L)->info = x;
}

void deleteNode(struct list** L, keyType key) {
    struct list* current = *L;
    struct list* save;
    
    if((*L)->key == key) {  //Trqbva da se iztrie purviq element
        current = (*L)->next;
        free(*L);
        (*L) = current;
        return;
    }
    
    //Find the element which must be deleted
    while(current->next != NULL && current->next->key != key) {
        current = current->next;
    }
    
    if(current->next == NULL) {
        fprintf(stderr, "Error: Element was not found. \n");
        return;
    }
    else {
        save = current->next;
        current->next = current->next->next;
        free(save);
    }
}

void print(struct list* L) {
    while(L != NULL) {
        printf("%d(%d) ", L->key, L->info);
        L = L->next;
    }
    printf("\n");
}

//Tyrsene po kluch
struct list* search(struct list* L, keyType key) {
    while(L != NULL) {
        if(L->key == key) {
            return L;
        }
        L = L->next;
    }
    return NULL;
}
#endif /* CLIST_H */

