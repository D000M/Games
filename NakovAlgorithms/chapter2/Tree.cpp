/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Tree.cpp
 * Author: default
 * 
 * Created on December 5, 2018, 2:11 PM
 */

#include "Tree.h"
#include <stdio.h>
#include <cstdlib>
#include <iostream>

/**
 * Search in binary tree
 * @param k
 * @param t
 * @return 
 */
Tree* Tree::search(int k, Tree* t) {
    if(t == NULL) {
        return NULL;
    }
    else if(k < t->key) {
        return search(k, t->left);
    }
    else if(k > t->key) {
        return search(k, t->right);
    }
    else {
        return t;
    }
}

/**
 * Insert in binary tree
 * @param k
 * @param x
 * @param t
 */
void Tree::insertKey(int k, const char* x, Tree** t) {
    if(*t == NULL) {
        *t = (Tree*)malloc(sizeof(**t));
        (*t)->key = k;
        (*t)->data = x;
        (*t)->left = NULL;
        (*t)->right = NULL;
        std::cout << k << " " << x << std::endl;
    }
    else if(k < (*t)->key) {
        insertKey(k, x, &(*t)->left);
    }
    else if(k > (*t)->key) {
        insertKey(k, x, &(*t)->right);
    }
    else {
        fprintf(stderr, "The element is already in the Tree! \n");
    }
}

//The functions for deleting 

/**
 * Search next element from the left pos of the tree if there is any return the element
 * else return NULL. 
 * @param t
 * @return 
 */
Tree* Tree::findMin(Tree* t) {
    while(t->left != NULL) {
        t = t->left;
    }
    return t;
}

void Tree::deleteKey(int k, Tree** t) {
    if(*t == NULL) {
        fprintf(stderr, "The tree that must be delete, is missing! \n");
    }
    else {
        if(k < (*t)->key) {
            deleteKey(k, &(*t)->left);
        }
        else if(k > (*t)->key) {
            deleteKey(k, &(*t)->right);
        }
        else {  //Element is found
            if((*t)->left && (*t)->right) { //vyrhut ima 2 naslednika
                //namira se vurhu za razmqna.
                Tree* temp = findMin((*t)->right);
                (*t)->key = temp->key;
                (*t)->data = temp->data;
                deleteKey((*t)->key, &(*t)->right);  //Vyrhut se izkluchva
            }
            else {  //Elementut ima 0 ili 1 poddurveta
                Tree* temp = *t;
                if((*t)->left){
                    *t = (*t)->left;
                }
                else {
                    *t = (*t)->right;
                }
                free(temp);
            }
        }
    }
}
