/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   BinarySearchTree.cpp
 * Author: default
 * 
 * Created on December 13, 2018, 4:14 PM
 */

#include <iostream>
#include <stack>

#include "BinarySearchTree.h"

#define COUT(x) std::cout << #x << std::endl

BinarySearchTree::BinarySearchTree() {
    root = nullptr;
}

BinarySearchTree::~BinarySearchTree() {
    destroyTree();
}

void BinarySearchTree::destroyTree() {
    destroyTree(root);
}

void BinarySearchTree::destroyTree(Node* leaf) {
    if(leaf != nullptr) {
        destroyTree(leaf->left);
        destroyTree(leaf->right);
        delete leaf;
    }
}

void BinarySearchTree::insertKey(int key) {
    if(root != nullptr) {
        insertKey(key, root);
    }
    else {
        root = new Node;
        root->key = key;
        root->left = nullptr;
        root->right = nullptr;
    }
}

void BinarySearchTree::insertKey(int key, Node* leaf) {
    if(key < leaf->key) {
        if(leaf->left != nullptr) {
            insertKey(key, leaf->left);
        }
        else {
            leaf->left = new Node;
            leaf->left->key = key;
            leaf->left->left = nullptr;
            leaf->left->right = nullptr;
        }
    }
    else if(key > leaf->key) { 
        if(leaf->right != nullptr) {
            insertKey(key, leaf->right);
        }
        else {
            leaf->right = new Node;
            leaf->right->key = key;
            leaf->right->right = nullptr;
            leaf->right->left = nullptr;
        }
    }
    else {
        std::cerr << "The element is already in the tree. \n";
    }
}

Node* BinarySearchTree::findMin() {
    findMin(root);
}

Node* BinarySearchTree::findMin(Node* leaf) {
    while(leaf->left != nullptr) {
        leaf = leaf->left;
    }
    return leaf;
}

Node* BinarySearchTree::findMax() {
    findMax(root);
}

Node* BinarySearchTree::findMax(Node* leaf) {
    while(leaf->right != nullptr) {
        leaf = leaf->right;
    }
    return leaf;
}

Node* BinarySearchTree::searchElement(int key) {
    searchElement(key, root);
}

Node* BinarySearchTree::searchElement(int key, Node* leaf) {
    if(leaf != nullptr) {
        if(key == leaf->key) {
            return leaf;
        }
        else if(key < leaf->key) {
            searchElement(key, leaf->left);
        }
        else if(key > leaf->key) {
            searchElement(key, leaf->right);
        }
    }
    else {
        std::cout << "The Element was not found!\n";
        return nullptr;
    }
}


void BinarySearchTree::deleteKey(int key) {
    deleteKey(key, root);
}

void BinarySearchTree::deleteKey(int key, Node* leaf) {
    if(root != nullptr) {
        if(root->key == key) {
            removeRootMatch();
        }
        else {
            if(key < leaf->key && leaf->left != nullptr) {
                leaf->left->key == key ? removeMatch(leaf, leaf->left, true) : deleteKey(key, leaf->left);
            }
            else if(key > leaf->key && leaf->right != nullptr) {
                leaf->right->key == key ? removeMatch(leaf, leaf->right, false) : deleteKey(key, leaf->right);
            }
            else {
                std::cout << "The Element with key [" << key << "] is not in the tree.\n";
            }
        }
    }
    else {
        COUT("The tree that must be delete is missing!");
    }
}

