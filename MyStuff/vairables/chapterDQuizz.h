/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   chapterDQuizz.h
 * Author: default
 *
 * Created on February 7, 2019, 3:41 PM
 */

#ifndef CHAPTERDQUIZZ_H
#define CHAPTERDQUIZZ_H

#include <iostream>
#include <complex>
#include "../utils/Constants.h"
#include "../utils/Utils.h"
#include "../utils/RNGGenerator.h"
#include "../utils/Input.h"

double getInDouble() {
    double d = 0.0;
    std::cout << "Input a double: ";
    std::cin >> d;
    return d;
}
char getInChar() {
    char c = 0;
    std::cout << "Input a char: ";
    std::cin >> c;
    return c;
}

void calc() {
    double a = getInDouble();
    double b = getInDouble();
    char c = getInChar();
    double result = 0.0;
    switch(c) {
        case '+': result = a + b; break;
        case '-': result = a - b; break;
        case '*': result = a * b; break;
        case '/': result = a / b; break;
        default: break;
    }
    std::cout << a << " " << c << " " << b << " = " << result;
}

double fallenDistance(double h, double sec) {
    return (myConst::gravity * (sec * sec)) / 2;
}

double currHeight(double height, double sec) {
    return height - fallenDistance(height, sec) >= 0 ? height - fallenDistance(height, sec) : 0;
}
bool isOnTheGround(double d) {
    if(d == 0) {
        return true;
    }
    return false;
}
void gravityCheck() {
    double height{getInDouble()};
    std::cout << "At 0 seconds, the ball is at height: " << currHeight(height, 0) << "\n";
    if(isOnTheGround(currHeight(height, 0))) {
        return;
    }
    std::cout << "At 1 seconds, the ball is at height: " << currHeight(height, 1)  << "\n";
    if(isOnTheGround(currHeight(height, 1))) {
        return;
    }
    std::cout << "At 2 seconds, the ball is at height: " << currHeight(height, 2)  << "\n";
    if(isOnTheGround(currHeight(height, 2))) {
        return;
    }
    std::cout << "At 3 seconds, the ball is at height: " << currHeight(height, 3)  << "\n";
    if(isOnTheGround(currHeight(height, 3))) {
        return;
    }
    std::cout << "At 4 seconds, the ball is at height: " << currHeight(height, 4)  << "\n";
    if(isOnTheGround(currHeight(height, 4))) {
        return;
    }
    std::cout << "At 5 seconds, the ball is at height: " << currHeight(height, 5)  << "\n";
    if(isOnTheGround(currHeight(height, 5))) {
        return;
    }
}

int isGreatThanPowTwo(int num, int bit) {
    if(num >= pow(2, bit)) {
        num -= pow(2, bit);
        std::cout << "1";
    }
    else {
        std::cout << "0";
    }
    return num;
}

void testBinary() {
    
    int number = 65535;
    for(int i = 15; i >= 0; --i) {
        number = isGreatThanPowTwo(number, i);
    }

}

void testFloatComparing() {
    if(approximatelyEqualAbsRel(0.00001, 0.000015, 0.00001, 0.000001)) {
        std::cout << "They are Equal!\n";
    }
    else {
        std::cout << "They are not Equal!\n";
    }
    double d = 0.1 + 0.1 + 0.1 + 0.1 + 0.1 + 0.1 + 0.1 + 0.1 + 0.1 + 0.1;
    double b = 1.0;
    if(d == b) {
        std::cout << "True";
    }
    else {
        std::cout << "False";
    }
}

void enumsTest() {
    enum class MonsterType {
        ORC,
        GOBLIN,
        TROLL,
        OGRE,
        SKELETON,
        MONSTER_COUNT,
    };
    MonsterType eMonster = MonsterType::MONSTER_COUNT;
    
    for(int i = 0; i < static_cast<int>(MonsterType::MONSTER_COUNT); ++i) {
        switch(i) {
            case static_cast<int>(MonsterType::ORC)     : std::cout << "ORC" << std::endl; break;
            case static_cast<int>(MonsterType::GOBLIN)  : std::cout << "GOBLIN" << std::endl; break;
            case static_cast<int>(MonsterType::OGRE)    : std::cout << "OGRE" << std::endl; break;
            case static_cast<int>(MonsterType::SKELETON): std::cout << "SKELETON" << std::endl; break;
            case static_cast<int>(MonsterType::TROLL)   : std::cout << "TROLL" << std::endl; break;
            default                                     : std::cout << "NO MONSTER" << std::endl; break;
        }
    }
    
}

using error_t = int;

error_t printData() {
    return -1;
}

struct Stuff {
    int a = 1;
    int b = 2;
};
void testSTuff() {
    Stuff v;
    std::cout << v.a << " " << v.b << std::endl;
}

struct WebSite {
    int ads = 0;
    double percent = 0.0;
    double win = 0.0;
};
void printAmount(WebSite site) {
    std::cout << "Total win: " << (site.ads * site.percent * site.win) << std::endl;
}
void sumWebSite() {
    WebSite ws{100, 0.05, 5};
    printAmount(ws);
}

struct Fraction {
    int32_t nominator = 0;
    int32_t denominator = 0;
};
void multiplyFraction(Fraction f, Fraction s) {
    std::cout << static_cast<float>(f.nominator * s.nominator) / (f.denominator * s.denominator) << std::endl;
}
void testFraction() {
    Fraction first{9, 3};
    Fraction second{4, 5};
    multiplyFraction(first, second);
}

