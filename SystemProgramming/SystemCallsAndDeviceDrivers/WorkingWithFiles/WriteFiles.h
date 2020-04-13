/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   WriteFiles.h
 * Author: default
 *
 * Created on November 20, 2019, 12:01 PM
 */

#ifndef WRITEFILES_H
#define WRITEFILES_H

#include <unistd.h>
#include <stdlib.h>

//size_t write(int fildes, const void* buf, size_t nbytes); //prototype for function write()

#ifdef __cplusplus
extern "C" {
#endif

void printToConsole() {
    if((write(1, "Here is some data\n", 18)) != 18) {
        write(2, "A write error occurred on file descriptor 1\n", 46);
    }
    exit(0);
}



#ifdef __cplusplus
}
#endif

#endif /* WRITEFILES_H */

