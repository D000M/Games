/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   MyTree.h
 * Author: default
 *
 * Created on December 5, 2018, 3:30 PMx
 */

#ifndef MYTREE_H
#define MYTREE_H

class Leaf {
public:
    int key;
//    const char* data;
    Leaf* left;
    Leaf* right;
    
    friend class MyTree;
};

class MyTree {
    
    
    
    void insertKey(int k, Leaf* leaf);
    Leaf* search(int k, Leaf* leaf);
    void destroyTree();
    void deleteKey(int k, Leaf* leaf);
    Leaf* findMin(Leaf* leaf);
    Leaf* findMax(Leaf* leaf);
    
    void removeRootMatch();
    void removeMatch(Leaf* parent, Leaf* match, bool left);
public:

    MyTree();
    ~MyTree();
    Leaf* search(int k);
    //Deleting functions
    
    void deleteKey(int k);
    Leaf* findMin();
    Leaf* findMax();
    void insertKey(int k);
    void destroyTree(Leaf* leaf);
    
    Leaf* root;
};

#endif /* MYTREE_H */

