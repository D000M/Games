/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   SpriteSheet.cpp
 * Author: default
 * 
 * Created on June 25, 2019, 1:23 PM
 */

#include "SpriteSheet.h"

SpriteSheet::SpriteSheet(TextureManager* lTextMgr) 
    : mTextureMgr{lTextMgr},
      mAnimationCurrent{nullptr},
      mSpriteScale{1.0f, 1.0f},
      mDirection{Direction::UP} {
    
}

SpriteSheet::~SpriteSheet() {
    releaseSheet();
}

void SpriteSheet::releaseSheet() {
    mTextureMgr->releaseResource(mTexture);
    mAnimationCurrent = nullptr;
    while(mAnimations.begin() != mAnimations.end()) {
        delete mAnimations.begin()->second;
        mAnimations.erase(mAnimations.begin());
    }
}

void SpriteSheet::setSpriteSize(const sf::Vector2i& lSize) {
    mSpriteSize = lSize;
    mSprite.setOrigin(mSpriteSize.x / 2, mSpriteSize.y / 2);
}

void SpriteSheet::setSpritePos(const sf::Vector2f& lPos) {
    mSprite.setPosition(lPos);
}

void SpriteSheet::setDirection(const Direction& lDir) {
    if(lDir == mDirection) {
        return;
    }
    mDirection = lDir;
    mAnimationCurrent->cropSprite();
}

void SpriteSheet::cropSprite(const sf::IntRect& lRect) {
    mSprite.setTextureRect(lRect);
}

bool SpriteSheet::setAnimation(const std::string& lName, const bool& lPlay, const bool& lLoop) {
    auto it = mAnimations.find(lName);
    if(it == mAnimations.end()) {
        return false;
    }
    
    if(it->second == mAnimationCurrent) {
        return false;
    }
    
    if(mAnimationCurrent) {
        mAnimationCurrent->stop();
    }
    mAnimationCurrent = it->second;
    mAnimationCurrent->setLooping(lLoop);
    
    if(lPlay) {
        mAnimationCurrent->play();
    }
    mAnimationCurrent->cropSprite();
    return true;
}

void SpriteSheet::update(const float& ldT) {
    mAnimationCurrent->update(ldT);
}

void SpriteSheet::draw(sf::RenderWindow* lWindow) {
    lWindow->draw(mSprite);
}

AnimBase* SpriteSheet::getCurrentAnim() {
    return mAnimationCurrent;
}

Direction SpriteSheet::getDirection() const {
    return mDirection;
}

sf::Vector2f SpriteSheet::getSpritePos() const {
    return mSprite.getPosition();
}

sf::Vector2i SpriteSheet::getSpriteSize() const {
    return mSpriteSize;
}

bool SpriteSheet::loadSheet(const std::string& lFile) {
    std::ifstream sheet;
    sheet.open(lFile);
    if(sheet.is_open()) {
        releaseSheet(); //Release current sheet resource.
        std::string line;
        while(std::getline(sheet, line)) {
            if(line[0] == '|') {
                continue;
            }
            std::stringstream keystream{line};
            std::string type;
            keystream >> type;
            
            if(type == "Texture") {
                if(mTexture != "") {
                    std::cerr << "! Duplicate texture entries in: " << lFile << std::endl;
                    continue;
                }
                std::string texture;
                keystream >> texture;
                if(!mTextureMgr->requireResource(texture)) {
                    std::cerr << "! Could not set up the texture: " << texture << std::endl;
                    continue;
                }
                mTexture = texture;
                mSprite.setTexture(*mTextureMgr->getResource(mTexture));
            }
            else if(type == "Size") {
                keystream >> mSpriteSize.x >> mSpriteSize.y;
                setSpriteSize(mSpriteSize);
            }
            else if(type == "Scale") {
                keystream >> mSpriteScale.x >> mSpriteScale.y;
                mSprite.setScale(mSpriteScale);
            }
            else if(type == "AnimationType") {
                keystream >> mAnimType;
            }
            else if(type == "Animation") {
                std::string name;
                keystream >> name;
                if(mAnimations.find(name) != mAnimations.end()) {
                    std::cerr << "! Duplicate animation(" << name << ") in: " << lFile << std::endl;
                    continue;
                }
                AnimBase* anim = nullptr;
                if(mAnimType == "Directional") {
                    anim = new AnimDirectional();
                }
                //Add More Animation types here.
//                else if() {   
//                    
//                }
                else {
                    std::cerr << "! Unknown animation type: " << mAnimType << std::endl;
                }
                anim->setSpriteSheet(this);
                anim->setName(name);
                anim->reset();
                mAnimations.emplace(name, anim);
                
                if(mAnimationCurrent) {
                    continue;
                }
                mAnimationCurrent = anim;
                mAnimationCurrent->play();
            }
            
        }
        sheet.close();
        return true;
    }
    std::cerr << "! Failed to loading spritesheet: " << lFile << std::endl;
    return false;
}

