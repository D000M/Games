/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   ChatRoom2.cpp
 * Author: default
 * 
 * Created on May 20, 2019, 1:33 PM
 */

#include "ChatRoom2.h"


void ChatRoom2::broadcast(const string &origin, const string &message)
{
  for (auto p : people)
    if (p->name != origin)
      p->receive(origin, message);
}

void ChatRoom2::join(ChatPerson2 *p)
{
  string join_msg = p->name + " joins the chat";
  broadcast(" room", join_msg);
  p->room = this;
  people.push_back(p);
}

