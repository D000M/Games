/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   CBSTree.h
 * Author: default
 *
 * Created on September 27, 2019, 2:17 PM
 */

#ifndef CBSTREE_H
#define CBSTREE_H

#include <stdlib.h>


#ifdef __cplusplus
extern "C" {
#endif

    struct CBSTNode {
        int data;
        CBSTNode* left;
        CBSTNode* right;
    };
    
    struct CBSTNode* insertCBST(struct CBSTNode* node, int element) {
        CBSTNode* temp = nullptr;
        if(node == nullptr) {
            temp = (struct CBSTNode*)malloc(sizeof(struct CBSTNode));
            temp->data = element;
            temp->left = temp->right = nullptr;
            return temp;
        }
        
        if(element > node->data) {
            node->right = insertCBST(node->right, element);
        }
        else {
            node->left = insertCBST(node->left, element);
        }
        
        return node;
    }

#ifdef __cplusplus
}
#endif

#endif /* CBSTREE_H */

