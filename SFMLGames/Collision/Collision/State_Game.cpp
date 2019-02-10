/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   State_Game.cpp
 * Author: DooM
 * 
 * Created on January 26, 2019, 1:20 PM
 */

#include <complex>

#include "State_Game.h"
#include "StateManager.h"
#include "game/PlayerCircle.h"
#include "game/EnemyCircle.h"
#include "Constants.h"

State_Game::State_Game(StateManager* l_state) 
    : BaseState(l_state) {
}

State_Game::~State_Game() {
}

void State_Game::OnCreate() {
//    m_increment = sf::Vector2f{400.0f, 400.0f};
    srand(time(nullptr));
    
    sf::Vector2u windowSize = m_stateMgr->GetContext()->m_wind->GetRenderWindow()->getSize();
    
    m_player = new PlayerCircle(constant::playerRadius, windowSize.x / 2.0f, windowSize.y / 2.0f, sf::Color::Blue);
    
    m_stateMgr->GetContext()->m_eventManager->AddCallback(StateType::Game, "Key_Escape", &State_Game::MainMenu, this);
    m_stateMgr->GetContext()->m_eventManager->AddCallback(StateType::Game, "Key_P", &State_Game::Pause, this);
    m_stateMgr->GetContext()->m_eventManager->AddCallback(StateType::Game, "Key_Down", &State_Game::MoveDown, this);
    m_stateMgr->GetContext()->m_eventManager->AddCallback(StateType::Game, "Key_Up", &State_Game::MoveUp, this);
    m_stateMgr->GetContext()->m_eventManager->AddCallback(StateType::Game, "Key_Right", &State_Game::MoveRight, this);
    m_stateMgr->GetContext()->m_eventManager->AddCallback(StateType::Game, "Key_Left", &State_Game::MoveLeft, this);
    
    m_gameTime = 0;
    m_frameTime = 0;
    m_increment = sf::Vector2f{400.0f, 400.0f};
    CreateEnemy(m_gameTime);
}

void State_Game::OnDestroy() {
    delete m_player;
    for(auto& elem : m_enemies) {
        delete elem;
    }
    m_enemies.clear();
    m_stateMgr->GetContext()->m_eventManager->RemoveCallback(StateType::Game, "Key_Escape");
    m_stateMgr->GetContext()->m_eventManager->RemoveCallback(StateType::Game, "Key_P");
    m_stateMgr->GetContext()->m_eventManager->RemoveCallback(StateType::Game, "Key_Down");
    m_stateMgr->GetContext()->m_eventManager->RemoveCallback(StateType::Game, "Key_Up");
    m_stateMgr->GetContext()->m_eventManager->RemoveCallback(StateType::Game, "Key_Right");
    m_stateMgr->GetContext()->m_eventManager->RemoveCallback(StateType::Game, "Key_Left");
}

void State_Game::Acitvate() {

}

void State_Game::Deactivate() {

}

void State_Game::Draw() {
    m_stateMgr->GetContext()->m_wind->GetRenderWindow()->draw(m_player->GetCircle());
    for(int i = 0; i < m_enemies.size(); ++i) {
        m_stateMgr->GetContext()->m_wind->GetRenderWindow()->draw(m_enemies.at(i)->GetCircle());
    }
}

void State_Game::Update(const sf::Time& l_time) {
    
    EnemyMove(l_time);
//    CreateEnemy(m_gameTime);
    m_player->SetCirclePos(m_player->GetCircle().getPosition().x, m_player->GetCircle().getPosition().y);
}

void State_Game::MainMenu(EventDetails* l_details) {
    m_stateMgr->SwitchTo(StateType::MainMenu);
}

void State_Game::Pause(EventDetails* l_details) {
    m_stateMgr->SwitchTo(StateType::Paused);
}

void State_Game::MoveDown(EventDetails* l_details) {
    sf::Vector2u l_windSize = m_stateMgr->GetContext()->m_wind->GetWindowSize();
    if((int(m_player->GetCircle().getPosition().y + constant::playerRadius) < l_windSize.y ) && 
            int(m_player->GetCircle().getPosition().y - constant::playerRadius) >= 0) {
        m_player->SetCirclePos(m_player->GetCircle().getPosition().x, m_player->GetCircle().getPosition().y + constant::playerSpeed);
    }
}

void State_Game::MoveUp(EventDetails* l_details) {
    sf::Vector2u l_windSize = m_stateMgr->GetContext()->m_wind->GetWindowSize();
    if((int(m_player->GetCircle().getPosition().y + constant::playerRadius) <= l_windSize.y ) && 
            int(m_player->GetCircle().getPosition().y - constant::playerRadius) > 0) {
        m_player->SetCirclePos(m_player->GetCircle().getPosition().x, m_player->GetCircle().getPosition().y - constant::playerSpeed);
    }
}

