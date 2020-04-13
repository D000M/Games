/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   TestStack.h
 * Author: default
 *
 * Created on August 8, 2019, 3:29 PM
 */

#ifndef TESTSTACK_H
#define TESTSTACK_H

#include <iostream>
#include <stack>
#include <cstring>
#include <complex>

#include "Stack.h"


void testStack() {
    Stack stack;
    stack.push(10);
    stack.push(20);
    stack.push(30);
    stack.push(40);
    
    std::cout << stack.pop() << std::endl;
    std::cout << stack.pop() << std::endl;
    std::cout << stack.pop() << std::endl;
    std::cout << stack.pop() << std::endl;
}


void testParanthesis() {
    std::stack<char> myStack;
    
    std::string sentence = "{([a+b)*[c+d]]/c}";
    
    bool isMatching = true;
    
    for(int i = 0; i < sentence.length(); i++) {
        if(sentence.at(i) == '{') {
            myStack.push('{');
        }
        else if(sentence.at(i) == '[') {
            myStack.push('[');
        }
        else if(sentence.at(i) == '(') {
            myStack.push('(');
        }
        else if(sentence.at(i) == '}') {
            char c = myStack.top();
            myStack.pop();
            if(c != '{') {
                isMatching = false;
                break;
            }
        }
        else if(sentence.at(i) == ']') {
            char c = myStack.top();
            myStack.pop();
            if(c != '[') {
                isMatching = false;
                break;
            }
        }
        else if(sentence.at(i) == ')') {
            char c = myStack.top();
            myStack.pop();
            if(c != '(') {
                isMatching = false;
                break;
            }
        }
    }
    if(myStack.empty() && isMatching) {
        std::cout << "Paranthesis are ok!\n";
    }
    else {
        std::cout << "Paranthesis are not Ok!\n";
    }
}


bool isOperand(char c) {
    if(c == '+' || c == '-' || c == '*' || c == '/' || c == '(' || c == ')' || c == '^') {
        return false;
    }
    else {
        return true;
    }
}

int precadence(char c){
    if(c == '+' || c == '-') {
        return 1;
    }
    else if(c == '*' || c == '/') {
        return 2;
    }
    return 0;
}

char* convertToPostFix(const char* infix) {
    std::stack<char> myStack;
    char* postfix = new char[strlen(infix) + 1];
    
    int i = 0, j = 0;
    
    while(infix[i] != '\0') {
        if(isOperand(infix[i])) {
            postfix[j++] = infix[i++];
        }
        else {
            if(myStack.empty() || (precadence(infix[i]) > precadence(myStack.top()))) {
                myStack.push(infix[i++]);
            }
            else {
                postfix[j++] = myStack.top();
                myStack.pop();
            }
        }
    }
    while(!myStack.empty()) {
        postfix[j++] = myStack.top();
        myStack.pop();
    }
    postfix[j] = '\0';
    return postfix;
}

void testConvertToPostfix() {
    const char* infixArr = "a+b*c-d/e";
    
    char* postFix = convertToPostFix(infixArr);

    std::cout << postFix;

    std::cout << std::endl;
    delete [] postFix;
}


///Complete postfix
int outStack(char c) {
    if(c == '+' || c == '-') {
        return 1;
    }
    else if(c == '*' || c == '/') {
        return 3;
    }
    else if(c == '^') {
        return 6;
    }
    else if(c == '(') {
        return 7;
    }
    return 0;   // ')'
}
int inStack(char c) {
    if(c == '+' || c == '-') {
        return 2;
    }
    else if(c == '*' || c == '/') {
        return 4;
    }
    else if(c == '^') {
        return 5;
    }
    else if(c == '(') {
        return 0;
    }
    return 0;   // ')'
}

char* convertToPostfixV2(const char* infix) {
    std::stack<char> myStack;
    char* postfix = new char[strlen(infix) + 1];
    
    int i = 0, j = 0;
    
    while(infix[i] != '\0') {
        if(isOperand(infix[i])) {
            postfix[j++] = infix[i++];
        }
        else {
            if(myStack.empty() || outStack(infix[i]) > inStack(myStack.top())) {
                myStack.push(infix[i++]);
            }
            else {
                if( outStack(infix[i]) == 0 && ( outStack(infix[i]) == inStack( myStack.top() ) ) ) {
                    myStack.pop();
                    i++;
                }
                else {
                    postfix[j++] = myStack.top();
                    myStack.pop();
                }
            }
        }
    }
    
    while(!myStack.empty()) {
        postfix[j++] = myStack.top();
        myStack.pop();
    }
    postfix[j] = '\0';
    return postfix;
}

int convertToNum(char c) {
    switch(c) {
        case 48:
            return 0;
        case 49:
            return 1;
        case 50:
            return 2;
        case 51:
            return 3;
        case 52:
            return 4;
        case 53:
            return 5;
        case 54:
            return 6;
        case 55:
            return 7;
        case 56:
            return 8;
        case 57:
            return 9;
    }
}

int evalPostfix(const char* postfix) {
    std::stack<int> myStack;

    for(int i = 0; postfix[i] != '\0'; i++) {
        if(isOperand(postfix[i])) {
            int c = postfix[i] - '0';
            myStack.push(c);
        } 
        else {
            int b = myStack.top();
            myStack.pop();
            int a = myStack.top();
            myStack.pop();
            char op = postfix[i];
            int result = 0;
            switch(op) {
                case '+':
                    result = a + b;
                    break;
                case '-':
                    result = a - b;
                    break;
                case '*':
                    result = a * b;
                    break;
                case '/':
                    result = a / b;
                    break;
                case '^':
                    result = std::pow(a, b);
                    break;
                default:break;
            }
            myStack.push(result);
        }
    }
    int result = myStack.top();
    myStack.pop();
    return result;
    
}
void testEvalPostfix() {
    const char* postfix = "35*62/+4-";
    std::cout << evalPostfix(postfix) << std::endl;
}
void testCompletePostfix() {
    const char* infix = "a+b*c-d^e^f";
    
    char* postfix = convertToPostfixV2(infix);
    std::cout << postfix << std::endl;
    
    delete [] postfix;
}
#endif /* TESTSTACK_H */

