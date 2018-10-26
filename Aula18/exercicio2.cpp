#include <boost/mpi/environment.hpp>
#include <boost/mpi/communicator.hpp>
#include <iostream>
#include <string>
#include "image.h"

namespace mpi = boost::mpi;
using namespace std;

int main(int argc, char* argv[])
{

    mpi::environment env(argc, argv);
    mpi::communicator world;
    int n = world.size();

    const char *path = argv[1];
    const char *name = argv[2];

    if(word.rank()==0){
        _PGMData img;
        FILE *pFile = fopen (path , "r");
        SkipComments(pFile);
        readImage(path, &img);

        int mult  = img.row/n;
         
    }

    

    
    // createImage(&img, img.row, img.col, img.max_gray);
    writeImage(name, &img, 0);
    


    return 0;
}