#include <boost/mpi.hpp>
#include <boost/serialization/string.hpp>
#include <boost/mpi/nonblocking.hpp>
#include <string>
#include <iostream>
#include <vector>
#include <ctime>

int main(int argc, char *argv[]) {
    boost::mpi::environment env{argc, argv};
    boost::mpi::communicator world;
    
    if (world.rank() == 0) {
        std::string s[2];
        std::vector <boost::mpi::request> r; 

        // auto r1 = ;
        // auto r2 = ;
        r.push_back(world.irecv(1, 10, s[0]));
        r.push_back(world.irecv(2, 20, s[1]));

        std::cout << r.size() << '\n';
        auto mensagem1 = wait_any(r.begin(), r.end());
        std::cout << s[std::distance(r.begin(), mensagem1.second)] << "\n" << std::endl;

        auto mensagem2 = wait_any(r.begin(), r.end()); 
        std::cout << s[std::distance(r.begin(), mensagem2.second)] << '\n';

    } else if (world.rank() == 1) {
        std::string s = "Hello, world!";
        sleep(2);
        world.send(0, 10, s);
        std::cout << "Fim rank 1 " << std::endl;
    } else if (world.rank() == 2) {
        std::string s = "Hello, moon!";
        sleep(1);
        world.send(0, 20, s);
        std::cout << "Fim rank 2 " << std::endl;
    }
}
