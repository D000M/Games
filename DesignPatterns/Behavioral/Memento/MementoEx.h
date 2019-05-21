/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   MementoEx.h
 * Author: default
 *
 * Created on May 20, 2019, 4:31 PM
 */

#ifndef MEMENTOEX_H
#define MEMENTOEX_H

#include <vector>
#include <memory>
#include <iostream>

namespace MementoEx {
    
    
    /**

Memento Coding Exercise

        A TokenMachine  is in charge of keeping tokens. Each Token  is a reference type with a single numerical value. 
     * The machine supports adding tokens and, when it does, 
     * it returns a memento representing the state of that system at that given time.

        You are asked to fill in the gaps and implement the Memento design pattern for this scenario. 
     *  Pay close attention to the situation where a token is fed in as a smart pointer 
     *  and its value is subsequently changed on that pointer 
     * - you still need to return the correct system snapshot!
     */
    
    struct Token {
        int value;
        static int tokens;
        Token(int val) : value{val} {
            std::cout <<"Tokens created: " << ++tokens << std::endl;
        }
        ~Token() {
            std::cout << "Token Destroyed!" << tokens-- <<"\n";
        }
    };
    int Token::tokens = 0;
    struct Memento {
        Memento(const std::vector<std::shared_ptr<Token>> t){
            for(auto& elem : t) {
                tokens.emplace_back(new Token{elem->value});
            }
        }
        std::vector<std::shared_ptr<Token>> tokens;
    };
    
    struct TokenMachine {
        std::vector<std::shared_ptr<Token>> tokens;

        Memento addToken(int value) {
            return addToken(std::make_shared<Token>(value));
        }
        
        // adds the token to the set of tokens and returns the
        // snapshot of the entire system
        Memento addToken(const std::shared_ptr<Token>& token) {
            tokens.push_back(token);
            return {tokens};
        }
        
        // reverts the system to a state represented by the token
        void revert(const Memento& m) {
            tokens = m.tokens;
        }
        friend std::ostream& operator<<(std::ostream& os, const TokenMachine& obj) {
            // Write obj to stream
            for(auto& elem : obj.tokens) {
                os << elem->value << " ";
            }
            return os;
        }

    };
    
    void testTokenMachine() {
        TokenMachine tm;
        auto st1 = tm.addToken(10);
        std::cout << tm << std::endl;
        
        auto st2 = tm.addToken(20);
        std::cout << tm << std::endl;
        
        auto st3 = tm.addToken(30);
        std::cout << tm << std::endl;
        
        auto st4 = tm.addToken(40);
        std::cout << tm << std::endl;
        
        tm.revert(st2);
        std::cout << tm << std::endl;
        
        tm.tokens[0]->value = 50;
        std::cout << tm << std::endl;
        
        tm.revert(st4);
        std::cout << tm << std::endl;
        
        tm.revert(st1);
        std::cout << tm << std::endl;
        
        tm.tokens[0]->value = 90;
        std::cout << tm << std::endl;
        tm.revert(st4);
        std::cout << tm << std::endl;
    }
}


#endif /* MEMENTOEX_H */

