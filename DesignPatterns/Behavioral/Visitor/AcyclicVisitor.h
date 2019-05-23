/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   AcyclicVisitor.h
 * Author: default
 *
 * Created on May 23, 2019, 2:42 PM
 */

#ifndef ACYCLICVISITOR_H
#define ACYCLICVISITOR_H
#include <iostream>
#include <string>
#include <sstream>
/**
 * Not Pattern from Gang of Four
 * Run-type time information (RTTI) type of visitor
 */
namespace AcyclicVisitor {
    
    template<typename Visitable>
    struct Visitor {
        virtual void visit(Visitable& obj) = 0;
    };
    
    //Marker Interface 
    //We cant leave it empty so we need to add something just vtables to be constructed.
    struct VisitorBase {
        virtual ~VisitorBase() = default;
    }; 
    
    struct Expression4 {
        virtual ~Expression4() = default;
        
        // We have to be sure that this obj is of type visitor of particular type T Visitor<T> in our case Visitor<Expression4>
        virtual void accept(VisitorBase& obj) {
            using EV = Visitor<Expression4>;
            if(auto ev = dynamic_cast<EV*>(&obj)) {
                ev->visit(*this);   //call visit with a reference to ourself
            }
        }
    }; //End Expression4
    
    struct DoubleExpression4 : Expression4 {
        double value;
        DoubleExpression4(double value)
            : value(value) {
        }

        // We have to be sure that this obj is of type visitor of particular type T Visitor<T> in our case Visitor<DoubleExpression4>
        virtual void accept(VisitorBase& obj) {
            using DEV = Visitor<DoubleExpression4>;
            if(auto ev = dynamic_cast<DEV*>(&obj)) {
                ev->visit(*this);   //call visit with a reference to ourself
            }
        }
    }; //End DoubleExpression4
    
    struct AdditionExpression4 : Expression4 {
        
        Expression4* left, *right;
        AdditionExpression4(Expression4* left, Expression4* right)
            : left(left), right(right) {
        }
        ~AdditionExpression4() {
            delete left;
            delete right;
        }
        // We have to be sure that this obj is of type visitor of particular type T Visitor<T> in our case Visitor<AdditionExpression4>
        virtual void accept(VisitorBase& obj) {
            using AEV = Visitor<AdditionExpression4>;
            if(auto ev = dynamic_cast<AEV*>(&obj)) {
                ev->visit(*this);   //call visit with a reference to ourself
            }
        }
    };
    //Implement the marker interface,
    //The marker interface allows us to warm our way into every single accept(VisitorBase&) method
    //We can now remove some of the Visitors and the program will continue to work.
    struct ExpressionPrinter4 : VisitorBase,
                                //Visitor<DoubleExpression4>,   //Uncomment or comment for test
                                Visitor<AdditionExpression4> {
        
//        void visit(DoubleExpression4& obj) override {     //Uncomment or comment for test
//            oss << obj.value;
//        }
        
        void visit(AdditionExpression4& obj) override {
            oss << "(";
            obj.left->accept(*this);
            oss << "+";
            obj.right->accept(*this);
            oss << ")";
        }
        
        std::string str() const {
            return oss.str();
        }
    private:
        std::ostringstream oss;
    };
    
    void testAcyclicVisitor() {
        auto e = new AdditionExpression4{
            new DoubleExpression4{1},
            new AdditionExpression4{
                new DoubleExpression4{2},
                new DoubleExpression4{3}
            }
        };
        
        ExpressionPrinter4 ep;
        ep.visit(*e);
        std::cout << ep.str() << std::endl;
    }
}

#endif /* ACYCLICVISITOR_H */

