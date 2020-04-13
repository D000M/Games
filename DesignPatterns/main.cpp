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
#include "Behavioral/Visitor/VisitorEx.h"
#include "Creational/Singleton/Multiton.h"
#include "Creational/Singleton/SingletonImplementation.h"
#include "Creational/Singleton/TotalSingletons.h"
#include "ORiley/StrategyPattern/TestStrategyDucks.h"
#include "ORiley/ObserverPattern/TestObserverPattern.h"
#include "ORiley/DecoratorPattern/FlowerDecorator/IFlower.h"
#include "ORiley/CommandPattern/TestCommandOriley.h"
#include "ORiley/Adapter/TestAdapterOreilly.h"
#include "ORiley/CompositePattern/HTMLElement.h"

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

void calculatePercentIncrease(float total, float increase) {
    float percent = ((increase - total) / total) * 100.0f;
    if(total == 0) {
        percent = 100;
    }
    std::string temp = "Win: ";
    if(percent < 0) {
        temp = "Lose: ";
    }
    std::cout << "Percent " << temp << percent << "%" << std::endl;
}
void calculateMoney(float buy, float sell, float& totalBuy, float& totalWin) {
    float totalPay = 0;
    float totalSell = 0;
    for(int i = 0; i < 5; i++) {
        totalPay += buy;
        totalSell += sell;
    }
    totalBuy += totalPay;
    totalWin += totalSell;
    std::cout << "Buyed for: " << totalPay << ", Can Sell For: " << totalSell << " Win: " << (totalSell - totalPay) 
        << "\n###################" << std::endl;
    
}
void calclulate20g(float buy, float sell, float& totalBuy, float& totalWin) {
    totalBuy += buy;
    totalWin += sell;
    std::cout << "Buyed for: " << buy << ", Can Sell For: " << sell << " Win: " << (sell - buy) 
        << "\n###################" << std::endl;
} 
/**
 * Total Spend: 5075, Total Can Win: 5915
20g Gold PAMP: Percent Win: 17.7539%
Buyed for: 1487, Can Sell For: 1751 Win: 264
###################
20g Gold Valcambi: Percent Win: 17.2806%
Buyed for: 1493, Can Sell For: 1751 Win: 258
###################
Total Spend: 8055, Total Can Win: 9417

============================ FINAL SCORE ===========================
Money Won: 1362, Percent Win: 16.9088%

 */
void caluclateYear(const std::string& year) {
    //This rally High
//    constexpr int SELL1G = 91;
//    constexpr int SELL20G = 1756;
    
    constexpr int SELL1G = 88;
    constexpr int SELL20G = 1691;

    float spend = 0;
    float canWin = 0;
    std::cout << "November: ";
    calculatePercentIncrease(76, SELL1G);
    calculateMoney(76, SELL1G, spend, canWin);
    std::cout << "December: ";
    calculatePercentIncrease(77, SELL1G);
    calculateMoney(77, SELL1G, spend, canWin);
    std::cout << "January: ";
    calculatePercentIncrease(80, SELL1G);
    calculateMoney(80, SELL1G, spend, canWin);
    std::cout << "February: ";
    calculatePercentIncrease(81, SELL1G);
    calculateMoney(81, SELL1G, spend, canWin);
    std::cout << "March: ";
    calculatePercentIncrease(80, SELL1G);
    calculateMoney(80, SELL1G, spend, canWin);
    std::cout << "April: ";
    calculatePercentIncrease(81, SELL1G);
    calculateMoney(81, SELL1G, spend, canWin);
    std::cout << "May: ";
    calculatePercentIncrease(80, SELL1G);
    calculateMoney(80, SELL1G, spend, canWin);
    std::cout << "Juny: ";
    calculatePercentIncrease(83, SELL1G);
    calculateMoney(83, SELL1G, spend, canWin);
    std::cout << "July: ";
    calculatePercentIncrease(88, SELL1G);
    calculateMoney(88, SELL1G, spend, canWin);
    
    std::cout << "August: ";
    calculatePercentIncrease(92, SELL1G);
    calculateMoney(92, SELL1G, spend, canWin);
    std::cout << "September: ";
    calculatePercentIncrease(98, SELL1G);
    calculateMoney(98, SELL1G, spend, canWin);
    std::cout << "October: ";
    calculatePercentIncrease(96, SELL1G);
    calculateMoney(96, SELL1G, spend, canWin);
    std::cout << "Bonus: ";
    calculatePercentIncrease(0, SELL1G);
    calculateMoney(0, SELL1G, spend, canWin);
    std::cout << "Total Spend: " << spend << ", Total Can Win: " << canWin << std::endl;
    
    std::cout << "20g Gold PAMP: ";
    calculatePercentIncrease(1487, SELL20G);
    calclulate20g(1487, SELL20G, spend, canWin);
    std::cout << "20g Gold Valcambi: ";
    calculatePercentIncrease(1493, SELL20G);
    calclulate20g(1493, SELL20G, spend, canWin);
    std::cout << "Total Spend: " << spend << ", Total Can Win: " << canWin << std::endl;
    std::cout << std::endl;
    std::cout << "============ FINAL SCORE " << year << " =================\n";
    std::cout << "Money Won: " << (canWin - spend) << ", ";
    calculatePercentIncrease(spend, canWin);
    
}

