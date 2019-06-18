/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   LightOffCommand.h
 * Author: default
 *
 * Created on June 18, 2019, 12:51 PM
 */

#ifndef LIGHTOFFCOMMAND_H
#define LIGHTOFFCOMMAND_H

#include "Light.h"
#include "ICommand.h"


class LightOffCommand : public ICommand {
    Light light;
public:
    LightOffCommand(const Light& l);
    virtual ~LightOffCommand();
    
    void execute() override;
    void unexecute() override;

private:    

};

#endif /* LIGHTOFFCOMMAND_H */

