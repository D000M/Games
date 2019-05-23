/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   ClassicVisitor.h
 * Author: default
 *
 * Created on May 23, 2019, 1:40 PM
 */

#ifndef CLASSICVISITOR_H
#define CLASSICVISITOR_H

#include <iosfwd>
#include <iostream>


namespace ClassicVisitor {
        
    struct DoubleExpression3;
    struct AdditionExpression3;
    struct SubstractionExpression3;
    
    struct ExpressionVisitor3 {
        std::ostringstream oss;
        //For every single element in the hierarchy
        virtual void visit(DoubleExpression3* de) = 0; 
        virtual void visit(AdditionExpression3* ae) = 0;
        virtual void visit(SubstractionExpression3* se) = 0;
        
        std::string str() const {
            return oss.str();
        }
    };
    
    struct ExpressionPrinter3 : ExpressionVisitor3 {
        void visit(AdditionExpression3* ae) override;
        void visit(DoubleExpression3* de) override;
        void visit(SubstractionExpression3* se) override;
    };
    
    struct ExpressionEvaluator : ExpressionVisitor3 {
        double result;
        void visit(DoubleExpression3* de) override;
        void visit(AdditionExpression3* ae) override;
        void visit(SubstractionExpression3* se) override;
    };    
    
    struct Expression3 {
        virtual void accept(ExpressionVisitor3* visitor) = 0;
    };
    
    struct DoubleExpression3 : Expression3 {
        double value;
        DoubleExpression3(double value)
            : value(value) {
        }
        void accept(ExpressionVisitor3* visitor) override {
            visitor->visit(this);
        }
    };
    struct AdditionExpression3 : Expression3 {
        Expression3* left, *right;
        AdditionExpression3(Expression3* left, Expression3* right)
         : left(left), right(right) {
        }
        
        ~AdditionExpression3() {
            delete left;
            delete right;
        }
        void accept(ExpressionVisitor3* visitor) override {
            visitor->visit(this);
        }
    };
    struct SubstractionExpression3 : Expression3 {
        Expression3* left, *right;
        SubstractionExpression3(Expression3* left, Expression3* right)
         : left(left), right(right) {
        }
        
        ~SubstractionExpression3() {
            delete left;
            delete right;
        }
        void accept(ExpressionVisitor3* visitor) override {
            visitor->visit(this);
        }
    };
    
    void ExpressionPrinter3::visit(DoubleExpression3* de) {
        oss << de->value;
    }
    
    void ExpressionPrinter3::visit(AdditionExpression3* e)
    {
      bool need_braces = dynamic_cast<SubstractionExpression3*>(e->right);
      e->left->accept(this);
      oss << "+";
      if (need_braces) oss << "(";
      e->right->accept(this);
      if (need_braces) oss << ")";
    }

    void ExpressionPrinter3::visit(SubstractionExpression3* se)
    {
      bool need_braces = dynamic_cast<SubstractionExpression3*>(se->right);
      if (need_braces) oss << "(";
      se->left->accept(this);
      oss << "-";
      se->right->accept(this);
      if (need_braces) oss << ")";
    }
    
    void ExpressionEvaluator::visit(DoubleExpression3* de) {
        result = de->value;
    }
    
    void ExpressionEvaluator::visit(AdditionExpression3* ae) {
        ae->left->accept(this);
        auto temp = result;
        ae->right->accept(this);
        result += temp;
    }
    void ExpressionEvaluator::visit(SubstractionExpression3* se) {
        se->left->accept(this);
        auto temp = result;
        se->right->accept(this);
        result = temp - result;
    }
    
    void testClassicVisitor() {
        auto e = new AdditionExpression3{
            new DoubleExpression3{1},
            new SubstractionExpression3{
                new DoubleExpression3{2},
                new DoubleExpression3{3}
            }
        };
        
        ExpressionPrinter3 ep;
        ep.visit(e);
        
        ExpressionEvaluator ev;
        ev.visit(e);
        std::cout << ep.str() << " = " << ev.result << std::endl;
    }
}

#endif /* CLASSICVISITOR_H */

