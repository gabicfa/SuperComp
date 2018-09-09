#include <stdio.h>
#include <omp.h>
#include <cstdlib>
#include <cmath>
#include <ctime>
#include <iostream>

double pi_omp_critical(long num_steps) {
  double step = 1.0/(double) num_steps;
  double d = 0;
  #pragma omp parallel for reduction (+:d)
    for (long i = 0; i < num_steps; i++) {
      double x = (i-0.5)*step;
      d += 4.0/(1.0+x*x);
    }
  return d * step;
}

int main () {
  double start_time, run_time;

  start_time = omp_get_wtime();

  double s = pi_omp_critical(100000000);

  run_time = omp_get_wtime() - start_time;
  std::cout<< run_time << std::endl;
  std::cout<< s << std::endl;

  start_time = omp_get_wtime();

  return 0;
}
