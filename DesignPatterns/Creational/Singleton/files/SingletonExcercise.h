/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   SingletonExcercise.h
 * Author: default
 *
 * Created on April 18, 2019, 3:06 PM
 */

#ifndef SINGLETONEXCERCISE_H
#define SINGLETONEXCERCISE_H
#include <functional>
#include <iostream>
using namespace std;

struct SingletonTester
{
  template <typename T>
  bool is_singleton(function<T*()> factory)
  {
    // TODO
      if(typeid(factory) == typeid(T)) {
          return true;
      }
      else {
          return false;
      }
  }
};

void testSingletonTester() {
    SingletonTester st;
//    if(st.is_singleton(Factory::PointFactory::newCartesian(10, 15))){
//        std::cout << "Is Factory!\n";
//    }
//    else {
//        std::cout << "Is Singleton!\n";
//    }
}

#endif /* SINGLETONEXCERCISE_H */