void State_Game::MoveLeft(EventDetails* l_details) {
    sf::Vector2u l_windSize = m_stateMgr->GetContext()->m_wind->GetWindowSize();
    if((int(m_player->GetCircle().getPosition().x + constant::playerRadius) <= l_windSize.x ) && 
            int(m_player->GetCircle().getPosition().x - constant::playerRadius) > 0 ) {
        m_player->SetCirclePos(m_player->GetCircle().getPosition().x - constant::playerSpeed, m_player->GetCircle().getPosition().y);
    }
}

void State_Game::MoveRight(EventDetails* l_details) {
    sf::Vector2u l_windSize = m_stateMgr->GetContext()->m_wind->GetWindowSize();
    if((int(m_player->GetCircle().getPosition().x + constant::playerRadius) < l_windSize.x ) && 
            int(m_player->GetCircle().getPosition().x - constant::playerRadius) >= 0) {
        m_player->SetCirclePos(m_player->GetCircle().getPosition().x + constant::playerSpeed, m_player->GetCircle().getPosition().y);
    }
}

void State_Game::CreateEnemy(int sec) {
    float x = rand() % 760 + 20;
    float y = rand() % 560 + 20;
    sf::Vector2f l_speed{rand() % 600 + 100, rand() % 600 + 100};
    
    m_enemies.push_back(new EnemyCircle(constant::enemyRadius, x, y, sf::Color::Red, l_speed));
    x = rand() % 760 + 20;
    y = rand() % 560 + 20;
    l_speed.x = rand() % 600 + 100;
    l_speed.y = rand() % 600 + 100;
    m_enemies.push_back(new EnemyCircle(constant::enemyRadius, x, y, sf::Color::Green, l_speed));
    x = rand() % 760 + 20;
    y = rand() % 560 + 20;
    l_speed.x = rand() % 600 + 100;
    l_speed.y = rand() % 600 + 100;
    m_enemies.push_back(new EnemyCircle(constant::enemyRadius, x, y, sf::Color::Yellow, l_speed));
    x = rand() % 760 + 20;
    y = rand() % 560 + 20;
    l_speed.x = rand() % 600 + 100;
    l_speed.y = rand() % 600 + 100;
    m_enemies.push_back(new EnemyCircle(constant::enemyRadius, x, y, sf::Color::Magenta, l_speed));
    x = rand() % 760 + 20;
    y = rand() % 560 + 20;
    l_speed.x = rand() % 600 + 100;
    l_speed.y = rand() % 600 + 100;
    m_enemies.push_back(new EnemyCircle(constant::enemyRadius, x, y, sf::Color::White, l_speed));
    
}

void State_Game::EnemyMove(const sf::Time& l_time) {
    m_gameTime += l_time.asSeconds();
    if(m_gameTime > 0.05f) {
        m_gameTime = 0;
        for(int i = 0; i < m_enemies.size(); ++i) {
            m_enemies.at(i)->m_isColliding = false;
        }
    }
    ProceedCollisions();
    sf::Vector2u l_windSize = m_stateMgr->GetContext()->m_wind->GetWindowSize();
    for(int i = 0; i < m_enemies.size(); ++i) {
        if(m_enemies.at(i)->GetCircle().getPosition().x + constant::enemyRadius > l_windSize.x && m_enemies.at(i)->getDirection().x > 0 ||
                m_enemies.at(i)->GetCircle().getPosition().x - constant::enemyRadius < 0 &&  m_enemies.at(i)->getDirection().x < 0) {
            m_enemies.at(i)->SetXDirection();
        }
        if(m_enemies.at(i)->GetCircle().getPosition().y + constant::enemyRadius > l_windSize.y &&  m_enemies.at(i)->getDirection().y > 0 ||
                m_enemies.at(i)->GetCircle().getPosition().y - constant::enemyRadius < 0 &&  m_enemies.at(i)->getDirection().y < 0) {
            m_enemies.at(i)->SetYDirection();
        }

        m_enemies.at(i)->SetCirclePos(m_enemies.at(i)->GetCircle().getPosition().x + (m_enemies.at(i)->getDirection().x * l_time.asSeconds()), 
                m_enemies.at(i)->GetCircle().getPosition().y + (m_enemies.at(i)->getDirection().y * l_time.asSeconds()));
    }
    
}

bool State_Game::CheckCollision(float x1, float y1, float rad1, float x2, float y2, float rad2) {
    return abs((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2)) < (rad1 + rad2) * (rad1 + rad2);
}

void State_Game::ProceedCollisions() {
    for(int i = 0; i < m_enemies.size(); ++i) {
        for(int j = 0; j < m_enemies.size(); ++j) {
            if( i != j) {
                if(CheckCollision(m_enemies.at(i)->GetCircle().getPosition().x, m_enemies.at(i)->GetCircle().getPosition().y, m_enemies.at(i)->GetCircle().getRadius(),
                        m_enemies.at(j)->GetCircle().getPosition().x, m_enemies.at(j)->GetCircle().getPosition().y, m_enemies.at(j)->GetCircle().getRadius())) {
                    if(!m_enemies.at(i)->m_isColliding && !m_enemies.at(j)->m_isColliding) {
                        MoveAway(*m_enemies.at(i), *m_enemies.at(j));
                        m_enemies.at(i)->m_isColliding = true;
                        m_enemies.at(j)->m_isColliding = true;
                    }
                }
            }
        }
    }
}

