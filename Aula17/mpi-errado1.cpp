#include <boost/mpi/environment.hpp>
#include <boost/mpi/communicator.hpp>
#include <iostream>
namespace mpi = boost::mpi;

int main(int argc, char* argv[]) {
    mpi::environment env(argc, argv);
    mpi::communicator world;
    
    if (world.rank() == 0) {
        int data;
        world.send(1, 0, 100);
        world.recv(2, 2, data);
        std::cout << "Received " << data << " from 2 \n";
    } else {
        if (world.rank() == 1) {
            int data;
            world.send(2, 1, 200);
            world.recv(0, 0, data);
            std::cout << "Received " << data << " from 0 \n";
        }
        else{
            int data;
            world.send(0, 2, 300);
            world.recv(1, 1, data);
            std::cout << "Received " << data << " from 1 \n";
        }
    }
    return 0;
}
