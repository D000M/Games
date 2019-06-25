/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   BaseAnim.cpp
 * Author: default
 * 
 * Created on June 25, 2019, 1:45 PM
 */

#include "AnimBase.h"
#include "SpriteSheet.h"

AnimBase::AnimBase() 
    : mFrameCurrent{0},
      mFrameStart{0},
      mFrameEnd{0},
      mFrameRow{0},
      mFrameTime{0.f},
      mElapsedTime{0.f},
      mFrameActionStart{-1},
      mFrameActionEnd{-1},
      mLoop{false},
      mPlaying{false}{

}

AnimBase::~AnimBase() {

}

void AnimBase::setSpriteSheet(SpriteSheet* lSheet) {
    mSpriteSheet = lSheet;
}

void AnimBase::setFrame(Frame lFrame) {
    if((lFrame >= mFrameStart && lFrame <= mFrameEnd) ||
        (lFrame >= mFrameEnd && lFrame <= mFrameStart) ) {
        mFrameCurrent = lFrame;
    }
}

bool AnimBase::isInAction() {
    if(mFrameActionStart == -1 || mFrameActionEnd == -1) {
        return true;
    }
    return (mFrameCurrent >= mFrameActionStart && mFrameCurrent <= mFrameActionEnd);
}

void AnimBase::play() {
    mPlaying = true;
}

void AnimBase::pause() {
    mPlaying = false;
}

void AnimBase::stop() {
    mPlaying = false;
    reset();
}

void AnimBase::reset() {
    mFrameCurrent = mFrameStart;
    mElapsedTime = 0.0f;
    cropSprite();
}

void AnimBase::update(const float& ldT) {
    if(!mPlaying) {
        return;
    }
    mElapsedTime += ldT;
    if(mElapsedTime < mFrameTime) {
        return;
    }
    
    frameStep();
    cropSprite();
    mElapsedTime = 0;
}

int AnimBase::getActionEnd() {
    return mFrameActionEnd;
}

int AnimBase::getActionStart() {
    return mFrameActionStart;
}

float AnimBase::getElapsedTime() {
    return mElapsedTime;
}

Frame AnimBase::getEndFrame() {
    return mFrameEnd;
}

Frame AnimBase::getFrame() {
    return mFrameCurrent;
}

float AnimBase::getFrameTime() {
    return mFrameTime;
}

std::string AnimBase::getName() {
    return mName;
}

Frame AnimBase::getRowFrame() {
    return mFrameRow;
}

SpriteSheet* AnimBase::getSpriteSheet() {
    return mSpriteSheet;
}

Frame AnimBase::getStartFrame() {
    return mFrameStart;
}

bool AnimBase::isLooping() {
    return mLoop;
}

bool AnimBase::isPlaying() {
    return mPlaying;
}

void AnimBase::setActionEnd(int lFrame) {
    mFrameActionEnd = lFrame;
}

void AnimBase::setActionStart(int lFrame) {
    mFrameActionStart = lFrame;
}

void AnimBase::setEndFrame(Frame lFrame) {
    mFrameEnd = lFrame;
}

void AnimBase::setFrameRow(Frame lFrame) {
    mFrameRow = lFrame;
}

void AnimBase::setFrameTime(float lTime) {
    mFrameTime = lTime;
}

void AnimBase::setLooping(bool lLoop) {
    mLoop = lLoop;
}

void AnimBase::setName(const std::string& lName) {
    mName = lName;
}

void AnimBase::setStartFrame(Frame lFrame) {
    mFrameStart = lFrame;
}














