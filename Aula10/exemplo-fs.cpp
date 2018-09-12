#include <iostream>
#include "boost/filesystem.hpp" 
#include <fstream>
#include <string>


using namespace boost::filesystem;
using namespace std;

void Keyword(ifstream &stream, string token){
    string line;
    while (getline(stream, line)) {
        if (line.find(token) != string::npos) {
            cout << line << endl;
        }
    }
    cout << token << " not found" << endl;
}

int main(int argc, char **argv) {

    string word;

    cout << "Qual a palavra que se deseja pesquisar:";
    cin >> word;

    path p(".");
    
    for (auto &entry : directory_iterator(p)) {
        std::cout << entry.path().string() << "\n";
        ifstream infile(entry.path().c_str());
        Keyword(infile,word);
    }
    
    return 0;
}
