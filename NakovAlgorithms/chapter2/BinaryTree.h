/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   BinaryTree.h
 * Author: default
 *
 * Created on December 5, 2018, 4:52 PM
 */

#ifndef BINARYTREE_H
#define BINARYTREE_H

class Node {
public:
    int key;
    Node* left;
    Node* right;
};

class BinaryTree {
    
    Node* root;
    
public:
    BinaryTree();
    ~BinaryTree();
    
    void insert(int k);
    Node* search(int k);
    void destroyTree();
    
private:
    
    void destroyTree(Node* leaf);
    void insert(int k, Node* leaf);
    Node* search(int k, Node* leaf);
    
};

#endif /* BINARYTREE_H */

