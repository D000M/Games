/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   FunctionalDecorator.h
 * Author: default
 *
 * Created on May 13, 2019, 11:03 AM
 */

#ifndef FUNCTIONALDECORATOR_H
#define FUNCTIONALDECORATOR_H

#include <functional>
#include <iostream>


namespace FunctionalDecorator {
    
    struct Logger {
        std::function<void()> myFunc;
        std::string name;
        
        Logger(const std::function<void()>& func, const std::string& name)
                    : myFunc{func}, name{name} {}
                    
        void operator()() {
            std::cout << "Entering Function: " << name << std::endl;
            myFunc();
            std::cout << "Exiting Function: " << name << std::endl;
        }
    };
    
    void testSimpleLogger() {
        Logger([](){std::cout << "Hello" << std::endl;}, "HelloFunction")();
        
        Logger obj2([](){std::cout << "Other" << std::endl;}, "OtherFunction");
        obj2();
    }
    
    ///////////////
    template<typename Func>
    struct Logger2 {
        Func myFunc;
        std::string name;
        
        Logger2(const Func& func, const std::string& name)
                    : myFunc{func}, name{name} {}
                    
        void operator()() {
            std::cout << "Entering Function: " << name << std::endl;
            myFunc();
            std::cout << "Exiting Function: " << name << std::endl;
        }
    };
    //We need helper function for this logger2 to work
    template<typename Func>
    auto makeLogger2(Func func, const std::string& name) {
        return Logger2<Func>{func, name};
    }
    
    double add(double a, double b) {
        std::cout << a << " + " << b << " = " << (a + b) << std::endl;
        return a + b;
    }
    
    //We need partial specialization for next struct Logger3 to work.
    template<typename>
    struct Logger3;
    
    //R - return type, Args - arguments
    template<typename R, typename... Args>
    struct Logger3<R(Args...)> {
        //Function which return R with number of Arguments Args
        std::function<R(Args...)> myFunc;
        std::string name;
        Logger3(const std::function<R(Args...)>& func, const std::string& name)
            : myFunc{func}, name{name} {}
        
        R operator() (Args... args) {
            std::cout << "Entering: " << name << std::endl;
            R result = myFunc(args...);
            std::cout << "Exiting: " << name << std::endl;
            return result;
        }
    };
    
    //We need helper function to figuring the arguments
    /**
     * Utility function to avoid calling template arguments for Logger3
     * This function will do everything for us.
     * @param func  pointer to a function with return type R, and arguments Args.
     * @param name name of the function
     * @return template argument R
     */
    template<typename R, typename... Args> 
    auto makeLogger3(R (*func)(Args...), const std::string& name) {
        return Logger3<R(Args...)>(
            std::function<R(Args...)>(func),    //First Logger3 Param   - std::function<R(Args...)>(func) 
            name                                //Second Logger3 Param  - std::string name
        );
    }
    
    void testSimpleLogger2() {
        //Logger2([](){std::cout << "Logger 2" << std::endl;}, "Logger2");
        auto log = makeLogger2([](){std::cout << "Logger 2" << std::endl;}, "Logger2");
        log();
        auto loggedAdd = makeLogger3(add, "Add");
        auto result = loggedAdd(2, 3);        //Function call. loggedAdd is actualy Logger3 ojbect
        std::cout << "result = " << result << std::endl;
    }
}

#endif /* FUNCTIONALDECORATOR_H */

