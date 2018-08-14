/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   ItemsDeck.h
 * Author: default
 *
 * Created on August 14, 2018, 1:54 PM
 */

#ifndef ITEMSDECK_H
#define ITEMSDECK_H

#include <vector>

#include "Item.h"


class ItemsDeck {
public:
    ItemsDeck();
    virtual ~ItemsDeck();
    
    Item& getItem();
    
    void printRemainingDeck();
private:
    
    //helper method
    void loadItems(const std::string& readFrom);
    ItemType stringToItemType(const std::string& type);
    std::vector<Item> items;
    
};

#endif /* ITEMSDECK_H */

