/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   DynamicStrategy.h
 * Author: default
 *
 * Created on May 22, 2019, 2:23 PM
 */

#ifndef DYNAMICSTRATEGY_H
#define DYNAMICSTRATEGY_H

#include <iosfwd>
#include <memory>
#include <vector>

//Dynamic approach switch at runtime between both formats.

enum class OutputFormat {
    markdown,
    html
};

struct ListStrategy {
    
    virtual void start(std::ostringstream& oss) {}
    
    virtual void addListItem(std::ostringstream& oss, const std::string& item) = 0;
    
    virtual void end(std::ostringstream& oss) {}
    
};

struct MarkDownListStrategy : ListStrategy {
    void addListItem(std::ostringstream& oss, const std::string& item) override {
        oss << "* " << item << std::endl;
    }

};

struct HtmlListStrategy : ListStrategy{
    void start(std::ostringstream& oss) override {
        oss << "<ul>\n";
    }
    void addListItem(std::ostringstream& oss, const std::string& item) override {
        oss << "  " << "<li>" << item << "</li>\n";
    }
    void end(std::ostringstream& oss) override {
        oss << "</ul>\n";
    }

};

struct TextProcessor {
    
    void clear() {
        oss.str("");
        oss.clear();
    }
    
    void appendList(const std::vector<std::string>& list) {
        listStrategy->start(oss);
        for(auto& item : list) {
            listStrategy->addListItem(oss, item);
        }
        listStrategy->end(oss);
    }
    
    void setOutputFormat(const OutputFormat& format) {
        switch(format) {
            case OutputFormat::markdown:
                listStrategy = std::make_unique<MarkDownListStrategy>();
                break;
            case OutputFormat::html:
                listStrategy = std::make_unique<HtmlListStrategy>();
                break;
        }
    }
    std::string str() const {
        return oss.str();
    }
private:
    std::ostringstream oss;
    std::unique_ptr<ListStrategy> listStrategy;
};

void testDynamicStrategy() {
    std::vector<std::string> items{"foo", "bar", "baz"};
    TextProcessor tp;
    tp.setOutputFormat(OutputFormat::markdown);
    tp.appendList(items);
    std::cout << tp.str() << std::endl;
    
    tp.clear();
    tp.setOutputFormat(OutputFormat::html);
    tp.appendList(items);
    std::cout << tp.str() << std::endl;
}


#endif /* DYNAMICSTRATEGY_H */

