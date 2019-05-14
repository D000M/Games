/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Adaptor.h
 * Author: default
 *
 * Created on April 18, 2019, 4:30 PM
 */

#ifndef ADAPTOR_H
#define ADAPTOR_H

namespace AdaptorExcercise {
    struct Square
    {
      int side{ 0 };


      explicit Square(const int side)
        : side(side)
      {
      }
    };

    struct Rectangle
    {
      virtual int width() const = 0;
      virtual int height() const = 0;

      int area() const
      {
        return width() * height();
      }
    };

    struct SquareToRectangleAdapter : Rectangle
    {
      SquareToRectangleAdapter(const Square& square)
      {
          // todo
          w = square.side;
          h = square.side;
      }
      // todo
      int height() const override {
          return h;
      };
      int width() const override {
          return w;
      };
      
      int w;
      int h;
    };
}

#endif /* ADAPTOR_H */