auto theHell() {
    return 5;
}
void shitHappens() {
    int b = theHell();
    std::cout << b << " " << theHell() << std::endl;
}

const int SIZE = 100;
int arrResult[SIZE] = {};

void setRNG(int num) {
    arrResult[num - 1]++;
}
void printResArray() {
    for(int i = 0; i < SIZE; ++i) {
        std::cout << i + 1 << ": " << arrResult[i] << std::endl;
    }
}
void testRNG() {
    std::cout << getRandomInteger(100000000000, 10000000000000);
//    for(int i = 0; i < 100000000; i++) {
//        setRNG(getRandomInteger(1, 100));
//    }
//    std::cout << std::endl;
//    for(int i = 0; i < 10; i++) {
//        std::cout << getRandomDouble(5, 25) << "\n";
//    }
//    printResArray();
}

void testInput() {
    char c = getOperator();
    double d = getDouble();
    double b = getDouble();
}

void gravityWithLoop() {
    double height = getDouble();
    for(int i = 0; i < 5; ++i) {
        if(isOnTheGround(currHeight(height, i))) {
            break;
        }
        std::cout << "At "<< i << " seconds, the ball is at height: " << currHeight(height, i) << "\n";
    }
}


void testRNG2() {
    for(int i = 0; i < 10; i++) {
        std::cout << rand() % 100 + 1 << " ";
    }
    std::cout << std::endl;
    randomize();
    for(int i = 0; i < 10; i++) {
        std::cout << getRandomInteger(1, 100) << " ";
    }
}

void testArrayLength() {
    int arr[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    std::cout << std::size(arr) << std::endl;
    for(int i = 0; i < std::size(arr); ++i) {
        std::cout << arr[i] << " ";
    }
}
void quizArr() {
    double arr[365] = {}; 
    for(int i = 0; i < std::size(arr); ++i) {
        if(i % 10 == 0) {
            std::cout << '\n';
        }
        std::cout << double(arr[i]) << " ";
    }
}
namespace tttt {
    enum Animals {
        CHICKEN,
        DOG,
        CAT,
        ELEPHANT,
        DUCK,
        SNAKE,
        COUNT,
    };
}
int arr[tttt::COUNT];
std::string getTTTTAnimalName(tttt::Animals type) {
    if(type == tttt::CHICKEN) {
        return "Chicken";
    }
    else if(type == tttt::DOG) {
        return "Dog";
    }
    else if(type == tttt::CAT) {
        return "Cat";
    }
    else if(type == tttt::ELEPHANT) {
        return "Elephant";
    }
    else if(type == tttt::DUCK) {
        return "Duck";
    }
    else if(type == tttt::SNAKE) {
        return "Snake";
    }
    
    return "Unknown";
}
void printNumberOfLegs2(tttt::Animals type) {
    std::cout << getTTTTAnimalName(type) << " has " << arr[type] << " legs.!\n";
}
void testAnimalTTT() {
    arr[tttt::CHICKEN] = 2;
    arr[tttt::DOG] = 4;
    arr[tttt::CAT] = 4;
    arr[tttt::ELEPHANT] = 4;
    arr[tttt::DUCK] = 2;
    arr[tttt::SNAKE] = 0; 
    printNumberOfLegs2(tttt::ELEPHANT);
}

void arrayQ2() {
    int arr[] = {4, 6, 7, 3, 8, 2, 1, 9, 5};
    for(int i = 0; i < std::size(arr); ++i) {
        std::cout << arr[i] << " ";
    }
    int input = 0;
    do {
        std::cout << "Input a number between 1 and 9 included: ";
        std::cin >> input;
        if(std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(32767, '\n');
            std::cout << "Wrong input try again!\n";
        }
    }
    while(input < 1 || input > 9);
    for(int i = 0; i < std::size(arr); ++i) {
        if(input == arr[i]) {
            std::cout << "The element " << input << " was found at position: " << i << std::endl;
        }
    }
    
    int scores[] = { 84, 92, 76, 81, 56 };
    const int numStudents = std::size(scores); // requires C++17
//  const int numStudents = sizeof(scores) / sizeof(scores[0]); // use this instead if not C++17 capable
 
    int maxScore = 0; // keep track of our largest score
    int index = 0;
    // now look for a larger score
    for (int student = 0; student < numStudents; ++student) {
        if (scores[student] > maxScore) {
            maxScore = scores[student];
            index = student;
        }
    }
 
    std::cout << "The best score was " << maxScore << '\n';
    std::cout << "The best score was on index " << index << '\n';
}


void bubbleSort() {
    const int length(9);
    int array[length] = { 6, 3, 2, 9, 7, 1, 5, 4, 8 };

    int iteration = 0;
    while(true) {
        bool bSorted = true;
        for(int i = 0; i < length - 1 - iteration; ++i) {
            std::cout << i << " ";
            if(array[i] > array[i + 1]){
                std::swap(array[i], array[i + 1]);
                bSorted = false;
            }
        }
        std::cout << std::endl;
        iteration++;
        if(bSorted) {
            break;
        }
    }
    for(int i = 0; i < length; ++i) {
        std::cout << array[i] << " ";
    }
}
#endif /* CHAPTERDQUIZZ_H */

