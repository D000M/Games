/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   DecoratorExcercise.h
 * Author: default
 *
 * Created on May 13, 2019, 12:30 PM
 */

#ifndef DECORATOREXCERCISE_H
#define DECORATOREXCERCISE_H

#include <string>
#include <iosfwd>
#include <sstream>
#include <cstring>
#include <assert.h>

namespace DecoratorExcercise {
//  Roses can be red, blue or red and blue. Given the class interface Flower and class Rose, build decorators RedFlower and BlueFlower that would print the following:
//
//    Rose rose;
//    RedFlower red_rose{rose};
//    RedFlower red_red_rose{red_rose};
//    BlueFlower blue_red_rose{red_rose};
//    cout << rose.str();          // "A rose"
//    cout << red_rose.str();      // "A rose that is red"
//    cout << red_red_rose.str();  // "A rose that is red"
//    cout << blue_red_rose.str(); // "A rose that is red and blue"
    
    struct Flower {
        virtual std::string str() const = 0;
    };
    
    struct Rose : Flower {
        std::string str() const override{
            std::ostringstream oss;
            oss << "A rose";
            return oss.str();
        }
    };
    
    struct RedFlower : Flower {
        Flower& rose;
        RedFlower(Flower& temp) : rose{temp} {}
        std::string str() const override {
            std::ostringstream oss;
            oss << rose.str();
            oss << " that is red";
            return oss.str();
        }
    };
    
    struct BlueFlower : Flower {
        Flower& rose;
        BlueFlower(Flower& temp) : rose{temp} {}
        std::string str() const override {
            std::ostringstream oss;
            oss << rose.str();
            if(strlen(rose.str().c_str()) < 10) {
                oss << " that is blue";
            }
            else {
                oss << " and blue";
            }
            return oss.str();
        }
    };
    
    struct RedFlower2 : Flower
    {
        const Flower& temp;
        RedFlower2(const Flower& t = Rose()) : temp{t} {}
        
        template<typename... Args>
        RedFlower2(Flower& t, Args... args) : temp{t}, Flower(forward<Args>(args)...) {}

        std::string str() const override {
            std::ostringstream oss;
            oss << temp.str();
            if(temp.str() == "A rose that is red and blue" || temp.str() == "A rose that is blue and red") {
                return oss.str();
            }
            if(strlen(temp.str().c_str()) < 10) {
                oss << " that is red";
            }
            else {
                oss << " and red";
            }
            return oss.str();
        }

    };

    struct BlueFlower2 : Flower
    {
        const Flower& temp;
        BlueFlower2(const Flower& t = Rose()) : temp{t} {}
        
        template<typename... Args>
        BlueFlower2(Flower& t, Args... args) : temp{t}, Flower(forward<Args>(args)...) {}

        std::string str() const override {
            std::ostringstream oss;
            oss << temp.str();
            if(temp.str() == "A rose that is red and blue" || temp.str() == "A rose that is blue and red") {
                return oss.str();
            }
            if(strlen(temp.str().c_str()) < 10) {
                oss << " that is blue";
            }
            else {
                oss << " and blue";
            }
            return oss.str();
        }
    };
    
    void testDecoratorEx() {
        Rose rose;
        RedFlower2 redRose{rose};
        RedFlower2 redRedRose{redRose};
        BlueFlower2 blueRedRose{redRose};
        BlueFlower2 blueRose{rose};
        std::cout << rose.str() << std::endl;
        std::cout << redRose.str() << std::endl;
        std::cout << redRedRose.str() << std::endl;
        std::cout << blueRose.str() << std::endl;
        std::cout << blueRedRose.str() << std::endl;
    }
    
    void testDecoratorEx2() {
        Rose rose;
        std::cout << rose.str() << std::endl;
        RedFlower2 red;
        std::cout << red.str() << std::endl;
        RedFlower2 redRose{rose};
        std::cout << redRose.str() << std::endl;
        BlueFlower2 blueRose{rose};
        std::cout << blueRose.str() << std::endl;
        RedFlower2 redRedRose{redRose};
        std::cout << redRedRose.str() << std::endl;
        BlueFlower2 blueRedRose{redRose};
        std::cout << blueRedRose.str() << std::endl;
        RedFlower2 redBlueRed{blueRedRose};
        std::cout << redBlueRed.str() << std::endl;
        
        BlueFlower2 blue_rose{rose};
        std::cout << blue_rose.str() << std::endl;
        BlueFlower2 blue{RedFlower2{BlueFlower2{RedFlower2{}}}};
        std::cout << blue.str() << std::endl;
        RedFlower2 red_Flower2{blue_rose};
//        RedFlower2<BlueFlower2<RedFlower2<Rose>>> redBlueRedRose{rose};
//        std::cout << redBlueRedRose.str() << std::endl;
        
//        RedFlower2 redRose2{rose};
//        std::cout << redRose2.str() << std::endl;
    }
}

#endif /* DECORATOREXCERCISE_H */

