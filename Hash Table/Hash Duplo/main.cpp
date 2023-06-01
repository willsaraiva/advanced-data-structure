#include <bits/stdc++.h>

#include "hashTable.h"

using namespace std;

int main () {

    HashTable<string, string> table;
    ifstream arquivo;
    arquivo.open("../dados.csv");
    string fst, snd;
    int op;
    string chave, valor;

    /* Popular a tabela */
    while(getline(arquivo, fst, ',')) {
        getline(arquivo, snd, '\n');

        table.insert(fst, snd);
    }

    while( true ) {

        system("clear");

        cout << endl << "-----------------------------------" << endl;
        cout << "Implementação da Tabela Hash com Hasing Duplo" << endl;
        cout << "-----------------------------------" << endl;

        cout << "1. Inserir elemento - (chave, valor)" << endl;
        cout << "2. Deleter elemento - (chave)" << endl;
        cout << "3. Remover todos" << endl;
        cout << "4. Mostrar todos os valores da tabela" << endl;
        cout << "5. Pesquisar chave e retorna valor" << endl;
        cout << "6. Quantidade de elementos" << endl;
        cout << "0. Sair" << endl;

        cout << endl << "Entre sua escolha !!!" << endl;

        cin >> op;

        switch(op) {
            case 0:
                return 0;
            case 1:
                system("clear");
                cout << "Insira a chave" << endl;
                cin >> chave;
                cout << "Insira o valor" << endl;
                cin >> valor;
                system("clear");
                if (table.insert(chave, valor)) {
                    cout << "Inserido com sucesso!" << endl;
                }else
                    cout << "Nao pode ser inserido!" << endl; 
                cout << endl << "Digite qualquer tecla para continuar!!!" << endl;
                getchar();
                getchar();
                break;
            case 2:
                system("clear");
                cout << "Insira a chave" << endl;
                cin >> chave;
                system("clear");
                if (table.remove(chave)) {
                    cout << "Removido com sucesso!" << endl;
                }
                cout << endl << "Digite qualquer tecla para continuar!!!" << endl;
                getchar();
                getchar();
                break;
            case 3:
                table.makeEmpty();
                break;
            case 4:
                system("clear");
                table.print();
                cout << endl << "Digite qualquer tecla para continuar!!!" << endl;
                getchar();
                getchar();
                break;
            case 5:
                system("clear");
                cout << "Insira a chave" << endl;
                cin >> chave;
                system("clear");
                if(table.search(chave, valor)) {
                    cout << valor << endl;
                }
                cout << endl << "Digite qualquer tecla para continuar!!!" << endl;
                getchar();
                getchar();
                break;
            case 6:
                system("clear");
                cout << table.size() << endl;
                cout << endl << "Digite qualquer tecla para continuar!!!" << endl;
                getchar();
                getchar();
                break;
        }

    }

	return 0;
}
