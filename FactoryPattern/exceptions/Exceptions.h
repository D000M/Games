/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Exceptions.h
 * Author: default
 *
 * Created on March 26, 2019, 1:39 PM
 */

#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H

#include <exception>
#include <string>



class MyException : public std::exception {
    std::string errorMsg;
    public:
        //We can override constructor
        MyException(const std::string& msg) : errorMsg{msg} {}
        
        
        //We can override what method
        const char* what() const noexcept override {
            return errorMsg.c_str();
        }

};

//example for throw on function
int divide(int a, int b) throw (MyException) {
    if(b == 0) {
        throw MyException("Division by Zero 2");
    }
    return a / b;
}

void testException() {
    int x = 5; int y = 0;
    try {
        int res = divide(x, y);
        std::cout << res << std::endl;
    }
    catch(MyException& e) {
        std::cout << e.what() << std::endl;
    }
    
}
#endif /* EXCEPTIONS_H */

