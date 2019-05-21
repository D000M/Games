/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   ChatPerson2.cpp
 * Author: default
 * 
 * Created on May 20, 2019, 1:31 PM
 */

#include "ChatPerson2.h"
#include "ChatRoom2.h"
#include <iostream>

ChatPerson2::ChatPerson2(const string &name) : name(name) {}

void ChatPerson2::say(const string &message) const
{
  room->broadcast(name, message);
}

void ChatPerson2::pm(const string &who, const string &message) const
{
  room->message(name, who, message);
}

void ChatPerson2::receive(const string &origin, const string &message)
{
  string s{origin + ": \"" + message + "\""};
  std::cout << "[" << name << "'s chat session] " << s << "\n";
  chat_log.emplace_back(s);
}

bool ChatPerson2::operator==(const ChatPerson2 &rhs) const {
  return name == rhs.name;
}

bool ChatPerson2::operator!=(const ChatPerson2 &rhs) const {
  return !(rhs == *this);
}

