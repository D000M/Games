/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   ReadFiles.h
 * Author: default
 *
 * Created on November 20, 2019, 12:07 PM
 */

#ifndef READFILES_H
#define READFILES_H

#include <unistd.h>
#include <stdlib.h>
/**
 * fildes can be 0, 1, 2
 *  ❑ 0: Standard input
    ❑ 1: Standard output
    ❑ 2: Standard error
 */
//size_t read(int fildes, void* buf, size_t nbytes);    //read function prototype in unistd.h

#ifdef __cplusplus
extern "C" {
#endif

    void readFromConsole() {
        char buffer[128];
        
        int nRead;
        
        nRead = read(0, buffer, 128);
        
        if(nRead == -1) {   //Error while reading
            write(2, "A read error was occurred\n", 26);
        }
        
        if((write(1, buffer, nRead)) != nRead) {
            write(2, "A write error was occurred\n", 27);
        }
        
        exit(0);
    }



#ifdef __cplusplus
}
#endif

#endif /* READFILES_H */

