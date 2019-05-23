/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   ObservablePlayer.h
 * Author: default
 *
 * Created on May 21, 2019, 11:10 AM
 */

#ifndef OBSERVABLEPLAYER_H
#define OBSERVABLEPLAYER_H

#include <iostream>

#include "Observer.h"
#include "Observable.h"
#include "SaferObservable.h"
#include <boost/signals2.hpp>   //For Observer Pattern

namespace ObserverPattern {

    class Player : public Observable<Player> {  //Observable
        int age;
    public:
        Player() {}
        Player(int a) : age{age} {}
        int getAge() const {
            return age;
        }

        void setAge(int age) {
            //Dont notify if age is not changed.
            if(this->age == age) {
                return;
            }
//            auto canVote = getCanVote();    //Dependancy problem
            this->age = age;
            notify(*this, "age");
            //Dependancy Problem
            if(true == getCanVote()) {
                notify(*this, "getCanVote");
            }
        }
        //Problems with Dependency
        bool getCanVote() const {
            return age >= 16;
        }
    };

    //2 Components Observer and Observable
    //Observer - monitoring something. Observable - the component that is to be monitored.

    struct ConsolePlayerObserver : public Observer<Player> {
    private:
        void fieldChange(Player& source, const std::string& fieldName) override {
            std::cout << "Player's " << fieldName << " has change to ";
            if(fieldName == "age") {
                std::cout << source.getAge();
            }
            if(fieldName == "getCanVote") {
                std::cout << std::boolalpha <<source.getCanVote();
            }
            std::cout << ".\n";
        }

    };

    void testPlayerObservable() {
        Player player{10};
        ConsolePlayerObserver cpo;

        player.subscribe(cpo);
        player.setAge(15);
        player.setAge(20);

        player.unsubscribe(cpo);
        player.setAge(25);
    }
    
    //Dependancy Problem
    void testObserverDependancyProblem() {
        Player p;
        ConsolePlayerObserver cpo;
        p.subscribe(cpo);
        p.setAge(10);
        p.setAge(15);
        p.setAge(16);
    }
    
    //Using boost::signals::signals2 //boost own implementation of Observer pattern
    template<typename T> struct BoostObservable {
        boost::signals2::signal<void(T&, const std::string&)> fieldChange;
    };
    class Player2 : public BoostObservable<Player2> {
        int age;
    public:
        int getAge() const {
            return age;
        }

        void setAge(int age) {
            if(this->age == age) {
                return;
            }
            this->age = age;
            fieldChange(*this, "age");
        }

    };
    void testBoostObservable() {
        Player2 p2;
        //Connect to observer
        auto conn = p2.fieldChange.connect(
            [](Player2& p, const std::string& fieldName) {
                std::cout << fieldName << " has changed!\n";
            }
        );
        
        p2.setAge(10);
        p2.setAge(20);
        //Disconect the observer
        conn.disconnect();
        p2.setAge(30);
    }
    //End boost::signals2::signal type Observer
    
    
    //Tread safety observer
    class SaferPlayer : public SaferObservable<SaferPlayer> {  //Observable
        int age;
    public:
        SaferPlayer() {}
        SaferPlayer(int a) : age{age} {}
        int getAge() const {
            return age;
        }

        void setAge(int age) {
            //Dont notify if age is not changed.
            if(this->age == age) {
                return;
            }
//            auto canVote = getCanVote();    //Dependancy problem
            this->age = age;
            notify(*this, "age");
            //Dependancy Problem
            if(true == getCanVote()) {
                notify(*this, "getCanVote");
            }
        }
        //Problems with Dependency
        bool getCanVote() const {
            return age >= 16;
        }
    };
    
    struct TrafficAdministration : Observer<SaferPlayer> {
        void fieldChange(SaferPlayer& source, const std::string& fieldName) override {
            if(fieldName == "age") {
                if(source.getAge() < 17) {
                    std::cout << "To young to drive!\n";
                }
                else {
                    std::cout << "Oh Ok we no longer care!\n";
                    source.unsubscribe(*this);
                }
            }
        }

    };
    
    void testSafetyObservable() {
        SaferPlayer p2;
        TrafficAdministration ta;
        p2.subscribe(ta);
        p2.setAge(15);
        p2.setAge(16);
        
        try {
            p2.setAge(17);
        }
        catch(const std::exception& e) {
            std::cout << "Ooops, " << e.what() << std::endl;
        }
        std::cout << "Exit Program!\n";
    }
    
}
#endif /* OBSERVABLEPLAYER_H */

