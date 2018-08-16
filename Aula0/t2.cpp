#include <iostream>
#include <random>
#include <chrono>


double soma_positivos1(double *a, int n){
    double soma=0;
    for (int i=0; i<n; i++){
        if (a[i] > 0){
            soma = soma + a[i];
        }
    }
    return soma;
}

double soma_positivos2(double *a, int n){
    double soma=0;
    for (int i=0; i<n; i++){
        (a[i] > 0)?soma = soma + a[i]:soma=soma;
    }
    return soma;
}

int main(){
    
    double *v = new double[10000000];
    std::random_device rd; // obtain a random number from hardware
    std::mt19937 eng(rd()); // seed the generator
    std::uniform_int_distribution<> distr(-10, 10); // define the range


    for (int i = 0; i < 10000000; i++) {
        v[i] = distr(eng);
    }

    using namespace std::chrono;

    high_resolution_clock::time_point t1 = high_resolution_clock::now();

    double r = soma_positivos1(v,10000000);

    high_resolution_clock::time_point t2 = high_resolution_clock::now();

    duration<double> time_span = duration_cast<duration<double> >(t2 - t1);
    std::cout << "It took me " << time_span.count() << " seconds.";
    std::cout << "result: " << r; 
    std::cout << std::endl;
    return 0;
}