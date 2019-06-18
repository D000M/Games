/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   LightOnCommand.cpp
 * Author: default
 * 
 * Created on June 18, 2019, 12:44 PM
 */

#include "LightOnCommand.h"

LightOnCommand::LightOnCommand(const Light& l) 
    : light{l} {
}

LightOnCommand::~LightOnCommand() {
}

void LightOnCommand::execute() {
    light.on();
}

void LightOnCommand::unexecute() {
    light.off();
}

