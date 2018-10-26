/*
 * fonte: https://www.boost.org/doc/libs/1_67_0/doc/html/mpi/tutorial.html
 */

#include <boost/mpi/environment.hpp>
#include <boost/mpi/communicator.hpp>
#include <iostream>
#include <unistd.h>


namespace mpi = boost::mpi;

int main(int argc, char* argv[]) {
    char name[100];
    mpi::environment env(argc, argv);
    mpi::communicator world;
    gethostname(name, 100);  
    if (world.rank() == 0) {
        world.send(1, 0, 3.14);
        std::cout << "I am process " << world.rank() << " of " << world.size()
            << " in " << name << std::endl;
    } else if (world.rank() == 1) {
        double data;
        world.recv(0, 0, data);
        std::cout << "I am process " << world.rank() << " of " << world.size()
            << " in " << name << ", " << data << std::endl;
        world.send(2, 0, data * 2);
    } else if (world.rank() == 2) {
        double data;
        world.recv(1, 0, data);
        std::cout << "I am process " << world.rank() << " of " << world.size()
            << " in " << name << ", " << data << std::endl;
    }
            
    return 0;
}
