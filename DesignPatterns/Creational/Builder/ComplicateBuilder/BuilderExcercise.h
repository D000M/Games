/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   BuilderExcercise.h
 * Author: default
 *
 * Created on April 12, 2019, 10:50 AM
 */

#ifndef BUILDEREXCERCISE_H
#define BUILDEREXCERCISE_H

#include <string>
#include <vector>

namespace excercise {
    
    /**
     * Desired output
    class Person {
        string name;
        int age;
    };
    */
    
    class CodeBuilder;
    
    class Code {
    public:
        std::string className;
        std::string name, type;
        std::vector<Code> elements;
        
        const std::size_t indentSize = 2;
        Code() {}
        Code(const std::string& className) 
            : className{className} {
            
        }
   
            
        //Function to print
        friend std::ostream& operator<<(std::ostream& os, const Code& obj) {
            os << "class " <<obj.className << std::endl;
            os << "{" << std::endl;
            std::string i(obj.indentSize, ' ');
            for(const auto& elem : obj.elements) {
                os << i << elem.type << " " << elem.name << ";" << std::endl;
            }
            os << "};" << std::endl;
            return os;
        }
    
    };
    
    class CodeBuilder{
        Code code;
    public:
        CodeBuilder(const std::string& class_name) {
            // Todo
            code.className = class_name;
        }
        
        CodeBuilder& add_field(const std::string& name, const std::string& type) {
            code.name = name;
            code.type = type;
            code.elements.emplace_back(code);
            return *this;
        }
        friend std::ostream& operator<<(std::ostream& os, const CodeBuilder& obj) {
            os << obj.code;
            return os;
        }

    };
    
    void testBuilderExcercise() {
//        CodeBuilder builder{"Person"};
//        std::cout << builder << std::endl;
        
        auto cb = CodeBuilder("Person").add_field("name", "string").add_field("age", "int");
        std::cout << cb << std::endl;
    }
}   //namespace excercise

#endif /* BUILDEREXCERCISE_H */
