#ifndef FUNZIONI_H
#define FUNZIONI_H
#include <vector>
#include <string>
using namespace std;

//inseime di mosse
extern vector<int> set_move;
//Prende un intero nell'intervallo [0, max] e restituisce lo status
vector<vector<int>> from_int_to_status(int s);

//Viceversa
int from_status_to_int(const vector<vector<int>> &s);

vector<vector<int>> from_int_to_move(int m);

int from_move_to_int(const vector<vector<int>> &m);

//funzioni per manipolare stati e mosse
//restituisce true se la differenza tra il numero di mosse fatte è sensato
//restituisce false anche se il numero dato è fuori range
bool correct(const int &s);

//restituisce true se lo status è "vinto"
//restituisce false se il numero dato è fuori range o se non è "correct"
bool won(const int &s);

//restituisce true se si può fare la mossa m quando lo status è s
bool possible(const int &s, const int &m);

int apply(const int &s, const int &m);

//prende uno status e restituisce una matrice stampabile
vector<vector<char>> transform_for_print(vector<vector<int>> m);

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
void printTree(Node* node, std::string prefix = "", bool isLast = true);


void create_tree(Node* &rad, const int &level);


#endif
