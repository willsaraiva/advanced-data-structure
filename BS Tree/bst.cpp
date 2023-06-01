#include <bits/stdc++.h>
#include "item.h"
#include "bst.h"

using namespace std;

/* Definição do Node */
struct Node {
	Tkey key;
	Tvalue value;
	struct Node* left;
	struct Node* right; 
};

void func(Node* node){
	cout << 2 * bst_getKey(node) << endl;
}

/* 
 * Recebe um node e retorna a sua chave
 * 
 *  */
Tkey bst_getKey(Node *node){
	return node->key;
}

/* 
 * Recebe um node e retorna o seu valor
 * 
 *  */
Tvalue bst_getValue(Node *node){
	return node->value;
}

/**
 * Recebe o ponteiro para a raiz da arvore e 
 * para a chave a ser pesquisada. Retorna o ponteiro
 * para o no se a chave for encontrada; ou retorna nullptr
 * caso contrário */
Node *bst_search(Node *node, Tkey key){
	if(node == nullptr){
		return nullptr;
	}if(node->key == key){
		return node;
	}if(key < node->key){
		return bst_search(node->left, key);
	}if(key > node->key)
		return bst_search(node->right, key);
}

void bst_inorder(Node *node){
	if(node == nullptr)
		return;
	bst_inorder(node->left);		
	cout << "Key: " <<node->key << " Value: " << node->value << endl;
	bst_inorder(node->right);
}

/**
 * Recebe um ponteiro para a raiz da arvore e 
 * Percorre os nos da arvore em pre-ordem e imprime na 
 * tela os pares (chave, valor) */
void bst_preorder(Node *node){
	if(node == nullptr)
		return;
	cout << "Key: " <<node->key << " Value: " << node->value << endl;
	bst_preorder(node->left);
	bst_preorder(node->right);
}

/**
 * Recebe um ponteiro para a raiz da arvore e 
 * recebe um ponteiro f para uma funcao. 
 * Percorre os nos da arvore em pre-ordem fazendo o que 
 * a funcao f disser para fazer. */
void bst_preorder(Node *node, void f(Node*)){
	if(node == nullptr)
		return;
	f(node);
	bst_preorder(node->left, f);
	bst_preorder(node->right, f);
}

/**
 * Recebe um ponteiro para a raiz da arvore e retorna a 
 * altura da arvore. */
int bst_height(Node *node){
	if(node == nullptr)
		return 0;
	int valueL = 1 + bst_height(node->left);
	int valueR = 1 + bst_height(node->right);
	return max(valueL, valueR);
}

/**
 * Recebe um ponteiro para a raiz da arvore.
 * Retorna true se a arvore estiver vazia e false, caso
 * contrario. */
bool bst_empty(Node* node){
	if(node == nullptr)
		return true;
	return false;
}

/**
 * Recebe um ponteiro para a raiz da arvore e libera todos
 * os nos, deixando a arvore vazia. Retorna nullptr. */
Node *bst_clear(Node *node){
	if(node == nullptr)
		return nullptr;
	node->left = bst_clear(node->left);
	node->right = bst_clear(node->right);
	delete node;
	return nullptr;
}

/**
 * Recebe um ponteiro para a raiz da arvore e 
 * retorna um ponteiro para o no que contem a maior chave */
Node *bst_maximum(Node *node){
	struct Node* before = nullptr;
	struct Node* current = node;
	while(current != nullptr){
		before = current;
		current = current->right;
	}
	return before;
}

/**
 * Recebe um ponteiro para a raiz da arvore e 
 * retorna um ponteiro para o no que contem a menor chave */
Node *bst_minimum(Node *node){
	struct Node* before = nullptr;
	struct Node* current = node;
	while(current != nullptr){
		before = current;
		current = current->left;
	}
	return before;
}

/*------------------ Inserção e Remoção ------------------------ */


