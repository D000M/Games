/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "RNGGenerator.h"

std::mt19937_64& globalURNG() {
    auto seed = std::chrono::high_resolution_clock::now().time_since_epoch().count();
    static std::mt19937_64 u{seed};
    return u;
}

void randomize() {
    static std::random_device randDevice{};
    globalURNG().seed(randDevice());
}

int64_t getRandomInteger(int64_t from, int64_t to) {
    static std::uniform_int_distribution<int64_t> num{};
    using parm_t = decltype(num)::param_type;
    return num(globalURNG(), parm_t(from, to));
}

double getRandomDouble(double from, double to) {
    static std::uniform_real_distribution<> num{};
    using parm_t = decltype(num)::param_type;
    return num(globalURNG(), parm_t(from, to));
}