#include <iostream>
#include "bnode.h"
#include "btree.h"
using namespace std;
const int MAX = 20;

int main() {
    Btree tree(2); // grau minimo D = 2
    
    for(int i = 1; i <= MAX; i++)
        tree.insert(i);
    
    tree.printKeys(); // Tem que programar esta funcao
    cout << endl;

    return 0;
}