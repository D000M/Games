/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Adapter.cpp
 * Author: default
 * 
 * Created on June 18, 2019, 2:52 PM
 */

#include "Adapter.h"

Adapter::Adapter() 
    : adaptee{} {
    
}

Adapter::~Adapter() {
}

void Adapter::request() {
    adaptee.specificRequest();
}
