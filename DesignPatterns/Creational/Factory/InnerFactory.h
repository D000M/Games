/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   InnerFactory.h
 * Author: default
 *
 * Created on April 12, 2019, 3:55 PM
 */

#ifndef INNERFACTORY_H
#define INNERFACTORY_H

namespace InnerFactory {

    class Point {
        Point(float x, float y)
        : x(x), y(y) {}
        float x, y;
             
        //Variant 1 with public static class
//    public:
//        friend std::ostream& operator<<(std::ostream& os, const Point& obj) {
//            os << obj.x << " " << obj.y;
//            return os;
//        }
//        class PointFactory {
//            PointFactory() {}
//        public:
//            //Cartesian coordinate system
//            static Point newCartesian(float x, float y) {
//                return {x, y};
//            }
//            //Polar coordinate system
//            static Point newPolar(float rho, float thet) {
//                return {rho * std::cos(thet), rho * std::sin(thet)};
//            }
//        };
        //Variant 2 with private static class and public static variable to this class
    public:
        friend std::ostream& operator<<(std::ostream& os, const Point& obj) {
            os << obj.x << " " << obj.y;
            return os;
        }
        
    private:
        class PointFactory {
            PointFactory() {}
        public:
            //Cartesian coordinate system
            static Point newCartesian(float x, float y) {
                return {x, y};
            }
            //Polar coordinate system
            static Point newPolar(float rho, float thet) {
                return {rho * std::cos(thet), rho * std::sin(thet)};
            }
        };
    public:
        static PointFactory factory;
    }; //end of Point

    
    
    void testPoint() {
        //With public static class
//        auto myPt = Point::PointFactory::newCartesian(5, 10);
//        auto myPt2 = Point::PointFactory::newPolar(45, 28);
//        std::cout << "Point 1: " << myPt << std::endl;
//        std::cout << "Point 2: " << myPt2 << std::endl;
        
        //With private static class and public static variable to the factory
        auto myPt = Point::factory.newCartesian(5, 10);
        auto myPt2 = Point::factory.newPolar(5, 10);
        std::cout << "Point 1: " << myPt << std::endl;
        std::cout << "Point 2: " << myPt2 << std::endl;
    }
}   //end namespace InnerFactory

#endif /* INNERFACTORY_H */

