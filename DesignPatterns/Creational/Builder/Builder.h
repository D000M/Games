/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Builder.h
 * Author: default
 *
 * Created on April 11, 2019, 3:46 PM
 */

#ifndef BUILDER_H
#define BUILDER_H

#include <string>
#include <vector>
#include <iostream>
#include <sstream>

namespace Builder {
    struct HtmlElement {
        
        std::string name, text;
        std::vector<HtmlElement> elements;
        
        const std::size_t indentSize = 2;
        
        HtmlElement() {
        }
        HtmlElement(const std::string& name, const std::string& text) 
            : name(name), text(text) {
        }
        
        //Function to print
        std::string str(int indent = 0) const {
            std::ostringstream oss;
            std::string i(indentSize * indent, ' ');
            oss << i << "<" << name << ">" << std::endl;
            if(text.size() > 0) {
                oss << std::string(indentSize * (indent + 1), ' ') << text << std::endl;
            }
            
            for(const auto& e : elements) {
                oss << e.str(indent + 1);
            }
            
            oss << i << "</" << name << ">" << std::endl;
            return oss.str();
        }
    };  //End of our simple structure
    
    //Now lets build our builder class
    struct HtmlBuilder {
        HtmlElement root;
        
        HtmlBuilder(const std::string& rootName) {
            root.name = rootName;
        }
        
        //Now lets add child to our linked list
        void addChild(const std::string& lName, const std::string& lText) {
            HtmlElement child{lName, lText};
            root.elements.emplace_back(child);  //Push child on last position on the vector.
        }
        
        std::string str() const {
            return root.str();
        }
    };
    
    
    void testBuilder() {
        HtmlBuilder builder{"ul"};
        builder.addChild("li", "Hello");
        builder.addChild("li", "World");
        std::cout << builder.str() << std::endl;
    }
}

//To avoid using constructors of HtmlElement and force
//Users to use builder make constructors private
namespace FluentBuilder2 {  //Not Working
    class HtmlElement {
    public:
        struct HtmlBuilder;
        std::string name, text;
        std::vector<HtmlElement> elements;
        
        const std::size_t indentSize = 2;
//    private:
        HtmlElement() {
        }
        HtmlElement(const std::string& name, const std::string& text) 
            : name(name), text(text) {
        }
    public:
        //Function to print
        std::string str(int indent = 0) const {
            std::ostringstream oss;
            std::string i(indentSize * indent, ' ');
            oss << i << "<" << name << ">" << std::endl;
            if(text.size() > 0) {
                oss << std::string(indentSize * (indent + 1), ' ') << text << std::endl;
            }
            
            for(const auto& e : elements) {
                oss << e.str(indent + 1);
            }
            
            oss << i << "</" << name << ">" << std::endl;
            return oss.str();
        }
        
        //We can also hint the user here how to use htmlbulder  this should work for private constructors
//        static HtmlBuilder htmlBuild(std::string rootName) {
//            return {rootName};
//        }
    };  //End of our simple structure
    
    //Now lets build our builder class
    struct HtmlBuilder {
        HtmlElement root;
        
        HtmlBuilder(const std::string& rootName) {
            root.name = rootName;
        }
        
        //Now lets add child to our linked list 
        //With this approach we can call HtmlBuilder obj like that
        //obj.addChild("firstParam", "secondParam").addChild("firstParam", "secondParam").addChild("firstParam", "secondParam").
        //... and so on to infinity.
        HtmlBuilder& addChild(const std::string& lName, const std::string& lText) {
            HtmlElement child{lName, lText};
            root.elements.emplace_back(child);  //Push child on last position on the vector.
            return *this;
        }
        
        std::string str() const {
            return root.str();
        }
    };
    
    
    void testBuilder() {
        HtmlBuilder builder{"ul"};
        builder.addChild("li", "Hello").addChild("li", "World").addChild("li", "Hell").addChild("li", "Paradise");
        std::cout << builder.str() << std::endl;
    }
}   //end FluentBuilder2

namespace GroovyStyleBuilder {
    struct Tag {
        std::string mName, mText;
        std::vector<Tag> children;
        std::vector<std::pair<std::string, std::string>> attributes;
        
        
        
        friend std::ostream& operator << (std::ostream& os, const Tag& tag) {
            os << "<" << tag.mName;
            for(const auto& att : tag.attributes) {
                os << " " << att.first << "=\"" << att.second << "\"";
            }
            if(tag.children.size() == 0 && tag.mText.length() == 0) {
                os << "/>" << std::endl;
            }
            else {
                os << ">" << std::endl;
                if(tag.mText.length()) {
                    os << tag.mText << std::endl;
                }
                for(const auto& child : tag.children) {
                    os << child;
                }
                os << "</" << tag.mName << ">" << std::endl;
            }
            return os;
        }   //End operator <<
        
    protected:
        Tag(const std::string& name, const std::string& text)
        : mName(name), mText(text) {
        }
        Tag(const std::string& mName, const std::vector<Tag>& children)
            : mName(mName), children(children) {
        }

        
    };  //end struct Tag
    
    //Create paragrah tag
    struct P : Tag {
        //Get rid of name argument and set "p" for paragraph in Tag Constructor
        P(const std::string& text)  
            : Tag("p", text) {
        }
        
        P(std::initializer_list<Tag> children)
            : Tag("p", children) {
        }

    };  //end of P struct
    
    //create img tag
    struct IMG : Tag {
        explicit IMG(const std::string& url) 
            : Tag("img", "") {
            attributes.emplace_back(std::make_pair("src", url));
        }
    };  //end IMG struct
    
    
    void testOurHtmlLanguage() {
        std::cout << 
                P { 
                    IMG {"http://sportal.bg/valencia.png"}
                }
        << std::endl;
    }
}   //end of GroovyStyleBuilder namespace




#endif /* BUILDER_H */