void simpleTest() {
    int arr[] = { 12, 41, 2, 12, 3, 5, 7, 0};
    
    auto lambdaSwap = [](int& a, int& b) -> void {
       int temp = a;
       a = b;
       b = temp;
    };
    
    auto lambdaFindMax = [](int* a) {
        int max = a[0];
        for(int i = 1; i < 8; i++) {
            if(a[i] > max) {
                max = a[i];
            }
        }
        return max;
    };
    
    auto lambdaFindMin = [](int* a) -> int {
      int min = a[0];
      for(int i{1}; i < 8; i++) {
          if(a[i] < min) {
              min = a[i];
          }
      }
      return min;
    };
    
    std::cout << "Max Element: " << lambdaFindMax(arr) << std::endl; 
    std::cout << "Min Element: " << lambdaFindMin(arr) << std::endl; 
    
    
//    auto lambdaPrintRec = [](int n) -> void {
//      if(n < 10) {
//          std::cout << n << " ";
//          lambdaPrintRec(n - 1);
//      }  
//    };
//    lambdaPrintRec(10);
    std::cout << std::endl;
    for(int i = 0; i < 8 - 1; i++) {
        for(int j = i + 1; j < 8; j++) {
            if(arr[i] > arr[j]) {
                lambdaSwap(arr[i], arr[j]);
            }
        }
    }
    for(auto elem : arr) {
        std::cout << elem << " ";
    }
    
    
    char charArr[] = "findingiiinntg";
    int duplicatesHash = 0;
    std::cout << duplicatesHash << std::endl;
    int dontPrint = 0;
    int x = 1;
    std::cout << std::endl;
    for(int i = 0; charArr[i] != '\0'; i++) {
        x = 1;
        x = x << charArr[i] - 97;
        if((x & duplicatesHash) > 0 && (x & dontPrint) == 0) {
            dontPrint = (x | dontPrint);
            std::cout << charArr[i] << " is duplicated\n";
        }
        else {
            duplicatesHash = (x | duplicatesHash);
        }
    }
    std::cout << duplicatesHash << std::endl;
    
}

struct MyStruct {
    char c;
    short int i;
//    double d;
};

void totalMoneyAmount() {
    double bank = 4690.78;
    double gold = 6814;
    double revolut = 204.83;
    double credits = 4505;
    double inMe = 140;
    double totalAmount = bank + gold + revolut + credits + inMe;
    std::cout << "В банка: " << bank
        << std::endl << "В Злато: " << gold 
        << std::endl << "В Револют: " << revolut
        << std::endl << "В Заеми: " << credits
        << std::endl << "В Мен: "   << inMe << std::endl;
    std::cout << "Total: " << totalAmount << " лева." <<std::endl;
}

class GoldAmount {
public:
    int amount1g;
    int amount20g;
    
    GoldAmount(const int& am1g, const int& am20g) 
        : amount1g{am1g},
          amount20g{am20g} {}
          
          void calc1g(const int& price) {
              amount1g *= price;
          }
          void calc20g(const int& price) {
              amount20g *= price;
          }
          
          void totalMoney(const int& price1g, const int& price20g) {
              std::cout << "Злато 1г тавекс: " << amount1g << " кюлчета" << ", цена: " << price1g << "лева за кюлче\n";
              calc1g(price1g);
              std::cout << "Злато 1г тавекс в левове: " << amount1g << " лева\n";
              std::cout << "Злато 20г Valcambi: " << amount20g << "  кюлчета " << ", цена: " << price20g << "лева за кюлче\n";
              calc20g(price20g);
              std::cout << "Злато 20г Valcambi в левове: " << amount20g << " лева\n";
              std::cout << "Total value: " << amount1g + amount20g << " лева\n";
          }
};

int main(int argc, char** argv) {

//    std::cout << sizeof(MyStruct) << std::endl; 
//    std::cout << sizeof(char) << " " << sizeof(short int) << " " << sizeof(double) << std::endl;

//    caluclateYear("11/2018 - 10/2019");
//    GoldAmount ga{39, 2};
//    ga.totalMoney(88, 1691);
    totalMoneyAmount();
    
    return 0;
}

