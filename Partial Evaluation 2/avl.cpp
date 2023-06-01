#include <bits/stdc++.h>

using namespace std;

template<typename Tkey>
class Node {

public:

	Tkey key;
    string value;
    int height;
    Node *left;
    Node *right;
 v
    Tkey getKey() {
    	return this->key;
    }
    int getHeight() {
    	return this->height;
    }
    void setHeight( int value ) {
    	this->height = value;
    }
};

template<typename Tkey>
class AVLTree{
private:	
	Node<Tkey> *root;
public:

	AVLTree();
	~AVLTree();
	int avl_height ();
	bool avl_empty ();
	void avl_clear (); // externo
	void avl_preorder (); //externo
	void preorder ( Node<Tkey>* node );
	Node<Tkey>* clear ( Node<Tkey> *node ); // interno
	Node<Tkey>* avl_search ( Tkey key );
	Node<Tkey>* avl_maximum ();
	Node<Tkey>* avl_minimum ();
	Node<Tkey>* rightRotation ( Node<Tkey> *node );
	Node<Tkey>* leftRotation ( Node<Tkey> *node );
	Node<Tkey>* rightDoubleRotation ( Node<Tkey> *node );
	Node<Tkey>* leftDoubleRotation ( Node<Tkey> *node );
	Node<Tkey>* insert ( Node<Tkey>* node, Tkey key, string value ); // interno
	void avl_insert ( Tkey key, string value ); // externo
	Node<Tkey>* fixup_node_deletion ( Node<Tkey>* node );
	Node<Tkey>* delete_predecessor ( Node<Tkey> *before, Node<Tkey> *node );
	Node<Tkey>* remove ( Node<Tkey>* node, Tkey key ); // interno
	void avl_delete ( Tkey key ); // externo
	int avl_height( Node<Tkey> *node ) {
		if(node == nullptr) 
			return 0;
		else 
			return node->height;
	}
	int avl_balance(Node<Tkey> *node) {
		if(node == nullptr) 
			return 0;
		return avl_height(node->right) - avl_height(node->left);
	}

};

// Constructor
template<typename Tkey>
AVLTree<Tkey>::AVLTree() {
	root = nullptr;
}

// PreOrder externo
template<typename Tkey>
void AVLTree<Tkey>::avl_preorder () {
	preorder( root );
}

// PreOrder interno
template<typename Tkey>
void AVLTree<Tkey>::preorder ( Node<Tkey>* node ) {
	if ( node == nullptr ) {
		return;
	}
	cout << node->getKey() << endl;
	preorder(node->left);
	preorder(node->right);
}

// Busca um elemento na árvore
template<typename Tkey>
Node<Tkey>* AVLTree<Tkey>::avl_search ( Tkey key ) {

	Node<Tkey> *node = root;
	Node<Tkey> *before = nullptr;

	if ( node == nullptr ) {
		return nullptr;
	} else {
		while ( node != nullptr ) {
			if(node->getKey() == key){
				before = node;
				break;
			}if(key < node->key){
				before = node;
				node = node->left;
			}if(key > node->key) {
				before = node;
				node = node->right;
			}
		}	
	}

	return before;
}

// Verifica se a árvore é vazia
template<typename Tkey>
bool AVLTree<Tkey>::avl_empty () {
	if( root == nullptr)
		return true;
	return false;
}

// Interno Clear
template<typename Tkey>
Node<Tkey>* AVLTree<Tkey>::clear ( Node<Tkey> *node ) {
	
	if( node == nullptr ) {
		return nullptr;
	}

	node->left = clear(node->left);
	node->right = clear(node->right);

	delete node;
	return nullptr;
}

// Externo Clear
template<typename Tkey>
void AVLTree<Tkey>::avl_clear () {
	
	if( root == nullptr ) {
		return;
	}

	root->left = clear(root->left);
	root->right = clear(root->right);
	
	root = nullptr;
}

/* -------------------------- Máximo e Minimo ----------------------------*/
template<typename Tkey>
Node<Tkey>* AVLTree<Tkey>::avl_maximum () {
	
	Node<Tkey>* before = nullptr;
	Node<Tkey>* node = root;

	while( node != nullptr ){
		before = node;
		node = node->right;
	}

	return before;
}

template<typename Tkey>
Node<Tkey>* AVLTree<Tkey>::avl_minimum () {

	Node<Tkey>* before = nullptr;
	Node<Tkey>* node = root;

	while( node != nullptr ){
		before = node;
		node = node->left;
	}
	return before;
}

/* -------------------------- Rotações ----------------------------*/
template<typename Tkey>	
Node<Tkey>* AVLTree<Tkey>::rightRotation ( Node<Tkey> *node ) {
	
	Node<Tkey>* u = node->left;
	
	/* Atualiza os campos filho dos nodes envolvidos na rotação */
	node->left = u->right;
	u->right = node;
	
	/* Atualiza o campo heigth dos nós envolvidos */
	node->setHeight( 1 + max( avl_height(node->left), avl_height(node->right) ) );
	u->setHeight( 1 + max( avl_height(u->left), avl_height(u->right) ));

	return u;
}

template<typename Tkey>	
Node<Tkey>* AVLTree<Tkey>::leftRotation ( Node<Tkey> *node ) {

	Node<Tkey>* u = node->right;
	
	/* Atualiza os campos filho dos nodes envolvidos na rotação */
	node->right = u->left;
	u->left = node;
	
	/* Atualiza o campo heigth dos nós envolvidos */
	node->setHeight( 1 + max( avl_height(node->left), avl_height(node->right) ) );
	u->setHeight( 1 + max( avl_height(u->left) , avl_height(u->right) ) );

	/* retorna nova raiz*/
	return u;
}

