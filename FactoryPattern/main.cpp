/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: default
 *
 * Created on March 14, 2019, 9:14 AM
 */

#include <cstdlib>
#include <complex>
#include <fstream>
#include <chrono>
#include <random>
#include <deque>
#include <cstdarg>

#include "factory/IAnimal.h"
#include "ToyFactory/ToyFactory.h"
#include "PizzaFactory/Pizza.h"
#include "Overloading/Rational.h"
#include "Overloading/Inheritance.h"
#include "exceptions/Exceptions.h"
#include "serialization/Items.h"
#include "numerical/OctalToBinary.h"

using namespace std;

/*
 * 
 */

void testFactoryPattern() {
//    IAnimal* pAnimal = nullptr;
//    std::string animalName;
//    
//    while (pAnimal == nullptr) {
//        std::cout << "Animal type or Q to quit\n";
//        std::cin >> animalName;
//        if(animalName == "Q") {
//            break;
//        }
//        pAnimal = AnimalFactory::Get()->CreateAnimal(animalName);
//        if(pAnimal) {
//            std::cout << "Your Animal has: " << pAnimal->GetAnimalLegs() << " Legs!\n";
//            std::cout << "Your Animal say: ";
//            pAnimal->Speak();
//        }
//        else {
//            std::cout << "The animal doesnt exist in the farm!\n";
//        }
//        if(pAnimal) {
//            pAnimal->Free();
//        }
//        pAnimal = nullptr;
//        animalName.clear();
//    }
    AnimalFactory* factory;
    factory->Register<Cat>("Cat");
    factory->Register<Horse>("Horse");
    factory->Register<Dog>("Dog");
    factory->Register<Spider>("Spider");
    
//    IAnimal* animal = factory->Get()->
    
}
void testToyFactory() {
    while(true) {
        std::cout << "Enter toy name or q to quit!\n";
        std::string type;
        std::cin >> type;
        if(type == "q") {
            break;
        }
        Toy* t = ToyFactory::createToy(type);
        if(t) {
            t->showProduct();
            delete t;
        }
    }
    std::cout << "Exit!\n";
}
void testPizzaFactory(PizzaFactory::PizzaType type) {
    std::unique_ptr<Pizza> pizza = PizzaFactory::createPizza(type);
    std::cout << "Price of "  << " is: " << pizza->getPrice() << std::endl;
}
void runPizza() {
    testPizzaFactory(PizzaFactory::PizzaType::Hawaiian);
    testPizzaFactory(PizzaFactory::PizzaType::HamMushroom);
    testPizzaFactory(PizzaFactory::PizzaType::Deluxe);
}

int gcd(int m, int n) {
    if(m == n) {
        return n;
    }
    if(m > n) {
        return gcd(m - n, n);
    }
    else {
        return gcd(m, n - m);
    }
}

void examplePrint2DimmArr() {
    int arr[2][3] = {1, 2, 3, 4};
    for(auto& row : arr) {
        for(auto& col : row) {
            std::cout << col << " ";
        }
        std::cout << std::endl;
    }
}
void pointers() {
    //    int a = 5;
//    int* p = nullptr;
//    p = &a;
//    std::cout << "a: " << a << std::endl;
//    std::cout << "&a: " << &a << std::endl;
//    std::cout <<  "p: " << p << std::endl;
//    std::cout <<  "&p: " << &p << std::endl;
//    std::cout <<  "*p: " << *p << std::endl;
//    
//    int A[] = {2, 4, 6, 8, 10, 12};
//    
//    for(int* p = A; p < A + 5; p++) {
//        std::cout << *p << " ";
//        *p = *p * 10;
//    }
//    
//    for(int i = 0; i < 5; i++) {
//        std::cout << i[A] << " ";
//    }
    //Segmentation fault
//    int* p;
//    std::cout << *p << std::endl;
    /////////////
}

int biggestNumber(int a, int b) {
    if(a >= b) {
        return a;
    }
    return b;
}

void display(int a) {
    std::cout << "Hello!\n";
}

