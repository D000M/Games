/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   BinaryTree.cpp
 * Author: default
 * 
 * Created on December 5, 2018, 4:52 PM
 */

#include "BinaryTree.h"

BinaryTree::BinaryTree() {
    root = nullptr;
}

BinaryTree::~BinaryTree() {
    destroyTree();
}

void BinaryTree::destroyTree(Node* leaf) {
    if(leaf != nullptr) {
        destroyTree(leaf->left);
        destroyTree(leaf->right);
        delete leaf;
    }
}

void BinaryTree::insert(int k, Node* leaf) {
    if(k < leaf->key) {
        if(leaf->left != nullptr) {
            insert(k, leaf->left);
        }
        else {
            leaf->left = new Node;
            leaf->left->key = k;
            leaf->left->left = nullptr;
            leaf->left->right = nullptr;
        }
    }
    else if(k >= leaf->key) {
        if(leaf->right != nullptr) {
            insert(k, leaf->right);
        }
        else {
            leaf->right = new Node;
            leaf->right->key = k;
            leaf->right->left = nullptr;
            leaf->right->right = nullptr;
        }
    }
}

Node* BinaryTree::search(int k, Node* leaf) {
    if(leaf != nullptr) {
        if(k == leaf->key) {
            return leaf;
        }
        if(k < leaf->key) {
            return search(k, leaf->left);
        }
        else {
            return search(k, leaf->right);
        }
    }
    else {
        return nullptr;
    }
}

void BinaryTree::insert(int k) {
    
    //If the root is set, insert k recursively using private insert(int, Node*);
    if(root != nullptr) {
        insert(k, root);
    }
    else { //If the root is not set, allocate memory and set root member variables, key - k, and left and right nullptr.
        root = new Node;
        root->key = k;
        root->left = nullptr;
        root->right = nullptr;
    }
}

Node* BinaryTree::search(int k) {
    return search(k, root);
}

void BinaryTree::destroyTree() {
    destroyTree(root);
}
