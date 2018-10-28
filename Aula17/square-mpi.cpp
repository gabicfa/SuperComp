#include <boost/mpi/environment.hpp>
#include <boost/mpi/communicator.hpp>
#include <iostream>
#include <math.h> 
namespace mpi = boost::mpi;


int square(int i){
    return pow(i,2);
}

int main(int argc, char* argv[])
{
    mpi::environment env(argc, argv);
    mpi::communicator world;
    int n = world.size();
    
    if(world.rank()==0){
        int data;
        world.send(world.rank()+1, 0, square(world.rank()));
        world.recv(n-1, 0, data);
        std::cout << "Received " << data << " from " << n-1 << "\n";
    }
    else if(world.rank()== n-1){
        int data;
        world.send(0, 0, square(world.rank()));
        world.recv(world.rank()-1, 0, data);
        std::cout << "Received " << data << " from " << world.rank()-1 << "\n";
    }
    else{
        int data;
        world.send(world.rank()+1, 0, square(world.rank()));
        world.recv(world.rank()-1, 0, data);
        std::cout << "Received " << data << " from " << world.rank()-1 << "\n";
    }
    return 0;
}