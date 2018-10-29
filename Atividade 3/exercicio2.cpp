#include <boost/mpi/environment.hpp>
#include <boost/mpi/communicator.hpp>
#include <boost/serialization/vector.hpp>
#include <iostream>
#include <stdio.h>
#include <string>
#include "edge.h"
#include "image.h"
#include "vector"

namespace mpi = boost::mpi;
using namespace std;

vector<vector<int>> malloc_to_vector (int *matrix, int row, int col){
    vector<vector<int>> new_matrix;
    for (int i = 0; i < row; i++){
        vector<int>lines;
        for(int j=0; j<col; j++){
            lines.push_back(matrix[i*col+j]);
        }
        new_matrix.push_back(lines);
    }
    return  new_matrix;
}

void vector_to_malloc (vector<vector<int>> matrix_vector, int *matrix, int row, int col){
    vector<vector<int>> new_matrix;
    for (int i = 0; i < row; i++){
        for(int j=0; j<col; j++){
            matrix[i*col+j] = matrix_vector[i][j];
        }
    } 
}

int main(int argc, char* argv[])
{   
    int count = 0;
    vector<char*> imagens; 
    while(argv[++count] != NULL){
        if(count!=0){
            imagens.push_back(argv[count]);
        }
    }

    std::vector<std::string> listName;
    for(int i=1;i<argc;i++){
        listName.push_back(argv[i]);
    }


    mpi::environment env(argc, argv);
    mpi::communicator world;
    int n = world.size();
    int numImagens = imagens.size();

    if(world.rank()==0){
        for (int r = 1; r <  world.size(); r++){
            
            if(r==1){
                for(int i=0; i<=numImagens/(world.size()-1); i++){
                    _PGMData imagemIn;
                    FILE *pFile = fopen (imagens[i] , "r");
                    readImage(imagens[i], &imagemIn);
                    vector<vector<int>> imgMatrix = malloc_to_vector(imagemIn.matrix, imagemIn.row, imagemIn.col);
                    world.send(r, 0, imagemIn);
                    world.send(r, 1, imgMatrix);
                    world.send(r, 2, listName[i]);
                }
            }
            else if(r==world.size()-1){
                for(int i= (r-1) * numImagens/(world.size()-1) + 1; i<numImagens; i++){
                    _PGMData imagemIn;
                    FILE *pFile = fopen (imagens[i] , "r");
                    readImage(imagens[i], &imagemIn);
                    vector<vector<int>> imgMatrix = malloc_to_vector(imagemIn.matrix, imagemIn.row, imagemIn.col);
                    world.send(r, 0, imagemIn);
                    world.send(r, 1, imgMatrix);
                    world.send(r, 2, listName[i]);
                }
            }
            else{
                for(int i= (r-1) * numImagens/(world.size()-1) + 1; i<=r * numImagens/(world.size()-1); i++){
                    _PGMData imagemIn;
                    FILE *pFile = fopen (imagens[i] , "r");
                    readImage(imagens[i], &imagemIn);
                    vector<vector<int>> imgMatrix = malloc_to_vector(imagemIn.matrix, imagemIn.row, imagemIn.col);
                    world.send(r, 0, imagemIn);
                    world.send(r, 1, imgMatrix);
                    world.send(r, 2, listName[i]);
                }
            } 
        }
    }

    if(world.rank()==1){
        for(int i=0; i<=numImagens/(world.size()-1); i++){
            _PGMData imagemIn;
            _PGMData imagemOut;
            string name;
            vector<vector<int>> imgMatrix;
            world.recv(0,0,imagemIn);
            world.recv(0,1,imgMatrix);
            world.recv(0,2,name);
            name.insert(name.size()-4,"_edges");
            cout << name << '\n';
            int *mat = (int *)malloc(sizeof(int) * imagemIn.row * imagemIn.col);
            vector_to_malloc(imgMatrix, mat, imagemIn.row, imagemIn.col);
            imagemIn.matrix = mat;

            createImage(&imagemOut, imagemIn.row, imagemIn.col, imagemIn.max_gray);
            edgeFilter(imagemIn.matrix, imagemOut.matrix, 0, imagemIn.row, 0, imagemIn.col);
            writeImage(name.c_str(), &imagemOut, 0);
        }
    }
    else if(world.rank()==n-1){
        for(int i= (world.rank()-1) * numImagens/(world.size()-1) + 1; i<numImagens; i++){
            _PGMData imagemIn;
            _PGMData imagemOut;
            string name;
            vector<vector<int>> imgMatrix;
            world.recv(0,0,imagemIn);
            world.recv(0,1,imgMatrix);
            world.recv(0,2,name);
            name.insert(name.size()-4,"_edges");
            cout << name << '\n';
            
            int *mat = (int *)malloc(sizeof(int) * imagemIn.row * imagemIn.col);
            vector_to_malloc(imgMatrix, mat, imagemIn.row, imagemIn.col);
            imagemIn.matrix = mat;

            createImage(&imagemOut, imagemIn.row, imagemIn.col, imagemIn.max_gray);
            edgeFilter(imagemIn.matrix, imagemOut.matrix, 0, imagemIn.row, 0, imagemIn.col);
            writeImage(name.c_str(), &imagemOut, 0);
        }
    }
    else{
        for(int i= (world.rank()-1) * numImagens/(world.size()-1) + 1; i<=world.rank() * numImagens/(world.size()-1); i++){
            _PGMData imagemIn;
            _PGMData imagemOut;
            string name;
            vector<vector<int>> imgMatrix;
            world.recv(0,0,imagemIn);
            world.recv(0,1,imgMatrix);
            world.recv(0,2,name);
            name.insert(name.size()-4,"_edges");            

            int *mat = (int *)malloc(sizeof(int) * imagemIn.row * imagemIn.col);
            vector_to_malloc(imgMatrix, mat, imagemIn.row, imagemIn.col);
            imagemIn.matrix = mat;

            createImage(&imagemOut, imagemIn.row, imagemIn.col, imagemIn.max_gray);
            edgeFilter(imagemIn.matrix, imagemOut.matrix, 0, imagemIn.row, 0, imagemIn.col);
            writeImage(name.c_str(), &imagemOut, 0);
        }
    }

    

    return 0;
}


