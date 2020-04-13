/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   CppTree.cpp
 * Author: default
 * 
 * Created on September 3, 2019, 2:41 PM
 */

#include <iostream>
#include <stack>

#include "CppTree.h"

CppTree::CppTree() 
    : root{nullptr} {
}


CppTree::~CppTree() {
    releaseResources(root);
}

void CppTree::create() {
    NodeTree* curr;
    NodeTree* temp;
    
    int value;
    std::cout << "Enter Root Value: ";
    std::cin >> value;
    root = new NodeTree;
    root->data = value;
    root->left = root->right = nullptr;
    
    std::queue<NodeTree*> myQueue;
    myQueue.push(root);
    
    while(!myQueue.empty()) {
        
        curr = myQueue.front();
        myQueue.pop();
        
        std::cout << "Enter Left Value of a node: " << curr->data << " ";
        std::cin >> value;
        
        if(value != -1) {
            temp = new NodeTree;
            temp->data = value;
            temp->left = temp->right = nullptr;
            curr->left = temp;
            myQueue.push(temp);
        }
        
        std::cout << "Enter Right Value of a node: " << curr->data << " ";
        std::cin >> value;
        
        if(value != -1) {
            temp = new NodeTree;
            temp->data = value;
            temp->left = temp->right = nullptr;
            curr->right = temp;
            myQueue.push(temp);
        }
        
    }
}

void CppTree::preOrder(NodeTree* curr) {
    if(curr) {
        std::cout << curr->data << " ";
        preOrder(curr->left);
        preOrder(curr->right);
    }
}

void CppTree::preOrder() {
    preOrder(root);
}

void CppTree::inOrder(NodeTree* curr) {
    if(curr) {
        inOrder(curr->left);
        std::cout << curr->data << " ";
        inOrder(curr->right);
    }
}

void CppTree::inOrder() {
    inOrder(root);
}

void CppTree::postOrder(NodeTree* curr) {
    if(curr) {
        postOrder(curr->left);
        postOrder(curr->right);
        std::cout << curr->data << " ";
    }
}

void CppTree::postOrder() {
    postOrder(root);
}

void CppTree::levelOrder(NodeTree* curr) {
    std::queue<NodeTree*> myQueue;
    
    std::cout << std::endl;
    std::cout << curr->data << " ";
    myQueue.push(curr);
    
    while(!myQueue.empty()) {
        curr = myQueue.front();
        myQueue.pop();
        if(curr->left) {
            std::cout << curr->left->data << " ";
            myQueue.push(curr->left);
        }      
        if(curr->right) {
            std::cout << curr->right->data << " ";
            myQueue.push(curr->right);
        }
    }
}

void CppTree::levelOrder() {
    levelOrder(root);
}

int CppTree::heightOfATree(NodeTree* curr) {
    int x = 0, y = 0;
    if(curr == nullptr) {
        return 0;
    }
    
    x = heightOfATree(curr->left);
    y = heightOfATree(curr->right);
    if(x > y) {
        return x + 1;
    }
    else {
        return y + 1;
    }
}

int CppTree::heightOfATree() {
    heightOfATree(root);
}

void CppTree::preOrderIt() {
    if(!root) {
        return;
    }
    std::stack<NodeTree*> myStack;
    myStack.push(root);
    
    while(!myStack.empty()) {
        NodeTree* temp = myStack.top();
        myStack.pop();
        std::cout << temp->data << " ";
        if(temp->right) {
            myStack.push(temp->right);
        }
        if(temp->left) {
            myStack.push(temp->left);
        }
    }
}

void CppTree::inOrderIt() {
    if(!root) {
        return;
    }
    
    std::stack<NodeTree*> myStack;
    myStack.push(root);
    
    NodeTree* temp = myStack.top();
    myStack.pop();
    
    while(temp || !myStack.empty()) {
        
        if(temp) {
            myStack.push(temp);
            temp = temp->left;
        }
        else {
            temp = myStack.top();
            myStack.pop();
            std::cout << temp->data << " ";
            temp = temp->right;
        }
    }
}

void CppTree::postOrderIt() {
    if(!root) {
        return;
    }

    std::stack<NodeTree*> myStack;
    myStack.push(root);
    
    NodeTree* temp = myStack.top();
    myStack.pop();
    
    while(temp || !myStack.empty()) {
        
        if(temp) {
            myStack.push(temp);
            temp = temp->left;
        }
        else {
            
            temp = myStack.top();
            myStack.pop();
             
            if(temp->data > 0) {
                temp->data = (temp->data * -1);
                myStack.push(temp);
                temp = temp->right;
            }
            else {
                if(temp->data < 0) {
                    temp->data = temp->data * -1;
                }
                std::cout << temp->data<< " ";
                temp = nullptr;
            }
        }
    }
    
}
void CppTree::releaseResources(NodeTree* curr) {
    if(curr) {
        releaseResources(curr->left);
        releaseResources(curr->right);
        std::cout << "Node: " << curr->data << ", Deleted!\n";
        delete curr;
    }
}

