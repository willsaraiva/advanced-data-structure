#include <bits/stdc++.h>
#include "avl.h"
#include "item.h"
#include <unistd.h>


using namespace std;

int main() {
	
	struct Node *root = nullptr;
	struct Node *aux = nullptr;
	int esc;
	string key, value;

	while(true) {

		system("clear");

		cout << "----------------------------" << endl;
		cout << "Implementação da Árvore AVL" << endl;
		cout << "-----------------------------" << endl;

		cout << "1. Inserir elemento na arvore" << endl;
		cout << "2. Deleter elemento da arvore" << endl;
		cout << "3. Valor maximo da arvore" << endl;
		cout << "4. Valor minimo da arvore" << endl;
		cout << "5. O sucessor do no x" << endl;
		cout << "6. O predecessor do no x" << endl;
		cout << "7. Percurso em pre-ordem" << endl;
		cout << "8. Percurso em in-ordem" << endl;
		cout << "9. Percurso em pos-ordem" << endl;
		cout << "10. Pesquisar chave" << endl;
		cout << "11. Altura da arvore" << endl;
		cout << "12. Remover todos os nós" << endl;
		cout << "0. Sair" << endl;

		cout << "Entre sua escolha: " << endl;

		cin >> esc;

		switch(esc){

			case 0:
				return 0;
			case 1:
				cout << "Insira a chave: ";
				cin >> key;
				cout << "Insira o valor: ";
				cin >> value;

				root = avl_insert(root, key, value);
				break;
			case 2:
				cout << "Insira a chave: ";
				cin >> key;
				root = avl_delete(root, key);
				break;
			case 3:
				cout << "Valor maximo: ";
				cout << avl_maximum(root);
				cout << "Digite qualquer tecla para continuar" << endl;
				getchar();
				getchar();
				break;
			case 4:
				cout << "Valor minimo: ";
				cout << avl_minimum(root);
				cout << "Digite qualquer tecla para continuar" << endl;
				getchar();
				getchar();
				break;
			case 5:
				cout << "Insira o valor " << endl;
				cin >> key;
				aux = avl_search(root, key);
				cout << "O sucessor de "<< key << "eh " << avl_sucessor(root, aux) << endl;
				getchar();
				getchar();
				break;
			case 6:
				cout << "Insira o valor " << endl;
				cin >> key;
				aux = avl_search(root, key);
				cout << "O predecessor de "<< key << "eh " << avl_predecessor(root, aux) << endl;
				getchar();
				getchar();
				break;
			case 7:
				if(root == nullptr){
					cout << "Arvore vazia" << endl;
					cout << "Digite qualquer tecla para continuar" << endl;
					getchar();
					getchar();
				}
				avl_preorder(root);
				cout << "Digite qualquer tecla para continuar" << endl;
				getchar();
				getchar();
				break;
			case 8:
				if(root == nullptr){
					cout << "Arvore vazia" << endl;
					cout << "Digite qualquer tecla para continuar" << endl;
					getchar();
					getchar();
				}
				avl_inorder(root);
				cout << "Digite qualquer tecla para continuar" << endl;
				getchar();
				getchar();
				break;
			case 9:
				if(root == nullptr){
					cout << "Arvore vazia" << endl;
					cout << "Digite qualquer tecla para continuar" << endl;
					getchar();
					getchar();
				}
				avl_posorder(root);
				cout << "Digite qualquer tecla para continuar" << endl;
				getchar();
				getchar();
				break;
			case 10:
				cout << "Insira a chave" << endl;
				cin >> key;
				aux = avl_search(root, key);

				if( aux != nullptr){
					cout << "Valor: " << avl_getValue(aux) << endl;
					cout << "Digite qualquer tecla para continuar" << endl;
					getchar();
					getchar();
				}
				else{
					cout << "Chave nao encontrada" << endl;
					cout << "Digite qualquer tecla para continuar" << endl;
					getchar();
					getchar();
				}
				break;
			case 11:
				if(root == nullptr){
					cout << "Arvore vazia" << endl;
					cout << "Digite qualquer tecla para continuar" << endl;
					getchar();
					getchar();
				}
				else{	
					cout << "Altura da arvore: " << avl_height(root) << endl;
					cout << "Digite qualquer tecla para continuar" << endl;
					getchar();
					getchar();
				}
				break;
			case 12:
				root = avl_clear(root);
				break;

			return 0;
		}
	}

	return 0;

}