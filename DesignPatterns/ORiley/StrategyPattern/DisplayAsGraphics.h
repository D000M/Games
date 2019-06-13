/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   DisplayAsGraphics.h
 * Author: default
 *
 * Created on June 13, 2019, 2:06 PM
 */

#ifndef DISPLAYASGRAPHICS_H
#define DISPLAYASGRAPHICS_H

#include "IDisplayStrategy.h"


class DisplayAsGraphics : public IDisplayStrategy{
public:
    DisplayAsGraphics();
    virtual ~DisplayAsGraphics();
    
    void display() override;

private:

};

#endif /* DISPLAYASGRAPHICS_H */

