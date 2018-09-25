#include <iostream>
#include <thread>
#include <random>
#include <cmath>

#include "semaphore.cpp"
#include "queue.cpp"

int produce_item(){
    return rand()%(100-0 + 1) + 0;
}

void consume_item(int item){
    std::cout << pow(item, 2) << '\n';
}

void produce(Queue& q, Semaphore& s){
    int it = produce_item();
    q.add(it);
    s.release();

    produce(q, s);
}

void consume(Queue& q, Semaphore& s){
    s.acquire();
    int it = q.get();
    consume_item(it);

    consume(q, s);
}

int main(int argc, char *argv[]) {
    Queue q();
    Semaphore s(0);

    std::thread t1(produce, std::ref(q), std::ref(s));
    std::thread t2(consume, std::ref(q), std::ref(s));

    t1.join();
    t2.join();
    return 0;
}
