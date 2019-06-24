/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   HTMLElement.h
 * Author: default
 *
 * Created on June 21, 2019, 1:05 PM
 */

#ifndef HTMLELEMENT_H
#define HTMLELEMENT_H

#include <string>
#include <vector>



class HTMLElement {
public:
    virtual std::string getHTMLTag() = 0;
};

class HTMLText : public HTMLElement {
    std::string text;
public:
    HTMLText(const std::string& text)
        : text{text} {
    }

    std::string getHTMLTag() override {
        return text;
    }
};

class HTMLULLITag : public HTMLElement {
    std::string title;
    std::vector<HTMLElement*> elements;
public:
    HTMLULLITag(const std::string& title, std::vector<HTMLElement*> elements)
        : title(title), elements(elements) {
    }
        
    void addMoreElements(HTMLElement* element) {
        elements.push_back(element);
    }    
    std::string getHTMLTag() override {
        std::string htmlString{""};
        htmlString += "<h1>" + title + "</h1>\n";
        htmlString += " <ul>\n";
        for(auto elem : elements) {
            htmlString += "  <li>";
            htmlString += elem->getHTMLTag();
            htmlString += "</li>\n";
        }
        htmlString += " </ul>\n";
        return htmlString;
    }
};


void testHTMLTags() {
    std::vector<HTMLElement*> elements;
    elements.emplace_back(new HTMLText{"List Item One"});
    elements.emplace_back(new HTMLText{"List Item Two"});
    elements.emplace_back(new HTMLText{"List Item Three"});
    elements.emplace_back(new HTMLULLITag{"Level list", elements});
    HTMLULLITag tags{"MyUnorderedList", elements};
    
    std::vector<HTMLElement*> el2;
    el2.emplace_back(new HTMLText{"Level 1"});
    el2.emplace_back(new HTMLText{"Level 2"});
    el2.emplace_back(new HTMLText{"Level 3"});
    
    HTMLULLITag levelTags{"Level List", el2};
    tags.addMoreElements(&levelTags);
    
//    std::vector<HTMLElement*> tags;
    
    
    std::cout << tags.getHTMLTag() << std::endl;
}
#endif /* HTMLELEMENT_H */

