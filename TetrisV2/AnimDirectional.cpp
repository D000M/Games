/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   AnimDirectional.cpp
 * Author: default
 * 
 * Created on June 25, 2019, 2:18 PM
 */

#include "AnimDirectional.h"
#include "SpriteSheet.h"

void AnimDirectional::cropSprite() {
    sf::IntRect rect (
        mSpriteSheet->getSpriteSize().x * mFrameCurrent,                                        //x
        mSpriteSheet->getSpriteSize().y * (mFrameRow + (short)mSpriteSheet->getDirection()),    //y
        mSpriteSheet->getSpriteSize().x,                                                        //width
        mSpriteSheet->getSpriteSize().y                                                         //height
    );
    mSpriteSheet->cropSprite(rect);
}

void AnimDirectional::frameStep() {
    if(mFrameActionStart < mFrameActionEnd) {
        ++mFrameCurrent;
    }
    else {
        --mFrameCurrent;
    }
    
    if((mFrameStart < mFrameEnd && mFrameCurrent > mFrameEnd) ||
        (mFrameStart > mFrameEnd && mFrameCurrent < mFrameEnd)) {
        if(mLoop) {
            mFrameCurrent = mFrameStart;
            return;
        }
        mFrameCurrent = mFrameEnd;
        pause();
    }
}

void AnimDirectional::readIn(std::stringstream& lStream) {
    lStream >> mFrameStart >> mFrameEnd >> mFrameRow >> mFrameTime >> mFrameActionStart >> mFrameActionEnd;
}


