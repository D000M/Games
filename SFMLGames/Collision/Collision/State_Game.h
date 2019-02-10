/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   State_Game.h
 * Author: DooM
 *
 * Created on January 26, 2019, 1:20 PM
 */

#ifndef STATE_GAME_H
#define STATE_GAME_H

#include "BaseState.h"
#include "EventManager.h"
#include "game/BaseCircle.h"


class State_Game : public BaseState {
public:
    State_Game(StateManager* l_state);
    virtual ~State_Game();
    
    void OnCreate() override;
    void OnDestroy() override;

    void Acitvate() override;
    void Deactivate() override;

    void Draw() override;
    void Update(const sf::Time& l_time) override;

    void MainMenu(EventDetails* l_details);
    void Pause(EventDetails* l_details);
    
    void MoveRight(EventDetails* l_details);
    void MoveLeft(EventDetails* l_details);
    void MoveDown(EventDetails* l_details);
    void MoveUp(EventDetails* l_details);
    
    //Logic
    void CreateEnemy(int sec);
    void EnemyMove(const sf::Time& l_time);
    void ProceedCollisions();
    bool CheckCollision(float x1, float y1, float rad1, float x2, float y2, float rad2);
    void MoveAway(BaseCircle& first, BaseCircle& second);
    void BouncingCircles(BaseCircle& first, BaseCircle& second);
private:
    sf::Vector2f m_increment;
    BaseCircle* m_player;
    std::vector<BaseCircle*> m_enemies;
    float m_gameTime;
    float m_frameTime;
    
    sf::Vector2f findClosestPoint(float lx1, float ly1, float lx2, float ly2, float x0, float y0);
};

#endif /* STATE_GAME_H */

