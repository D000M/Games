/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   InterpreterExcercise.h
 * Author: default
 *
 * Created on May 16, 2019, 1:06 PM
 */

#ifndef INTERPRETEREXCERCISE_H
#define INTERPRETEREXCERCISE_H

#include <string>
#include <map>
#include <iosfwd>
#include <iostream>
#include <locale>
#include <boost/lexical_cast.hpp>
#include <sstream>

/**

You are asked to write an expression processor for simple numeric expressions with the following constraints:

    Expressions use integral values (e.g., "13" ), single-letter variables defined in variables , as well as + and - operators only
    There is no need to support braces or any other operations
    If a variable is not found in Variables  (or if we encounter a variable with >1 letter, e.g. ab), the evaluator returns 0 (zero)
    In case of any parsing failure, evaluator returns 0

Example:

    calculate("1+2+3")  should return 6
    calculate("1+2+xy")  should return 0
    calculate("10-2-x")  when x=3 is in variables should return 5
 */

namespace InterpreterEx {
    
    struct ExpressionProcessor {
        
        enum Type { integer, letter, plus, minus } type;
        std::map<char, int> variables;
        
        void loadMap() {
            variables['+'] = Type::plus;
            variables['-'] = Type::minus;
            variables['0'] = Type::integer;
            variables['x'] = Type::letter;
        }
        
        int calculate(const std::string& expression) {
            
            int result{0};
            bool hasLeft{false};
            int number{0};
            
            for(int i = 0; i < expression.length(); i++) {
                std::ostringstream buffer;
                
                if(isdigit(expression[i])) {
                    buffer << expression[i];
                    for(int j = i + 1; j < expression.size(); ++j) {
                        if(isdigit(expression[j])) {
                            buffer << expression[j];
                            i++;
                        }
                        else {
                            number = stoi(buffer.str());
//                            type = Type::integer;
                            if(!hasLeft) {
                                result = number;
                                hasLeft = true;
                            }
                            else {
                                switch(type) {
                                    case Type::plus:
                                        result += number;
                                        break;
                                    case Type::minus:
                                        result -= number;
                                        break;
                                }
                            }
                            break;
                        }
                    } //end for
                    if(i == expression.size() - 1) {
                        number = boost::lexical_cast<int>(buffer.str());
                        if(!hasLeft) {
                            result = number;
                        }
                        else {
                            switch(type) {
                                case Type::plus:
                                    result += number;
                                    break;
                                case Type::minus:
                                    result -= number;
                                    break;
                            }
                        }
                    }
                }
                else if(isalpha(expression[i])) {
                    buffer << expression[i];
                    for(int j = i + 1; j < expression.size(); ++j) {
                        if(isalpha(expression[j])) {
                            return 0;
                        }
                    } //end for
                    switch(type) {
                        case Type::plus:
                            result += atoi(buffer.str().c_str());
                            break;
                        case Type::minus:
                            result -= atoi(buffer.str().c_str());
                            break;
                    }
                }
                else if(expression[i] == '+') {
                    type = Type::plus;
                }
                else if(expression[i] == '-') {
                    type = Type::minus;
                }
                else {
                    return 0;
                }
            }
                
            return result;
        }
        
        friend std::ostream& operator<<(std::ostream& os, const ExpressionProcessor& obj) {
            // Write obj to stream
            for(auto it = obj.variables.cbegin(); it != obj.variables.cend(); ++it) {
                os << (int)it->first << ": " << it->second << std::endl;
            }
            return os;
        }

        
    };
    
    void testExpressionInterpreter() {
        ExpressionProcessor e;
        e.loadMap();
        std::cout << e.calculate("1+2+3+10") << std::endl;
    }
}


#endif /* INTERPRETEREXCERCISE_H */

