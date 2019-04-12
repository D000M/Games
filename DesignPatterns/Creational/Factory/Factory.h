/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Factory.h
 * Author: default
 *
 * Created on April 12, 2019, 3:49 PM
 */

#ifndef FACTORY_H
#define FACTORY_H

namespace Factory {

    class Point {
    public:
        Point(float x, float y)
        : x(x), y(y) {}
        float x, y;
                
        friend std::ostream& operator<<(std::ostream& os, const Point& obj) {
            os << obj.x << " " << obj.y;
            return os;
        }

    }; //end of Point

    struct PointFactory {
        //Cartesian coordinate system
        static Point newCartesian(float x, float y) {
            return {x, y};
        }
        //Polar coordinate system
        static Point newPolar(float rho, float thet) {
            return {rho * std::cos(thet), rho * std::sin(thet)};
        }
    };
    
    void testPoint() {
        auto myPt = PointFactory::newCartesian(5, 10);
        auto myPt2 = PointFactory::newPolar(45, 28);
        std::cout << "Point 1: " << myPt << std::endl;
        std::cout << "Point 2: " << myPt2 << std::endl;
    }
}   //end namespace Factory

#endif /* FACTORY_H */

