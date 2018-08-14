/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Item.h
 * Author: default
 *
 * Created on August 14, 2018, 1:23 PM
 */

#ifndef ITEM_H
#define ITEM_H

#include <string>
#include <iostream>

enum class ItemType {
    COLD_WEAPON = 0,    // нож, сабя, кинжал, сатър, ятаган, ножче.
    HOLY,               // кръст, библия, кандилница.
    DESTRUCT,           // бомба, граната, динамит, бомба-бухалка.
    DIGGING,            // кирка, лопата, мотика, миньорски пистолет, лъжица.
    FLAMEBLE,           // свещ, кибрит, факла, запалка.
    FIRE_EXTINGUISHER,  // кофа, маркуч, кофпомпа, пожарогасител. 
    PRISON_GRID,        // Решетка.
    HACKSAW,            // Ножовка, пила.
    POINTER,            // Указател.
    WOODEN_TOOLS,       // колец, подпора, дъска, греда.
    MGM,                // Вълшебна зелена пара.
    ITEM_COUNT          // Total count of the item types.
};

class Item {
public:
    
    Item(ItemType type, const std::string& name);
    virtual ~Item();
    
    void printItem();
    
    void setItemType(ItemType type);
    void setItemName(const std::string& name);
    
    ItemType getItemType() const;
    std::string getItemName() const;
    
//    friend std::ostream& operator << (std::ostream& os, const Item& obj) {
//        return os << obj.m_itemName << std::endl; 
//    }
private:
    
    ItemType m_type;
    std::string m_itemName;
    
    //helper method must be removed later.
    std::string typeToString(ItemType type);
    
};

#endif /* ITEM_H */

