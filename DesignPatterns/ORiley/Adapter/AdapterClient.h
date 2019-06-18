/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   AdapterClient.h
 * Author: default
 *
 * Created on June 18, 2019, 2:54 PM
 */

#ifndef ADAPTERCLIENT_H
#define ADAPTERCLIENT_H

#include "IAdapter.h"


class AdapterClient {
    
public:
    IAdapter* adapter;
    AdapterClient(IAdapter* a);
    virtual ~AdapterClient();
private:

};

#endif /* ADAPTERCLIENT_H */

