/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   ChatRoom2.h
 * Author: default
 *
 * Created on May 20, 2019, 1:33 PM
 */

#ifndef CHATROOM2_H
#define CHATROOM2_H


#include <algorithm>
#include <vector>
#include <string>
#include "ChatPerson2.h"
using namespace std;

struct ChatRoom2
{
  vector<ChatPerson2*> people;

  void broadcast(const string& origin,
    const string& message);

  void join(ChatPerson2* p);

  void message(const string& origin,
    const string& who,
    const string& message)
  {
    auto target = std::find_if(
      begin(people),
      end(people),
      [&](const ChatPerson2 *p) {
        return p->name == who;
      });
    if (target != end(people))
    {
      (*target)->receive(origin, message);
    }
  }
};

#endif /* CHATROOM2_H */

