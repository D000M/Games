/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   TestVechicle.h
 * Author: default
 *
 * Created on April 12, 2019, 2:15 PM
 */

#ifndef TESTVECHICLE_H
#define TESTVECHICLE_H

#include "Vechicle.h"
#include "VechicleBuilder.h"
#include "VechicleTypeBuilder.h"
#include "VechicleComponentsBuilder.h"


void testVechicle() {
    Vechicle v = Vechicle::createVechicle()
            .vechicleType()
                .isType("Car")
                .isBrand("BMW")
            .vechicleComponents()
                .setColor("Black")
                .setEngine("Four Cylinder")
                .setFuel("Benzin")
                .setPrice(120000);
    std::cout << v << std::endl;
}

#endif /* TESTVECHICLE_H */

