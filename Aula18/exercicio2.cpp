#include <boost/mpi/environment.hpp>
#include <boost/mpi/communicator.hpp>
#include <boost/serialization/vector.hpp>
#include <iostream>
#include <string>
#include "image.h"
#include "vector"

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

        for (int r = 1; r <=  world.size()-2; r++){
            if(r==1){
                vector<vector<int>> img_value;
                for (int i = 0; i <= r * (img.row/(world.size()-2)) + 1; ++i){
                    vector<int> lines;
                    for (int j = 0; j < img.col; ++j) {
                        lines.push_back(img.matrix[i*img.col+j]);
                    }
                    img_value.push_back(lines);
                }
                world.send(r, 0, img_value);
            }

            else if(r == world.size()-2){
                vector<vector<int>> img_value;
                for (int i = (r-1)* (img.row/(world.size()-2)); i <= img.row-1; ++i){
                    vector<int> lines;
                    for (int j = 0; j < img.col; ++j) {
                        lines.push_back(img.matrix[i*img.col+j]);
                    }
                    img_value.push_back(lines);
                }
                world.send(r, 0, img_value);
            }

            else{
                vector<vector<int>> img_value;
                for (int i = (r-1)* (img.row/(world.size()-2)); i <= r * (img.row/(world.size()-2)) + 1; ++i){
                    vector<int> lines;
                    for (int j = 0; j < img.col; ++j) {
                        lines.push_back(img.matrix[i*img.col+j]);
                    }
                    img_value.push_back(lines);
                }
                world.send(r, 0, img_value);
            }
        }
    }

    else if (world.rank() != n-1){

        vector<vector<int>> img_info;

        world.recv(0, 0, img_info);

        int row = img_info.size();
        int col = img_info[0].size();

        vector<vector<int>> limiar_adapt_img;
        int v;
        int media;
        for (int i = 0; i < row; ++i){
            vector<int>lines;
            for (int j = 0; j < col; ++j) {
                if(i == 0 && world.rank()==1){
                    lines.push_back(img_info[i][j]);
                }
                else if(i == row-1 && world.rank()==n-2){
                    lines.push_back(img_info[i][j]);
                }
                else if(j == 0 || j== col-1){
                    lines.push_back(img_info[i][j]);
                }
                else if (i!= 0 && i!= row-1){
                    v = img_info[i][j];
                    media = (img_info[i][j-1]+img_info[i][j+1]+img_info[i][j]+img_info[i+1][j-1]+img_info[i+1][j+1]+img_info[i+1][j]+img_info[i-1][j-1]+img_info[i-1][j+1]+img_info[i-1][j])/9;
                    if(v> media){
                        lines.push_back(255); 
                    }
                    else{
                        lines.push_back(0); 
                    }
                } 
            }
            if(lines.size() != 2){
                limiar_adapt_img.push_back(lines);
            }
        }
        world.send(n-1, 0, limiar_adapt_img);
    }

    else{
        vector<vector<int>> limiar_adapt_img_completo;
        for (int r = 1; r <=  world.size()-2; r++){
            vector<vector<int>> limiar_adapt_img_parcial;
            world.recv(r, 0, limiar_adapt_img_parcial);
            for(int i=0; i<limiar_adapt_img_parcial.size(); i++){
                limiar_adapt_img_completo.push_back(limiar_adapt_img_parcial[i]);
            }
        }
        int l = limiar_adapt_img_completo.size();
        int c = limiar_adapt_img_completo[0].size();
        int *mat = (int *)malloc(sizeof(int) * l * c);
        for (int i = 0; i < l; ++i){
            for (int j = 0; j < c; ++j) {
                mat[i*c+j] = limiar_adapt_img_completo[i][j];
            }
        }
        _PGMData img_limiar_adap;
        createImage(&img_limiar_adap, l, c, 255);
        img_limiar_adap.matrix = mat;
        writeImage(name, &img_limiar_adap, 0);
    }    
    return 0;
}