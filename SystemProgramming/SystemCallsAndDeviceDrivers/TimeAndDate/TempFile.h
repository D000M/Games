/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   TempFile.h
 * Author: default
 *
 * Created on November 21, 2019, 2:16 PM
 */

#ifndef TEMPFILE_H
#define TEMPFILE_H

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <cstring>


#ifdef __cplusplus
extern "C" {
#endif

    void testTMPNAMAndTMPFILE() {
        
        char tmpName[L_tmpnam];
        char* fileName;
        FILE* tmpFilePtr;
        fileName = tmpnam(tmpName); //create temporary random file name
        printf("Temporary file name is: %s\n", fileName);
        
        tmpFilePtr = tmpfile();     //creates and open random name file at the same time
        
        if(tmpFilePtr) {
            printf("Opened a temprorary file: \n" );
        }
        else {
            perror("tmpFilePtr");
        }
        
        printf("Random Filename from template");
        char temp[] = "/tmp/fileXXXXXX";
        char fname[PATH_MAX];
        strcpy(fname, temp);
        mktemp(fname);
        printf("Generate a filename: %s\n", fname);
        
        exit(0);
    }


#ifdef __cplusplus
}
#endif

#endif /* TEMPFILE_H */

