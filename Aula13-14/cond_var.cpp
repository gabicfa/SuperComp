#include <iostream>
#include <thread>
#include <condition_variable>
#include <chrono>
#include <mutex>

void thread0(int &resultado_para_thread1) {
    // faz trabalho longo
    std::this_thread::sleep_for(std::chrono::milliseconds(300));
    
    resultado_para_thread1 = 10;
    
    // faz trabalho longo
    std::this_thread::sleep_for(std::chrono::milliseconds(1300));
    std::cout << "Fim thread0!" << std::endl;
}

void thread1(int const &resultado_da_thread0, int &resultado_para_thread2) {
    // faz trabalho long com resultado de thread0
    std::this_thread::sleep_for(std::chrono::milliseconds(1500));
    
    // finja que isto depende da thread0
    resultado_para_thread2 = 20; 
    
    std::cout << "Fim thread1!" << std::endl;
}

void thread2(int const &resultado_thread_0, int const &resultado_thread_1) {
    // faz trabalho longo com resultado de thread0
    std::this_thread::sleep_for(std::chrono::milliseconds(1500));
    
    // faz trabalho longo com resultado de thread1
    std::this_thread::sleep_for(std::chrono::milliseconds(500));
    
   
    std::cout << "thread2:" << resultado_thread_0 + resultado_thread_1 << "\n";
    std::cout << "Fim thread2!" << std::endl;
}

int main(int argc, char **argv) {
    int res_t0, res_t1;
    
    thread0(res_t0);
    thread1(res_t0, res_t1);
    thread2(res_t0, res_t1);
       
    return 0;
}
