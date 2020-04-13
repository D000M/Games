/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "ObjectCounter.h"

ObjectCounter::CleanupCheck ObjectCounter::verifier;
int ObjectCounter::count = 0;

void testObjectCounterExample() {
    TestObjectCounter t1;
    TestObjectCounter t2;
    TestObjectCounter t3;
    TestObjectCounter t4;
    
}