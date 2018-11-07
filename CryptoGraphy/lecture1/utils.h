/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   utils.h
 * Author: default
 *
 * Created on November 7, 2018, 3:17 PM
 */

#ifndef UTILS_H
#define UTILS_H

#include <fstream>
#include <sstream>

std::string textToString(std::ifstream& f) {
    return static_cast<std::stringstream const&>(std::stringstream() << f.rdbuf()).str();
}

#endif /* UTILS_H */

