/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   ListUtils.h
 * Author: default
 *
 * Created on July 29, 2019, 2:47 PM
 */

#ifndef LISTUTILS_H
#define LISTUTILS_H

#include "LinkedList.h"


class ListUtils {
public:
    static int sumOfList(const LinkedList& list);
    static int sumOfListR(const Node* root);
    static int max(const LinkedList& list);
    static int maxR(Node* root);
    static int min(const LinkedList& list);
    static int minR(const Node* root);
    static Node* linearSearch(const LinkedList& list, int key);
    static Node* linearSearchR(Node* root, int key);
};

#endif /* LISTUTILS_H */

