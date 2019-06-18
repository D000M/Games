/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   TestAdapterOreilly.h
 * Author: default
 *
 * Created on June 18, 2019, 2:56 PM
 */

#ifndef TESTADAPTEROREILLY_H
#define TESTADAPTEROREILLY_H

#include "AdapterClient.h"
#include "Adapter.h"


void testOreillyAdapter() {
    Adapter myAdapter;
    AdapterClient client{&myAdapter};
    client.adapter->request();
}

#endif /* TESTADAPTEROREILLY_H */

