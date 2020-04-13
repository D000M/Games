/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   CppTree.h
 * Author: default
 *
 * Created on September 3, 2019, 2:41 PM
 */

#ifndef CPPTREE_H
#define CPPTREE_H

#include <queue>


class NodeTree {
public:
    NodeTree* left;
    int data;
    NodeTree* right;
};

class CppTree {
public:
    
    
    CppTree();
    virtual ~CppTree();
    
    void create();
    void preOrder();
    void inOrder();
    void postOrder();
    
    void levelOrder();
    int heightOfATree();
    
    void preOrderIt();
    void inOrderIt();
    void postOrderIt();
    
    int leafCount();
    
    //For Binary Search Tree //Return pointer to the node which key is found or nullptr if not found
    NodeTree* recursiveBinarySearch(int key);
    void insertBST(int element);
    NodeTree* recursiveInsertBST(int element);
    
    NodeTree* recursiveDelete(int element);
    
    
    void createBSTPreorder(int arr[], int size);
private:
    
    NodeTree* root;
    void preOrder(NodeTree* curr);
    void inOrder(NodeTree* curr);
    void postOrder(NodeTree* curr);
    void levelOrder(NodeTree* curr);
    int heightOfATree(NodeTree* curr);
    int leafCount(NodeTree* curr);
    void releaseResources(NodeTree* curr);
    
    //For Binary Search Tree    //Return pointer to the node which key is found or nullptr if not found
    NodeTree* recursiveBinarySearch(NodeTree* curr, int key);
    
    //Iterative version of BST
    NodeTree* binarySearch(int key);
    
    NodeTree* recursiveInsertBST(NodeTree* curr, int element);
    NodeTree* recursiveDelete(NodeTree* curr, int element);
    NodeTree* inorderPredessesor(NodeTree* curr);
    NodeTree* inorderSuccesor(NodeTree* curr);
};

#endif /* CPPTREE_H */

