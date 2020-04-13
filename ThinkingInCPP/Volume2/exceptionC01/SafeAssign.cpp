/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "SafeAssign.h"

void testSafeAssignment() {
    int someNumbers[] = {1, 2, 3, 4};
    size_t someCount = sizeof someNumbers / sizeof(someNumbers[0]);
    int someMoreNumbers[] = {5, 6, 7};
    size_t someMoreCount = sizeof someMoreNumbers / sizeof(someMoreNumbers[0]);
    
    HasPointers h1("Hello", someNumbers, someCount);
    HasPointers h2("GoodBye", someMoreNumbers, someMoreCount);
    
    std::cout << h1 << std::endl;
    h1 = h2;
    std::cout << h1 << std::endl;
}