#include <iostream>
#include <cmath>
#include <vector>
#include "search_tree.h"
using namespace std;

vector<int> set_move = {-9, -8, -7, -6, -5, -4, -3, -2, -1, 1, 2, 3, 4, 5, 6, 7, 8, 9};
//Prende un intero nell'intervallo [0, 19682] e restituisce lo status
vector<vector<int>> from_int_to_status(long s) {
    vector<vector<int>> matrix(3, std::vector<int>(3, 0));
    vector<int> base3_digits(9, 0);
    if(s>19682 || s<0) {
        vector<vector<int>> err(3, std::vector<int>(3, -1));
        cout << "Not in range" << endl;
        return err;
    } 

    // Calcola la rappresentazione in base 3 e la inserisce nell'array base3_digits
    for (int i = 8; i >= 0; i--) {
        base3_digits[i] = s % 3;
        s /= 3;
    }

    // Riempie la matrice 3x3 con i valori da base3_digits
    int index = 0;
    for (int row = 0; row < 3; row++) {
        for (int col = 0; col < 3; col++) {
            matrix[row][col] = base3_digits[index];
            index++;
        }
    }

    return matrix;
}

long from_status_to_int(const vector<vector<int>> &s) {
    int ret = 0;
    if(s.size() != 3 || s[0].size() != 3) {
        cout << "Wrong shape" << endl;
        return -1;       
    }
    for(int i=0; i<3; i++) {
        for(int j=0; j<3; j++) {
            if(s[i][j] < 0 || s[i][j] >2) {
                cout << "Not in range" << endl;
                return -1;
            } 
            ret += s[i][j] * pow(3, 8 - (3*i+j));
        }
    }
    return ret;
}

vector<vector<int>> from_int_to_move(int m) {
    vector<vector<int>> matrix(3, std::vector<int>(3, 0));
    if(m > 9 || m < -9 || m == 0) {
        vector<vector<int>> err(3, std::vector<int>(3, -1));
        cout << "Not in range" << endl;
        return err;
    }
    int val = abs(m);
    val--;
    if(m > 0) matrix[val / 3][val % 3] = 1; // se positivo metti 1
    else matrix[val / 3][val % 3] = 2; // se negativo metti 2
    return matrix;
}

int from_move_to_int(const vector<vector<int>> &m) {
    //controlla che la forma sia corretta
    if(m.size() != 3 || m[0].size() != 3) {
        cout << "Wrong shape" << endl;
        return -1;       
    }
    //controlla quale è diversa da zero, e contemporaneamente che siano tutti diversi da 0 tranne una
    int quanti_non_nulli = 0;
    int ret;
    for(int i=0; i<3; i++) {
        for(int j=0; j<3; j++) {
            if(m[i][j] != 0) {
                quanti_non_nulli++;
                ret = 3 * i + j + 1;
                if(m[i][j] == 2) ret = - ret;
            }
        }
    }
    if(quanti_non_nulli != 1) {
        cout << "Not in range" << endl;
        return 0;
    }
    return ret;
}

//funzioni per manipolare stati e mosse
//restituisce true se la differenza tra il numero di mosse fatte è sensato
//restituisce false anche se il numero dato è fuori range
bool correct(const long &s) {
    auto status = from_int_to_status(s);
    vector<vector<int>> err(3, std::vector<int>(3, -1));
    if(status == err) {
        cout << "Not in range" << endl;
        return false;
    }
    int n_1=0, n_2=0;
    for(int i=0; i<3; ++i) {
        for(int j=0; j<3; ++j) {
            if(status[i][j] == 1) n_1++;
            if(status[i][j] == 2) n_2++;
        }
    }
    //si assume che inizi sempre il giocatore 1, quindi n_1 - n_2 può essere solo 1 o 0
    if((n_1 - n_2) < 0 || (n_1 - n_2) > 1) return false;
    return true;
}

