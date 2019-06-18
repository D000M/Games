/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   ICommand.h
 * Author: default
 *
 * Created on June 18, 2019, 12:43 PM
 */

#ifndef ICOMMAND_H
#define ICOMMAND_H

class ICommand {
public:
    virtual void execute() = 0;
    virtual void unexecute() = 0;
};

#endif /* ICOMMAND_H */

