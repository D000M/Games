/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   enumStructs.h
 * Author: default
 *
 * Created on February 12, 2019, 11:40 AM
 */

#ifndef ENUMSTRUCTS_H
#define ENUMSTRUCTS_H

#include <string>


enum class MonsterType {
    OGRE,
    DRAGON,
    ORC,
    GIANT_SPIDER,
    SLIME,
    NONE,
};

struct Monster {
    MonsterType eMonsterType = MonsterType::NONE;
    std::string monsterName = "";
    int health = 0;
};

std::string getMosterTypeString(MonsterType type) {
    if(type == MonsterType::DRAGON) {
        return "Dragon";
    }
    else if(type == MonsterType::GIANT_SPIDER) {
        return "Giant Spider";
    }
    else if(type == MonsterType::OGRE) {
        return "Ogre";
    }
    else if(type == MonsterType::ORC) {
        return "Orc";
    }
    else if(type == MonsterType::SLIME) {
        return "Slime";
    }
    return "Unknown";
}

void printMonster(Monster m) {

    std::cout << "This " << getMosterTypeString(m.eMonsterType) << " is named " << m.monsterName << " and has " << m.health << " health.\n";
}

void testMonster() {
    Monster ogre{MonsterType::OGRE, "Torg", 146};
    Monster slime{MonsterType::SLIME, "Blurp", 23};
    printMonster(ogre);
    printMonster(slime);
}

enum class State {
    BAD_OPERATOR = -1,
    SUCCESS,
};

int printError(State status) {
    switch(static_cast<int>(status)) {
        case static_cast<int>(State::BAD_OPERATOR): return static_cast<int>(State::BAD_OPERATOR);
        case static_cast<int>(State::SUCCESS): return static_cast<int>(State::SUCCESS);
        default: return 0;
    }
}

int calculate(int a, int b, char op) {
    switch(op) {
        case '+':
            return a + b;
        case '-':
            return a - b;
        case '*':
            return a * b;
        case '/':
            return a / b;
        case '%':
            return a % b;
        default: printError(State::BAD_OPERATOR); 
            break; 
    }
}
void testMAths() {
    std::cout << calculate(1, 2, 'a') << std::endl;
}

enum class Animal {
    PIG, 
    CHICKEN, 
    GOAT, 
    CAT, 
    DOG, 
    OSTRICH,
};
void printErrorAnimal() {
    std::cout << "Unknown Animal type" << std::endl;
}
std::string getAnimalName(Animal type) {
    switch(type) {
        case Animal::PIG:                   return "Pig";
        case Animal::CHICKEN:               return "Chicken";
        case Animal::GOAT:                  return "Goat";
        case Animal::CAT:                   return "Cat";
        case Animal::DOG:                   return "Dog";
        case Animal::OSTRICH:               return "Ostrich";
        default:     printErrorAnimal();    return "";
    }
}
int getAnimalNumberOfLegs(Animal type) {
    switch(type) {
        case Animal::PIG:                return 4;
        case Animal::CHICKEN:            return 2;
        case Animal::GOAT:               return 4;
        case Animal::CAT:                return 4;
        case Animal::DOG:                return 4;
        case Animal::OSTRICH:            return 2;
        default:   printErrorAnimal();   return -1;
    }
}
void printAnimal(Animal type) {
    std::cout << "A " << getAnimalName(type) << " has " << getAnimalNumberOfLegs(type) << " legs.\n";
}
void testAnimals() {
    printAnimal(Animal::CAT);
    printAnimal(Animal::CHICKEN);
    printAnimal(static_cast<Animal>(10));
}

void printChars() {
    char a = 'a';
    while(a <= 'z') {
        std::cout << static_cast<char>(a);
        a++;
    }
    std::cout << std::endl;
}

int sumTo(int value) {
   return (value * (value + 1)) / 2; 
}
void forTest() {
    for(int num = 0; num <= 20; num += 2) {
        std::cout << num << " ";
    }
    std::cout << std::endl;
    std::cout << sumTo(5) << std::endl;
    std::cout << std::endl;
    for(int i = 0; i < 10; i++) {
        if(i == 3 || i == 6) {
            continue;
        }
        std::cout << i << std::endl;
    }
}
#endif /* ENUMSTRUCTS_H */

