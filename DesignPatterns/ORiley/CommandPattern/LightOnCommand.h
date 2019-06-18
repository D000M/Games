/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   LightOnCommand.h
 * Author: default
 *
 * Created on June 18, 2019, 12:44 PM
 */

#ifndef LIGHTONCOMMAND_H
#define LIGHTONCOMMAND_H

#include "ICommand.h"
#include "Light.h"

class LightOnCommand : public ICommand {
    Light light;
public:
    LightOnCommand(const Light& l);
    virtual ~LightOnCommand();
    
    void execute() override;
    void unexecute() override;

private:

};

#endif /* LIGHTONCOMMAND_H */

