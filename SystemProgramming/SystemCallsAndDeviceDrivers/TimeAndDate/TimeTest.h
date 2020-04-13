/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   TimeTest.h
 * Author: default
 *
 * Created on November 20, 2019, 4:41 PM
 */

#ifndef TIMETEST_H
#define TIMETEST_H

#include <time.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <cstring>


#ifdef __cplusplus
extern "C" {
#endif

    void testTime() {
        int i;
        time_t theTime;
        for(i = 0; i <= 10; i++) {
            theTime = time((time_t*)0);
            printf("The time is: %ld\n", theTime);
            sleep(2);
        }
        exit(0);
    }
    
    void testDiffTime2() {
        time_t timeOne = time((time_t*)0);
        sleep(5);
        time_t timeTwo = time((time_t*)0);
        double diff = difftime(timeOne, timeTwo);
        printf("The time diff between %ld and %ld is: %f\n", timeOne, timeTwo, diff);
        exit(0);
    }

    void testGMTtime() {

        struct tm *tmPtr;
        time_t theTime;
        
        (void)time(&theTime);
        
        tmPtr = gmtime(&theTime);
        printf("Raw Time is: %ld\n", theTime);
        printf("gmtime gives:\n");
        
        printf("date: %02d/%02d/%02d\n", tmPtr->tm_year + 1900, tmPtr->tm_mon + 1, tmPtr->tm_mday);
        printf("time: %02d:%02d:%02d", tmPtr->tm_hour, tmPtr->tm_min, tmPtr->tm_sec);
        exit(0);
    }
    
    void testUsingLocalTime() {
        struct tm* tmPtr;
        time_t currTime;
        (void) time(&currTime);
        
        tmPtr = localtime(&currTime);
        printf("Raw Time is: %ld\n", currTime);
        printf("local time gives:\n");
        
        printf("date: %02d/%02d/%02d\n", tmPtr->tm_year + 1900, tmPtr->tm_mon + 1, tmPtr->tm_mday);
        printf("time: %02d:%02d:%02d\n", tmPtr->tm_hour, tmPtr->tm_min, tmPtr->tm_sec);
        
        exit(0);
    }
    
    void convertStructTmToTime() {
        struct tm* tmPtr;
        time_t currTime;
        (void)time(&currTime);
        printf("Before to Time: %ld\n", currTime);
        
        tmPtr = localtime(&currTime);
        time_t backToTime = mktime(tmPtr);
        printf("After to Time: %ld\n", backToTime);
        exit(0);
    }

    
    void testASCtime() {
        struct tm* tmPtr;
        time_t currTime;
        (void)time(&currTime);
        tmPtr = localtime(&currTime);
        
        printf("Time: %s\n", asctime(tmPtr));
        printf("Time: %s\n", asctime(localtime(&currTime)));
        exit(0);
    }
    
    void testCTime() {
        time_t timeval;
        (void)time(&timeval);
        printf("Date: %s\n", ctime(&timeval));
        exit(0);
    }
    
    /**
     * 
   Conversion Specifier Description
%a      Abbreviated weekday name
%A      Full weekday name
%b      Abbreviated month name
%B      Full month name
%c      Date and time
%d      Day of the month, 01-31
%H      Hour, 00-23
%I      Hour in 12-hour clock, 01-12
%j      Day of the year, 001-366
%m      Month of the year, 01-12
%M      Minutes, 00-59
%X      Time in local format
%y      Year number less 1900
%Y      Year
%Z      Time zone name
%%      A % character
%p      a.m. or p.m.
%S      Seconds, 00-61
%u      Day in the week, 1-7 (1 = Monday)
%U      Week in the year, 01-53 (Sunday is the first day of the week.)
%V      Week in the year, 01-53 (Monday is the first day of the week.)
%w      Day in the week, 0-6 (0 = Sunday)
%x      Date in local format
     */
    
    void testSTRFTIMEandSTRPTIME() {
        struct tm* tmPtr;
        struct tm timeStruct;
        time_t currTime;
        
        (void)time(&currTime);
        tmPtr = localtime(&currTime);
        
        char buf[256];
        
        strftime(buf, 256, "%A %d %B,%I:%M %p", tmPtr);
        printf("strftime gives: %s\n", buf);
        
        strcpy(buf, "Wed 20 November 2019, 17:31 Will do fine\n");
        printf("calling strptime with: %s\n", buf);
        
        tmPtr = &timeStruct;
        
        char* result;
        result = strptime(buf, "%a %d %b %Y, %R", tmPtr);
        printf("strptime consumed up to: %s\n", result);
        printf("strptime gives:\n");
        printf("date: %02d/%02d/%02d\n", tmPtr->tm_year % 100, tmPtr->tm_mon + 1, tmPtr->tm_mday);
        printf("time: %02d:%02d\n", tmPtr->tm_hour, tmPtr->tm_min);
        exit(0);
    }
#ifdef __cplusplus
}
#endif

#endif /* TIMETEST_H */

