#include <omp.h>

double pi_omp_critical(long num_steps) {
    double step = 1.0/(double) num_steps;
    double sum = 0;
    
    #pragma omp parallel 
    {
        int id = omp_get_thread_num();
        long nt = omp_get_num_threads();
        double d = 0;
        for (long i = id; i < num_steps; i+=nt) {
            double x = (i-0.5)*step;
            d += 4.0/(1.0+x*x);
        }
        #pragma omp critical 
        {
            sum += d;
        }
    }

    return sum * step;
}

