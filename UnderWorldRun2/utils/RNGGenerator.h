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
std::mt19937& globalURNG();

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
int getRandomInteger(int from, int to);

/**
 * Provide random integer from mt19937 random engine
 * @param from bottom border of the random sequence
 * @param to upper border of the random sequence
 * @return the pseudo random double.
 */
double getRandomDouble(double from, double to);

#endif /* RNGGENERATOR_H */

