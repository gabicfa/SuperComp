#include <iostream>
#include "boost/filesystem.hpp" 
#include <fstream>
#include <string>
#include <omp.h>
#include <vector>
#include <chrono>

using namespace std::chrono;
using namespace boost::filesystem;
using namespace std;

void busca_no_arquivo(string path, string term) {
    std::vector<int> lines;
    string temp;
    int line = 0;
    ifstream f(path);
    while (getline(f, temp)) {
        line++;
        if (temp.find(term) != string::npos) {
            lines.push_back(line);
        }
    }

    for(int i=0; i<lines.size(); i++){
        #pragma omp critical
        {
            cout << path << ":" << lines[i] << "\n";
        }

    }
}

int main(int argc, char* argv[]){

    string word = "people";

    path p(argv[1]);
    high_resolution_clock::time_point t1 = high_resolution_clock::now();
    #pragma omp parallel
    {
        #pragma omp master
        {
            

            for (auto entry : directory_iterator(p)) {
                std::string path_str = entry.path().string();
                #pragma omp task
                {   
                    busca_no_arquivo(path_str, word);
                    
                }
            }
            
        }
    }
    high_resolution_clock::time_point t2 = high_resolution_clock::now();
    duration<double> time_span = duration_cast<duration<double> >(t2 - t1);
    cout << time_span.count() << '\n';
    return 0;
}
