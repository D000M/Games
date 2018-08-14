/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Item.cpp
 * Author: default
 * 
 * Created on August 14, 2018, 1:23 PM
 */

#include "Item.h"
#include <iostream>

Item::Item(ItemType type, const std::string& name) 
    : m_type{type},
      m_itemName{name} {
        std::cout << "Item: "<< name << ", type: " << typeToString(type) << ", Created\n";
}

Item::~Item() {
}

void Item::setItemName(const std::string& name) {
    m_itemName = name;
}

void Item::setItemType(ItemType type) {
    m_type = type;
}

ItemType Item::getItemType() const {
    return m_type;
}

std::string Item::getItemName() const {
    return m_itemName;
}

void Item::printItem() {
    std::cout << "Item type: " << typeToString(m_type) << ", name: " << m_itemName << std::endl;
}


std::string Item::typeToString(ItemType type) {
    switch(type) {
        case ItemType::COLD_WEAPON:
            return "Cold Weapon Item";
        case ItemType::HOLY:
            return "Holy Item";
        case ItemType::DESTRUCT:
            return "Destructuble Item";
        case ItemType::DIGGING:
            return "Digging Item";
        case ItemType::FLAMEBLE:
            return "Flamable Item";
        case ItemType::FIRE_EXTINGUISHER:
            return "Fire Protection Item";
        case ItemType::PRISON_GRID:
            return "Reshetka Item";
        case ItemType::HACKSAW:
            return "Pila/Nojovka Item";
        case ItemType::POINTER:
            return "Ukazatel";
        case ItemType::WOODEN_TOOLS:
            return "Wooden Item";
        case ItemType::MGM:
            return "Magic Green Money";
        default:
            return "Should not enter here Error!\n";
    }
}

