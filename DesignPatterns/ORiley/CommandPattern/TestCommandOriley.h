/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   TestCommandOriley.h
 * Author: default
 *
 * Created on June 18, 2019, 12:48 PM
 */

#ifndef TESTCOMMANDORILEY_H
#define TESTCOMMANDORILEY_H

#include "Light.h"
#include "LightOnCommand.h"
#include "LightOffCommand.h"
#include "Invoker.h"



void testCommandOriley() {
    Light light;
    LightOnCommand onCommand{light};
    LightOffCommand offCommand{light};
    
    Invoker invoker;
    invoker.setCommand(&onCommand);
    invoker.clickOn();
    
}

#endif /* TESTCOMMANDORILEY_H */

