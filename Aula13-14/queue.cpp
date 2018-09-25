class Queue{
    public:
        Queue();
        void add(int elem);
        int get();

    private:
        int to_produce;
        int to_consume;
        int *data;
};

Queue::Queue(){
    to_produce = 0;
    to_consume = 0;
};


void Queue::add(int elem){
    data[to_produce] = elem;
    to_produce ++;
}

int Queue::get(){
    int it = data[to_consume];
    to_consume++;
    return it;
}
