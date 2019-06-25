/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   AnimDirectional.h
 * Author: default
 *
 * Created on June 25, 2019, 2:18 PM
 */

#ifndef ANIMDIRECTIONAL_H
#define ANIMDIRECTIONAL_H

#include "AnimBase.h"


class AnimDirectional : public AnimBase {
    protected:
        void cropSprite() override;
        void frameStep() override;
        void readIn(std::stringstream& lStream) override; 
};

#endif /* ANIMDIRECTIONAL_H */

