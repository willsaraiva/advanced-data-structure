#ifndef AVL_H
#define AVL_H
#include "item.h"

/**
 * Tipo Node. Um struct que possui campos
 * para a chave, para o valor, e ponteiros
 * para o filho esquerdo e direito. */
struct Node;

/**
 * Recebe um ponteiro para um no da arvore e retorna 
 * a chave associada a este no */
Tkey avl_getKey(Node *node);

/**
 * Recebe um ponteiro para um no da arvore e retorna 
 * o valor associado a este no */
Tvalue avl_getValue(Node *node);

/**
 * Recebe o ponteiro para a raiz da arvore e 
 * para a chave a ser pesquisada. Retorna o ponteiro
 * para o no se a chave for encontrada; ou retorna nullptr
 * caso contrário */
Node *avl_search(Node *node, Tkey key);

/**
 * Recebe um ponteiro para a raiz da arvore e 
 * Percorre os nos da arvore em pre-ordem e imprime na 
 * tela os pares (chave, valor) */
void avl_preorder(Node *node);

/**
 * Recebe um ponteiro para a raiz da arvore e 
 * Percorre os nos da arvore em ordem e imprime na 
 * tela os pares (chave, valor) */
void avl_inorder(Node *node);

/**
 * Recebe um ponteiro para a raiz da arvore e 
 * Percorre os nos da arvore em pós ordem e imprime na 
 * tela os pares (chave, valor) */
void avl_posorder(Node *node);

//void avl_level_traversal(Node *node);

/**
 * Recebe um ponteiro para a raiz da arvore e retorna a 
 * o valor do campo height */
int avl_height(Node *node);

/**
 * Recebe um ponteiro para a raiz da arvore e retorna a 
 * quantidade de nós da árvore. */
int avl_size(Node *node);

/**
 * Recebe um ponteiro para a raiz da arvore.
 * Retorna true se a arvore estiver vazia e false, caso
 * contrario. */
bool avl_empty(Node *node);

/**
 * Recebe um ponteiro para a raiz da arvore e libera todos
 * os nos, deixando a arvore vazia. Retorna nullptr. */
Node *avl_clear(Node *node);

int avl_balance(Node *node);

/* ----------------------- Rotação ------------------------------------*/

/**
 * Recebe um ponteiro para a raiz da arvore e realiza a 
 * rotação simples direita sobre essa raiz */
Node *rightRotation(Node *node);

/**
 * Recebe um ponteiro para a raiz da arvore e realiza a 
 * rotação simples esquerda sobre essa raiz */
Node *leftRotation(Node *node);

/**
 * Recebe um ponteiro para a raiz da arvore e realiza a 
 * rotação dupla direita sobre essa raiz */
Node *rightDoubleRotation(Node *node);

/**
 * Recebe um ponteiro para a raiz da arvore e realiza a 
 * rotação dupla esquerda sobre essa raiz */
Node *leftDoubleRotation(Node *node);

/* -------------------------- Máximo e Minimo ----------------------------*/

/**
 * Recebe um ponteiro para a raiz da arvore e 
 * retorna um ponteiro para o no que contem a maior chave */
Node *avl_maximum(Node *node);

/**
 * Recebe um ponteiro para a raiz da arvore e 
 * retorna um ponteiro para o no que contem a menor chave */
Node *avl_minimum(Node *node);

/* -------------------------- Sucessor e Antecessor ----------------------------*/

/**
 * Recebe como parametro um ponteiro para a raiz da arvore 
 * e um ponteiro para um no x.
 * Retorna o ponteiro para o no cuja chave eh sucessora
 * da chave contida em x. */
Node* avl_sucessor(Node* root, Node *x);

/**
 * Recebe como parametro um ponteiro para a raiz da arvore 
 * e um ponteiro para um no x.
 * Retorna o ponteiro para o no cuja chave eh antecessora
 * da chave contida em x. */
Node* avl_predecessor(Node* root, Node *x);

/* ----------------------- Inserção e Remoção ------------------------------------*/

/**
 * Recebe um ponteiro para a raiz da arvore, uma chave e um valor.
   Busca um nó que tenha o mesmo valor da chave, se não houver ele
   cria um novo nó com essa chave e valor e insere-o na posição devida */
Node* avl_insert(Node *node, Tkey key, Tvalue value);

/**
 * Recebe um ponteiro para a raiz da arvore e uma chave.
 * Se existir um no com essa chave, remove o no.
 * Se nao existir, nada acontece.
 * Ele retorna consertando as alturas e se a árvore estiver
 * desbalanceada, balanceia ela */
Node* avl_delete(Node *node, Tkey key);

/*
 * Remove o sucessor de um determinado nó.
 * Esse nó que se deseja remover o sucessor é passada
 * como parâmetro.
 *  */
Node *delete_predecessor(Node *root, Node *node);

Node *fixup_node_deletion(Node *node);

#endif  
