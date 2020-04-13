/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   CppTreeTest.h
 * Author: default
 *
 * Created on September 3, 2019, 3:16 PM
 */

#ifndef CPPTREETEST_H
#define CPPTREETEST_H

#include "CppTree.h"
#include <iostream>

void testCppTree() {
    CppTree myTree;
    myTree.create();
    
    std::cout << "Preorder: ";
    myTree.preOrder();
    std::cout << "\nPreorderIt: ";
    myTree.preOrderIt();
    std::cout << "\nInOrder: ";
    myTree.inOrder();
    std::cout << "\nInOrderIt: ";
    myTree.inOrderIt();
    std::cout << "\nPostOrder: ";
    myTree.postOrder();
    std::cout << "\nPostOrderIt: ";
    myTree.postOrderIt();
    
    std::cout << "\nHeight of A Tree: " << myTree.heightOfATree() << "\n";
    std::cout << "\nLevel of a Tree: ";
    myTree.levelOrder();
    std::cout << "\nLeaf Count: " << myTree.leafCount() << std::endl;
    std::cout << "\nClean Tree!\n";
}

void testBST() {
    int arr[] = { 9, 15, 5, 20, 16, 8, 12, 3, 6 };
    
    CppTree myTree;
//    myTree.recursiveInsertBST(9);
//    myTree.recursiveInsertBST(15);
//    myTree.recursiveInsertBST(5);
//    myTree.recursiveInsertBST(20);
//    myTree.recursiveInsertBST(16);
//    myTree.recursiveInsertBST(8);
//    myTree.recursiveInsertBST(12);
//    myTree.recursiveInsertBST(3);
//    myTree.recursiveInsertBST(6);
    myTree.insertBST(9);
    myTree.insertBST(15);
    myTree.insertBST(5);
    myTree.insertBST(20);
    myTree.insertBST(16);
    myTree.insertBST(8);
    myTree.insertBST(12);
    myTree.insertBST(3);
    myTree.insertBST(6);
    std::cout << "Height: " << myTree.heightOfATree() << "\n";
    std::cout << "Count: " << myTree.leafCount() << "\n";
    std::cout << "\nPreorder: ";
    myTree.preOrder();
    std::cout << "\nPostorder: ";
    myTree.postOrder();
    std::cout << "\nInOrder: ";
    myTree.inOrder();
    std::cout << "\nLevel Of A Tree: ";
    myTree.levelOrder();
    
    
    
    if(NodeTree* temp = myTree.recursiveBinarySearch(13)) {
        std::cout << "\nElement " << temp->data << " was found!\n";
    }
    else {
        std::cout << "\nSearched element was not found!\n";
    }
    
    myTree.recursiveDelete(12);
//    myTree.recursiveDelete(12);
    std::cout << "Height: " << myTree.heightOfATree() << "\n";
    std::cout << "Count: " << myTree.leafCount() << "\n";
    std::cout << "\nPreorder: ";
    myTree.preOrder();
    std::cout << "\nPostorder: ";
    myTree.postOrder();
    std::cout << "\nInOrder: ";
    myTree.inOrder();
    std::cout << "\nLevel Of A Tree: ";
    myTree.levelOrder();
    if(NodeTree* temp = myTree.recursiveBinarySearch(9)) {
        std::cout << "\nElement " << temp->data << " was found!\n";
    }
    else {
        std::cout << "\nSearched element was not found!\n";
    }
    
    myTree.recursiveDelete(9);
//    myTree.recursiveDelete(12);
    std::cout << "Height: " << myTree.heightOfATree() << "\n";
    std::cout << "Count: " << myTree.leafCount() << "\n";
    std::cout << "\nPreorder: ";
    myTree.preOrder();
    std::cout << "\nPostorder: ";
    myTree.postOrder();
    std::cout << "\nInOrder: ";
    myTree.inOrder();
    std::cout << "\nLevel Of A Tree: ";
    myTree.levelOrder();
    if(NodeTree* temp = myTree.recursiveBinarySearch(9)) {
        std::cout << "\nElement " << temp->data << " was found!\n";
    }
    else {
        std::cout << "\nSearched element was not found!\n";
    }
    
    std::cout << "\nClean Tree!\n";
} 

#endif /* CPPTREETEST_H */

