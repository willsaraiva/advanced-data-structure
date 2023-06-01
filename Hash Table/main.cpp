#include <bits/stdc++.h>

using namespace std;

int main () {

    ifstream arquivo;
    arquivo.open("dados.csv");
    string fst, snd;

    while(getline(arquivo, fst, ',')) {
        getline(arquivo, snd, '\n');

        cout << fst << " : " << snd << endl;
    }

	return 0;
}