/**
 * Recebe um ponteiro para a raiz da arvore, uma chave e um valor.
 * Se a chave nao existir, insere um novo no com o par (chave,valor)
 * Se a chave existir, nao insere nada.
 * Retorna um ponteiro para a raiz da arvore modificada. */
Node *bst_insert(Node *node, Tkey key, Tvalue value){
	if(node == nullptr){
		struct Node* newNode = new Node;
		newNode->key = key;
		newNode->value = value;
		newNode->left = nullptr;
		newNode->right = nullptr;
		return newNode;
	}
	if(node->key == key){
		return node;
	}if(key < node->key){
		node->left = bst_insert(node->left, key, value);
		return node;
	}
	if(key > node->key){
		node->right = bst_insert(node->right, key, value);
		return node;
	}
}

/**
 * Recebe um ponteiro para a raiz da arvore e uma chave.
 * Se existir um no com essa chave, remove o no.
 * Se nao existir, nada acontece.
 * Retorna um ponteiro para a raiz da arvore modificada. */
Node *bst_remove(Node *node, Tkey key){

	/* Árvore é vazia */
	if(node == nullptr)
		return nullptr;
	if(key < node->key)
		node->left = bst_remove(node->left, key);
	else if(key > node->key)
		node->right = bst_remove(node->right, key);
	/* Elemento não possui filho esquerdo */
	else if(node->left == nullptr){
		return node->right;
	}
	/* Elemento não possui filho direito */
	else if(node->right == nullptr){
		return node->left;
	}
	else{
	/* Elemento possui ambos os filhos, e é
		preciso remover o seu sucessor     */
		struct Node* minSucc = bst_minimum(node->right);
		node->key = minSucc->key;
		node->value = minSucc->value;
		node->right = remove_succ(node->right);
	}

	return node;
}

Node *remove_succ(Node *node){

	struct Node* before = nullptr;
	struct Node* current = node;

	while(current->left){
		before = current;
		current = current->left;
	}

	if(current->right != nullptr)
		before->left = current->right;
	else
		before->left = nullptr;
	return node;
}

/*------------------ Sucessor e Antecessor------------------------ */

/**
 * Recebe como parametro um ponteiro para a raiz da arvore 
 * e um ponteiro para um no x.
 * Retorna o ponteiro para o no cuja chave eh sucessora
 * da chave contida em x. */
Node* bst_successor(Node* root, Node *x){

	/* Árvore é vazia*/
	if(root == nullptr)
		return nullptr;
	/* X é o maior elemento da estrutura */
	if(x == bst_maximum(root))
		return x;
	/* Se filho direito de x é diferente de nulo */
	if(x->right != nullptr){
		return bst_minimum(x->right);
	}

	int keySucc = 9999999;
	struct Node* succ = nullptr;
	struct Node* current = root;

	while(current != x){
		if((current->key < keySucc) && (current->key > x->key)){
			keySucc = current->key;
			succ = current;
		}if(x->key < current->key){
			current = current->left;
		}else 
		 	current = current->right;
	}

	return succ;
}

/**
 * Recebe como parametro um ponteiro para a raiz da arvore 
 * e um ponteiro para um no x.
 * Retorna o ponteiro para o no cuja chave eh antecessora
 * da chave contida em x. */
Node* bst_predecessor(Node* root, Node *x){
	/* Árvore é vazia*/
	if(root == nullptr)
		return nullptr;
	/* X é o menor elemento da estrutura */
	if(x == bst_minimum(root))
		return x;
	/* Se filho esquerdo de x é diferente de nulo */
	if(x->left != nullptr){
		return bst_maximum(x->left);
	}

	int keyAnt = -999999;
	struct Node* ant = root;
	struct Node* current = root;

	while(current != x){
		if((current->key > keyAnt) && (current->key < x->key)){
			keyAnt = current->key;
			ant = current;
		}if(x->key > current->key){
			current = current->right;
		}else
			current = current->left;
	}
	return ant;
}

int main() {


	return 0;
}
