#include <iostream>
#include <algorithm>
#include <queue>
#include "item.h"
#include "avl.h"
#include <string>

using namespace std;

struct Node {
    Tkey key;
    Tvalue value;
    int height;
    Node *left;
    Node *right;
};

Tkey avl_getKey(Node *node) {
    return node->key;
}

Tvalue avl_getValue(Node *node) {
    return node->value;
}

Node *avl_search(Node *node, Tkey key){
	if(node == nullptr){
		return nullptr;
	}if(node->key == key){
		return node;
	}if(key < node->key){
		return avl_search(node->left, key);
	}if(key > node->key)
		return avl_search(node->right, key);
	
	return node;
}

void avl_preorder(Node *node){
	if(node == nullptr)
		return;
	cout << "Key: " <<node->key << " Value: " << node->value << "-" << node->height <<endl;
	avl_preorder(node->left);
	avl_preorder(node->right);
}

void avl_inorder(Node *node){
	if(node == nullptr)
		return;
	avl_inorder(node->left);		
	cout << "Key " <<node->key << " Value " << node->value << endl;
	avl_inorder(node->right);
}

void avl_posorder(Node *node){
	if(node == nullptr)
		return;
	avl_inorder(node->left);		
	avl_inorder(node->right);
	cout << "Key " <<node->key << " Value " << node->value << endl;
}

int avl_height(Node *node){
	if(node == nullptr)
		return 0;
	return node->height;
}

int avl_size(Node *node){
	if(node == nullptr)
		return 0;
	else
		return 1 + avl_size(node->left) + avl_size(node->right); 
}

bool avl_empty(Node *node){
	if(node == nullptr)
		return true;
	return false;
}

Node *avl_clear(Node *node){

	if(node == nullptr)
		return nullptr;
	node->left = avl_clear(node->left);
	node->right = avl_clear(node->right);
	delete node;
	return nullptr;
}

int avl_balance(Node *node) {
	return avl_height(node->right) - avl_height(node->left);
}

/* -------------------------- Máximo e Minimo ----------------------------*/
Node *avl_maximum(Node *node){
	struct Node* before = nullptr;
	struct Node* current = node;
	while(current != nullptr){
		before = current;
		current = current->right;
	}
	return before;
}

Node *avl_minimum(Node *node){
	struct Node* before = nullptr;
	struct Node* current = node;
	while(current != nullptr){
		before = current;
		current = current->left;
	}
	return before;
}

/* -------------------------- Sucessor e Antecessor ----------------------------*/

Node* avl_sucessor(Node* root, Node *x){

	/* Árvore é vazia*/
	if(root == nullptr)
		return nullptr;
	/* X é o maior elemento da estrutura */
	if(x == avl_maximum(root))
		return x;
	/* Se filho direito de x é diferente de nulo */
	if(x->right != nullptr){
		return avl_minimum(x->right);
	}

	Tkey keySucc = avl_maximum(root)->key;
	struct Node* succ = nullptr;
	struct Node* current = root;

	while(current != x){
		if((current->key <= keySucc) && (current->key > x->key)){
			keySucc = current->key;
			succ = current;
		}if(x->key < current->key){
			current = current->left;
		}else 
		 	current = current->right;
	}

	return succ;
}

Node* avl_predecessor(Node* root, Node *x){
	
	/* Árvore é vazia*/
	if(root == nullptr)
		return nullptr;
	/* X é o menor elemento da estrutura */
	if(x == avl_minimum(root))
		return x;
	/* Se filho esquerdo de x é diferente de nulo */
	if(x->left != nullptr){
		return avl_maximum(x->left);
	}

	Tkey keyAnt = avl_minimum(root)->key;
	struct Node* ant = root;
	struct Node* current = root;

	while(current != x){
		if((current->key >= keyAnt) && (current->key < x->key)){
			keyAnt = current->key;
			ant = current;
		}if(x->key > current->key){
			current = current->right;
		}else
			current = current->left;
	}
	return ant;
}

/* -------------------------- Rotações ----------------------------*/

Node *rightRotation(Node *node){
	
	Node* u = node->left;
	
	/* Atualiza os campos filho dos nodes envolvidos na rotação */
	node->left = u->right;
	u->right = node;
	
	/* Atualiza o campo heigth dos nós envolvidos */
	node->height = 1 + max(avl_height(node->left), avl_height(node->right));
	u->height = 1 + max(avl_height(u->left), avl_height(u->right));

	return u;
}

