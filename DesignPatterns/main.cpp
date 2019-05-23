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
#include "Creational/Singleton/files/SingletonExcercise.h"
#include "Structural/Bridge/PimplIdiom/PimplIdiom.h"
//#include "Creational/Singleton/SingletonImplementation.h"
#include "Structural/Bridge/PimplIdiom/Person2.h"
#include "Structural/Bridge/PimplIdiom/SecondAttempt.h"
//#include "Structural/Bridge/BridgeImplementation/Bridge.h"
#include "Structural/Bridge/BridgeImplementation/BridgeExcercise.h"
#include "Structural/Composite/GeometricShapes.h"
#include "Structural/NeuralNetworks/NeuralNetwork.h"
#include "Structural/Composite/ArrayBackedProps.h"
#include "Structural/Decorator/DynamicDecorator.h"
#include "Structural/Decorator/FunctionalDecorator.h"
#include "Structural/Decorator/DecoratorExcercise.h"
#include "Structural/Flyweight/HandmadeFlyweight.h"
#include "Structural/Flyweight/TextFormating.h"
#include "Structural/Flyweight/FlyweightExcercise.h"
#include "Structural/Proxy/SmartPointers.h"
#include "Structural/Proxy/ProprtyProxy.h"
#include "Structural/Proxy/VirtualProxy.h"
#include "Structural/Proxy/ProxyExcercise.h"
#include "Behavioral/ChainOfResponsibility/PointerChain.h"
#include "Behavioral/BrokerChain/BrokerChain.h"
#include "Behavioral/BrokerChain/BrokerEx.h"
#include "Behavioral/Command/Command.h"
#include "Behavioral/Command/CompositeCommand.h"
#include "Behavioral/Command/CommandEx.h"
#include "Behavioral/Interpreter/HandmadeInterpeter.h"
#include "Behavioral/Interpreter/InterpreterExcercise.h"
#include "Behavioral/Iterator/IteratorsInSTL.h"
#include "Behavioral/Iterator/BinaryTreeIterator.h"
#include "Behavioral/Iterator/BoostIteratorFacade.h"
#include "Behavioral/Iterator/IteratorExcercise.h"
#include "Behavioral/Mediator/TestChatRoom.h"
#include "Behavioral/Mediator/EventBroker2.h"
#include "Behavioral/Mediator/MediatorEx.h"
#include "Behavioral/Memento/Memento.h"
#include "Behavioral/Memento/MementoEx.h"
#include "Behavioral/Observer/ObservablePlayer.h"
#include "Behavioral/Observer/ObserverEx.h"
#include "Behavioral/State/ClassicStateMachine.h"
#include "Behavioral/State/HandMadeStateMachine.h"
#include "Behavioral/State/BoostStateMachine.h"
#include "Behavioral/State/StateEx.h"
#include "Behavioral/Strategy/DynamicStrategy.h"
#include "Behavioral/Strategy/StaticStrategy.h"
#include "Behavioral/Strategy/StrategyEx.h"
#include "Behavioral/TemplateMethod/TemplateMethod.h"
#include "Behavioral/TemplateMethod/TemplateEx.h"
#include "Behavioral/Visitor/IntrusiveVisitor.h"
#include "Behavioral/Visitor/ReflectiveVisitor.h"
#include "Behavioral/Visitor/ClassicVisitor.h"
#include "Behavioral/Visitor/AcyclicVisitor.h"
#include "Behavioral/Visitor/MulthiMethods.h"
#include "Behavioral/Visitor/VariantAndStdVisitor.h"

/**
 

 
 */
using namespace std;

/*
 * 
 */

int towerOfHanoi(int disks, const std::string& left, const std::string& middle, const std::string& right) {
    if(disks > 0) {
        towerOfHanoi(disks - 1, left, right, middle);
        printf("from %s to %s\n", left.c_str(), right.c_str());
        towerOfHanoi(disks - 1, middle, left, right);
    }
}


int main(int argc, char** argv) {

    BoostVariantAndVisitor::testSTDVariantAndVisitor();

    return 0;
}

