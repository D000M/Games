/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   BinaryTreeIterator.h
 * Author: default
 *
 * Created on May 17, 2019, 1:51 PM
 */

#ifndef BINARYTREEITERATOR_H
#define BINARYTREEITERATOR_H

#include <string>
#include <iostream>

namespace BTIterator {
    
    template<typename T>
    struct BinaryTree;

    template<typename T>
    struct Node {
        T value = T();

        Node<T> *left{nullptr};
        Node<T> *right{nullptr};
        Node<T> *parent{nullptr};
        BinaryTree<T> *tree{nullptr};
        
        
        Node(T value) : value(value) { }

        Node(T value, Node<T>* left, Node<T>* right)
            : value(value), left(left), right(right) {
            this->left->tree = this->right->tree = tree;
            this->left->parent = this->right->parent = this;
        }

        void setTree(BinaryTree<T>* t) {
            tree = t;
            if(left) {
                left->setTree(t);
            }
            if(right) {
                right->setTree(t);
            }
        }
        
        ~Node() {
            if(left) {
                delete left;
            }
            if(right) {
                delete right;
            }
        }

    };  //End Node
    
    template<typename T>
    struct BinaryTree {
        
        Node<T>* root{nullptr};
        BinaryTree(Node<T>* root) : root(root), preOrder{*this} {
            root->setTree(this);
        }

        ~BinaryTree() {
            if(root) {
                delete root;
            }
        }
        
        template<typename U>
        struct PreOrderIterator {
            Node<U>* current;
            
            PreOrderIterator(Node<U>* current) : current(current) {}
            
            bool operator != (const PreOrderIterator<U>& other) {
                return current != other.current;
            }

            // no recursion! Monstrosity
            PreOrderIterator<U>& operator ++ () {
                if(current->right) {
                    current = current->right;
                    while(current->left) {
                        current = current->left;
                    }
                }
                else {
                    Node<T>* p = current->parent;
                    while(p && current == p->right) {
                        current = p;
                        p = p->parent;
                    }
                    current = p;
                }
                return *this;
            }
            
            Node<U>& operator * () {
                return *current;
            }
            
        };  //End PreOrderIterator
        
        typedef PreOrderIterator<T> iterator;
        
        iterator begin() {
            Node<T>* n = root;
            if(n) {
                while(n->left) {
                    n = n->left;
                }
            }
            return iterator{ n };
        }
        
        iterator end() {
            return iterator{ nullptr };
        }
        
        //Other types of iterators 
        class PreOrderTraversal {
            BinaryTree& tree;
        public:
            PreOrderTraversal(BinaryTree& tree) : tree(tree) {}
            
            iterator begin() { return tree.begin(); }
            iterator end() { return tree.end(); }
        } preOrder;
        
        
        
        
    };  //End BinaryTree
    
    
    void testBinaryTree() {
        //Family tree
        //      me
        //    /    \
        //  mother father
        //  /    \
        // m'm   m'f
        BinaryTree<std::string> family {
            new Node<std::string>{"me",
                        new Node<std::string>{"Mother",
                                        new Node<std::string>{"mother's mother"}, 
                                        new Node<std::string>{"mother's father"}
                                },
                        new Node<std::string>{"Father"}
                    }
        };

        for(auto it = family.begin();  it != family.end(); ++it) {
            std::cout << (*it).value << std::endl;
        }
        
        std::cout << "PReORDER\n";
        for(const auto& it : family.preOrder) {
            std::cout << it.value << std::endl;
        }
        
        std::cout << "Recursive call\n";
    }
}

#endif /* BINARYTREEITERATOR_H */

