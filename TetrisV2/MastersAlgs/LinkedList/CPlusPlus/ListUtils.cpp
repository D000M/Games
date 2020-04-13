/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   ListUtils.cpp
 * Author: default
 * 
 * Created on July 29, 2019, 2:47 PM
 */

#include "ListUtils.h"
#include <iostream>
#include <climits>
int ListUtils::sumOfList(const LinkedList& list) {
    int sum = 0;
    Node* temp = list.getNode();
    while(temp) {
        sum += temp->data;
        temp = temp->next;
    }
    return sum;
}

int ListUtils::sumOfListR(const Node* root) {
    if(root) {
        return sumOfListR(root->next) + root->data;
    }
    return 0;
}

int ListUtils::min(const LinkedList& list) {
    Node* temp = list.getNode();
    int min = temp->data;
    while(temp) {
        if(min > temp->data) {
            min = temp->data;
        }
        temp = temp->next;
    }
    return min;
}

int ListUtils::minR(const Node* root) {
    if(root) {
        int min = minR(root->next);
        return min < root->data ? min : root->data;
    }
    return INT_MAX;
}

int ListUtils::max(const LinkedList& list) {
    Node* temp = list.getNode(); 
    int max = temp->data;
    while(temp) {
        if(max < temp->data) {
            max = temp->data;
        }
        temp = temp->next;
    }
    return max;
}

int ListUtils::maxR(Node* root) {
    if(root) {
        int max = maxR(root->next);
        return max > root->data ? max : root->data;
    }
    return INT_MIN;
}

Node* ListUtils::linearSearch(const LinkedList& list, int key) {
    Node* temp = list.getNode();
    while(temp) {
        if(temp->data == key) {
            return temp;
        }
        temp = temp->next;
    }
    return nullptr;
}

Node* ListUtils::linearSearchR(Node* root, int key) {
    if(root) {
        if(root->data == key) {
            return root;
        }
        return linearSearchR(root->next, key);
    }
    return nullptr;
}

