/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Adapter.h
 * Author: default
 *
 * Created on June 18, 2019, 2:52 PM
 */

#ifndef ADAPTER_H
#define ADAPTER_H

#include "IAdapter.h"
#include "Adaptee.h"


class Adapter : public IAdapter {
    Adaptee adaptee;
public:
    Adapter();
    virtual ~Adapter();
    
    void request() override;    

private:

};

#endif /* ADAPTER_H */

