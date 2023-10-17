#include <iostream>
#include <vector>
#include <list>
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

struct Edge;
struct Node {
    int status;
    vector<Edge*> list_moves;
    Node(int s): status(s), list_moves({}) {}
};
struct Edge {
    int move;
    Node* result;
    Edge(int m): move(m), result(nullptr) {}
};


// Funzione per stampare l'albero generico con indentazioni per chiarezza
void printTree(Node* node, std::string prefix = "", bool isLast = true) {
    if (node == nullptr)
        return;

    std::cout << prefix;
    if (isLast) {
        std::cout << "└── ";
        prefix += "    ";
    } else {
        std::cout << "├── ";
        prefix += "│   ";
    }

    cout << node->status << ' ' << ((won(node->status)) ? "won" : "") << endl;

    for (size_t i = 0; i < node->list_moves.size(); ++i) {
        bool last = (i == node->list_moves.size() - 1);
        printTree(node->list_moves[i]->result, prefix, last);
    }
}

void create_tree(Node* &rad, const int &level) {
    //cout << "Chiamata " << level << endl;
    if(rad && level > 0) {
        //cout << "Chiamata" << endl;
        for(int i=1; i<=9; ++i) {
            if(possible(rad->status, i)) {
                Edge* e = new Edge(i); //crea l'arco mossa
                rad->list_moves.push_back(e); //connetti l'arco mossa alla radice
                Node * res = new Node(apply(rad->status, e->move)); //crea il nodo risultato
                if(!won(res->status)) create_tree(res, level - 1); //crea l'albero del nodo risultato
                e->result = res; //collega il nodo risultato alla mossa
            }
        }
        for(int i=-1; i>=-9; --i) {
            if(possible(rad->status, i)) {
                Edge* e = new Edge(i); //crea l'arco mossa
                rad->list_moves.push_back(e); //connetti l'arco mossa alla radice
                Node * res = new Node(apply(rad->status, e->move)); //crea il nodo risultato
                if(!won(res->status)) create_tree(res, level - 1); //crea l'albero del nodo risultato
                e->result = res; //collega il nodo risultato alla mossa
            }
        }
    }

}

int main() {
    vector<vector<int>> v = {{0, 0, 2}, {2, 1, 1}, {1, 0, 2}};
    //auto status_inizio = from_int_to_status(0);
    Node * rad = new Node(from_status_to_int(v));
    create_tree(rad, 4);
    printTree(rad);

}

/*
{2, 0, 2}, 
{2, 0, 1}, 
{1, 1, 2}
*/