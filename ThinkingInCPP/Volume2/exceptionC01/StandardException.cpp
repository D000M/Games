/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "StandardException.h"

void testMyException() {
    try {
        throw MyException("In testMyException() try");
    }
    catch(MyException& e) {
        std::cout << e.what() << std::endl;
    }
}