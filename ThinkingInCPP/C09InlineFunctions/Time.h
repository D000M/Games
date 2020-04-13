/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Time.h
 * Author: default
 *
 * Created on December 6, 2019, 1:25 PM
 */

#ifndef TIME_H
#define TIME_H

#include <ctime>
#include <cstring>

class Time {
    std::time_t t;
    std::tm local;
    char asciiRep[26];
    unsigned char lflag, aflag;
    
    void updateLocal() {
        if(!lflag) {
            local = *std::localtime(&t);
            lflag++;
        }
    }
    void updateAscii() {
        if(!aflag) {
            updateLocal();
            std::strcpy(asciiRep, std::asctime(&local));
        }
    }
    
public:
    Time() {
        mark();
    }
    
    void mark() {
        lflag = aflag = 0;
        std::time(&t);
    }
    
    const char* ascii() {
        updateAscii();
        return asciiRep;
    }
    
    //Difference in seconds
    int delta(Time* dt) const {
        return int(std::difftime(t, dt->t));
    }
    
    int daylightSavings() {
        updateLocal();
        return local.tm_isdst;
    }
    
    int dayOfYear() {       //Since jan 1
        updateLocal();
        return local.tm_yday;
    }
    
    int dayOfWeek() {       //Since sunday
        updateLocal();
        return local.tm_wday;
    }
    
    int since1900() {       //Years Since 1900
        updateLocal();
        return local.tm_year;
    }
    
    int month() {           //Since january
        updateLocal();
        return local.tm_mon;
    }
    
    int dayOfMonth() {      
        updateLocal();
        return local.tm_mday;
    }
    
    int hour() {    //Since midnight, 24-hour clock
        updateLocal();
        return local.tm_hour;
    }
    
    int minute() {
        updateLocal();
        return local.tm_min;
    }
    
    int second() {
        updateLocal();
        return local.tm_sec;
    }
};

#endif /* TIME_H */

