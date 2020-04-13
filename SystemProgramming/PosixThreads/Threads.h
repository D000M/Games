/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Threads.h
 * Author: default
 *
 * Created on November 26, 2019, 4:12 PM
 */

#ifndef THREADS_H
#define THREADS_H

#include <condition_variable>
#include <unistd.h>
#include <string.h>
#include <pthread.h>

#ifdef __cplusplus
extern "C" {
#endif

    //pthread functionality
    /**
     * pthread_t* - the object that we can use to refer to the thread afterward
     * pthread_attr_t* - attributes to modify, usualy use NULL
     * void* (*start_routine)(void*) - the function to call
     * void* arg - the argument pass to the function.
     * @param arg
     * @return 
     */
    //int pthread_create(pthread_t *thread, pthread_attr_t *attr_t, void* (*start_routine)(void*), void *arg);
    
    void *thread_function(void* arg);   //prototype for thread function
    char message[] = "Hello Threads";
    
    void testPThread() {
        int res;
        pthread_t a_thread;
        void* thread_result;
        
        // 1 create thread different from main one, and pass thread_function with argument message array
        res = pthread_create(&a_thread, NULL, thread_function, (void*)message); //start running the new thread
        
        if(res != 0) {  // 2 check for the new thread is active, if thread is active both threads are now running
            perror("Thread creation failed!\n");
            exit(EXIT_FAILURE);
        }
        
        //3 step print 
        printf("Waiting for thread to finish...\n");
        
        //4 pass identifier of the thread that we are waiting, and pointer to the result.
        //This function will wait until the other thread terminates before returns.
        res = pthread_join(a_thread, &thread_result);
        if(res != 0) {
            perror("Thread join failed\n");
            exit(EXIT_FAILURE);
        }
        
        //5 now print the return value from the thread, and the contents of the variable thread_result, which is set on pthread_exit()
        printf("Thread joined, it returned %s\n", (char*)thread_result);
        printf("Message is now %s\n", message);
        exit(EXIT_SUCCESS);
    }
    
    void *thread_function(void* arg) {
        //3 step from the other thread , running simultaneously with main thread
        printf("thread_function is running. Argument was %s\n", (char*)arg);
        sleep(3);
        strcpy(message, "Bye!");
        pthread_exit((char*)"Thank you for the cpu time!\n");
    }

    
    //simultaneous run of two threads
    int runNow = 1;
    int count = 0;
    bool bExit = false;
    void* otherThreadFunc(void* arg) {
        while(true) {
            if(runNow == 2) {
                std::cout << "\n";
                printf(" 2 ");
                runNow = 1;
                count++;
                sleep(1);
            }
            if(count == 10) {
                runNow = 1;
                bExit = true;
                
                break;
            }
        }
        
    }
    void test2Threads() {
        int res;
        pthread_t otherThread;
        void* otherThreadRes;
        res = pthread_create(&otherThread, NULL, otherThreadFunc, (char*)message);
        
        if(res != 0) {
            perror("Thread creation failed!\n");
            exit(EXIT_FAILURE);
        }
        
        while(true) {
            if(runNow == 1) {
                std::cout << "\n"; 
                printf(" 1 ");
                runNow = 2;
                sleep(2);
            }
            if(bExit) {
                break;
            }
        }
        printf("\nWaiting for the thread to finish!\n");
        printf("Other Thread finished: ", (char*)otherThreadRes);
    }

#ifdef __cplusplus
}
#endif

#endif /* THREADS_H */

