//**********************************************************
// Pseudo random number generator:
//     double random
//     void seed (lower_limit, higher_limit)
//**********************************************************
//
// A simple linear congruential random number generator
// (Numerical Recipies chapter 7, 1st ed.) with parameters
// from the table on page 198j.
//
//  Uses a linear congruential generator to return a value between
//  0 and 1, then scales and shifts it to fill the desired range.  This
//  range is set when the random number generator seed is called.
// 
// USAGE:
//
//      pseudo random sequence is seeded with a range
//
//            void seed(lower_limit, higher_limit)
//   
//      and then subsequent calls to the random number generator generates values
//      in the sequence:
//
//            double drandom()
//
// History: 
//      Written by Tim Mattson, 9/2007.
//      changed to drandom() to avoid collision with standard libraries, 11/2011


// static long MULTIPLIER  = 1366;
// static long ADDEND      = 150889;
// static long PMOD        = 714025;
// long random_last = 0;
// double random_low, random_hi;

#include "random.h"
#include <stdio.h>
#include <iostream>

random::random(long mult, long pmod, long random_last, double random_low, double random_hi):
    mult(mult),
    pmod(pmod),
    random_last(random_last),
    random_low(random_low),
    random_hi(random_hi){}

double random::get_next_random()
{
    long random_next;
    double ret_val;

    random_next = (mult  * random_last)% pmod;
    random_last = random_next;

    ret_val = ((double)random_next/(double)pmod)*(random_hi-random_low)+random_low;
    
    return ret_val;
}

