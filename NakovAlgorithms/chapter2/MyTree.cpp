/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   MyTree.cpp
 * Author: default
 * 
 * Created on December 5, 2018, 3:30 PM
 */

#include <iostream>

#include "MyTree.h"

MyTree::MyTree() {
    root = nullptr;
}

MyTree::~MyTree() {
    destroyTree();
}

void MyTree::destroyTree() {
    destroyTree(root);
}

void MyTree::destroyTree(Leaf* leaf) {
    if(leaf != nullptr) {
        destroyTree(leaf->left);
        destroyTree(leaf->right);
        delete leaf;
    }
}


/**
 * Search element in the binary tree
 * @param k searched element
 * @return the element on pos k
 */
Leaf* MyTree::search(int k) {
    
    return search(k, root);
    
}

Leaf* MyTree::search(int k, Leaf* leaf) {
    if(leaf != nullptr) {
        if(k == leaf->key) {
            return leaf;
        }
        if( k < leaf->key ) {
            return search(k, leaf->left);
        }
        else if(k >= leaf->key) {
            return search(k, leaf->right);
        }
    }
    else {
        std::cout << "The Element was not found!\n";
        return nullptr;
    }
}

void MyTree::insertKey(int k) {
    if(root != nullptr) {
        insertKey(k, root);
    }
    else {
        root = new Leaf;
        root->key = k;
//        root->data = x;
        root->left = nullptr;
        root->right = nullptr;
    }
}

void MyTree::insertKey(int k, Leaf* leaf) {
    if(k < leaf->key) {
        if(leaf->left != nullptr) {
            insertKey(k, leaf->left);
        }
        else {
            leaf->left = new Leaf;
            leaf->left->key = k;
            leaf->left->left = nullptr;
            leaf->left->right = nullptr;
        }
    }
    else if(k > leaf->key) { 
        if(leaf->right != nullptr) {
            insertKey(k, leaf->right);
        }
        else {
            leaf->right = new Leaf;
            leaf->right->key = k;
            leaf->right->right = nullptr;
            leaf->right->left = nullptr;
        }
    }
    else {
        std::cerr << "The element is already in the tree. \n";
    }
}

Leaf* MyTree::findMin() {
    return findMin(root);
}


Leaf* MyTree::findMin(Leaf* leaf) {
    while(leaf->left != nullptr) {
        leaf = leaf->left;
    }
    return leaf;
}

Leaf* MyTree::findMax() {
    return findMax(root);
}


Leaf* MyTree::findMax(Leaf* leaf) {
    while(leaf->right != nullptr) {
        leaf = leaf->right;
    }
    return leaf;
}


void MyTree::deleteKey(int k) {
    deleteKey(k, root);
}

void MyTree::deleteKey(int k, Leaf* leaf) {
    
    if(root != nullptr) {
        if(root->key == k) {
            removeRootMatch();
        }
        else {
            if(k < leaf->key && leaf->left != nullptr) {
                leaf->left->key == k ? removeMatch(leaf, leaf->left, true) : deleteKey(k, leaf->left);
            }
            else if(k > leaf->key && leaf->right != nullptr) {
                leaf->right->key == k ? removeMatch(leaf, leaf->right, false) : deleteKey(k, leaf->right);
            }
            else {
                std::cout << "The Element [" << k << "] was not in the tree!\n";
            }
        }
    }
    else {
        std::cout << "The tree that must be delete, is missing!\n";
    }
}

void MyTree::removeRootMatch() {
    if(root != nullptr) {
        Leaf* delPtr = root;
        int rootKey = root->key;
        int smallestInRightSubTree;
        
        //case 0 no childrens
        if(root->left == nullptr && root->right == nullptr) {
            root = nullptr;
            delete delPtr;
        }
        //case 1 - 1 children
        else if(root->left == nullptr && root->right != nullptr) {
            root = root->right;
            delPtr->right = nullptr;
            delete delPtr;
            std::cout << "The Root node with key [" << rootKey << "] was deleted. The new root contains key [" << root->key << "]" <<std::endl;
        }
        else if(root->left != nullptr && root->right == nullptr) {
            root = root->left;
            delPtr->left = nullptr;
            delete delPtr;
            std::cout << "The Root node with key [" << rootKey << "] was deleted. The new root contains key [" << root->key << "]" <<std::endl;
        }
        //case 2 - 2 childrens
        else {
            smallestInRightSubTree = findMin(root->right)->key;
            deleteKey(smallestInRightSubTree, root);
            root->key = smallestInRightSubTree;
            std::cout << "The Root key containing key [" << rootKey << "] was overwriten with key [" << root->key << "]" << std::endl;
        }
    }
    else {
        std::cout << "The Root is empty!\n";
    }
}

void MyTree::removeMatch(Leaf* parent, Leaf* match, bool left) {
    if(root != nullptr) {
        Leaf* delPtr;
        int matchKey = match->key;
        int smallestInRightSubTree;
        
        //case 0 - 0 children
        if(match->left == nullptr && match->right == nullptr) {
            delPtr = match;
            left == true ? parent->left = nullptr : parent->right = nullptr;
            delete delPtr;
            std::cout << "3The Node containing key [" <<matchKey << "] was removed.\n";
        }
        // case 1 - 1 child
        else if(match->left == nullptr && match->right != nullptr) {
            left == true ? parent->left = match->right : parent->right = match->right;
            match->right = nullptr;
            delPtr = match;
            delete delPtr;
            std::cout << "2The Node containing key [" <<matchKey << "] was removed.\n";
        }
        else if(match->left != nullptr && match->right == nullptr) {
            left == true ? parent->left = match->left : parent->right = match->left;
            match->left = nullptr;
            delPtr = match;
            delete delPtr;
            std::cout << "1The Node containing key [" << matchKey << "] was removed.\n";
        }
        //case 2 - 2 children
        else {
            smallestInRightSubTree = findMin(match->right)->key;
            deleteKey(smallestInRightSubTree, match);
            match->key = smallestInRightSubTree;
        }
    }
    else {
        std::cout << "Cannot remove match. The Tree Is EMPTY!\n";
    }
}
