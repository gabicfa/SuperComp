#include <boost/mpi/environment.hpp>
#include <boost/mpi/communicator.hpp>
#include <boost/mpi/collectives.hpp>
#include <iostream>
#include <random>
#include <vector>
#include <math.h> 

namespace mpi = boost::mpi;
using namespace std;

int main(int argc, char* argv[])
{
    mpi::environment env(argc, argv);
    mpi::communicator world;
    int n = world.size();

    if(world.rank()==0){
        vector<int> myVector;
        srand((unsigned)time(NULL));
        int size = 1000;
        int i = 0;
        for (int i =0; i < size; i++){
            int randNum = rand()%(100-10 + 1) + 10;
            myVector.push_back(randNum);
        }
        int s = myVector.size()/n;
        int s_UltimoProcesso;
        if(s*n == myVector.size()){
            s_UltimoProcesso = s;
        }
        else{
            s_UltimoProcesso = s + (myVector.size()-s*n);
        }
        vector<int> vectorSize;
        for(int p=0; p<n; p++){
            if(p!=n-1){
                vectorSize.push_back(s);
            }
            else{
                vectorSize.push_back(s_UltimoProcesso);
            }
        }
        vector<int> vectorProcesso;
        mpi::scatterv(world, myVector, vectorSize, vectorProcesso, 0);
        cout << world.rank() << ": " << vectorProcesso.size() << '\n';
    }
}