void State_Game::BouncingCircles(BaseCircle& first, BaseCircle& second) {
        float firstNewX = (first.getDirection().x * (10 - 5) + (2 * 5 * second.getDirection().x)) / (10 + 5);
        float firstNewY = (first.getDirection().y * (10 - 5) + (2 * 5 * second.getDirection().y)) / (10 + 5);
        float secondNewX = (second.getDirection().x * (5 - 10) + (2 * 10 * first.getDirection().x)) / (10 + 5);
        float secondNewY = (second.getDirection().y * (5 - 10) + (2 * 10 * first.getDirection().y)) / (10 + 5);
        first.SetXCollision(firstNewX);
        first.SetYCollision(firstNewY);
        second.SetXCollision(secondNewX);
        second.SetYCollision(secondNewY);
//    newVelX1 = (firstBall.speed.x * (firstBall.mass – secondBall.mass) + (2 * secondBall.mass * secondBall.speed.x)) / (firstBall.mass + secondBall.mass);
//    newVelY1 = (firstBall.speed.y * (firstBall.mass – secondBall.mass) + (2 * secondBall.mass * secondBall.speed.y)) / (firstBall.mass + secondBall.mass);
//    newVelX2 = (secondBall.speed.x * (secondBall.mass – firstBall.mass) + (2 * firstBall.mass * firstBall.speed.x)) / (firstBall.mass + secondBall.mass);
//    newVelY2 = (secondBall.speed.y * (secondBall.mass – firstBall.mass) + (2 * firstBall.mass * firstBall.speed.y)) / (firstBall.mass + secondBall.mass);
}

sf::Vector2f State_Game::findClosestPoint(float lx1, float ly1, float lx2, float ly2, float x0, float y0) {
    float A1 = ly2 - ly1;
    float B1 = lx1 - lx2;
    double C1 = (ly2 - ly1) * lx1 + (lx1 - lx2) * ly1;
    double C2 = (-B1 * x0) + (A1 * y0);
    double det = A1 * A1 - -B1 * B1;
    float cx = 0;
    float cy = 0;
    if(det != 0) {
        cx = (float)((A1 * C1 - B1 * C2) / det);
        cy = (float)((A1 * C2 - -B1 * C1) / det);
    }
    else {
        cx = x0;
        cy = y0;
    }
    return sf::Vector2f{cx, cy};
}

void State_Game::MoveAway(BaseCircle& first, BaseCircle& second) {
    float dist = sqrt(((second.GetCircle().getPosition().x - first.GetCircle().getPosition().x) * (second.GetCircle().getPosition().x - first.GetCircle().getPosition().x)) +
    ((second.GetCircle().getPosition().y - first.GetCircle().getPosition().y) * (second.GetCircle().getPosition().y - first.GetCircle().getPosition().y)));
    float c1x = first.GetCircle().getPosition().x;
    float c1y = first.GetCircle().getPosition().y;
    float c2x = second.GetCircle().getPosition().x;
    float c2y = second.GetCircle().getPosition().y;
    float c1vx = first.getDirection().x;
    float c1vy = first.getDirection().y;
    float c2vx = second.getDirection().x;
    float c2vy = second.getDirection().y;
    float c1rad = first.GetCircle().getRadius();
    float c2rad = second.GetCircle().getRadius();
    
    sf::Vector2f d = findClosestPoint(c1x, c1y, 
                c1x + c1vx, c1y + c1vy, c2x, c2y); 
    double closestdistsq = std::pow(c2x - d.x, 2) + std::pow(c2y - d.y, 2); 
    
    if(closestdistsq <= std::pow(c1rad + c2rad, 2)){ 
        double dist = sqrt(std::pow(c1x - c2x, 2) + std::pow(c1y - c2y, 2)); 
        double nx = (c2x - c1x) / dist; 
        double ny = (c2y - c1y) / dist; 
        double p = 2 * (c1vx * nx + c1vy * ny - c2vx * nx - c2vy * ny) / (first.mass + second.mass); 
        float vx1 = c1vx - p * first.mass * nx; 
        float vy1 = c1vy - p * first.mass * ny; 
        float vx2 = c2vx + p * second.mass * nx; 
        float vy2 = c2vy + p * second.mass * ny;
        first.SetXCollision(vx1);
        first.SetYCollision(vy1);
        second.SetXCollision(vx2);
        second.SetYCollision(vy2);
    }else{ 
        // no collision has occurred
    }
}
