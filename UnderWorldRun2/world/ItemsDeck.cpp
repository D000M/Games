/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   ItemsDeck.cpp
 * Author: default
 * 
 * Created on August 14, 2018, 1:54 PM
 */

#include <fstream>
#include <iostream>
#include <sstream>
#include <algorithm>
#include "ItemsDeck.h"

ItemsDeck::ItemsDeck() {
    loadItems("resources/items/itemList");
    std::random_shuffle(items.begin(), items.end());
    for(int i = 0; i < items.size(); ++i) {
        items.at(i).printItem();
    }
}

ItemsDeck::~ItemsDeck() {
}

void ItemsDeck::loadItems(const std::string& readFrom) {
    std::ifstream file{readFrom};
    if(!file.is_open()) {
        std::cerr << "! Failed To load item List: " << readFrom << std::endl;
        return;
    }
    std::string line;
    while(std::getline(file, line)) {
        if(line.at(0) == '|') {
            continue;
        }
        std::stringstream keystream{line};
        std::string type;
        std::string name;
        keystream >> type;
        keystream >> name;

        items.push_back(Item(stringToItemType(type), name));
    }
}

Item& ItemsDeck::getItem() {
    Item& temp = items.back();
    items.pop_back();
    return temp;
}

void ItemsDeck::printRemainingDeck() {
    std::cout << "------------------------------\n";
    for(int i = 0; i < items.size(); ++i) {
        items.at(i).printItem();
    }
}

ItemType ItemsDeck::stringToItemType(const std::string& type) {
    if(type == "COLD_WEAPON") {
        return ItemType::COLD_WEAPON;
    }
    else if(type == "HOLY") {
        return ItemType::HOLY;
    }
    else if(type == "DESTRUCT") {
        return ItemType::DESTRUCT;
    }
    else if(type == "DIGGING") {
        return ItemType::DIGGING;
    }
    else if(type == "FLAMEBLE") {
        return ItemType::FLAMEBLE;
    }
    else if(type == "FIRE_EXTINGUISHER") {
        return ItemType::FIRE_EXTINGUISHER;
    }
    else if(type == "PRISON_GRID") {
        return ItemType::PRISON_GRID;
    }
    else if(type == "HACKSAW") {
        return ItemType::HACKSAW;
    }
    else if(type == "POINTER") {
        return ItemType::POINTER;
    }
    else if(type == "WOODEN_TOOLS") {
        return ItemType::WOODEN_TOOLS;
    }
    else if(type == "MGM") {
        return ItemType::MGM;
    }
    else if(type == "HOLY") {
        return ItemType::HOLY;
    }
}

