/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   BinarySearchTree.h
 * Author: default
 *
 * Created on December 13, 2018, 4:14 PM
 */

#ifndef BINARYSEARCHTREE_H
#define BINARYSEARCHTREE_H

struct Node {
    
    
    int key;        //Node key
    Node* left;     //Pointer to the left Node
    Node* right;    //Pointer to the right Node
    
    
    friend class BinarySearchTree;
    
public:
    inline int getKey() const {
        return key;
    }
};

class BinarySearchTree {
public:
    BinarySearchTree();
    virtual ~BinarySearchTree();

    Node* root; //The Root Of the Tree
    
    //Functions
    
    void destroyTree(Node* leaf);
    void insertKey(int key);
    void deleteKey(int key);
    Node* searchElement(int key);
    
    Node* findMin();
    Node* findMax();
    
    //Print the Tree recursive
    void printTree(Node* n);
    
    //Print Tree in 2D (root is on the left and childs are top and bottom)
    void print2DTree(Node* n, int space);
    
    //Print The Tree Iterative Inorder
    void printInorder();
    
    //Print the Tree Iterative Postorder
    void printPostorder();
private:
    
    /**
     * Delete all Nodes in the tree
     */
    void destroyTree();
    void insertKey(int key, Node* leaf);
    void deleteKey(int key, Node* leaf);
    Node* searchElement(int key, Node* leaf);
    
    
    void removeRootMatch();
    void removeMatch(Node* parent, Node* match, bool left);
    Node* findMin(Node* leaf);
    Node* findMax(Node* leaf);
    
    //Private Helper function
    void createNewNode(int key, Node* newNode, bool left);
};

#endif /* BINARYSEARCHTREE_H */

