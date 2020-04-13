/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   RunningOtherPrograms.h
 * Author: default
 *
 * Created on November 25, 2019, 3:34 PM
 */

#ifndef RUNNINGOTHERPROGRAMS_H
#define RUNNINGOTHERPROGRAMS_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <condition_variable>
#include <sys/wait.h>


#ifdef __cplusplus
extern "C" {
#endif

    void runPS() {
        
        char* const  c[] = {"-a"};
        
        printf("Running ps with system or with execl\n");
        execlp("/home/default/NetBeansProjects/Games/TestRunningWithSystem/", "hello", 0);
//        system("/home/default/NetBeansProjects/Games/TestRunningWithSystem/ ./hello");
        printf("Done\n");
        exit(0);
    }

    
    void testFork() {
        pid_t pid;
        const char* message;
        int n;
        printf("Form Program starting\n");
        
        pid = fork();   //start another process
//        pid = fork();
        
        //Check for success
        switch(pid) {
            case -1:
                perror("Fork Failed!\n");
                exit(EXIT_FAILURE);
            case 0:
                message = "This is child!";
                n = 5;
            default:
                message = "This is parrent!";
                n = 3;
                break;               
        }
        
        for(; n > 0; n--) {
            puts(message);
            sleep(1);
        }
        exit(EXIT_SUCCESS);
    }

    void testWaitFork() {
        pid_t pid;
        int n;
        const char* message;
        int exit_code;
        printf("Program started\n");
        
        pid = fork();   //start another process
        
        switch(pid) {
            case -1:
                perror("Fork failed!\n");
                exit(EXIT_FAILURE);
            case 0:
                message = "Child";
                n = 5;
                exit_code = 37;
                break;
            default:
                message = "Parent";
                n = 3;
                exit_code = 0;
                break;
        }
        for(; n > 0; n--) {
            puts(message);
            sleep(1);
        }
        
        //This section here waits for a child to finish
        if(pid != 0) {
            int stat_val;
            pid_t pid_child;
            pid_child = wait(&stat_val);
            printf("Child has finished: PID = %d\n", pid_child);
            if(WIFEXITED(stat_val)) {
                printf("Child exited with code: %d\n", WEXITSTATUS(stat_val));
            }
            else {
                printf("Chiled terminated abnormaly!\n");
            }
        }
        exit(EXIT_SUCCESS);
    }
    
    //using void (*signal(int sig, void (*func(int)))(int);
    
    void ouch(int sig) {
        printf("OUCH! - I Got a Signal! %d\n", sig);
        (void)signal(SIGINT, SIG_DFL);      //return void *signal() to the default behavior after first ctrl+c click, and on second the program will terminate
    }
    void testSignalHandling() {
        (void)signal(SIGINT, ouch);
        while(true) {
            printf("Hello!\n");
            sleep(1);
        }
    }
   
#ifdef __cplusplus
}
#endif

#endif /* RUNNINGOTHERPROGRAMS_H */

