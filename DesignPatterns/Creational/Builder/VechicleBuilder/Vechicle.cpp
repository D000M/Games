/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Vechicle.cpp
 * Author: default
 * 
 * Created on April 12, 2019, 1:47 PM
 */

#include "Vechicle.h"
#include "VechicleBuilder.h"

std::string Vechicle::getMBrand() const {
        return mBrand;
}

void Vechicle::setMBrand(const std::string& mBrand) {
    this->mBrand = mBrand;
}

std::string Vechicle::getMColor() const {
    return mColor;
}

void Vechicle::setMColor(const std::string& mColor) {
    this->mColor = mColor;
}

std::string Vechicle::getMEngine() const {
    return mEngine;
}

void Vechicle::setMEngine(const std::string& mEngine) {
    this->mEngine = mEngine;
}

std::string Vechicle::getMFuel() const {
    return mFuel;
}

void Vechicle::setMFuel(const std::string& mFuel) {
    this->mFuel = mFuel;
}

std::string Vechicle::getMType() const {
    return mType;
}

void Vechicle::setMType(const std::string& mType) {
    this->mType = mType;
}

int Vechicle::getVechiclePrice() const {
    return vechiclePrice;
}

void Vechicle::setVechiclePrice(const int vechiclePrice) {
    this->vechiclePrice = vechiclePrice;
}

//Static function to create vechicle

VechicleBuilder Vechicle::createVechicle() {
    return VechicleBuilder();
}
