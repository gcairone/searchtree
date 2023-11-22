#include <iostream>
#include <vector>
#include <list>
#include <fstream>
#include <cmath>
#include "search_tree.h"
using namespace std;

//funzioni di utilità
 
//stampa matrice qualsiasi
void print_matrix(const vector<vector<int>> &S) {
    for(int i=0; i<S.size(); i++) {
        for(int j=0; j<S[0].size(); j++) cout<< S[i][j] << ' ';
        cout << endl;
    }
}




int main() {
    std::streambuf *coutBuf = std::cout.rdbuf();
    std::ofstream file("output.txt");
    std::cout.rdbuf(file.rdbuf());

    vector<vector<int>> v = {{0, 2, 2}, {0, 1, 2}, {1, 0, 1}};
    //auto status_inizio = from_int_to_status(0);
    Node * rad = new Node(from_status_to_int(v));
    create_tree(rad, 4);
    printTree(rad);
    cout.rdbuf(coutBuf);

}

/*
{2, 0, 2}, 
{2, 0, 1}, 
{1, 1, 2}
*/