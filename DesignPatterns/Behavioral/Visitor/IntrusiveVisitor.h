/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   IntrusiveVisitor.h
 * Author: default
 *
 * Created on May 23, 2019, 1:07 PM
 */

#ifndef INTRUSIVEVISITOR_H
#define INTRUSIVEVISITOR_H

#include <iosfwd>
#include <iostream>


/**
 * Not good approach cause we have to break open-closed principle.
 * And have to modify all classes in the hierarchy for added some new functionality.
 */



namespace IntrusiveVisitor {
    
    //      
    
    struct Expression {
        virtual ~Expression() = default;
        //our visitor method we must break open-closed principle and start modify every class in the herarhy for print method...
        virtual void print(std::ostringstream& oss) = 0;
    };
    
    struct DoubleExpression : Expression {
        double value;
        DoubleExpression(double value)
            : value(value) {
        }
        
        void print(std::ostringstream& oss) override {
            oss << value;
        }

    };
    
    //Represent a tree of a type    of expression (1+(2+3))
    //          +       root
    //         / \
    //        1   +
    //           / \
    //          2   3
    struct AdditionExpression : Expression {
        Expression* left, *right;
        AdditionExpression(Expression* left, Expression* right)
         : left(left), right(right) {
        }
        
        ~AdditionExpression() {
            delete left;
            delete right;
        }
        
        void print(std::ostringstream& oss) override {
            oss << "(";
            left->print(oss);
            oss << "+";
            right->print(oss);
            oss << ")";
        }


    };
    
    void testIntrusiveExpression() {
        auto expr = new AdditionExpression{
            new DoubleExpression{1},
            new AdditionExpression{
                new DoubleExpression{2},
                new DoubleExpression{3}
            }
        };
        
        //Expected print (1+(2+3))
        std::ostringstream oss;
        expr->print(oss);
        std::cout << oss.str() << std::endl;
        delete expr;
    }
    
}

#endif /* INTRUSIVEVISITOR_H */

