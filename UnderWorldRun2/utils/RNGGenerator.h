/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   RNGGenerator.h
 * Author: default
 *
 * Created on July 30, 2018, 10:38 AM
 */

#ifndef RNGGENERATOR_H
#define RNGGENERATOR_H

#include <chrono>
#include <functional>
#include <random>
#include <iostream>

/**
 * Seed mt19937 random engine.
 * @return seeded mt19937 static object.
 */
std::mt19937& globalURNG() {
    auto seed = std::chrono::high_resolution_clock::now().time_since_epoch().count();
    static std::mt19937 u{seed};
    return u;
}

/**
 * Randomize the random device.
 */
void randomize() {
    static std::random_device rd{};
    globalURNG().seed(rd());
}

/**
 * Provide random integer from mt19937 random engine
 * @param from bottom border of the random sequence
 * @param to upper border of the random sequence
 * @return the pseudo random integer.
 */
int getRandomInteger(int from, int to) {
    static std::uniform_int_distribution<> d{};
    using parm_t = decltype(d)::param_type;
    return d(globalURNG(), parm_t(from, to));
}

/**
 * Provide random integer from mt19937 random engine
 * @param from bottom border of the random sequence
 * @param to upper border of the random sequence
 * @return the pseudo random double.
 */
double getRandomDouble(double from, double to) {
    static std::uniform_real_distribution<> d{};
    using parm_t = decltype(d)::param_type;
    return d(globalURNG(), parm_t(from, to));
}

#endif /* RNGGENERATOR_H */

