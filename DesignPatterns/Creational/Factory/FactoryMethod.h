/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   FactoryMethod.h
 * Author: default
 *
 * Created on April 12, 2019, 3:41 PM
 */

#ifndef FACTORYMETHOD_H
#define FACTORYMETHOD_H

#include <complex>


namespace FactoryMethod {

    class Point {
    private:
        Point(float x, float y)
        : x(x), y(y) {}

    public:
        float x, y;
        //Cartesian coordinate system
        static Point newCartesian(float x, float y) {
            return {x, y};
        }
        //Polar coordinate system
        static Point newPolar(float rho, float thet) {
            return {rho * std::cos(thet), rho * std::sin(thet)};
        }
        
        friend std::ostream& operator<<(std::ostream& os, const Point& obj) {
            os << obj.x << " " << obj.y;
            return os;
        }

    }; //end of Point

    void testPoint() {
        auto myPt = Point::newCartesian(5, 10);
        auto myPt2 = Point::newPolar(45, 28);
        std::cout << "Point 1: " << myPt << std::endl;
        std::cout << "Point 2: " << myPt2 << std::endl;
    }
}
#endif /* FACTORYMETHOD_H */

