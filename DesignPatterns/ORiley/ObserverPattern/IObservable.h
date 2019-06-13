/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   IObservable.h
 * Author: default
 *
 * Created on June 13, 2019, 3:54 PM
 */

#ifndef IOBSERVABLE_H
#define IOBSERVABLE_H

#include "IObserver.h"

class IObservable {
public:
    virtual void add(IObserver*) = 0;
    virtual void remove(IObserver*) = 0;
    virtual void notify() = 0;
};

#endif /* IOBSERVABLE_H */

