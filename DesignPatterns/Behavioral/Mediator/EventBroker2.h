/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   EventBroker2.h
 * Author: default
 *
 * Created on May 20, 2019, 2:14 PM
 */

#ifndef EVENTBROKER2_H
#define EVENTBROKER2_H

#include <boost/signals2.hpp>
#include <iostream>

struct EventData {
    virtual void print() const = 0;
};

struct FootballGame {
    boost::signals2::signal<void(EventData*)> events;
};


struct PlayerScoredData : EventData {
    std::string playerName;
    int goalsScoredSoFar;
    
    PlayerScoredData(const std::string& playerName, int goalsScoredSoFar)
        : playerName(playerName), goalsScoredSoFar(goalsScoredSoFar) {
    }

    void print() const override {
        std::cout << playerName << " has scored! (their " << goalsScoredSoFar << " goal)\n"; 
    }

};

struct Player {
    std::string name;
    int goalsScored{0};
    FootballGame& game;
    
    Player(const std::string& name, FootballGame& game)
        : name(name), game(game) {
    }

    void score() {
        goalsScored++;
        PlayerScoredData ps{name, goalsScored};
        game.events(&ps);
    }
    
};

struct Coach {
    FootballGame& game;
    
    Coach(FootballGame& game)
        :game(game) {
        game.events.connect([](EventData* e) {
           PlayerScoredData* ps = dynamic_cast<PlayerScoredData*>(e);
           if(ps && ps->goalsScoredSoFar < 3) {
               std::cout << "coach says well done: " << ps->playerName << "!\n";
           }
        });
    }

};

void testFootballGameEventBroke() {
    FootballGame game;
    Player sam{"sam", game};
    Coach coach{game};
    sam.score();
    sam.score();
    sam.score();
    
}
#endif /* EVENTBROKER2_H */

