/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   VisitorEx.h
 * Author: default
 *
 * Created on May 27, 2019, 10:27 AM
 */

#ifndef VISITOREX_H
#define VISITOREX_H

#include <string>
#include <sstream>
#include <iostream>
using namespace std;


/**
Visitor Coding Exercise


 * You are asked to implement a double-dispatch visitor called ExpressionPrinter  
 * for printing different mathematical expressions. 
 * The range of expressions covers addition and multiplication - 
 * please put round brackets around addition but not around multiplication! 
 * Also, please avoid any blank spaces in output.

Example:

    Input: AdditionExpression{Literal{2}, Literal{3}}  -- btw, this is pseudocode, you cannot inline those references unfortunately
    Output: (2+3) 

Here is the corresponding unit test:

    Value v2{2};
    Value v3{3};
    AdditionExpression simple{v2,v3};
    ExpressionPrinter ep;
    ep.accept(simple);
    ASSERT_EQ("(2+3)", ep.str());
 */

namespace VisitorEx {
    
    struct AdditionExpression;
    struct MultiplicationExpression;
    struct Value;
    
    struct ExpressionVisitor {
        std::ostringstream oss;
        //accept methods here.
        virtual void visit(Value& v) = 0;   //
        virtual void visit(AdditionExpression& ae) = 0; //
        virtual void visit(MultiplicationExpression& me) = 0;   //
        
        string str() const {
            return oss.str();
        }
    };
    
    struct Expression {
        virtual void accept(ExpressionVisitor& ev) = 0;   
    };
    
    struct Value : Expression {
        int value;
        Value(int val) : value{val} {}
        
        void accept(ExpressionVisitor& ev) override {
            ev.visit(*this);  //
        }
    };
    
    struct AdditionExpression : Expression {
        Expression &lhs, &rhs;
        
        AdditionExpression(Expression& lhs, Expression& rhs)
            : lhs(lhs), rhs(rhs) {
        }
        
        void accept(ExpressionVisitor& ev) override {
            ev.visit(*this); //
        }

    };
    
    struct MultiplicationExpression : Expression {
        Expression &lhs, &rhs;
        
        MultiplicationExpression(Expression& lhs, Expression& rhs)
            : lhs(lhs), rhs(rhs) {
        }
        void accept(ExpressionVisitor& ev) override {
            ev.visit(*this);  //
        }
    };
    
    struct ExpressionPrinter : ExpressionVisitor {
        
        //Accept methods here.
        void visit(Value& v) override;  //
        void visit(AdditionExpression& ae) override;   //
        void visit(MultiplicationExpression& me) override;  //
        
        string str() const {
            return oss.str();
        }
    };
    void ExpressionPrinter::visit(Value& v) {  //
        oss << v.value;
    }
    void ExpressionPrinter::visit(AdditionExpression& ae) { //
        oss << "(";
        ae.lhs.accept(*this);
        oss << "+";
        ae.rhs.accept(*this);
        oss << ")";
    }
    void ExpressionPrinter::visit(MultiplicationExpression& me) { //
        me.lhs.accept(*this);
        oss << "*";
        me.rhs.accept(*this);
    }
    void testVisitorEx() {
        Value v2{2};
        Value v3{3};
        AdditionExpression simple{v2, v3};
        ExpressionPrinter exp;
        exp.visit(simple);  //
        cout << exp.str() << endl;
        
        MultiplicationExpression mult{v2, v3};
        exp.visit(mult);
        cout << exp.str() << endl;
    }
}

#endif /* VISITOREX_H */

