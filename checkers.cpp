#include <iostream>
#include <cmath>
#include <vector>
#include "search_tree.h"
using namespace std;

vector<int> set_move;
int main() {
    for(int i=1; i<=32; ++i) {
        set_move.push_back(i);
        set_move.push_back(-i);
    }
    return 0;
}
 
