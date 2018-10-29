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
    int processoAtual = 1;

    if(world.rank()==0){
        for (int i = 0; i <  listName.size(); i++){
            _PGMData imagemIn;
            FILE *pFile = fopen (imagens[i] , "r");
            readImage(imagens[i], &imagemIn);
            vector<vector<int>> imgMatrix = malloc_to_vector(imagemIn.matrix, imagemIn.row, imagemIn.col);
            world.send(processoAtual, 2, listName[i]);
            world.send(processoAtual, 0, imagemIn);
            world.send(processoAtual, 1, imgMatrix);
            processoAtual+=1;
            
            if(processoAtual == n){
                processoAtual = 1;
            }    
        }

        for (int p = 1; p <  world.size(); p++){
            string end = "null";
            world.send(p, 2, end);
        }
    }

    else{
        while(true){

            _PGMData imagemIn;
            _PGMData imagemOut;
            string name;
            vector<vector<int>> imgMatrix;
            
            world.recv(0,2,name);

            string null = "null";
            if (null.compare(name) == 0){
                break;
            }

            world.recv(0,0,imagemIn);
            world.recv(0,1,imgMatrix);
            
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


