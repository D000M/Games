/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   GetUserInformation.h
 * Author: default
 *
 * Created on November 21, 2019, 2:59 PM
 */

#ifndef GETUSERINFORMATION_H
#define GETUSERINFORMATION_H

#include <stdlib.h>
#include <pwd.h>
#include <unistd.h>
#include <sys/utsname.h>

#ifdef __cplusplus
extern "C" {
#endif

    void getUserIDInformation() {
        uid_t uid;
        gid_t gid;
        struct passwd* pw;
        uid = getuid();
        gid = getgid();
        
        printf("User is: %s\n", getlogin());
        printf("Used IDs: uid = %d, gid = %d\n", uid, gid);
        
        pw = getpwuid(uid);
        printf("UID password entry:\nname = %s, uid = %d, gid = %d, home = %s, shell = %s\n", 
                pw->pw_name, pw->pw_uid, pw->pw_gid, pw->pw_dir, pw->pw_shell);
        
        pw = getpwnam("root");
        printf("root password entry:\n");
        printf("name = %s, uid = %d, gid = %d, home = %s, shell = %s\n", 
                pw->pw_name, pw->pw_uid, pw->pw_gid, pw->pw_dir, pw->pw_shell);
        
        exit(0);
        
    }

    void getHostName() {
        char buffer[255];
        gethostname(buffer, 255);
        printf("Host Name is: %s\n", buffer);
        
        printf("Print PC Information:\n");
        struct utsname myMachine;
        uname(&myMachine);
        printf("SysName: %s\nNodeName: %s\nRelease: %s\nVersion: %s\nMachine: %s\n",
                myMachine.sysname, myMachine.nodename, myMachine.release, myMachine.version, myMachine.machine);
    }

#ifdef __cplusplus
}
#endif

#endif /* GETUSERINFORMATION_H */

