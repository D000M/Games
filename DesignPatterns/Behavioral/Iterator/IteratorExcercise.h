/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   IteratorExcercise.h
 * Author: default
 *
 * Created on May 17, 2019, 3:50 PM
 */

#ifndef ITERATOREXCERCISE_H
#define ITERATOREXCERCISE_H

#include <vector>
#include <iostream>
#include <string>
#include <stack>

namespace IteratorEx {
    template<typename T>
    struct Node {
        T value;
        Node* left{nullptr};
        Node* right{nullptr};
        Node* parent{nullptr};
        
        Node(T value) : value(value) {
        }
        
        Node(T value, Node<T>* left, Node<T>* right) : value(value), left(left), right(right) {
            left->parent = right->parent = this;
        }
        
        ~Node() {
            if(left) {
                delete left;
            }
            if(right) {
                delete right;
            }
            std::cout << "Node Destryoed\n";
        }
        // traverse the node and its children preorder
        // and put all the results into `result`
        void preorder_traversal(std::vector<Node<T>*>& result) {
            std::stack<Node<T>*> s;
            s.push(this);
            while(!s.empty()) {
                Node<T>* temp = s.top();
                s.pop();
                
                if(temp->right){
                    s.push(temp->right);
                }
                if(temp->left) {
                    s.push(temp->left);
                }
                
                result.push_back(temp);
            }
        }
    };
    
    //        a
    //      /   \
    //     b     e
    //    / \     \
    //   c   d     f
    //            / \
    
    void testIteratorEx() {
        Node<std::string> first{"a", 
                new Node<std::string>{"b", new Node<std::string>{"c"}, new Node<std::string>{"d"}
        }, new Node<std::string>{"e", new Node<std::string>{"f"}, new Node<std::string>{"g"}} 
            };

        std::vector<Node<std::string>*> result;
        first.preorder_traversal(result);
//        first.preorder_traversal(result);
        
        for(auto& elem : result) {
            std::cout << elem->value << std::endl;
        }
    }
}

#endif /* ITERATOREXCERCISE_H */

