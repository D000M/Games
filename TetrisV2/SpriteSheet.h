/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   SpriteSheet.h
 * Author: default
 *
 * Created on June 25, 2019, 1:23 PM
 */

#ifndef SPRITESHEET_H
#define SPRITESHEET_H

#include <unordered_map>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Sprite.hpp>

#include "AnimDirectional.h"
#include "TextureManager.h"
#include "Direction.h"


using Animations = std::unordered_map<std::string, AnimBase*>;

class SpriteSheet {
public:
    SpriteSheet(TextureManager* lTextMgr);
    ~SpriteSheet();
    
    void cropSprite(const sf::IntRect& lRect);
    //Getters and Setters
    sf::Vector2i getSpriteSize() const;
    sf::Vector2f getSpritePos() const;
    
    void setSpriteSize(const sf::Vector2i& lSize);
    void setSpritePos(const sf::Vector2f& lPos);
    
    void setDirection(const Direction& lDir);
    Direction getDirection() const;
    
    bool loadSheet(const std::string& lFile);
    void releaseSheet();
    
    AnimBase* getCurrentAnim();
    bool setAnimation(const std::string& lName, const bool& lPlay = false, const bool& lLoop = false);
    
    void update(const float& ldT);
    void draw(sf::RenderWindow* lWindow);
    
private:

    std::string mTexture;
    sf::Sprite mSprite;
    sf::Vector2i mSpriteSize;
    sf::Vector2f mSpriteScale;
    Direction mDirection;
    std::string mAnimType;
    Animations mAnimations;
    AnimBase* mAnimationCurrent;
    TextureManager* mTextureMgr;
    
};

#endif /* SPRITESHEET_H */

