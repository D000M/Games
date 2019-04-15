/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: default
 *
 * Created on April 10, 2019, 3:34 PM
 */

#include <cstdlib>

#include "SOLID/SingleResponsibilityPrinciple.h"
#include "SOLID/OpenClosedPrinciple.h"
#include "SOLID/MySingleResponsibilityPrinciple.h"
#include "SOLID/MyOpenClosedPrinciple.h"
#include "SOLID/LiskovSubstititution/LiskovExample.h"
#include "SOLID/DependancyInversion/DependancyInversion.h"
#include "Creational/Builder/LifeWithoutBuilder.h"
#include "Creational/Builder/Builder.h"
#include "Creational/Builder/ComplicateBuilder/TestCompleteProgram.h"
#include "Creational/Builder/ComplicateBuilder/BuilderExcercise.h"
#include "Creational/Builder/VechicleBuilder/TestVechicle.h"
#include "Creational/Factory/FactoryMethod.h"
#include "Creational/Factory/Factory.h"
#include "Creational/Factory/InnerFactory.h"
#include "Creational/Factory/AbstractFactory/AbstractFactory.h"
#include "Creational/Factory/AbstractFactory/FactoryExcercise.h"
#include "Creational/Factory/AbstractFactory/MyAbstractFactory/MyAbstractFactory.h"
#include "Creational/Prototype/RecordKeeping/RecordKeeping.h"
#include "Creational/Prototype/Prototype/Prototype.h"
#include "Creational/Prototype/PrototypeFactory/PrototypeFactory.h"
#include "Creational/Prototype/PrototypeViaSerialization/Serialization.h"
#include "Creational/Prototype/Excercise/PrototypeExcercise.h"


/**
 

 
 */
using namespace std;

/*
 * 
 */
int main(int argc, char** argv) {
    
    PrototypeExcercise::testDeepCopyLine();
    
    return 0;
}