template<typename Tkey>	
Node<Tkey>* AVLTree<Tkey>::rightDoubleRotation ( Node<Tkey> *node ) {
	
	Node<Tkey>* u = node->left;

	/* Realiza uma rotação simples a esquerda sobre u */
	node->left = leftRotation(u);
	
	/* Realiza uma rotação simples direita sobre node */
	return rightRotation(node);
}

template<typename Tkey>
Node<Tkey>* AVLTree<Tkey>::leftDoubleRotation ( Node<Tkey> *node ) {
	Node<Tkey>* u = node->right;
	
	/* Rotação simples a direita feita sobre u */
	node->right = rightRotation(u);
	
	/* Rotação simples a esquerda feita sobre node */
	return leftRotation(node);
}

/* -------------------------- Inserção ----------------------------*/

// Interno 
template<typename Tkey>
Node<Tkey>* AVLTree<Tkey>::insert ( Node<Tkey>* node, Tkey key, string value ) {

	if( node == nullptr ){
		//Node<Tkey>* newNode = new Node<Tkey>( key, value);
		node = new Node<Tkey>();
		node->key = key;
		node->value = value;
		node->setHeight(1);
		node->left = nullptr;
		node->right = nullptr;
		return node;
	}else if( key < node->key )
		node->left = insert(node->left, key, value);
	else if( key > node->key )
		node->right = insert(node->right, key, value);
	else
		return node;

	/* Atualizar o campo heigth do node */
	node->setHeight( 1 + max( avl_height(node->left) , avl_height(node->right) ));
	/* Calcular o campo balanço */
	int balance = avl_balance(node);

	/* 4 casos de balanceamento */
	/* Caso 1.1 */
	if( balance < -1 && key < node->left->getKey() ){
		//cout << "Entrou 1 " << endl;
		return rightRotation(node);
	}
	/* Caso 1.2 */
	else if( balance < -1 && key > node->left->getKey() ){
		//cout << "Entrou 2 " << endl;
		return rightDoubleRotation(node);
	}
	/* Caso 2.1 */
	else if( balance > 1 && key > node->right->getKey() ){
		//cout << "Entrou 3 " << endl;
		return leftRotation(node);
	}
	/* Caso 2.2 */
	else if( balance > 1 && key < node->right->getKey() ){
		//cout << "Entrou 4 " << endl;
		return leftDoubleRotation(node);
	}

	return node;
}

// Externo
template<typename Tkey>
void AVLTree<Tkey>::avl_insert ( Tkey key, string value ) {

	cout << "Inserindo: " << key << endl;
	root = insert( root, key, value );

}

/* -------------------------- Remoção ----------------------------*/

template<typename Tkey>
Node<Tkey>* AVLTree<Tkey>::fixup_node_deletion ( Node<Tkey>* node ) {
	
	// ajustando a altura do nó
	node->setHeight( 1 + max( avl_height(node->left) , avl_height(node->right)) );
	
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
	else if ( balance < -1 && avl_balance(node->left) <= 0 ) {
		return rightRotation(node);
	}
	// Caso simetrico 4.c
	else if ( balance < -1 && avl_balance(node->left) > 0 ) {
		node->left = leftRotation(node->left);
		return rightRotation(node);
	}
	return node;
}

template<typename Tkey>
Node<Tkey>* AVLTree<Tkey>::delete_predecessor (Node<Tkey> *before, Node<Tkey> *node) {

	if ( node->right != nullptr ) {
		node->right = delete_predecessor( before, node->right );
	}
	else {
		root->key = node->key;
		Node<Tkey> *aux = node->left;
		delete node;
		return aux; 
	}
	// atualiza o campo 'height' e regula o nó
	node = fixup_node_deletion(node);
	return node;
}

// Interno
template<typename Tkey>
Node<Tkey>* AVLTree<Tkey>::remove ( Node<Tkey>* node, Tkey key ) {
	
	if ( node == nullptr ) {
		return nullptr;
	}else if ( key < node->getKey() ) {
		node->left = remove(node->left, key);
	}else if( key > node->getKey() ){
		//cout << "Passou aqui" << endl;
		node->right = remove(node->right, key);
	
	// Nó não tem filho
	}else if ( node->left == nullptr && node->right == nullptr ) {
		delete node;
		return nullptr;
	}
	// Nó tem algum dos dois filhos
	else if ( node->left == nullptr || node->right == nullptr ) {
		//Node *aux = node->left ? node->left : node->right;
		Node<Tkey> *aux;
		if ( node->left != nullptr )
			aux = node->left;
		else
			aux = node->right;
			
		delete node;
		return aux;
	}
	else { // Nó tem dois filhos
		node->left = delete_predecessor( node, node->left );
	}
	
	node = fixup_node_deletion(node);
	return node;	
}

// Externo
template<typename Tkey>
void AVLTree<Tkey>::avl_delete ( Tkey key ){
	
	if ( root == nullptr ) {
		return;
	}
	
	root = remove ( root, key );
}

int main () {

	AVLTree<int> tree;

	tree.avl_insert(5, "5");
	tree.avl_insert(2, "2");
	cout << "Deu bom" << endl;
	tree.avl_insert(9, "9");

	tree.avl_preorder();

	return 0;
}