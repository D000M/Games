/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   LifeWithoutBuilder.h
 * Author: default
 *
 * Created on April 11, 2019, 3:31 PM
 */

#ifndef LIFEWITHOUTBUILDER_H
#define LIFEWITHOUTBUILDER_H

#include <string>
#include <iostream>
#include <sstream>


namespace NotABuilder {
    void testHTML() {
        auto text = "Hello";
        std::string output{""};
        output += "<p>";
        output += text;
        output += "</p>\n";
        
        std::cout << output << std::endl;
        
        std::string words[] = {"Hello", "World"};
        std::ostringstream oss;
        oss << "<ul>\n";
        for(auto& word : words) {
            oss << " <li>" << word << "</li>\n";
        }
        oss << "</ul>\n";
        std::cout << oss.str() << std::endl;
    }
}

#endif /* LIFEWITHOUTBUILDER_H */