void BinarySearchTree::removeRootMatch() {
    if(root != nullptr) {
        Node* delPtr = root;
        int rootKey = root->key;
        int smallestInTheRightSubTree;
        
        //case 1  NO Childrens
        if(root->left == nullptr && root->right == nullptr) {
            root = nullptr;
            delete delPtr;
        }
        //case 2 Has Only Right Children
        else if(root->left == nullptr && root->right != nullptr){
            root = root->right;
            delPtr->right = nullptr;
            delete delPtr;
            std::cout << "The Root node with key [" << rootKey << "] was deleted. The new root contains key [" << root->key << "]" <<std::endl;
        }
        //case 3 Has Only Left Children
        else if(root->left != nullptr && root->right == nullptr) {
            root = root->left;
            delPtr->left = nullptr;
            delete delPtr;
            std::cout << "The Root node with key [" << rootKey << "] was deleted. The new root contains key [" << root->key << "]" <<std::endl;
        }
        //case 4 Has Both Childrens
        else {
            smallestInTheRightSubTree = findMin(root->right)->key;
            deleteKey(smallestInTheRightSubTree, root);
            root->key = smallestInTheRightSubTree;
            std::cout << "The Root key containing key [" << rootKey << "] was overwriten with key [" << root->key << "]" << std::endl;
        }
    }
    else {
        std::cout << "The Root is empty!\n";
    }
}

void BinarySearchTree::removeMatch(Node* parent, Node* match, bool left) {
    if(root != nullptr) {
        Node* delPtr;
        int matchKey = match->key;
        int smallestInRightSubTree;
        
        //case 1 NO Childrens
        if(match->left == nullptr && match->right == nullptr) {
            delPtr = match;
            left == true ? parent->left = nullptr : parent->right = nullptr;
            delete delPtr;
            std::cout << "The Node containing key [" << matchKey << "] was removed.\n";
        }
        //case 2 Has Only Right Children
        else if(match->left == nullptr && match->right != nullptr){
            left == true ? parent->left = match->right : parent->right = match->right;
            match->right = nullptr;
            delPtr = match;
            delete delPtr;
            std::cout << "The Node containing key [" << matchKey << "] was removed.\n";
        }
        //case 3 Has Only Left Children
        else if(match->left != nullptr && match->right == nullptr){
            left == true ? parent->left = match->left : parent->right = match->left;
            match->left = nullptr;
            delPtr = match;
            delete delPtr;
            std::cout << "The Node containing key [" << matchKey << "] was removed.\n";
        }
        //case 4 Has Both Childrens
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

void BinarySearchTree::printTree(Node* n) {
    if(n == nullptr) {
        return;
    }
    std::cout << n->key << " ";
    printTree(n->left);
    printTree(n->right);
}

void BinarySearchTree::print2DTree(Node* n, int space) {
    if(n == nullptr) {
        return;
    }
    space += 4;
    
    //Process right child first
    print2DTree(n->right, space);
    std::cout << std::endl;
    for(int i = 4; i < space; i++) {
        std::cout << " ";
    }
    std::cout << n->key << "\n"; 
    
    //Process left child 
    print2DTree(n->left, space);
}


void BinarySearchTree::printInorder() {
    std::stack<Node* > nodes;
    
    Node* current = root;
    while(current != nullptr || nodes.empty() == false ) {
        //Reach the left most Node of the current Node
        while(current != nullptr) {
            //Place pointer to a tree node on the stack before traversing the node's left subtree
            nodes.push(current);
            current = current->left;
        }
        
        //current must be nullptr at this point.
        current = nodes.top();
        nodes.pop();
        std::cout << current->key << " ";
        
        //We have visited the node and its left subtree. Now it's right subtree turn
        current = current->right;
    }
}

void BinarySearchTree::printPostorder() {
    std::stack<Node*> nodes;
    Node* current = root;
    while(current != nullptr || nodes.empty() == false ) {
        while(current != nullptr) {
            nodes.push(current);
            current = current->right;
        }
        current = nodes.top();
        nodes.pop();
        std::cout << current->key << " ";
        current = current ->left;
    }
}



////// HELPER FUNCTIONS ////////////
void BinarySearchTree::createNewNode(int key, Node* newNode, bool left) {
    if(left) {
        newNode->left = new Node;
        newNode->key = key;
        newNode->left->left = nullptr;
        newNode->left->right = nullptr;
    }
    else {
        newNode->right = new Node;
        newNode->key = key;
        newNode->right->left = nullptr;
        newNode->right->right = nullptr;
    }
}



