/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   HandmadeInterpeter.h
 * Author: default
 *
 * Created on May 16, 2019, 10:19 AM
 */

#ifndef HANDMADEINTERPETER_H
#define HANDMADEINTERPETER_H

#include <string>
#include <vector>
#include <iosfwd>
#include <iostream>
#include <memory>
#include <boost/lexical_cast.hpp>

namespace Lexing {
    
    struct Token {
        enum Type { integer, plus, minus, lparent, rparent } type;
        std::string text;
        explicit Token(const Type& type, const std::string& text)
            : type(type), text(text) {
        }
        
        friend std::ostream& operator<<(std::ostream& os, const Token& obj) {
            // Write obj to stream
            os << "'" << obj.text << "'";  
            return os;
        }
    };
    
    //Lexing Process
    std::vector<Token> lex(const std::string& input) {
        std::vector<Token> result;
        
        for(int i = 0; i < input.size(); ++i) {
            switch(input[i]){
                case '+':
                    result.push_back(Token{Token::Type::plus, "+"});
                    break;
                case '-':
                    result.push_back(Token{Token::Type::minus, "-"});
                    break;
                case '(':
                    result.push_back(Token{Token::Type::lparent, "("});
                    break;
                case ')':
                    result.push_back(Token{Token::Type::rparent, ")"});
                    break;
                default:    //its integer
                    std::ostringstream buffer;
                    buffer << input[i];
                    for(int j = i + 1; j < input.size(); ++j) {
                        if(isdigit(input[j])) {
                            buffer << input[j];
                            i++;
                        }
                        else {
                            result.push_back(Token{Token::Type::integer, buffer.str()});
                            break;
                        }
                    } //end for
            } //end switch
        }
        return result;
    }
    void testLexing() {
        std::string input{"(13-4)-(12+1)"};
        
        auto tokens = lex(input);
        for(auto& t : tokens) {
            std::cout << t << " ";
        }
        std::cout << std::endl;
    }
}

namespace Parsing {
    
    struct Element {
        virtual int eval() const = 0;
    };
    
    struct Integer : Element {
        int value;
        Integer(int value)
            : value(value) {
        }

        int eval() const override {
            return value;
        }
    };
    
    struct BinaryOperation : Element {
        enum Type { addition, subtraction } type;
        std::shared_ptr<Element> lhs, rhs;
        
        int eval() const override {
            auto left = lhs->eval();
            auto right = rhs->eval();
            
            if(type == addition) {
                return left + right;
            }
            else {
                return left - right;
            }
        }
    };
    
    std::shared_ptr<Element> parse(const std::vector<Lexing::Token>& tokens) {
        auto result = std::make_unique<BinaryOperation>();
        bool haveLhs{false};
        
        for(int i = 0; i < tokens.size(); ++i) {
            auto& token = tokens.at(i);
            switch(token.type) {
                case Lexing::Token::integer: 
                {
                    int value = boost::lexical_cast<int>(token.text);
                    auto integer = std::make_shared<Integer>(value);
                    if(!haveLhs) {
                        result->lhs = integer;
                        haveLhs = true;
                    }
                    else {
                        result->rhs = integer;
                    }
                }
                    break;
                case Lexing::Token::plus:
                    result->type = BinaryOperation::addition;
                    break;
                case Lexing::Token::minus:
                    result->type = BinaryOperation::subtraction;
                    break;
                case Lexing::Token::lparent:
                {
                    int j = i;
                    for( ; j < tokens.size(); j++) {
                        if(tokens[j].type == Lexing::Token::rparent) {
                            break;
                        }
                    }
                    std::vector<Lexing::Token> subexpression(&tokens[i + 1], &tokens[j]);
                    auto element = parse(subexpression);
                    
                    if(!haveLhs) {
                        result->lhs = element;
                        haveLhs = true;
                    }
                    else {
                        result->rhs = element;
                    }
                    i = j;
                }
                    break;
            }
        }
        return result;
    }
    
    void testParsing() {
        std::string input{"(13-4)-(12+1)"};
        
        auto tokens = Lexing::lex(input);
        for(auto& t : tokens) {
            std::cout << t << " ";
        }
        std::cout << std::endl;
        
        try {
            auto parsed = parse(tokens);
            std::cout << input << " = " << parsed->eval() << std::endl;
        }
        catch(const std::exception& e) {
            std::cout << e.what() << std::endl;
        }
    }
}

#endif /* HANDMADEINTERPETER_H */

