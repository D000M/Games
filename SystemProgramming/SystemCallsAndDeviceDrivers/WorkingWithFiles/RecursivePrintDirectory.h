/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   RecursivePrintDirectory.h
 * Author: default
 *
 * Created on November 20, 2019, 2:20 PM
 */

#ifndef RECURSIVEPRINTDIRECTORY_H
#define RECURSIVEPRINTDIRECTORY_H

#include <dirent.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>
#include <string.h>


#ifdef __cplusplus
extern "C" {
#endif

    void printDirectory(char* directory, int depth) {
        DIR* directoryPtr;
        struct dirent* entry;
        struct stat statBuffer;
        
        if((directoryPtr = opendir(directory)) == NULL) {
            fprintf(stderr, "cannot open directory: %s\n", directory);
            return;
        }
        
        chdir(directory);
        
        while((entry = readdir(directoryPtr)) != NULL) {
            lstat(entry->d_name, &statBuffer);
            
            if(S_ISDIR(statBuffer.st_mode)) {
                /**Found a directory, but ignore "." and ".."*/
                if(strcmp(".", entry->d_name) == 0 || strcmp("..", entry->d_name) == 0) {
                    continue;
                }
                printf("%*s%s/\n", depth, "", entry->d_name);
                /*Recurse at the new indent level*/
                printDirectory(entry->d_name, depth + 4);
            }
            else {
                printf("%*s%s\n", depth, "", entry->d_name);
            }
        }
        chdir("..");
        closedir(directoryPtr);
    }


    void testPrintHomeDirectory() {
        char* directory = "/home/default/NetBeansProjects/Games/DesignPatterns/";
        printf("Directory scan of %s\n", directory);
        printDirectory(directory, 0);
        printf("Done.!\n");
        exit(0);
    }
    
    void printDirectoryTree(int argc, char* argv[]) {
        char* topDirectory = ".";
        
        if(argc >= 2) {
            topDirectory = argv[1];
        }
        
        printf("Directory scan of %s\n", topDirectory);
        printDirectory(topDirectory, 0);
        printf("Done.\n");
        exit(0);
    }
    
#ifdef __cplusplus
}
#endif

#endif /* RECURSIVEPRINTDIRECTORY_H */

