/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   RNGGenerator.h
 * Author: default
 *
 * Created on February 12, 2019, 2:55 PM
 */

#ifndef RNGGENERATOR_H
#define RNGGENERATOR_H

#include <random>
#include <chrono>
#include <functional>
#include <iostream>

/**
 * Seed mt19937 random engine.
 * @return seeded mt19937 static object.
 */
std::mt19937_64& globalURNG();

/**
 * Randomize the random device.
 */
void randomize();

/**
 * Provide random integer from mt19937 random engine
 * @param from bottom border of the random sequence
 * @param to upper border of the random sequence
 * @return the pseudo random integer.
 */
int64_t getRandomInteger(int64_t from, int64_t to);

/**
 * Provide random integer from mt19937 random engine
 * @param from bottom border of the random sequence
 * @param to upper border of the random sequence
 * @return the pseudo random double.
 */
double getRandomDouble(double from, double to);

#endif /* RNGGENERATOR_H */

