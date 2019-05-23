/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   ReflectiveVisitor.h
 * Author: default
 *
 * Created on May 23, 2019, 1:22 PM
 */

#ifndef REFLECTIVEVISITOR_H
#define REFLECTIVEVISITOR_H

#include <string>
#include <iostream>
#include <sstream>

namespace ReflectiveVisitor {
    
    struct Expression2 {
        virtual ~Expression2() = default;
    };
    
    struct DoubleExpression2 : Expression2 {
        double value;
        DoubleExpression2(double value)
            : value(value) {
        }

    };
    
    //Represent a tree of a type    of expression (1+(2+3))
    //          +       root
    //         / \
    //        1   +
    //           / \
    //          2   3
    struct AdditionExpression2 : Expression2 {
        Expression2* left, *right;
        AdditionExpression2(Expression2* left, Expression2* right)
         : left(left), right(right) {
        }
        
        ~AdditionExpression2() {
            delete left;
            delete right;
        }
    };
    
    struct ExpressionPrinter2  {
        std::ostringstream oss;
        
        //We now can dynamic_cast Expression2 and do nesessery stuff
        void print(Expression2* e) {
            if(DoubleExpression2* de = dynamic_cast<DoubleExpression2*>(e)) {
                oss << de->value;
            }
            else if(AdditionExpression2* ae = dynamic_cast<AdditionExpression2*>(e)) {
                oss << "(";
                print(ae->left);
                oss << "+";
                print(ae->right);
                oss << ")";
            }
        }
        
        std::string str() const {
            return oss.str();
        }
    };
    
    void testReflectiveExpression() {
        auto expr = new AdditionExpression2{
            new DoubleExpression2{1},
            new AdditionExpression2{
                new DoubleExpression2{2},
                new DoubleExpression2{3}
            }
        };

        ExpressionPrinter2 ep;
        ep.print(expr);
        std::cout << ep.str() << std::endl;
        delete expr;
    }
}

#endif /* REFLECTIVEVISITOR_H */

