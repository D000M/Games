/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   AdapterClient.cpp
 * Author: default
 * 
 * Created on June 18, 2019, 2:54 PM
 */

#include "AdapterClient.h"
#include "Adapter.h"

AdapterClient::AdapterClient(IAdapter* s) {
    adapter = s;
}

AdapterClient::~AdapterClient() {
//    delete adapter;
}

