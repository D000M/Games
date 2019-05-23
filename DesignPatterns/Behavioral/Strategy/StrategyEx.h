/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   StrategyEx.h
 * Author: default
 *
 * Created on May 22, 2019, 3:12 PM
 */

#ifndef STRATEGYEX_H
#define STRATEGYEX_H

#include <iostream>
#include <vector>
#include <complex>
#include <tuple>
#include <numeric>
#include <limits>
#include <libavutil/mathematics.h>

/**
 * Strategy Coding Exercise

Consider the quadratic equation and its canonical solution:

   
 * The part b^2-4*a*c is called the discriminant. 
 * Suppose we want to provide an API with two different strategies for calculating the discriminant:

    In OrdinaryDiscriminantStrategy , 
 *              If the discriminant is negative, we return it as-is. 
 *              This is OK, since our main API returns std::complex  numbers anyway.
    In RealDiscriminantStrategy , 
 *              if the discriminant is negative, 
 *              the return value is NaN (not a number). 
 *              NaN propagates throughout the calculation, so the equation solver gives two NaN values.
 */


namespace StrategyEx {
    
    struct DiscriminantStrategy {
    protected:
        double calculateDiscriminant(double a, double b, double c){
            return (b * b) - (4 * a * c);
        }
    public:
        virtual std::complex<double> calculateComplexDiscriminant(double a, double b, double c) = 0;
    };
    
    struct OrdinaryDiscriminantStrategy : DiscriminantStrategy {
        std::complex<double> calculateComplexDiscriminant(double a, double b, double c) override {
            return std::complex<double>{DiscriminantStrategy::calculateDiscriminant(a, b, c)};
        }
    };
    
    struct RealDiscriminantStrategy : DiscriminantStrategy {
        std::complex<double> calculateComplexDiscriminant(double a, double b, double c) override {
            double discriminant = DiscriminantStrategy::calculateDiscriminant(a, b, c);
            
            return discriminant < 0.0 ? NAN : std::complex<double>(discriminant);
        }
    };
    
    class QuadraticEquationSolver {
        DiscriminantStrategy& strategy;
    public:
        QuadraticEquationSolver(DiscriminantStrategy& strategy)
            : strategy(strategy) {
        }

        std::tuple<std::complex<double>, std::complex<double>> solve(double a, double b, double c) {
            std::complex<double> discriminant = strategy.calculateComplexDiscriminant(a, b, c);
            
            if(isnan(discriminant.imag())) {
                return std::tuple<std::complex<double>, std::complex<double>>{discriminant, discriminant};
            }
            else {
                return std::tuple<std::complex<double>, std::complex<double>>{(-b + std::sqrt(discriminant)) / (2 * a),
                    (-b - std::sqrt(discriminant)) / (2 * a)};
            }
        }
    };
    
    void testStrategyEx() {
        OrdinaryDiscriminantStrategy ordinaryDisc;
        QuadraticEquationSolver ordinarySolver(ordinaryDisc);
        std::tuple<std::complex<double>, std::complex<double>> result = ordinarySolver.solve(5, 2, 2);
        std::cout << "xOne: " << get<0>(result) << ", xTwo: " << get<1>(result);

    }
}

#endif /* STRATEGYEX_H */

