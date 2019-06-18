/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   LightOffCommand.cpp
 * Author: default
 * 
 * Created on June 18, 2019, 12:51 PM
 */

#include "LightOffCommand.h"

LightOffCommand::LightOffCommand(const Light& l)
    : light{l} {
}

LightOffCommand::~LightOffCommand() {
}

void LightOffCommand::execute() {
    light.off();
}

void LightOffCommand::unexecute() {
    light.on();
}
