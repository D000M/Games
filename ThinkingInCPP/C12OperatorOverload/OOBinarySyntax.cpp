/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "OOBinarySyntax.h"

const IntegerV3 operator + (const IntegerV3& left, const IntegerV3& right){
    return IntegerV3(left.value + right.value);
}
const IntegerV3 operator - (const IntegerV3& left, const IntegerV3& right) {
    return IntegerV3(left.value - right.value);
}
const IntegerV3 operator * (const IntegerV3& left, const IntegerV3& right) {
    return IntegerV3(left.value * right.value);
}
const IntegerV3 operator / (const IntegerV3& left, const IntegerV3& right) {
    if(right.value == 0) {
        throw("ERROR Division by 0");
    }
    return IntegerV3(left.value / right.value);
}
const IntegerV3 operator % (const IntegerV3& left, const IntegerV3& right) {
    if(right.value == 0) {
        throw ("ERROR modulus by 0");
    }
    return IntegerV3(left.value % right.value);
}
const IntegerV3 operator ^ (const IntegerV3& left, const IntegerV3& right) {
    return IntegerV3(left.value ^ right.value);
}
const IntegerV3 operator & (const IntegerV3& left, const IntegerV3& right) {
    return IntegerV3(left.value & right.value);
}
const IntegerV3 operator | (const IntegerV3& left, const IntegerV3& right) {
    return IntegerV3(left.value | right.value);
}
const IntegerV3 operator << (const IntegerV3& left, const IntegerV3& right) {
    return IntegerV3(left.value << right.value);
}
const IntegerV3 operator >> (const IntegerV3& left, const IntegerV3& right) {
    return IntegerV3(left.value >> right.value);
}

//Assignments modify return value
IntegerV3& operator += (IntegerV3& left, const IntegerV3& right) {
    if(&left == &right) {
        /**self assignment*/
    }
    left.value += right.value;
    return left;
}
IntegerV3& operator -= (IntegerV3& left, const IntegerV3& right) {
    if(&left == &right) {
        /**self assignment*/
    }
    left.value -= right.value;
    return left;
}
IntegerV3& operator *= (IntegerV3& left, const IntegerV3& right) {
    if(&left == &right) {
        /**self assignment*/
    }
    left.value *= right.value;
    return left;
}
IntegerV3& operator /= (IntegerV3& left, const IntegerV3& right) {
    if(right.value == 0) {
        throw ("ERROR division by 0");
    }
    if(&left == &right) {
        /**self assignment*/
    }
    left.value /= right.value;
    return left;
}
IntegerV3& operator %= (IntegerV3& left, const IntegerV3& right) {
    if(right.value == 0) {
        throw ("ERROR modulus by 0");
    }
    if(&left == &right) {
        /**self assignment*/
    }
    left.value %= right.value;
    return left;
}
IntegerV3& operator ^= (IntegerV3& left, const IntegerV3& right) {
    if(&left == &right) {
        /**self assignment*/
    }
    left.value ^= right.value;
    return left;
}
IntegerV3& operator &= (IntegerV3& left, const IntegerV3& right) {
    if(&left == &right) {
        /**self assignment*/
    }
    left.value &= right.value;
    return left;
}
IntegerV3& operator |= (IntegerV3& left, const IntegerV3& right) {
    if(&left == &right) {
        /**self assignment*/
    }
    left.value |= right.value;
    return left;
}
IntegerV3& operator >>= (IntegerV3& left, const IntegerV3& right) {
    if(&left == &right) {
        /**self assignment*/
    }
    left.value >>= right.value;
    return left;
}
IntegerV3& operator <<= (IntegerV3& left, const IntegerV3& right) {
    if(&left == &right) {
        /**self assignment*/
    }
    left.value <<= right.value;
    return left;
}

//Conditional operators returns true/false
int operator == (const IntegerV3& left, const IntegerV3& right) {
    return left.value == right.value;
}
int operator != (const IntegerV3& left, const IntegerV3& right) {
    return left.value != right.value;
}
int operator < (const IntegerV3& left, const IntegerV3& right) {
    return left.value < right.value;
}
int operator > (const IntegerV3& left, const IntegerV3& right) {
    return left.value > right.value;
}
int operator <= (const IntegerV3& left, const IntegerV3& right) {
    return left.value <= right.value;
}
int operator >= (const IntegerV3& left, const IntegerV3& right) {
    return left.value >= right.value;
}
int operator && (const IntegerV3& left, const IntegerV3& right) {
    return left.value && right.value;
}
int operator || (const IntegerV3& left, const IntegerV3& right) {
    return left.value || right.value;
}