int CppTree::leafCount() {
    return leafCount(root);
}

int CppTree::leafCount(NodeTree* curr) {
    int left;
    int right;
    
    if(curr) {
        left = leafCount(curr->left);
        right = leafCount(curr->right);
        return left + right + 1;
    }
    return 0;
}

NodeTree* CppTree::recursiveBinarySearch(int key) {
    return recursiveBinarySearch(root, key);
}

NodeTree* CppTree::recursiveBinarySearch(NodeTree* curr, int key) {
    if(!curr) {
        return nullptr;
    }
    if(curr->data == key) {
        return curr;
    }
    else if(key > curr->data) {
        return recursiveBinarySearch(curr->right, key);
    }
    else if(key < curr->data) {
        return recursiveBinarySearch(curr->left, key);
    }
}

NodeTree* CppTree::binarySearch(int key) {
    NodeTree* temp = root;
    
    while(temp) {
        if(temp->data == key) {
            return temp;    //Element found 
        }
        else if(key > temp->data) {
            temp = temp->right;
        }
        else {
            temp = temp->left;
        }
    }
    return nullptr;     //Key not found.
}

void CppTree::insertBST(int element) {
    if(root == nullptr) {
        root = new NodeTree;
        root->data = element;
        root->left = root->right = nullptr;
        return;
    }
    NodeTree* curr = root;
    NodeTree* temp = curr;
    NodeTree* createPtr = nullptr;
    
    while(curr) {
        temp = curr;
        if(curr->data == element) {
            std::cout << "Cannot insert element who is already in the tree!\n";
            return;
        }
        else if(element > curr->data) {
            curr = curr->right;
        }
        else if(element < curr->data) {
            curr = curr->left;
        }
    }
    
    createPtr = new NodeTree;
    createPtr->data = element;
    createPtr->left = nullptr;
    createPtr->right = nullptr;
    
    if(element > temp->data) {
        temp->right = createPtr;
    }
    else {
        temp->left = createPtr;
    }
}

NodeTree* CppTree::recursiveInsertBST(int element) {
    if(root == nullptr) {
        root = new NodeTree;
        root->data = element;
        root->left = root->right = nullptr;
        return nullptr;
    }
    return recursiveInsertBST(root, element);
}

NodeTree* CppTree::recursiveInsertBST(NodeTree* curr, int element) {
    NodeTree* temp = nullptr;
    if(curr == nullptr) {
        temp = new NodeTree;
        temp->data = element;
        temp->left = temp->right = nullptr;
        return temp;
    }
    
    if(element > curr->data) {
        curr->right = recursiveInsertBST(curr->right, element);
    }
    else {
        curr->left = recursiveInsertBST(curr->left, element);
    }
    
    return curr;
}

NodeTree* CppTree::recursiveDelete(int element) {
    return recursiveDelete(root, element);
}

NodeTree* CppTree::recursiveDelete(NodeTree* curr, int element) {
    
    if(curr == nullptr) {
        return nullptr;
    }
    
    if(!curr->left && !curr->right) {
        if(curr == root) {
            root = nullptr;
        }
        delete curr;
        return nullptr;
    }
    
    
    if(element > curr->data) {
        curr->right = recursiveDelete(curr->right, element);
    }
    else if(element < curr->data) {
        curr->left = recursiveDelete(curr->left, element);
    }
    else {
        NodeTree* temp = nullptr;
        
        if(heightOfATree(curr->left) > heightOfATree(curr->right)) {
            temp = inorderPredessesor(curr->left);
            curr->data = temp->data;
            curr->left = recursiveDelete(curr->left, element);
        }
        else {
            temp = inorderSuccesor(curr->right);
            curr->data = temp->data;
            curr->right = recursiveDelete(curr->right, element);
        }
    }
    return curr;
}

NodeTree* CppTree::inorderPredessesor(NodeTree* curr) {
    while(curr && curr->right) {
        curr = curr->right;
    }
    return curr;
}
NodeTree* CppTree::inorderSuccesor(NodeTree* curr) {
    while(curr && curr->left) {
        curr = curr->left;
    }
    return curr;
}

void CppTree::createBSTPreorder(int arr[], int size) {
    std::stack<NodeTree*> myStack;
    
    NodeTree* temp = nullptr;
    int i = 0;
    root = new NodeTree;
    root->data = arr[i++];
    root->left = root->right = nullptr;
    
    NodeTree* prev = root;
    
    while(i < size) {
        if(arr[i] < temp->data) {
            temp = new NodeTree;
            temp->data = arr[i++];
            temp->left = temp->right = nullptr;
            prev->left = temp;
            myStack.push(prev);
            prev = temp;
        }
        else {
            
            if(arr[i] > prev->data && arr[i] < myStack.top()->data) {
                temp = new NodeTree;
                temp->data = arr[i++];
                temp->left = temp->right = nullptr;
                prev->right = temp;
                prev = temp;
            }
            else {
                prev = myStack.top();
                myStack.pop();
            }
        }
    }
}