/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Examples.h
 * Author: default
 *
 * Created on December 4, 2018, 3:08 PM
 */

#ifndef EXAMPLES_H
#define EXAMPLES_H

#include <stack>

#include "Stack.h"
#include "CQueue.h"
#include "CList.h"
#include "MyStack.h"
#include "MyQueue.h"
#include "Tree.h"
#include "MyTree.h"
#include "../utils/BinarySearchTree.h"
#include "hashTables/CHashTables/CHash.h"
#include "hashTables/HashTables/HashTable.h"
//Test CStack
void testCStack() {
    data p;
    init();
    
    /**
     * Input integers until number 0 is inputed
     */
    scanf("%d", &p);
    while(p != 0) {
        push(p);
        scanf("%d", &p);
    }
    
    /**
     * Remove every element from the stack and print it.
     */
    while(!isEmpty()) {
        printf("%d ", pop());
    }
    printf("\n");
}

//Test CQueue
void testCQueue() {
    dataQ p;
    initQ();
    
    for(int i = 0; i < 2 * MAX; i++ ) {
        putQ(i);
        p = getQ();
        printf("%d ", p);
    }
    printf("\n");
    for(int i = 0; i < MAX + 1; i++) {
        putQ(i);
    }
    for(int i = 0; i < MAX + 1; i++) {
        getQ();
    }
}

//Test List
void testCList() {
    struct list* L = NULL;
    int edata;
    insertBegin(&L, 0, 42);
    
    for(int i = 1; i < 6; i++) {
        edata = rand() % 100;
        printf("Insert Before: %d(%d) \n", i, edata);
        insertBefore(&L, i, edata);
    }
    
    for(int i = 6; i < 10; i++) {
        edata = rand() % 100;
        printf("Insert After: %d(%d) \n", i, edata);
        insertAfter(&L, i, edata);
    }
    print(L);
    deleteNode(&L, 9);
    print(L);
    deleteNode(&L, 0);
    print(L);
    deleteNode(&L, 3);
    print(L);
    deleteNode(&L, 5);
    print(L);
    deleteNode(&L, 5);

}

void testMyStack() {
    MyStack p;
    p.init();
    for(int i = 0; i < 5; i++) {
        p.push(i + 1);
    }
    while(!p.isEmpty()) {
        std::cout << (int)p.pop() << " ";
    }
}

void testMyQueue() {
    MyQueue p;
    p.init();
    for(int i = 1; i <= 5; i++) {
        p.put(i);
    }
    for(int i = 0; i < 5; i++) {
        std::cout << (int)p.get() << " ";
    }
}


//Tree
void printTree(Tree* t) {
    if(t == NULL) {
        return;
    }
    printf("%d ", t->key);
    printTree(t->left);
    printTree(t->right);
}
void testTree() {
    Tree* t = NULL;
    Tree* result;
    
    //Insert 10 vyrha s proizvolni stoinosti
    for(int i = 0; i < 5; i++) {
        int iKey = (rand() % 20) + 1;
        printf("Вмъква се елемент с ключ: %d \n", iKey);
        t->insertKey(iKey, "someInfo", &t);
    }
    printf("Дърво: ");
    printTree(t);
    printf("\n");
//    
//    //Pretursva za elementa s kluch 5
//    result = t->search(14, t);
//    printf("Намерен е: %s\n", result->data);
//    
//    //Istriva proizvolni 10 vyrha ot dyrvoto.
//    for(int i = 0; i < 10; i++) {
//        int iKey = (rand() % 20) + 1;
//        printf("Изтрива се елемент с ключ: %d \n", iKey);
//        t->deleteKey(iKey, &t);
//    }
//    printf("Дърво: ");
//    
//    printTree(t);
//    
//    printf("\n");
}

template<typename T>
void printMyTree(T* ptrN) {
    if(ptrN == NULL) {
        return;
    }
    std::cout << ptrN->key << " ";
    printMyTree(ptrN->left);
    printMyTree(ptrN->right);
}

