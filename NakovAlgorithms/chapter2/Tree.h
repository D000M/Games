/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Tree.h
 * Author: default
 *
 * Created on December 5, 2018, 2:11 PM
 */

#ifndef TREE_H
#define TREE_H

class Tree {

public:
    int key;
    const char* data;
    Tree* left;
    Tree* right;
    //Dobavqne na vruh
    void insertKey(int k, const char* x, Tree** t);
    
    //Iztrivane na vryh po zadaden kluch
    void deleteKey(int k, Tree** t);
    
    //Tyrsene na vryh i izvlichane na dannite ot nego
    Tree* findMin(Tree* t);
    Tree* search(int k, Tree* t);
};

#endif /* TREE_H */

