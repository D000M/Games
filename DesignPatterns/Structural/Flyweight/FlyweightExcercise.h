/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   FlyweightExcercise.h
 * Author: default
 *
 * Created on May 14, 2019, 1:45 PM
 */

#ifndef FLYWEIGHTEXCERCISE_H
#define FLYWEIGHTEXCERCISE_H

#include <string>
#include <vector>
#include <algorithm>
#include <locale>
#include <iostream>

/**
You are given a class called Sentence , which takes a string such as "hello world". You need to provide an interface such that the indexer (operator [] ) returns a WordToken  that can be used to capitalize a particular word in the sentence.

Typical use would be something like:

    Sentence sentence("hello world");
    sentence[1].capitalize = true;
    cout << sentence.str(); // prints "hello WORLD"
 */
namespace FlyweightEx {
        
    struct Sentence {

        struct WordToken {
            bool capitalize;
            std::string word;
        };
//        std::string toUpper(std::string str) {
//            std::transform(str.begin(), str.end(), str.begin(), [](unsigned char c) {
//              return std::toupper(c);  
//            });
//            return str;
//        }
        
        Sentence(const std::string& plainText)
            : plainText(plainText) {
            //Todo
            std::string word = "";
            for(int i = 0; i < plainText.length(); i++) {
                if(plainText[i] == ' ') {
                    WordToken temp{false, word};
                    formatting.emplace_back(temp);
                    word = "";
                    continue;
                }
                word += plainText.at(i);
            }
            WordToken temp{false, word};
            formatting.emplace_back(temp);
        }
        WordToken& operator[](std::size_t index) {
            // Actual access to element
            return formatting.at(index);
        }
        std::string str() const {
            //Todo
            std::string result = "";
            for(int i = 0; i < formatting.size(); i++) {
                if(formatting.at(i).capitalize == true) {
                    //Lambda Function which returns std::string and take argument std::string
                    auto temp = [](std::string str)->std::string {
                        std::transform(str.begin(), str.end(), str.begin(), [](unsigned char c) {
                           return std::toupper(c); 
                        });
                        
                        return str;
                    };
                    result += temp(formatting.at(i).word) + " ";
                }
                else {
                    if(i == formatting.size() - 1) {
                        result += formatting.at(i).word;
                    }
                    else {
                        result += formatting.at(i).word + " ";
                    }
                }
            }
            return result;
        }
                
        std::string plainText;
        std::vector<WordToken> formatting;
        
    };
    
    void testFlyweightEx() {
//        std::string s{ "Psss SSssssSSS pppp "};
//        s = toUpper(s);
//        std::cout << s << std::endl;
        Sentence sentence{"alpha beta gamma"};
        sentence[1].capitalize = true;
        std::cout << sentence.str() << std::endl;
    }
}

#endif /* FLYWEIGHTEXCERCISE_H */

