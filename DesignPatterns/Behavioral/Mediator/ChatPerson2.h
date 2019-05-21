/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   ChatPerson2.h
 * Author: default
 *
 * Created on May 20, 2019, 1:31 PM
 */

#ifndef CHATPERSON2_H
#define CHATPERSON2_H

#include <string>
#include <vector>
using namespace std;

struct ChatRoom2;

struct ChatPerson2 {
  string name;
  ChatRoom2* room{nullptr};
  vector<string> chat_log;

  ChatPerson2(const string &name);

  void say(const string& message) const;
  void pm(const string& who,
    const string& message) const;

  void receive(const string& origin,
    const string& message);

  bool operator==(const ChatPerson2 &rhs) const;

  bool operator!=(const ChatPerson2 &rhs) const;
};

#endif /* CHATPERSON2_H */

