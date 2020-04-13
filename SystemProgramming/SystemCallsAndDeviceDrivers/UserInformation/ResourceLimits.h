/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   ResourceLimits.h
 * Author: default
 *
 * Created on November 21, 2019, 3:26 PM
 */

#ifndef RESOURCELIMITS_H
#define RESOURCELIMITS_H

#include <stdio.h>
#include <math.h>
#include <sys/resource.h>
#include <unistd.h>
#include <stdlib.h>


#ifdef __cplusplus
extern "C" {
#endif

    void work() {
        FILE* file;
        int i;
        double x = 4.5;
        file = tmpfile();
        for(i = 0; i < 10000; i++) {
            fprintf(file, "Do Some Output!\n");
            if(ferror(file)) {
                fprintf(stderr, "Error writing to temporary file\n");
                exit(1);
            }
        }
        
        for(i = 0; i < 1000000; i++) {
            x = log(x * x + 3.21);
        }
    }

    void testResourceUsage() {
        struct rusage resUsage;
        struct rlimit resLimit;
        int priority;
        work();
        
        getrusage(RUSAGE_SELF, &resUsage);
        printf("CPU usage: User = %ld.%06ld, System = %ld.06%ld\n",
                resUsage.ru_utime.tv_sec, resUsage.ru_utime.tv_usec,
                resUsage.ru_stime.tv_sec, resUsage.ru_stime.tv_usec);
        
        priority = getpriority(PRIO_PROCESS, getpid());
        printf("Current Priority: %d\n", priority);
        
        getrlimit(RLIMIT_FSIZE, &resLimit);
        printf("Current FSIZE limit: software = %ld, hardware = %ld\n", 
                resLimit.rlim_cur, resLimit.rlim_max);
        
//        resLimit.rlim_cur = 2048;   //To small file size cant write 10000 rows by 15 chars
//        resLimit.rlim_max = 4096;   //To small file size cant write 10000 rows by 15 chars
//        
//        printf("Setting a 2K FSIZE limit!\n");
//        setrlimit(RLIMIT_FSIZE, &resLimit);
        
//        work();
        
        exit(0);
    }

#ifdef __cplusplus
}
#endif

#endif /* RESOURCELIMITS_H */

