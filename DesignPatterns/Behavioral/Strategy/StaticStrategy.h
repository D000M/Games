/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   StaticStrategy.h
 * Author: default
 *
 * Created on May 22, 2019, 3:06 PM
 */

#ifndef STATICSTRATEGY_H
#define STATICSTRATEGY_H


#include <iosfwd>
#include <memory>
#include <vector>

//Dynamic approach switch at runtime between both formats.

enum class OutputFormatStatic {
    markdown,
    html
};

struct ListStrategyStatic {
    
    virtual void start(std::ostringstream& oss) {}
    
    virtual void addListItem(std::ostringstream& oss, const std::string& item) = 0;
    
    virtual void end(std::ostringstream& oss) {}
    
};

struct MarkDownListStrategyStatic : ListStrategyStatic {
    void addListItem(std::ostringstream& oss, const std::string& item) override {
        oss << "* " << item << std::endl;
    }

};

struct HtmlListStrategyStatic : ListStrategyStatic{
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

template<typename Strategy>
struct TextProcessorStatic {
    
    void clear() {
        oss.str("");
        oss.clear();
    }
    
    void appendList(const std::vector<std::string>& list) {
        listStrategy.start(oss);
        for(auto& item : list) {
            listStrategy.addListItem(oss, item);
        }
        listStrategy.end(oss);
    }
    std::string str() const {
        return oss.str();
    }
private:
    std::ostringstream oss;
    Strategy listStrategy;
};

void testStaticStrategy() {
    TextProcessorStatic<MarkDownListStrategyStatic> tpm;
    std::vector<std::string> items{"foo", "bar", "baz"};
    tpm.appendList(items);
    std::cout << tpm.str() << std::endl;
    
    TextProcessorStatic<HtmlListStrategyStatic> tph;
    tph.appendList(items);
    std::cout << tph.str() << std::endl;
}

#endif /* STATICSTRATEGY_H */

