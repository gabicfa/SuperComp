/*

This program will numerically compute the integral of

                  4/(1+x*x)

from 0 to 1.  The value of this integral is pi -- which
is great since it gives us an easy way to check the answer.

The is the original sequential program.  It uses the timer
from the OpenMP runtime library

History: Written by Tim Mattson, 11/99.
         Updated by Luciano Soares
*/
#include <stdio.h>
#include <omp.h>
#include <cstdlib>
#include <cmath>
#include <ctime>
#include <iostream>

double pi_seq(long steps,long start, long end){
  double step;

  int i;
  double x, pi, sum = 0.0;

  step = 1.0/(double) steps;

  for (i=start;i<= end; i++) {
      x = (i-0.5)*step;
      sum = sum + 4.0/(1.0+x*x);
  }

  pi = step * sum;

  return pi;
}

double pi_par1(long steps){
  int max_threads =  omp_get_max_threads();
  int part_size =  steps/ max_threads+1;
  double s = 0;

  #pragma omp parallel
  {

    long start = omp_get_thread_num()*part_size;
    long end = start+part_size;
    if(end>steps) end=steps;

    double r = pi_seq(steps, start,end);

    #pragma omp critical
    s+=r;
  }

  return s;
}


int main () {
  double start_time, run_time;

  start_time = omp_get_wtime();

  double s = pi_par1(100000000);

  run_time = omp_get_wtime() - start_time;
  std::cout<< run_time << std::endl;
  std::cout<< s << std::endl;

  start_time = omp_get_wtime();

  double s2 = pi_seq(100000000, 0, 100000000);

  run_time = omp_get_wtime() - start_time;
  std::cout<< run_time << std::endl;
  std::cout<< s2 << std::endl;

  return 0;
}
