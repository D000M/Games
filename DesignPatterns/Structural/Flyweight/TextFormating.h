/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   TextFormating.h
 * Author: default
 *
 * Created on May 14, 2019, 1:16 PM
 */

#ifndef TEXTFORMATING_H
#define TEXTFORMATING_H

#include <string>
#include <cstring>
#include <vector>
#include <locale>


namespace TextFormat {
    //Typical formatted text
    class FormattedText {
        std::string plainText;
        bool* caps;
    public:
        FormattedText(const std::string& plainText)
        : plainText(plainText) {
            caps = new bool[plainText.length()];
            memset(caps, 0, plainText.length());
        }
        ~FormattedText() {
            delete caps;
        }
        
        void capitalize(int start, int end) {
            for(int i = start; i <= end; i++) {
                caps[i] = true;
            }
        }
        friend std::ostream& operator<<(std::ostream& os, const FormattedText& obj) {
            std::string s;
            for(int i = 0; i < obj.plainText.length(); i++) {
                char c = obj.plainText.at(i);
                s += (obj.caps[i] ? toupper(c) : c);
            }
            return os << s;
        }

    };  //We can use Flyweight to avoid using bool array
    
    class FlyweightFormattedText {
    public:
        struct TextRange {
            int start, end;
            bool capitalize;        //other options like Bold, Italic...
            
            bool covers(int position) const {
                return position >= start && position <= end;
            }
          
        };
        
        FlyweightFormattedText(const std::string& plainText)
            : plainText(plainText){
        }
        
        TextRange& getRange(int start, int end) {
            formatting.emplace_back(TextRange{start, end});
            return *formatting.rbegin();
        }
        
        friend std::ostream& operator<<(std::ostream& os, const FlyweightFormattedText& obj) {
            // Write obj to stream
            std::string s;
            for(int i = 0; i < obj.plainText.length(); i++) {
                auto c = obj.plainText.at(i);
                for(const auto& rng : obj.formatting) {
                    if(rng.covers(i) && rng.capitalize) {
                        c = toupper(c);
                    }
                    s += c;
                }
            }
            return os << s;
        }

    private:
        std::string plainText;
        std::vector<TextRange> formatting;
    };
    
    void testFormatter() {
        FormattedText ft{"This is a brave new World"};
        ft.capitalize(10, 20);
        std::cout << ft << std::endl;
        
        FlyweightFormattedText fft{"This is a brave new World"};
        fft.getRange(10, 15).capitalize = true;
        std::cout << fft << std::endl;
    }
}

#endif /* TEXTFORMATING_H */

