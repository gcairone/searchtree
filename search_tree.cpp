#include "search_tree.h"

void create_tree(Node* &rad, const int &level) {
    if(rad && level > 0) {
        for(auto i: set_move) {
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