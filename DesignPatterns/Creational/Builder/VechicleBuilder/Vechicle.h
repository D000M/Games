/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Vechicle.h
 * Author: default
 *
 * Created on April 12, 2019, 1:47 PM
 */

#ifndef VECHICLE_H
#define VECHICLE_H

#include <string>
#include <ostream>

class VechicleBuilder;

class Vechicle {
private:
    //type builder
    std::string mType, mBrand;
    //components builder
    std::string mColor, mEngine, mFuel;
    int vechiclePrice{0};
public:
    
    static VechicleBuilder createVechicle();
    
    std::string getMBrand() const;

    void setMBrand(const std::string& mBrand);

    std::string getMColor() const;

    void setMColor(const std::string& mColor);

    std::string getMEngine() const;

    void setMEngine(const std::string& mEngine);

    std::string getMFuel() const;

    void setMFuel(const std::string& mFuel);

    std::string getMType() const;

    void setMType(const std::string& mType);

    int getVechiclePrice() const;

    void setVechiclePrice(const int vechiclePrice);

    
    friend std::ostream& operator << (std::ostream& os, const Vechicle& obj) {
        os << "Type: " << obj.mType
                << "\nBrand: " << obj.mBrand
                << "\nColor: " << obj.mColor
                << "\nFuel: " << obj.mFuel
                << "\nPrice: " << obj.vechiclePrice << std::endl;
        return os;
    }
};

#endif /* VECHICLE_H */