Node *leftRotation(Node *node){

	Node* u = node->right;
	
	/* Atualiza os campos filho dos nodes envolvidos na rotação */
	node->right = u->left;
	u->left = node;
	
	/* Atualiza o campo heigth dos nós envolvidos */
	node->height = 1 + max(avl_height(node->left), avl_height(node->right));
	u->height = 1 + max(avl_height(u->left), avl_height(u->right));

	/* retorna nova raiz*/
	return u;
}

Node *rightDoubleRotation(Node *node){
	
	Node* u = node->left;

	/* Realiza uma rotação simples a esquerda sobre u */
	node->left = leftRotation(u);
	
	/* Realiza uma rotação simples direita sobre node */
	return rightRotation(node);
}

Node *leftDoubleRotation(Node *node){
	Node* u = node->right;
	
	/* Rotação simples a direita feita sobre u */
	node->right = rightRotation(u);
	
	/* Rotação simples a esquerda feita sobre node */
	return leftRotation(node);
}

/* -------------------------- Inserção ----------------------------*/

Node* avl_insert(Node *node, Tkey key, Tvalue value){

	if(node == nullptr){
		struct Node* newNode = new Node;
		newNode->key = key;
		newNode->value = value;
		newNode->height = 1;
		newNode->left = nullptr;
		newNode->right = nullptr;
		return newNode;
	}else if(key < node->key)
		node->left = avl_insert(node->left, key, value);
	else if(key > node->key)
		node->right = avl_insert(node->right, key, value);
	else
		return node;

	/* Atualizar o campo heigth do node */
	node->height = 1 + max(avl_height(node->left),avl_height(node->right));
	/* Calcular o campo balanço */
	int balance = avl_balance(node);

	/* 4 casos de balanceamento */
	/* Caso 1.1 */
	if(balance < -1 && key < node->left->key){
		//cout << "Entrou 1 " << endl;
		return rightRotation(node);
	}
	/* Caso 1.2 */
	else if(balance < -1 && key > node->left->key){
		//cout << "Entrou 2 " << endl;
		return rightDoubleRotation(node);
	}
	/* Caso 2.1 */
	else if(balance > 1 && key > node->right->key){
		//cout << "Entrou 3 " << endl;
		return leftRotation(node);
	}
	/* Caso 2.2 */
	else if(balance > 1 && key < node->right->key){
		//cout << "Entrou 4 " << endl;
		return leftDoubleRotation(node);
	}

	return node;
}

/* -------------------------- Remoção ----------------------------*/

Node *fixup_node_deletion(Node *node) {
	
	// ajustando a altura do nó
	node->height = 1 + max(avl_height(node->left), avl_height(node->right));
	
	// calculando bal
	int balance = avl_balance(node);

	// Casos 4.a e 4.b
	if ( balance > 1 && avl_balance(node->right) >= 0 ) {
		return leftRotation(node);
	}
	// Caso 4.c
	else if ( balance > 1 && avl_balance(node->right) < 0 ) {
		node->right = rightRotation(node->right);
		return leftRotation(node);
	}
	// Casos simetricos 4.a e 4.b
	else if ( balance < -1 && avl_balance(node->left) <= 0) {
		return rightRotation(node);
	}
	// Caso simetrico 4.c
	else if ( balance < -1 && avl_balance(node->left) > 0 ) {
		node->left = leftRotation(node->left);
		return rightRotation(node);
	}
	return node;
}

Node *delete_predecessor(Node *root, Node *node){

	if ( node->right != nullptr ) {
		node->right = delete_predecessor(root, node->right);
	}
	else {
		root->key = node->key;
		Node *aux = node->left;
		delete node;
		return aux; 
	}
	// atualiza o campo 'height' e regula o nó
	node = fixup_node_deletion(node);
	return node;
}

Node *avl_delete(Node *node, Tkey key){
	
	if ( node == nullptr ) {
		return nullptr;
	}else if ( key < node->key ) {
		node->left = avl_delete(node->left, key);
	}else if( key > node->key ){
		cout << "Passou aqui" << endl;
		node->right = avl_delete(node->right, key);
	// Nó não tem filho
	}else if ( node->left == nullptr && node->right == nullptr ) {
		delete node;
		return nullptr;
	}
	// Nó tem algum dos dois filhos
	else if ( node->left == nullptr || node->right == nullptr ) {
		//Node *aux = node->left ? node->left : node->right;
		Node *aux;
		if ( node->left != nullptr )
			aux = node->left;
		else
			aux = node->right;
			
		delete node;
		return aux;
	}
	else { // Nó tem dois filhos
		node->left = delete_predecessor(node, node->left);
	}
	
	node = fixup_node_deletion(node);
	return node;	
}
