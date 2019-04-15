/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   PrototypeExcercise.h
 * Author: default
 *
 * Created on April 15, 2019, 4:42 PM
 */

#ifndef PROTOTYPEEXCERCISE_H
#define PROTOTYPEEXCERCISE_H

#include <iostream>


namespace PrototypeExcercise {

    struct Point {
        int x{ 0}, y{ 0};

        Point() {
        }

        Point(const int x, const int y) : x{x}, y{y}
        {
            std::cout << "Point Created: " << x << " " << y << std::endl;
        }
        Point(const Point& other)
            : x{other.x},
              y{other.y}{
                std::cout << "Point: " << x << " " << y << ", Copied!\n";
        }
        ~Point() {
            std::cout << "Point " << x << " " << y <<" Destroyed\n";
        }
        friend std::ostream& operator<<(std::ostream& os, const Point& obj) {
            os << obj.x << " " << obj.y;
            return os;
        }


    };

    struct Line {
        Point *start, *end;

        Line(Point * const start, Point * const end)
            : start(start), end(end) {
        }

        Line(const Line& other)
            : start{new Point{*other.start}},
              end{new Point{*other.end}}{
                std::cout << "Line: " << other.start->x << " " << other.start->y << ", " << other.end->x << " " << other.end->y << ", Copied!\n";
        }
        
        ~Line() {
            delete start;
            delete end;
        }

        Line deep_copy() const {
            return *this; //Return copy object constructed by copy Constructor of this Line
        }
        friend std::ostream& operator<<(std::ostream& os, const Line& obj) {
            os << "Start Point: " << *obj.start << ", End Point: " << *obj.end;
            return os;
        }

    };
    
    void testDeepCopyLine() {

        Line lineA(new Point{5,5}, new Point{7,7});
        std::cout << "Original: " << lineA << std::endl;
        Line pointCopy{lineA};
        std::cout << "Deep Copy: " << pointCopy << std::endl;
    }
}

#endif /* PROTOTYPEEXCERCISE_H */

