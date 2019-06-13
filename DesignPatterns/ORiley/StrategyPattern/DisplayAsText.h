/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   DisplayAsText.h
 * Author: default
 *
 * Created on June 13, 2019, 2:05 PM
 */

#ifndef DISPLAYASTEXT_H
#define DISPLAYASTEXT_H

#include "IDisplayStrategy.h"


class DisplayAsText : public IDisplayStrategy {
public:
    DisplayAsText();
    virtual ~DisplayAsText();
    
    void display() override;

private:

};

#endif /* DISPLAYASTEXT_H */

