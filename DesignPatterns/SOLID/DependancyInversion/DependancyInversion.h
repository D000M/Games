/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * 
 * 
 * tuple iteration
 * Tuple Iteration
 * Tuple Traverse
 * File:   DependancyInversion.h
 * Author: default
 *
 * Created on April 11, 2019, 1:58 PM
 */

#ifndef DEPENDANCYINVERSION_H
#define DEPENDANCYINVERSION_H

#include <string>
#include <vector>
#include <tuple>
#include <iostream>
#include <algorithm>
#include <utility>

/**
 * Simple specify the best way to form dependencies between different objects.
 * Split between 2 different ideas >>>
 * 1 - High-Level modules should not depend on low-level modules. Both should depend on abstractions.
 * 2 - Abstraction should not depend on details. Details should depend on abstractions. 
 */

namespace DependancyInv {
    
    enum class Relationship {
        PARENT,
        CHILD,
        SIBLING
    };
    
    struct Person {
        std::string name;
    };
    
    ////Instead of having high-level dependency of a low-level approach we must use some abstractions
    //Correct Way
    
    struct RelationshipBrowser {
        virtual std::vector<Person> findAllChildrenOfAParent(const std::string& lName) = 0;
    }; //Now we can implement this interface in to our Relationships class
    //Wrong Way
    //Low level struct to actualy storing relationships
    struct Relationships : RelationshipBrowser{  //low-level module. Essentialy provide a data structure of vector of tuples to store 
            //our Person , and provide utility function to add data in the vector.
        
        std::vector<std::tuple<Person, Relationship, Person>> relations;
        
        void addParentAndChild(const Person& parent, const Person& child) {
            relations.push_back({parent, Relationship::PARENT, child});
            relations.push_back({child, Relationship::CHILD, parent});
        }
        
        std::vector<Person> findAllChildrenOfAParent(const std::string& lName) override {
            std::vector<Person> result;
            for(auto& elem : relations) {
                if(std::get<0>(elem).name == "John" && std::get<1>(elem) == Relationship::PARENT) {
                    std::cout << "John Has a Child Called " << std::get<2>(elem).name << std::endl;
                }
            }
            return result;
        }

    };  //End of struct Relationship
    
    struct Research {   //High-level
        //Wrong way cause we will make High level module which directly depends on low-level module
        //thus we break 1st princip of Dependency Inversions
        Research(Relationships& relationships) {
//            auto& relations = relationships.relations;
            
            //C++17 traversing a tuple doesnt work
//            for(auto&& [first, rel, second] : relations) {
//                if(first.name == "John" && rel == Relationship::PARENT) {
//                    std::cout << "John has a child called " << second.name << std::endl;
//                }
//            }
            
            //c++11 approach Both Working
//            for(int i = 0; i < relationships.relations.size(); i++) {
//                
//                std::string parentName = std::get<0>(relationships.relations[i]).name;
//                
//                if(parentName == "John" && std::get<1>(relationships.relations[i]) == Relationship::PARENT) {
//                    
//                    std::string childName = std::get<2>(relationships.relations[i]).name;
//                    std::cout << "John Has a Child Called " << childName << std::endl;
//                    
//                }
//            }
            
            for(auto& elem : relationships.relations) {
                if(std::get<0>(elem).name == "John" && std::get<1>(elem) == Relationship::PARENT) {
                    std::cout << "John Has a Child Called " << std::get<2>(elem).name << std::endl;
                }
            }
            
        }
    };  //End of Wrong Way
    
    struct ResearchCorrect {
        ResearchCorrect(RelationshipBrowser& browser) {
            for(auto& child : browser.findAllChildrenOfAParent("John")) {
                std::cout << "John has a child called " << child.name << std::endl;
            }
        }
    };
    
    void testDependancyInversion() {
        Person parent{"John"};
        Person child1{"Chriss"}, child2{"Matt"};
        
        Relationships relationships;
        relationships.addParentAndChild(parent, child1);
        relationships.addParentAndChild(parent, child2);
        
        ResearchCorrect rsrch(relationships);
        
    }
    
}   //End of namespace DependancyInv

#endif /* DEPENDANCYINVERSION_H */

