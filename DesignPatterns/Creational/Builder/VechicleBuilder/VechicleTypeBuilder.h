/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   VechicleTypeBuilder.h
 * Author: default
 *
 * Created on April 12, 2019, 2:04 PM
 */

#ifndef VECHICLETYPEBUILDER_H
#define VECHICLETYPEBUILDER_H

#include "VechicleBuilder.h"


class VechicleTypeBuilder : public VechicleBuilderBase {
    using VTP = VechicleTypeBuilder;
    
    public:
    explicit VechicleTypeBuilder(Vechicle& refV)
        : VechicleBuilderBase(refV) {
    }
    
    VTP& isType(const std::string& t) {
        refVechicle.setMType(t);
        return *this;
    }     
    VTP& isBrand(const std::string& b) {
        refVechicle.setMBrand(b);
        return *this;
    }
};

#endif /* VECHICLETYPEBUILDER_H */

