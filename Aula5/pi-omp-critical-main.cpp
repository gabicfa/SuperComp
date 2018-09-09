/*

This program will numerically compute the integral of

                  4/(1+x*x) 
				  
from 0 to 1.  The value of this integral is pi -- which 
is great since it gives us an easy way to check the answer.

The is the original sequential program.  It uses the timer
from the OpenMP runtime library

History: Written by Tim Mattson, 11/99.
         Updated by Luciano Soares, Igor Montagner
*/

#include <stdio.h>
#include "pi-omp-critical.cpp"

int main () {
    long num_steps = 1000000000;
    double pi;
    double start_time, run_time;

    start_time = omp_get_wtime();
    pi = pi_omp_critical(num_steps);
    run_time = omp_get_wtime() - start_time;
    printf("\n pi with %ld steps is %.12lf in %lf seconds\n ",num_steps,pi,run_time);
    return 0;
}
