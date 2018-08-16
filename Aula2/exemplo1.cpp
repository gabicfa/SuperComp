#include <cstdlib>
#include <cmath>
#include <ctime>
#include <iostream>
#include <thread>
#include <iostream>

using namespace std;
 // return a uniformly distributed random number
double RandomGenerator()
{
  return ( (double)(rand()) + 1. )/( (double)(RAND_MAX) + 1. );
}
 // return a normally distributed random number
double normalRandom()
{
  double y1=RandomGenerator();
  double y2=RandomGenerator();
  return cos(2*3.14*y2)*sqrt(-2.*log(y1));
}

double soma_vec_seq(double *vec, int n, int start, int end){
  double soma = 0;
  for(int i=start; i<end; i++){
    soma = soma + vec[i];
  }
  return soma;
}

void soma_thread(double *vec, int n, int start, int end, double *res){
  *res = soma_vec_seq(vec,n,start,end);
}

double soma_vec_par(double *vec, int n){
  int max_threads = std::thread::hardware_concurrency();
  std::thread *arr = new std::thread[max_threads];
  double *somas_parciais = new double[max_threads];

  int part_size = n / max_threads + 1;

  for(int i = 0; i < max_threads; i++){
    somas_parciais[i] = 0;
    int start = i*part_size;
    int end = start+part_size;
    if(end>n) end = n;
    arr[i] = std::thread(soma_thread, vec, n, start, end, &somas_parciais[i]);
  }

  double sum = 0;
  for (int i = 0; i< max_threads; i++){
    arr[i].join();
    sum +=somas_parciais[i];
  }
}

int main(){
double sigma = 1.;
double Mi = 5.;
double *v = new double[100];

  for(int i=0;i<100;i++){
    double x = normalRandom()*sigma+Mi;
    v[i] = x;
  }

  soma_vec_par(v, 100);

  return 0;
}
