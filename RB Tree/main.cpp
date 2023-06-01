#include <bits/stdc++.h>
#include "RBTree.h"

using namespace std;

/*
		A main é divida em três menus que podem ser selecionados
	no momento de execução do programa.
		Opção 1: key e value são do tipo int;
		Opção 2: key e value são do tipo string;
		Opção 3: key e value são do tipo double;
*/

int main () {

	int op;

	cout << endl << "Quais tipos deseja?" << endl;
	cout << endl << "Escolha 1 : Key e Value -> int" << endl;
	cout << "Escolha 2 : Key e Value -> string" << endl;
	cout << "Escolha 3 : Key e Value -> double" << endl;
	cout << endl << "Faça sua escolha !!!" << endl;

	cin >> op;

	switch( op ) {
		case 1: { 
			RBTree<int, int> Tree(0);

			int esc;
			int key;
			int value;
			int valor;


			while( true ) {

				system("clear");

				cout << endl << "-----------------------------------" << endl;
				cout << "Implementação da Árvore Rubronegra" << endl;
				cout << "-----------------------------------" << endl;

				cout << "1. Inserir elemento na arvore" << endl;
				cout << "2. Deleter elemento da arvore" << endl;
				cout << "3. Remover todos os nós" << endl;
				cout << "4. Percurso em pre-ordem" << endl;
				cout << "5. Pesquisar chave" << endl;
				cout << "6. Calcular altura da arvore" << endl;
				cout << "0. Sair" << endl;

				cout << endl << "Entre sua escolha !!!" << endl;

				cin >> esc;

				switch( esc ){
					case 0:
						return 0;
					case 1:
						cout << "Insira a chave: ";
						cin >> key;
						cout << "Insira o valor: ";
						cin >> value;
						Tree.insert( key, value );
						break;
					case 2:
						cout << "Insira a chave: ";
						cin >> key;
						Tree.remove( key );
						break;
					case 3:
						Tree.removeAll();
						break;
					case 4:
						if( Tree.empty() ){
							cout << endl << "Arvore vazia" << endl;
							cout << endl << "Digite enter para continuar !!!" << endl;
							getchar();
							getchar();
						}
						cout << endl;
						Tree.preorder();
						cout << endl << "Digite enter para continuar !!!" << endl;
						getchar();
						getchar();
						break;
					case 5:
						cout << "Insira a chave: ";
						cin >> key;
						if ( Tree.search( key, valor ) ) {
							cout << "O valor de "<< key << " eh " << valor;
						}else {
							cout << endl << "Chave inexistente";
						}
						cout << endl << "Digite enter para continuar !!!" << endl;
						getchar();
						getchar();
						break;
					case 6:
						cout << endl << "Altura Negra da arvore eh: " << Tree.blackheight() << endl;
						cout << endl <<  "Digite enter para continuar !!!" << endl;
						getchar();
						getchar();
						break;
					default:
						break;
					}
			}
			break;
		}
		case 2: {
			RBTree<string, string> Tree("0");
			int esc;
			string key;
			string value;
			string valor;

			while( true ) {

				system("clear");

				cout << endl << "-----------------------------------" << endl;
				cout << "Implementação da Árvore Rubronegra" << endl;
				cout << "-----------------------------------" << endl;

				cout << "1. Inserir elemento na arvore" << endl;
				cout << "2. Deleter elemento da arvore" << endl;
				cout << "3. Remover todos os nós" << endl;
				cout << "4. Percurso em pre-ordem" << endl;
				cout << "5. Pesquisar chave" << endl;
				cout << "6. Calcular altura da arvore" << endl;
				cout << "0. Sair" << endl;

				cout << endl << "Faça a sua escolha !!! " << endl;

				cin >> esc;

				switch(esc){
					case 0:
						return 0;
					case 1:
						cout << "Insira a chave: ";
						cin >> key;
						cout << "Insira o valor: ";
						cin >> value;
						Tree.insert( key, value );
						break;
					case 2:
						cout << "Insira a chave: ";
						cin >> key;
						Tree.remove( key );
						break;
					case 3:
						Tree.removeAll();
						break;
					case 4:
						if( Tree.empty() ){
							cout << endl << "Arvore vazia" << endl;
							cout << endl << "Digite enter para continuar !!!" << endl;
							getchar();
							getchar();
						}
						cout << endl;
						Tree.preorder();
						cout << endl << "Digite enter para continuar !!!" << endl;
						getchar();
						getchar();
						break;
					case 5:
						cout << "Insira a chave: ";
						cin >> key;
						if ( Tree.search( key, valor ) ) {
							cout << endl << "O valor de "<< key << " eh " << valor;
						}else {
							cout << endl << "Chave inexistente";
						}
						cout << endl << "Digite enter para continuar !!!" << endl;
						getchar();
						getchar();
						break;
					case 6:
						cout << endl << "Altura Negra da arvore eh: " << Tree.blackheight() << endl;
						cout << endl <<  "Digite enter para continuar !!!" << endl;
						getchar();
						getchar();
						break;
					default:
						break;
				}

			}

			break;
		} 
		case 3: { 	

			RBTree<double, double> Tree(0.0);

			int esc;
			double key;
			double value;
			double valor;

				while( true ) {

				system("clear");

				cout << "-----------------------------------" << endl;
				cout << endl << "Implementação da Árvore Rubronegra" << endl;
				cout << "-----------------------------------" << endl;

				cout << "1. Inserir elemento na arvore" << endl;
				cout << "2. Deleter elemento da arvore" << endl;
				cout << "3. Remover todos os nós" << endl;
				cout << "4. Percurso em pre-ordem" << endl;
				cout << "5. Pesquisar chave" << endl;
				cout << "6. Calcular altura da arvore" << endl;
				cout << "0. Sair" << endl;

				cout << "Entre sua escolha " << endl;

				cin >> esc;

				switch(esc){
					case 0:
						return 0;
					case 1:
						cout << "Insira a chave: ";
						cin >> key;
						cout << "Insira o valor: ";
						cin >> value;
						Tree.insert( key, value );
						break;
					case 2:
						cout << "Insira a chave: ";
						cin >> key;
						Tree.remove( key );
						break;
					case 3:
						Tree.removeAll();
						break;
					case 4:
						if( Tree.empty() ){
							cout << endl << "Arvore vazia" << endl;
							cout << endl << "Digite enter para continuar !!!" << endl;
							getchar();
							getchar();
						}
						cout << endl;
						Tree.preorder();
						cout << endl << "Digite enter para continuar !!!" << endl;
						getchar();
						getchar();
						break;
					case 5:
						cout << "Insira a chave: ";
						cin >> key;
						if ( Tree.search( key, valor ) ) {
							cout << endl << "O valor de "<< key << " eh " << valor;
						}else {
							cout << endl << "Chave inexistente";
						}
						cout << endl << "Digite enter para continuar  !!!" << endl;
						getchar();
						getchar();
						break;
					case 6:
						cout << endl << "Altura Negra da arvore eh: " << Tree.blackheight() << endl;
						cout << endl <<  "Digite enter para continuar !!!" << endl;
						getchar();
						getchar();
						break;
					default:
						break;
				}

			}
			break;
		}
	}

	return 0;

}

