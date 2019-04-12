/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   VechicleComponentsBuilder.h
 * Author: default
 *
 * Created on April 12, 2019, 2:04 PM
 */

#ifndef VECHICLECOMPONENTSBUILDER_H
#define VECHICLECOMPONENTSBUILDER_H

#include "VechicleBuilder.h"


class VechicleComponentsBuilder : public VechicleBuilderBase {
    using VCB = VechicleComponentsBuilder;
    public:
        explicit VechicleComponentsBuilder(Vechicle& refV) 
            : VechicleBuilderBase{refV} {}
        
            VCB& setColor(const std::string& c) {
                refVechicle.setMColor(c);
                return *this;
            }
            VCB& setEngine(const std::string& e) {
                refVechicle.setMEngine(e);
                return *this;
            }
            VCB& setFuel(const std::string& f) {
                refVechicle.setMFuel(f);
                return *this;
            }
            VCB& setPrice(const int price) {
                refVechicle.setVechiclePrice(price);
                return *this;
            }
};

#endif /* VECHICLECOMPONENTSBUILDER_H */

