/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Invoker.h
 * Author: default
 *
 * Created on June 18, 2019, 12:52 PM
 */

#ifndef INVOKER_H
#define INVOKER_H

#include <list>
#include <stack>

#include "ICommand.h"


class Invoker {
    std::stack<ICommand*> commands;
public:
    Invoker();
    virtual ~Invoker();
    
    void setCommand(ICommand* command);
    void clickOn();
    void clickOff();
private:
    
};

#endif /* INVOKER_H */

