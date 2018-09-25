#include <thread>
#include <iostream>
#include <mutex>

std::mutex mtx;

void thread_f(int i) {
  std::unique_lock<std::mutex> lck(mtx);
  std::cout << "thread id= " << i << std::endl;
}


int main() {

  int max_threads = 4;

  std::thread *array = new std::thread[max_threads];

  for(int i = 0; i < max_threads; i++){
    array[i] = std::thread(thread_f,i);
  }
  for(int i = 0; i< max_threads; i++){
    array[i].join();
  }
}