//restituisce true se lo status è "vinto"
//restituisce false se il numero dato è fuori range o se non è "correct"
bool won(const long &s) {
    //verifichiamo che il numero sia nel range
    auto status = from_int_to_status(s);
    vector<vector<int>> err(3, std::vector<int>(3, -1));
    if(status == err) {
        cout << "Not in range" << endl;
        return false;
    }
    //status non corretto, cioè troppe mosse di uno solo dei due giocatori
    if(!correct(s)) {
        cout << "Status not correct" << endl;
        return false;
    }
    //trasforma i 2 in -1
    for(int i=0; i<3; i++) {
        for(int j=0; j<3; j++) {
            if(status[i][j] == 2) status[i][j] = -1;
        }
    }
    //print_matrix(status);
    if(abs(status[0][0] + status[0][1] + status[0][2]) == 3) return true;
    if(abs(status[1][0] + status[1][1] + status[1][2]) == 3) return true;
    if(abs(status[2][0] + status[2][1] + status[2][2]) == 3) return true;

    if(abs(status[0][0] + status[1][0] + status[2][0]) == 3) return true;
    if(abs(status[0][1] + status[1][1] + status[2][1]) == 3) return true;
    if(abs(status[0][2] + status[1][2] + status[2][2]) == 3) return true;

    if(abs(status[0][0] + status[1][1] + status[2][2]) == 3) return true;
    if(abs(status[2][0] + status[1][1] + status[0][2]) == 3) return true;
    return false;
}

//restituisce true se si può fare la mossa m quando lo status è s
bool possible(const long &s, const int &m) {
    auto status = from_int_to_status(s);
    auto move = from_int_to_move(m);
    vector<vector<int>> err(3, std::vector<int>(3, -1));
    //gestione errori, casi in cui restituire false a prescindere:
    //se s non è nel range giusto
    if(status == err) {
        cout << "Status does not exists" << endl;
        return false;
    }
    //se m non è nel range giusto
    if(move == err) {
        cout << "Move does not exists" << endl;
        return false;
    }
    //se s non è correct
    if(!correct(s)) {
        cout << "Status not correct" << endl;
        return false;
    }

    //qui sappiamo che mossa e status sono sensati

    //controllare se il segno della mossa è compatibile con lo status
    int n_1=0, n_2=0;
    for(int i=0; i<3; ++i) {
        for(int j=0; j<3; ++j) {
            if(status[i][j] == 1) n_1++;
            if(status[i][j] == 2) n_2++;
        }
    }
    if(m < 0 && (n_1 - n_2 != 1)) {
        //cout << "Turn 1" << endl;
        return false;
    }
    if(m > 0 && (n_1 - n_2 != 0)) {
        //cout << "Turn 2" << endl;
        return false;
    }
    //controllare se la mossa non sovrascrive 
    for(int i=0; i<3; ++i) {
        for(int j=0; j<3; ++j) {
            if(move[i][j] != 0 && status[i][j] != 0) return false;
        }
    }
    return true;
}

long apply(const long &s, const int &m) {
    auto status = from_int_to_status(s);
    auto move = from_int_to_move(m);
    vector<vector<int>> res(status);
    if(!possible(s, m)) {
        cout << "Not possible move" << endl;
        return s;
    }
    for(int i=0; i<3; ++i) {
        for(int j=0; j<3; ++j) {
            if(move[i][j] != 0) res[i][j] = move[i][j];
        }
    }
    return from_status_to_int(res);
}

//specifica per ticatactoe, prende la matrice con 0, 1, 2 e restituisce la matrice con O  X
vector<vector<char>> transform_for_print(vector<vector<int>> m) {
    vector<vector<char>> res(3, std::vector<char>(3, ' '));
    for(int i=0; i<3; ++i) {
        for(int j=0; j<3; ++j) {
            if(m[i][j] == 1) res[i][j] = 'X';
            if(m[i][j] == 2) res[i][j] = 'O';
        }
    }
    return res;
}


// Funzione per stampare l'albero generico con indentazioni per chiarezza
void printTree(Node* node, std::string prefix, bool isLast) {
    if (node == nullptr)
        return;

    std::cout << prefix << "│   " << endl << prefix;
    if (isLast) {
        std::cout << "└── ";
        prefix += "    ";
    } else {
        std::cout << "├── ";
        prefix += "│   ";
    }
    vector<vector<char>> m = transform_for_print(from_int_to_status(node->status));


    for(int i=0; i<3; ++i) {
        for(int j=0; j<3; ++j) {
            cout << m[i][j] << ' ';
        }
        //if(won(node->status) && i==0) cout << " WON";
        cout << endl;
        if(i != 2) cout << prefix;
    }
    

    for (size_t i = 0; i < node->list_moves.size(); ++i) {
        bool last = (i == node->list_moves.size() - 1);
        printTree(node->list_moves[i]->result, prefix, last);
    }
}