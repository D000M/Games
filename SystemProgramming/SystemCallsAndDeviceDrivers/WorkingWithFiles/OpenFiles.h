/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   OpenFiles.h
 * Author: default
 *
 * Created on November 20, 2019, 12:18 PM
 */

#ifndef OPENFILES_H
#define OPENFILES_H

#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>




/**
 * function prototypes
 * 
 * int open(const char *path, int oflags);
    
 * int open(const char *path, int oflags, mode_t mode);
 * 
 * int close(int fildes);   //return 0 if succesful, -1 if failed to close
 * 
 * 
 * 
 *  O_RDONLY        Open for read-only
    O_WRONLY        Open for write-only
    O_RDWR          Open for reading and writing
 * 
 * The call may also include a combination (using a bitwise OR) of the following optional modes in the oflags parameter:
    ❑ O_APPEND:     Place written data at the end of the file.
    ❑ O_TRUNC:      Set the length of the file to zero, discarding existing contents.
    ❑ O_CREAT:      Creates the file, if necessary, with permissions given in mode.
    ❑ O_EXCL:       Used with O_CREAT, ensures that the caller creates the file.
 * 
 * Initial permissions
 *  ❑ S_IRUSR: Read permission, owner
    ❑ S_IWUSR: Write permission, owner
    ❑ S_IXUSR: Execute permission, owner
    ❑ S_IRGRP: Read permission, group
    ❑ S_IWGRP: Write permission, group
    ❑ S_IXGRP: Execute permission, group
    ❑ S_IROTH: Read permission, others
    ❑ S_IWOTH: Write permission, others
    ❑ S_IXOTH: Execute permission, others
 * 
 */
#ifdef __cplusplus
extern "C" {
#endif

    void writeInFiles() {
        char c;
        int in, out;
        in = open("SystemCallsAndDeviceDrivers/WorkingWithFiles/ReadFiles.h", O_RDONLY);
        out = open("SystemCallsAndDeviceDrivers/WorkingWithFiles/result/ReadFilesResult.txt", O_WRONLY | O_CREAT | S_IRUSR | S_IWUSR);
        
        while(read(in, &c, 1) == 1) {
            write(out, &c, 1);
        }
        exit(0);
    }
    
    void copyFromBlocks() {
        char block[1024];
        
        int in, out;
        int nread;
        in = open("SystemCallsAndDeviceDrivers/WorkingWithFiles/ReadFiles.h", O_RDONLY);
        out = open("SystemCallsAndDeviceDrivers/WorkingWithFiles/result/CopyBlocks.txt", O_WRONLY | O_CREAT | S_IRUSR | S_IWUSR);
        
        while((nread = read(in, block, sizeof(block))) > 0) {
            write(out, block, nread);
        }
        exit(0);
    }

#ifdef __cplusplus
}
#endif

#endif /* OPENFILES_H */

