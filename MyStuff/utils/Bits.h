/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Bits.h
 * Author: default
 *
 * Created on February 8, 2019, 3:05 PM
 */

#ifndef BITS_H
#define BITS_H

#include <iostream>
#include <bitset>
//Define 8 separate bit flags (these can represent whatever you want)
const unsigned char option0 = 0b0000'0001;   //represent bit 0
const unsigned char option1 = 0b0000'0010;   //represent bit 1
const unsigned char option2 = 0b0000'0100;   //represent bit 2
const unsigned char option3 = 0b0000'1000;   //represent bit 3
const unsigned char option4 = 0b0001'0000;   //represent bit 4
const unsigned char option5 = 0b0010'0000;   //represent bit 5
const unsigned char option6 = 0b0100'0000;   //represent bit 6
const unsigned char option7 = 0b1000'0000;   //represent bit 7


//In order to use 16bit or 32bit number we must put option0-15 for 16bit and option0-31 for 32bit numbers.
// Since we have 8 options above, we'll use an 8-bit value to hold our options
// Each bit in myflags corresponds to one of the options defined above
unsigned char myflags = 0;      // all bits turned off to start 8bit number

/**
 * How do we turn on/off bits of our variable? we used bitwise OR equals operator (|=)
 * for example
 * myflags |= option4;  // turn option 4 on this is equvalent of myflags = (myflags | option4);
 * 
 * myflags = 0000 0000 (we initialized this to 0) 
 * option4 = 0001 0000
 * ---------------------
 * result  = 0001 0000
 * 
 * We can also turn on multiple bits at the same time using bitwise OR:
 * myflags |= (option4 | option5); // turn options 4 and 5 on at the same time
 * 
 * Turning individual bits off
 * 
 * To clear a bit (turn off), we use bitwise AND with an inverse bit pattern:
 * myflags &= ~option4; // turn option 4 off
 * 
 * This works similarly to the above. Let’s say myflags was initially set to 0001 1100 (options 2, 3, and 4 turned on).
 * myflags &= ~option4; is the equivalent of myflags = (myflags & ~option4).
 * myflags  = 0001 1100
 * ~option4 = 1110 1111
 * --------------------
   result   = 0000 1100
 * 
 * We can turn off multiple bits at the same time:
 * myflags &= ~(option4 | option5); // turn options 4 and 5 off at the same time
 * 
 * Flipping individual bits
 * 
 * To toggle a bit state, we use bitwise XOR:
 * myflags ^= option4; // flip option4 from on to off, or vice versa
 * myflags ^= (option4 | option5); // flip options 4 and 5 at the same time
 * 
 * Determining if a bit is on or off
 * 
 * To query a bit state, we use bitwise AND:
 *  if (myflags & option4)
        std::cout << "myflags has option 4 set";
    if (!(myflags & option5))
        std::cout << "myflags does not have option 5 set";
 */


void testSimpleBits() {
    // Define a bunch of physical/emotional states
    const unsigned char isHungry = 1 << 0; // 0000 0001
    const unsigned char isSad = 1 << 1; // 0000 0010
    const unsigned char isMad = 1 << 2; // 0000 0100
    const unsigned char isHappy = 1 << 3; // 0000 1000
    const unsigned char isLaughing = 1 << 4; // 0001 0000
    const unsigned char isAsleep = 1 << 5; // 0010 0000
    const unsigned char isDead = 1 << 6; // 0100 0000
    const unsigned char isCrying = 1 << 7; // 1000 0000

    unsigned char me = 0; // all flags/options turned off to start
    me |= isHappy | isLaughing; // I am happy and laughing
    me &= ~isLaughing; // I am no longer laughing

    // Query a few states (we'll use static_cast<bool> to interpret the results as a boolean value rather than an integer)
    std::cout << "I am happy? " << static_cast<bool>(me & isHappy) << '\n';
    std::cout << "I am laughing? " << static_cast<bool>(me & isLaughing) << '\n';
}

void quizzBits() {
    unsigned char option_viewed = 0b0000'0001;
    unsigned char option_edited = 0b0000'0010;
    unsigned char option_favorited = 0b0000'0100;
    unsigned char option_shared = 0b0000'1000;
    unsigned char option_deleted = 0b0001'0000;
    
    std::bitset<8> bits;
    
    unsigned char myArticleFlags = 0;
    bits = myArticleFlags;
    std::cout << bits << std::endl;
    //set flag to viewed;
    myArticleFlags |= option_viewed;
    bits = myArticleFlags;
    std::cout << bits << std::endl;
     
    myArticleFlags |= option_deleted;
    bits = myArticleFlags;
    std::cout << bits << std::endl;
    //Check if myArticleFlags is deleted.
    if(myArticleFlags & option_deleted) {
        std::cout << "option_deleted is on!\n";
    }
    else {
        std::cout << "option_deleted is off!\n";
    }
    
    //Set option_favorited on
    myArticleFlags |= option_favorited;
    bits = myArticleFlags;
    std::cout << bits << std::endl;
    
    //clear the article as a favorite.
    myArticleFlags &= ~option_favorited;
    bits = myArticleFlags;
    std::cout << bits << std::endl;
}

#endif /* BITS_H */

