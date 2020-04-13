/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   CBinaryTree.h
 * Author: default
 *
 * Created on August 28, 2019, 2:32 PM
 */

#ifndef CBINARYTREE_H
#define CBINARYTREE_H

#include <queue>
#include <stdio.h>
#include <stdlib.h>
#include <stack>
#include <iostream>


#ifdef __cplusplus
extern "C" {
#endif

    struct CTreeNode {
        struct CTreeNode* left;
        struct CTreeNode* right;
        int data;
    }*root = nullptr;
    
    
    void createCTree() {
        CTreeNode* current;
        CTreeNode* temp;
        int element;
        std::queue<CTreeNode*> myQueue;
       
        std::cout << "Enter a root Value: ";
        std::cin >> element;
        root = (struct CTreeNode*)malloc(sizeof(struct CTreeNode));
        root->data = element;
        root->left = root->right = nullptr;
        myQueue.push(root);
        
        while(!myQueue.empty()) {
            current = myQueue.front();
            myQueue.pop();
            std::cout << "Enter Left Child of a node: " << current->data << ": ";
            std::cin >> element;
            if(element != -1) {
                temp = (struct CTreeNode*)malloc(sizeof(struct CTreeNode));
                temp->data = element;
                temp->left = temp->right = nullptr;
                current->left = temp;
                myQueue.push(temp);
            }
            std::cout << "Enter Right Child of a node: " << current->data << ": ";
            std::cin >> element;
            if(element != -1) {
                temp = (struct CTreeNode*)malloc(sizeof(struct CTreeNode));
                temp->data = element;
                temp->left = temp->right = nullptr;
                current->right = temp;
                myQueue.push(temp);
            }
        }
    }
    
    void preOrderCTree(struct CTreeNode* tree) {
        if(tree) {
            printf("%d ", tree->data);
            preOrderCTree(tree->left);
            preOrderCTree(tree->right);
        }
    }
    void inOrderCTree(struct CTreeNode* tree) {
        if(tree) {
            inOrderCTree(tree->left);
            printf("%d ", tree->data);
            inOrderCTree(tree->right);
        }
    }
    void postOrderCTree(struct CTreeNode* tree) {
        if(tree) {
            postOrderCTree(tree->left);
            postOrderCTree(tree->right);
            printf("%d ", tree->data);
        }
    }
    void testCTree() {
        createCTree();
        std::cout << "Preorder: ";
        preOrderCTree(root);
        std::cout << "\nInOrder: ";
        inOrderCTree(root);
        std::cout << "\nPostOrder: ";
        postOrderCTree(root);
    }
    
#ifdef __cplusplus
}
#endif

#endif /* CBINARYTREE_H */

