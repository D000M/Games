/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   BaseAnim.h
 * Author: default
 *
 * Created on June 25, 2019, 1:45 PM
 */

#ifndef BASEANIM_H
#define BASEANIM_H

#include <string>

class SpriteSheet;
using Frame = unsigned int;

class AnimBase {
    friend class SpriteSheet;
public:
    AnimBase();
    virtual ~AnimBase();
    
    //Getters and Setters
    void setSpriteSheet(SpriteSheet* lSheet);
    void setFrame(Frame lFrame);
    void setStartFrame(Frame lFrame);
    void setEndFrame(Frame lFrame);
    void setFrameRow(Frame lFrame);
    void setActionStart(int lFrame);
    void setActionEnd(int lFrame);
    void setFrameTime(float lTime);
    void setLooping(bool lLoop);
    void setName(const std::string& lName);
    
    SpriteSheet* getSpriteSheet();
    Frame getFrame();
    Frame getStartFrame();
    Frame getEndFrame();
    Frame getRowFrame();
    int getActionStart();
    int getActionEnd();
    float getFrameTime();
    float getElapsedTime();
    bool isLooping();
    bool isPlaying();
    bool isInAction();
    std::string getName();
    
    void play();
    void pause();
    void stop();
    void reset();
    
    virtual void update(const float& ldT);
    
    friend std::stringstream& operator >> (std::stringstream& stream, AnimBase& obj) {
        obj.readIn(stream);
        return stream;
    }
    
protected:
    virtual void frameStep() = 0;
    virtual void cropSprite() = 0;
    virtual void readIn(std::stringstream& lStream) = 0;
    
    
    Frame mFrameCurrent;
    Frame mFrameStart;
    Frame mFrameEnd;
    Frame mFrameRow;
    int mFrameActionStart;
    int mFrameActionEnd;
    float mFrameTime;
    float mElapsedTime;
    bool mLoop;
    bool mPlaying;
    
    std::string mName;
    SpriteSheet* mSpriteSheet;
};

#endif /* BASEANIM_H */

