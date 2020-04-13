/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Usingmmap.h
 * Author: default
 *
 * Created on November 20, 2019, 2:55 PM
 */

#ifndef USINGMMAP_H
#define USINGMMAP_H

#include <stdio.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <unistd.h>

#ifdef __cplusplus
extern "C" {
#endif

    typedef struct {
        int integer;
        char string[24];
    } RECORD;

#define NRECORDS (100)
    
    void createRecords() {
        RECORD record;
        RECORD *mapped;
        
        int i;
        int f;
        
        FILE* filePtr;
        filePtr = fopen("records.dat", "w+");
        
        for(i = 0; i < NRECORDS; i++) {
            record.integer = i;
            sprintf(record.string, "RECORD-%d\n", i);
            fwrite(&record, sizeof(record),1, filePtr);
        }
        
        fclose(filePtr);
        
        //2. Next, change the integer value of record 43 to 143 and write this to the 43rd record’s string:
        filePtr = fopen("records.dat", "r+");
        fseek(filePtr, 43 * sizeof(record), SEEK_SET);
        
        fread(&record, sizeof(record),1, filePtr);
        record.integer = 143;
        sprintf(record.string, "RECORD-%d\n", record.integer);
        
        fseek(filePtr, 43 * sizeof(record), SEEK_SET);
        fwrite(&record, sizeof(record), 1, filePtr);
        fclose(filePtr);
        
        //3. Now map the records into memory and access the 43rd record in order to change the integer to
        //243 (and update the record string), again using memory mapping:
        
        f = open("records.dat", O_RDWR);
        mapped = (RECORD*)mmap(0, NRECORDS * sizeof(record), PROT_READ | PROT_WRITE, MAP_SHARED, f, 0);
        mapped[43].integer = 243;
        sprintf(mapped[43].string, "RECORD-%d\n", mapped[43].integer);
        
        msync((void*)mapped, NRECORDS * sizeof(record), MS_ASYNC);
        munmap((void*)mapped, NRECORDS * sizeof(record));
        close(f);
        exit(0);
    }

#ifdef __cplusplus
}
#endif

#endif /* USINGMMAP_H */

