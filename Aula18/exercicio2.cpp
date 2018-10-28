#include <boost/mpi/environment.hpp>
#include <boost/mpi/communicator.hpp>
#include <iostream>
#include <string>
#include "image.h"

namespace mpi = boost::mpi;
using namespace std;

int main(int argc, char* argv[])
{
    const char *path = argv[1];
    const char *name = argv[2];

    mpi::environment env(argc, argv);
    mpi::communicator world;
    int n = world.size();

    if(world.rank()==0){
        _PGMData img;
        FILE *pFile = fopen (path , "r");
        SkipComments(pFile);
        readImage(path, &img);
        // int mult  = img.row/(n-2);
        // for(int p=1; p< n-1; p++){

        // }
    }
    else
    
    // createImage(&img, img.row, img.col, img.max_gray);
    // writeImage(name, &img, 0);
    
    return 0;
}