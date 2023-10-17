#ifndef FUNZIONI_H
#define FUNZIONI_H
#include <vector>
using namespace std;
//Prende un intero nell'intervallo [0, 19682] e restituisce lo status
vector<vector<int>> from_int_to_status(int s);

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


#endif
