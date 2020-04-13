/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "RNGGenerator.h"

std::mt19937& globalURNG() {
    auto seed = std::chrono::high_resolution_clock::now().time_since_epoch().count();
    static std::mt19937 u{seed};
    return u;
}

void randomize() {
    static std::random_device rd{};
    globalURNG().seed(rd());
}

int getRandomInteger(int from, int to) {
    static std::uniform_int_distribution<> d{};
    using parm_t = decltype(d)::param_type;
    return d(globalURNG(), parm_t(from, to));
}

double getRandomDouble(double from, double to) {
    static std::uniform_real_distribution<> d{};
    using parm_t = decltype(d)::param_type;
    return d(globalURNG(), parm_t(from, to));
}