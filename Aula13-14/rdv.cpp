#include <iostream>
#include <chrono>
#include <thread>
#include "semaphore.cpp"

Semaphore s2(0);
Semaphore s1(0);

void tarefaA() {

    std::cout << "Faz trabalho A" << std::endl;
    s2.release();
    s1.acquire();
    std::cout << "Fim trabalho A" << std::endl;
    
// DESEJO ESPERAR POR B AQUI!
    
}

void tarefaB() {

    std::cout << "Faz trabalho B" << std::endl;
    s1.release();
    s2.acquire();
    std::cout << "Fim trabalho B" << std::endl;    

// DESEJO ESPERAR POR A AQUI!
    
}

int main(int argc, char *argv[]) {
    std::thread t1(tarefaA);
    std::thread t2(tarefaB);
    t1.join();
    t2.join();
    return 0;
}