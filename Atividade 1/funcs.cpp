#include <math.h>
#include <iostream>
#include <random>
#include <chrono>
#include <fstream>


double inner_prod(double *a, double *b, unsigned long n) {
    double sum = 0;
    for (int i = 0; i < n; i++) {
        sum += a[i] * b[i];
    }
    return sqrt(sum);
}

double sum_positive(double *a, unsigned long n) {
    double s = 0;
    for (int i = 0; i < n; i++) {
        if (a[i] > 0) {
            s += a[i];
        }
    }
    return s;
}

void sqrt_element(double *a, unsigned long n) {
    for (int i = 0; i < n; i++) {
        a[i] = sqrt(a[i]);
    }
}

void exp_element(double *a, unsigned long n) {
    for (int i = 0; i < n; i++) {
        a[i] = exp(a[i]);
    }
}

void log_element(double *a, unsigned long n) {
    for (int i = 0; i < n; i++) {
        a[i] = log(a[i]);
    }
}

void gauss(double *a, double *b, unsigned long n) {
    double p = 1 / sqrt(2.0 * M_PI);
    for (int i = 0; i < n; i++) {
        b[i] = p * exp(-a[i]*a[i]/2);
    }
}

void copy_vector(double *a, double *b, int n){
  for (int i=0 ; i<n; i++){
    a[i] = b[i];
  }
}

int main(){

    std::random_device rd; // obtain a random number from hardware
    std::mt19937 eng(rd()); // seed the generator
    std::uniform_int_distribution<> distr(0, 10); // define the range

    int amostras = 20;
    unsigned long *tamanho = new unsigned long[amostras];
    double *tempo_inner_prod = new double[amostras];
    double *tempo_sum_positive = new double[amostras];
    double *tempo_sqrt_element = new double[amostras];
    double *tempo_exp_element = new double[amostras];
    double *tempo_log_element = new double[amostras];
    double *tempo_gauss = new double[amostras];

    unsigned long n = 100;

    for(int i = 0; i<=amostras; i++){
        tamanho[i]= n;
        double *v = new double[n];
        double *a = new double[n];

        for (int j = 0; j < n; j++) {
            v[j] = distr(eng);
        }

        using namespace std::chrono;

        copy_vector(a,v,n);
        std::cout << "inner_prod " << n;
        high_resolution_clock::time_point t1 = high_resolution_clock::now();
        inner_prod(a,a,n);
        high_resolution_clock::time_point t2 = high_resolution_clock::now();
        duration<double> time_span1 = duration_cast<duration<double> >(t2 - t1);
        tempo_inner_prod[i] = time_span1.count();
        std::cout << std::endl;

        copy_vector(a,v,n);
        std::cout << "sum_positive " << n;
        high_resolution_clock::time_point t3 = high_resolution_clock::now();
        sum_positive(a,n);
        high_resolution_clock::time_point t4 = high_resolution_clock::now();
        duration<double> time_span2 = duration_cast<duration<double> >(t4 - t3);
        tempo_sum_positive[i] = time_span2.count();
        std::cout << std::endl;

        copy_vector(a,v,n);
        std::cout << "sqrt_element " << n;
        high_resolution_clock::time_point t5 = high_resolution_clock::now();
        sqrt_element(a,n);
        high_resolution_clock::time_point t6 = high_resolution_clock::now();
        duration<double> time_span3 = duration_cast<duration<double> >(t6 - t5);
        tempo_sqrt_element[i] = time_span3.count();
        std::cout << std::endl;

        copy_vector(a,v,n);
        std::cout << "log_element " << n;
        high_resolution_clock::time_point t7 = high_resolution_clock::now();
        log_element(a,n);
        high_resolution_clock::time_point t8 = high_resolution_clock::now();
        duration<double> time_span4 = duration_cast<duration<double> >(t8 - t7);
        tempo_log_element[i] = time_span4.count();
        std::cout << std::endl;

        copy_vector(a,v,n);
        std::cout << "gauss " << n;
        high_resolution_clock::time_point t9 = high_resolution_clock::now();
        gauss(a,a,n);
        high_resolution_clock::time_point t10 = high_resolution_clock::now();
        duration<double> time_span5 = duration_cast<duration<double> >(t10 - t9);
        tempo_gauss[i] = time_span5.count();
        std::cout << std::endl;

        copy_vector(a,v,n);
        std::cout << "exp_element " << n;
        high_resolution_clock::time_point t11 = high_resolution_clock::now();
        exp_element(a,n);
        high_resolution_clock::time_point t12 = high_resolution_clock::now();
        duration<double> time_span6 = duration_cast<duration<double> >(t12 - t11);
        tempo_exp_element[i] = time_span6.count();
        std::cout << std::endl;

        n = n*2;
    }


    std::ofstream o("t3Tempos.txt");
    o << "tamanhos=[";
    for(int i = 0; i<=amostras; i++){
        if (i != amostras){
            o << tamanho[i] << ", ";
        }
        else{
            o << tamanho[i];
        }
    }
    o <<"]"<< std::endl;

    o << "tempo_inner_prod=[";
    for(int i = 0; i<=amostras; i++){
        if (i != amostras){
            o << tempo_inner_prod[i] << ", ";
        }
        else{
            o << tempo_inner_prod[i];
        }
    }
    o <<"]"<< std::endl;

    o<< "tempo_sum_positive=[";
    for(int i = 0; i<=amostras; i++){
        if (i != amostras){
            o << tempo_sum_positive[i] << ", ";
        }
        else{
            o << tempo_sum_positive[i];
        }
    }
    o <<"]"<< std::endl;

    o << "tempo_sqrt_element=[";
    for(int i = 0; i<=amostras; i++){
        if (i != amostras){
            o << tempo_sqrt_element[i] << ", ";
        }
        else{
            o << tempo_sqrt_element[i];
        }
    }
    o <<"]"<< std::endl;

    o << "tempo_exp_element=[";
    for(int i = 0; i<=amostras; i++){
         if (i != amostras){
            o << tempo_exp_element[i] << ", ";
        }
        else{
            o << tempo_exp_element[i];
        }
    }
    o <<"]"<< std::endl;

    o<< "tempo_log_element=[";
    for(int i = 0; i<=amostras; i++){
        if (i != amostras){
            o << tempo_log_element[i] << ", ";
        }
        else{
            o << tempo_log_element[i];
        }
    }
    o <<"]"<< std::endl;

    o << "tempo_gauss=[";
    for(int i = 0; i<=amostras; i++){
        if (i != amostras){
            o << tempo_gauss[i] << ", ";
        }
        else{
            o << tempo_gauss[i];
        }
    }
    o <<"]"<< std::endl;

    return 0;
}
