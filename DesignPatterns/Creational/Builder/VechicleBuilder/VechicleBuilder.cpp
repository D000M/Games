/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   VechicleBuilder.cpp
 * Author: default
 * 
 * Created on April 12, 2019, 1:56 PM
 */

#include "VechicleBuilder.h"
#include "VechicleComponentsBuilder.h"
#include "VechicleTypeBuilder.h"


VechicleBuilderBase::VechicleBuilderBase(Vechicle& refV) 
    : refVechicle{refV} {

}


VechicleBuilder::VechicleBuilder() 
    : VechicleBuilderBase{mVechicle} {
    
}

VechicleComponentsBuilder VechicleBuilderBase::vechicleComponents() const {
    return VechicleComponentsBuilder{refVechicle};
}

VechicleTypeBuilder VechicleBuilderBase::vechicleType() const {
    return VechicleTypeBuilder{refVechicle};
}
