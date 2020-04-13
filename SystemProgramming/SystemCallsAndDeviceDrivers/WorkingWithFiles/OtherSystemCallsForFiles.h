/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   OtherSystemCallsForFiles.h
 * Author: default
 *
 * Created on November 20, 2019, 12:55 PM
 */

#ifndef OTHERSYSTEMCALLSFORFILES_H
#define OTHERSYSTEMCALLSFORFILES_H

#include <stdio.h>
#include <sys/stat.h>
#include <fcntl.h>


/**
 * 
 * off_t lseek(int fildes, off_t offset, int whence);  
 * 
 *   ❑ SEEK_SET: offset is an absolute position
     ❑ SEEK_CUR: offset is relative to the current position
     ❑ SEEK_END: offset is relative to the end of the file 
 * 
 *  int fstat(int fildes, struct stat *buf);
 *  int lstat(const char *path, struct stat *buf); 
 *  int stat(const char *path, struct stat *buf);   
      
 */

#ifdef __cplusplus
extern "C" {
#endif

    void testCopyFile() {
        int c;
        FILE *in;
        FILE *out;
        
        in = fopen("SystemCallsAndDeviceDrivers/WorkingWithFiles/ReadFiles.h", "r");
        out = fopen("SystemCallsAndDeviceDrivers/WorkingWithFiles/result/CopyFiles.out", "w");
        
        while((c = fgetc(in)) != EOF) {
            fputc(c, out);
        }
        exit(0);
        
        mkdir("SystemCallsAndDeviceDrivers/WorkingWithFiles/mkdirUsed",O_CREAT);
    }


#ifdef __cplusplus
}
#endif

#endif /* OTHERSYSTEMCALLSFORFILES_H */

