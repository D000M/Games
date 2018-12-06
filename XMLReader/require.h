/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   require.h
 * Author: default
 *
 * Created on October 26, 2017, 10:54 AM
 */

#ifndef REQUIRE_H
#define REQUIRE_H

#include <cstdio>
#include <cstdlib>
#include <fstream>
#include <string>

inline void require(bool requirement, const std::string& msg = "Requirement failed" ) {
    using namespace std;
    if(!requirement) {
        fputs(msg.c_str(), stderr);
        fputs("\n", stderr);
        exit(1);
    }
}

inline void requireArgs(int argc, int args, const std::string& msg = "Must use &d arguments") {
    using namespace std;
    if(argc != args + 1) {
        fprintf(stderr, msg.c_str(), args);
        fputs("\n", stderr);
        exit(1);
    }
}

inline void requireMinArgs(int argc, int minArgs, const std::string& msg = "Must use atleast &d arguments") {
    using namespace std;
    if(argc < minArgs + 1) {
        fprintf(stderr, msg.c_str(), minArgs);
        fputs("\n", stderr);
        exit(1);
    }
}

inline void assure(std::ifstream& in, const std::string& filename = "") {
    using namespace std;
    if(!in) {
        fprintf(stderr, "Could not open file%s\n", filename.c_str());
        exit(1);
    }
}

inline void assure(std::ofstream& out, const std::string& filename = "") {
    using namespace std;
    if(!out) {
        fprintf(stderr, "Could not open file%s\n", filename.c_str());
        exit(1);
    }
}
#endif /* REQUIRE_H */

