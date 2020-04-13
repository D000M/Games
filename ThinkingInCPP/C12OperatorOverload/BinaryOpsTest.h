/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   BinaryOpsTest.h
 * Author: default
 *
 * Created on December 7, 2019, 1:46 PM
 */

#ifndef BINARYOPSTEST_H
#define BINARYOPSTEST_H

#include <fstream>
#include <iostream>
#include "OOBinarySyntax.h"
#include "ByteMemberBinaryOO.h"


std::ofstream out("IntegerV3Test.out");

void IntegerFunc(IntegerV3& c1, IntegerV3& c2){
//    //A Complex expression
//    c1 += c1 * c2 + c2 % c1;
    //macros
#define TRY(op) \
    out << "c1: "; c1.print(out); \
    out << ", c2: "; c2.print(out); \
    out << "; c1 " #op " c2 = "; \
    (c1 op c2).print(out); \
    out << std::endl;
    
    TRY(+)
    TRY(-)
    TRY(*)
    TRY(/)
    TRY(%)
    TRY(^)
    TRY(&)
    TRY(|)
    TRY(<<)
    TRY(>>)
    TRY(+=)
    TRY(-=)
    TRY(*=)
    TRY(/=)
    TRY(%=)
    TRY(^=)
    TRY(&=)
    TRY(|=)
    TRY(>>=)
    TRY(<<=)
            
//Conditionals
#define TRYC(op) \
    out << "c1: "; c1.print(out); \
    out << ", c2: "; c2.print(out); \
    out << "; c1 " #op " c2 = "; \
    out << (c1 op c2); \
    out << std::endl;
            
    TRYC(<)
    TRYC(>)
    TRYC(==)
    TRYC(!=)
    TRYC(<=)
    TRYC(>=)
    TRYC(&&)
    TRYC(||)

}

void testBinaryIntegerV3() {
    std::cout << "Friend Functions!\n";
    IntegerV3 c1{47}, c2(9);
    IntegerFunc(c1, c2);
}

std::ofstream out2("ByteV2Test.out");

void testByteV2(ByteV2& b1, ByteV2& b2) {
    b1 = b1 * b2 + b2 % b1;
    
#define TRY(op) \
    out2 << "b1: "; b1.print(out2); \
    out2 << ", b2: "; b2.print(out2); \
    out2 << "; b1 " #op " b2 = "; \
    (b1 op b2).print(out2); \
    out2 << std::endl;
    b1 = 9; b2 = 47;
    TRY(+)
    TRY(-)
    TRY(*)
    TRY(/)
    TRY(%)
    TRY(^)
    TRY(&)
    TRY(|)
    TRY(<<)
    TRY(>>)
    TRY(+=)
    TRY(-=)
    TRY(*=)
    TRY(/=)
    TRY(%=)
    TRY(^=)
    TRY(&=)
    TRY(|=)
    TRY(>>=)
    TRY(<<=)
    TRY(=)
            
//Conditionals
#define TRYC(op) \
    out2 << "b1: "; b1.print(out2); \
    out2 << ", b2: "; b2.print(out2); \
    out2 << "; b1 " #op " b2 = "; \
    out2 << (b1 op b2); \
    out2 << std::endl;
            
    b1 = 9; b2 = 47;
    TRYC(<)
    TRYC(>)
    TRYC(==)
    TRYC(!=)
    TRYC(<=)
    TRYC(>=)
    TRYC(&&)
    TRYC(||)
            
    ByteV2 b3 = 92;
    b1 = b2 = b3;
}


void testBinaryMemberByteV2() {
    out << "Member Functions\n";
    ByteV2 b1{47}, b2{9};
    testByteV2(b1, b2);
}
#endif /* BINARYOPSTEST_H */

