/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   VechicleBuilder.h
 * Author: default
 *
 * Created on April 12, 2019, 1:56 PM
 */

#ifndef VECHICLEBUILDER_H
#define VECHICLEBUILDER_H

#include <deque>

#include "Vechicle.h"


class VechicleTypeBuilder;
class VechicleComponentsBuilder;

class VechicleBuilderBase {
protected:
    Vechicle& refVechicle;
public:
    VechicleBuilderBase(Vechicle& refV);
    
    //case operator, provide functionality of the type Object obj = static Object create();
    operator Vechicle() const {
        return std::move(refVechicle);
    }
    
    VechicleTypeBuilder vechicleType() const;
    VechicleComponentsBuilder vechicleComponents() const;
};

class VechicleBuilder : public VechicleBuilderBase {
private:
    Vechicle mVechicle;
public:
    VechicleBuilder();
};

#endif /* VECHICLEBUILDER_H */

