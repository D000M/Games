/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Invoker.cpp
 * Author: default
 * 
 * Created on June 18, 2019, 12:52 PM
 */

#include "Invoker.h"

Invoker::Invoker() {
}

Invoker::~Invoker() {
}

void Invoker::setCommand(ICommand* command) {
    commands.push(command);
}

void Invoker::clickOn() {
    commands.top()->execute();
    commands.pop();
}

void Invoker::clickOff() {
    commands.top()->unexecute();
    commands.pop();
}