void functionPointer() {
   
    /**
     * Way of declaring function pointer
     * return type - void, primitive type, class
     * name of a pointer inside brackets example : (*myFuncPtr)
     * arguments (int,char,class...) or empty ();
     * example
     * void (*myFuncPtr) ();   function pointer to a function with return type void and no parameters
     * int (*myFuncPtr) (int a);  function pointer to a function with return type int and parameter int
     */
    
   void (*fp)(int a);    //Declaration of a pointer to a function(function pointer)
   fp = display;    //Assign display function to pointer fp;
   (*fp)(10); //call the same way as declaration
   
   int (*funcPtr)(int, int);
   funcPtr = biggestNumber;
   std::cout << (*funcPtr)(17, 15) << std::endl;
}
void testOverloading() {
    Rational r1{12, 24}, r2{5, 8}, r3;
    std::cout << r1 << std::endl << r2 << endl;
    r3 = r1 + r2;
    std::cout << r3 << std::endl;
}
void testItemSerialization() {
    Item axe("Axe", 15.5f, 25);
    std::cout << axe << std::endl;
    std::ofstream file("files/items.txt" , std::ios::trunc);
    file << axe;
    
    Item bread("Bread", 0.99f, 31);
    std::cout << bread << std::endl;
    file << bread;
    
    
    Item newItem;
    std::cin >> newItem;
    std::cout << newItem<< std::endl;
    file << newItem;
    file.close();
    std::cout << "Reading@#########\n";
    std::ifstream read("files/items.txt");
    
    while(!read.eof()) {
    Item temp;
        read >> temp;
        std::cout << temp << std::endl;
    }
    read.close();
}

void testMap( ) {
    std::map<int, std::string> myMap;
    myMap.insert(std::pair<int, string>(5, "Vanq"));
    myMap.insert(std::pair<int, string>(6, "Eli"));
    myMap.insert(std::pair<int, string>(2, "Stela"));
    myMap.insert(std::pair<int, string>(1, "Lina"));
    myMap.insert(std::pair<int, string>(8, "Lina"));
    
    for(std::map<int, std::string>::iterator it = myMap.begin(); it != myMap.end(); it++) {
        std::cout << it->first << " " << it->second << std::endl;
    }
    
    for(auto& itr : myMap) {
        std::cout << itr.first << " " << itr.second << std::endl;
    }
}

void testmt19937() {
    auto seed = std::chrono::high_resolution_clock::now().time_since_epoch().count();
    
    std::mt19937 u{seed};
    
    std::random_device rd{};
    u.seed(rd());
    std::uniform_int_distribution<> d{};
    using parmType = decltype(d)::param_type;
    for(int i = 0; i < 100; i++) {
        int randNum = d(u, parmType(1, 10));
        std:: cout << randNum << std::endl;
    }

}


//Template for passing a lambda to a function
template<typename T>
void passLambda(T function) {
    function();
}

void lambdaTest() {
    /*
     * Syntax
     * [capture_list](parameter_list)->return_type{
     *  body
     * };
     */
    
    //Examples
    auto lambdaFunc = [](){
        std::cout << "I am Lambda!\n";
    };
    lambdaFunc();
    
    //Or direct call
    [](){
        std::cout << "I am Lambda Direct call!\n";
    }();
    
    
    //Lambda that takes parameters
    // Direct Call
    [](int x, int y) {
        std::cout << "Direct lambda call: "<< x + y << std::endl;
    }(10, 25);
    
    //Set name
    auto sumOf2Nums = [](int x, int y) {
        std::cout << x << " + " << y << " = " << x + y;
    };
    sumOf2Nums(13, 26);
    
    //Lambda that returns
    //Direct call
    int result = [](int x, int y) {
        return x + y;
    }(100, 200);
    std::cout << "Lambda direct call returns: " << result << std::endl;
    
    //Set lambda function with return type int
    auto res = [](int x, int y)->int {
        return x + y;
    };
    std::cout << "Lambda with return: " << res(14, 23) << std::endl;
    
    //Access local/global variables in lambda
    int varOne = 45;
    int varTwo = 56;
    //Direct call
    [varOne, varTwo]() {
        std::cout << varOne << " + " << varTwo << " = " << varOne + varTwo << std::endl;
    }();
    
    auto globVarSum = [varOne, varTwo]() {
        std::cout << varOne << " + " << varTwo << " = " << varOne + varTwo << std::endl;
    };
    globVarSum();
    
    auto globVarSum2 = [&varOne, &varTwo] (int a, int b) {
        varOne += a;
        varTwo += b;
    };
    globVarSum2(10, 20);
    auto globVarSum3 = [varOne, varTwo]() {
        std::cout << varOne << " + " << varTwo << " = " << varOne + varTwo << std::endl;
    };
    globVarSum3();
    
    //Accessing all the things in the scope
    auto multiply = [&](int a, int b, int c)->int {
        varOne *= a * b * c;
        varTwo *= a * b * c;
        return varOne * varTwo;
    };
    std::cout << multiply(4, 5, 6) << std::endl;
    
    //Pass labda to a function
    auto passMe = []() {
        std::cout << "Pass to a function!\n";
    };
    passLambda(passMe);
}


