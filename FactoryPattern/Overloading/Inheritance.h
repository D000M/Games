/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Inheritance.h
 * Author: default
 *
 * Created on March 25, 2019, 4:42 PM
 */

#ifndef INHERITANCE_H
#define INHERITANCE_H

#include <string>
#include <iostream>

class Employee {
private:
    int employeeId;
    std::string name;
public:
    Employee(int id, const std::string& s) {
        employeeId = id;
        name = s;
    }
    int getEmployeeId() const {
        return employeeId;
    }
    std::string getEmployeeName() const {
        return name;
    }
};

class FullPartEmployee : public Employee {
private:
    float salary;
public:
    FullPartEmployee(int id, const std::string& n, float s) 
     : Employee(id, n) {
         salary = s;
    }
    float getSalary() const {
        return salary;
    } 
};

class PartTimeEmployee : public Employee {
private:
    float wage;
public:
    PartTimeEmployee(int id, const std::string& n, float w) 
        : Employee(id, n) {
        wage = w;
    }
    float getWage() const {
        return wage;
    }    
};

void testEmployee() {
    FullPartEmployee fullE1{1, "BaHuA", 2500.45f};
    PartTimeEmployee partE{2, "MySelf", 3500.55f};
    std::cout << fullE1.getEmployeeName() << " " << fullE1.getEmployeeId() << " " << fullE1.getSalary() << std::endl;
    std::cout << partE.getEmployeeName() << " " << partE.getEmployeeId() << " " << partE.getWage() << std::endl;
}


class Shape {
public:
    virtual void draw() = 0;
    virtual float area() const = 0;
    virtual float perimeter() const = 0;
};
class Rectangle : public Shape {
    int width;
    int height;
public:
    Rectangle(int w, int h){
        width = w;
        height = h;
    }
    void draw() override {
        std::cout << "Rect with width: " << width << ", and height: " << height << std::endl;
    }
    float area() const override {
        return width * height;
    }
    float perimeter() const override {
        return 2 * ( width + height );
    }

};
class Circle : public Shape {
    float radius;
public:
    Circle(float r) {
        radius = r;
    }
    void draw() override {
        std::cout << "Circle with radius: " << radius << std::endl;
    }
    float area() const override {
        return 3.14f * radius * radius;
    }
    float perimeter() const override {
        return 2 * 3.14f * radius;
    }

};
class Triangle : public Shape {
public:
    
};
void testPolymorphism()  {
    Shape* sPtr = new Circle(4.55f);
    sPtr->draw();
    std::cout << "Area of Circle: " << sPtr->area() << std::endl;
    std::cout << "Perimeter of Circle: " << sPtr->perimeter() << std::endl;
    delete sPtr;
    sPtr = new Rectangle(4, 8);
    sPtr->draw();
    std::cout << "Area of Rectangle: " << sPtr->area() << std::endl;
    std::cout << "Perimeter of Rectangle: " << sPtr->perimeter() << std::endl;
    delete sPtr;
}
#endif /* INHERITANCE_H */

