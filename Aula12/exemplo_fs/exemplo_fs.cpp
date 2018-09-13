#include <iostream>
#include <fstream>
#include "boost/filesystem.hpp"

using namespace boost::filesystem;

void busca_no_arquivo(std::string path, std::string term) {
    std::string temp;
    int line = 0;
    std::ifstream f(path);
    while (std::getline(f, temp)) {
        if (temp.find("the") != std::string::npos) {
            std::cout << path << ":" << line << "\n";
            line++;
        }
    }
}

int main(int argc, char **argv) {
    
    path p(".");
    for (auto entry : directory_iterator(p)) {
        std::string path_str = entry.path().string();
        busca_no_arquivo(path_str, "the");
    }
    return 0;
}