///Smart Pointers
/**
 * unique_ptr
 * shared_ptr
 * weak_ptr
 */
void testSmartPointers() {
    /**
     * std::unique_ptr
     * this pointer can point to only 1 object
     * other pointer cant point to this pointer 
     * if we want to use another pointer that point to this object we should call std::move()
     */
    std::unique_ptr<Item> uqPtrItem(new Item("Not Leaked", 23.5, 10));
    std::cout << &uqPtrItem << " " << *uqPtrItem << std::endl;
    std::unique_ptr<Item> uqPtrItem2 = std::move(uqPtrItem);
    std::cout << &uqPtrItem2 << " " << *uqPtrItem2 << std::endl;
    Item* nPtrItem = new Item("Leaked", 1, 1);
    std::cout << *nPtrItem << std::endl;
    //Leaked memory if not deleted
    delete nPtrItem;
    
    //At the end of scope std::unique_ptr automatically delete the allocated memory
    //no need to call delete for std::unique_ptr
    
//    std::unique_ptr<Item> uqPtrItem2 = uqPtrItem; !!!!! Forbidden copy operator for std::unique_ptr
    
    
    //Using Shared Pointers std::shared_ptr<>
    //Both pointers point to 1 object
    std::shared_ptr<Item> sdPtrItem1(new Item("Shared Ptr", 2, 2));
    std::shared_ptr<Item> sdPtrItem2 = sdPtrItem1;
    std::cout << sdPtrItem1 << " " << *sdPtrItem1 << std::endl;
    std::cout << sdPtrItem2 << " " << *sdPtrItem2 << std::endl;
    std::cout << sdPtrItem1.use_count() << " " << sdPtrItem2.use_count() << std::endl;
    sdPtrItem1.reset(); //delete one of the pointers
    std::cout << sdPtrItem2.use_count() << std::endl;
    
    //std::weak_ptr<> , same as shared_ptr except didnt count how many pointers are pointing to this object.
}

//Ellipsis
//First parameter is number of how many elements i am passing in to the function
//Example sumEllipsis(3, 20, 30, 40); << 3 parameters
//Example sumEllipsis(7, 12, 13, 15, 176, 14, 18, 19); << 7 parameters
int sumEllips(int n, ...) {
    //#include <stdarg>
    va_list list;
    va_start(list, n);
    
    int sum = 0;
    for(int i = 0; i < n; i++) {
        sum += va_arg(list, int);
    }   
    va_end(list);       
    return sum;
}

void testOctalToBinary() {
    convertOctalToBinary(266);
    convertBinaryToOctal("010110110");
}
void shitHappends(float a,float b,float c) {
    float d,r1,r2;
    
    //calculate d
    // print nature of roots using nested if
    d = b * b - (4 * a * c);
    if(d == 0) {
        cout << "real and equal ";
        cout << (-b) / (2 * a);
    }
    else if(d > 0) {
        cout << "real and unequal ";
        r1 = (((-b) + sqrt(d)) / (2 * a));
        r2 = ((-b) - sqrt(d)) / (2 * a);
    }
    else {
        cout << "imaginary" << endl;
    }
}
void Discount(int amount)
{
    float disAmount;
    
    //write nested onditions to print discounted amount 
    if(amount >= 5000) {
        disAmount =amount - (amount * 0.2);
        cout << disAmount;
    }
    else if(amount >= 2000 && amount < 5000) {
        disAmount = amount - (amount * 0.1);
        cout << disAmount;
    }
    else {
        disAmount = amount - (amount * 0.05);
        cout << disAmount;
    }
    
}
int main(int argc, char** argv) {

    Discount(6200);
    
    return 0;
}

