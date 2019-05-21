/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   TestChatRoom.h
 * Author: default
 *
 * Created on May 20, 2019, 1:18 PM
 */

#ifndef TESTCHATROOM_H
#define TESTCHATROOM_H

#include "ChatRoom2.h"
#include "ChatPerson2.h"


namespace Mediator {
    
    void testChatRoom() {
        
        ChatRoom2 room;
        ChatPerson2 john{"john"};
        ChatPerson2 jane{"jane"};
        
        room.join(&john);
        room.join(&jane);

        john.say("Hi, Room");
        jane.say("Oh, hey John");
        
        ChatPerson2 simon{"simon"};
        room.join(&simon);
        simon.say("Hey, Everyone");
        
        jane.pm("simon", "Glad you Found us, Simon!");
    }
}


#endif /* TESTCHATROOM_H */