void testMyTree() {
    MyTree mt;
    
//    for(int i = 0; i < 5; i++) {
        for(int i = 0; i < 20; i++) {
            int num = std::rand() % 1000 + 1;
            std::cout << num << std::endl;
            mt.insertKey(num);
        }
        
        printMyTree(mt.root);
        std::cout << std::endl;
//        mt.deleteKey(6);
//        mt.deleteKey(9);
//        mt.deleteKey(3);
//        mt.deleteKey(14);
//        mt.deleteKey(12);
//        mt.deleteKey(1);
//        mt.deleteKey(4);
//        mt.deleteKey(17);
//        mt.deleteKey(14);
//        mt.deleteKey(16);
//        std::cout << "Found: " << mt.search(11)->key << std::endl;
        std::cout << "Min Element: " << mt.findMin()->key << std::endl;
        std::cout << "Max Element: " << mt.findMax()->key << std::endl;
        printMyTree(mt.root);
//    }
//    std::cout << std::endl;
//    printMyTree(mt.root);
}

void testZadOne() {
    BinarySearchTree myTree;
//    for(int i = 0; i < 20; i++) {
//        int num = std::rand() % 1000 + 1;
//        std::cout << num << std::endl;
        
//    }
    myTree.insertKey(6);
    myTree.insertKey(5);
    myTree.insertKey(10);
    myTree.insertKey(3);
    myTree.insertKey(8);
    myTree.insertKey(13);
    myTree.insertKey(1);
    myTree.insertKey(7);
    myTree.insertKey(11);
    myTree.insertKey(14);
    myTree.insertKey(12);
    
    printMyTree(myTree.root);
    std::cout << std::endl;
    std::cout << "Min Element: " << myTree.findMin()->key << "\n";
    std::cout << "Max Element: " << myTree.findMax()->key << "\n";

    myTree.deleteKey(8);
    myTree.deleteKey(13);
    myTree.deleteKey(5);
    myTree.deleteKey(6);
    printMyTree(myTree.root);
}

void printIterativeTree(BinarySearchTree tree) {
    std::stack<Node*> nStack;
    
    Node* current = tree.root;
    while(current != nullptr || nStack.empty() == false) {
        //Reach the left most Node of the current Node
        while(current != nullptr) {
            //Place pointer to a tree node on the stack before traversing the node's left subtree
            nStack.push(current);
            current = current->left;
        }
        
        //current must be nullptr at this point.
        current = nStack.top();
        nStack.pop();
        std::cout << current->key << " ";
        
        //We have visited the node and its left subtree. Now it's right subtree turn
        current = current->right;
    }
}

void testIterativeTreePrint() {
    BinarySearchTree myTree;
//    for(int i = 1; i <= 8; i++) {
//        int num = std::rand() % 100 + 1;
//        myTree.insertKey(num);
//    }
    myTree.insertKey(28);
    myTree.insertKey(64);
    myTree.insertKey(13);
    myTree.insertKey(61);
    myTree.insertKey(12);
    myTree.insertKey(65);
    myTree.insertKey(14);
    myTree.insertKey(42);
    myTree.insertKey(7);
    myTree.insertKey(81);
    myTree.insertKey(18);
    myTree.insertKey(35);
    myTree.insertKey(4);
    std::cout << std::endl;
    myTree.print2DTree(myTree.root, 0);

}

void CHashTableTest() {
    testHashTable();
}

void testMyHashTable() {
    HashTable ht;
    ht.initHashTable();
    ht.put(1234, 100);
    ht.put(1774, 120);
    ht.put(86, 180);
    ht.get(12);
//    std::cout << "Otpechatva dannite s kluch   86: " << ht.get(86) << std::endl;
//    std::cout << "Otpechatva dannite s kluch 1234: " << ht.get(1234) << std::endl;
//    std::cout << "Otpechatva dannite s kluch 1774: " << ht.get(1774) << std::endl;
//    std::cout << "Otpechatva dannite s kluch 1773: " << ht.get(1773) << std::endl;
}
#endif /* EXAMPLES_H */

