#include <bits/stdc++.h>

using namespace std;

enum Color { RED , BLACK };

/* Definição de Node */
template<typename K, typename V>
class Node {
public :
	K key ;
	V value ;
	Color color ;
	Node<K, V> * left ;
	Node<K, V> * right ;
	Node<K, V> * parent ;
};

template<typename K = int , typename V = int>
class RBTree {

	private :
		Node<K, V> * root ;
		Node<K, V> * NIL ;

	protected :
		void leftRotate( Node<K, V> * node ) ;
		void rightRotate( Node<K, V> * node ) ;
		void RBinsert( Node<K, V> * node ) ;
		void RBinsert_fixUp( Node<K, V> * node ) ;
		void RBdelete( Node<K, V> * z ) ;
		void RBdelete_fixUp( Node<K, V> * z ) ;
		void clear( Node<K, V> *node );
		Node<K, V>* minimum( Node<K, V> * node ) ;
	
		public :
		RBTree ();
		~RBTree ();
		void insert ( const K &key , const V &v );
		void remove ( const K &key );
		bool search ( const K &key ) const;
		void removeAll ();
		void preorder () const;
		bool empty () const;
		int blackheight();
};

// Constructor
template<typename K, typename V>
RBTree<K, V>::RBTree() {
	NIL = new Node<K, V>;
	NIL->key = 0;
	NIL->left = NIL->right = NIL->parent = NIL ;
	NIL->color = BLACK ;
	root = NIL ;
}

// Destructor
template<typename K, typename V>
RBTree<K, V>::~RBTree() {
	RBTree<K, V>::clear( root ) ;
	delete NIL ;
	NIL = nullptr ;
	root = nullptr ;
}

template<typename K, typename V>
void RBTree<K, V>::preorder () const {

	Node<K, V> *node = root;

	stack<Node<K, V>*> stack;

	stack.push( node );

	while ( !stack.empty() ) {

		Node<K, V> *node = stack.top();

		cout << "Key: " << node->key << " Color " << node->color << endl;

		stack.pop();
		if ( node->right != NIL)
			stack.push(node->right); 
		if ( node->left != NIL)
			stack.push(node->left);
	}
}

template<typename K, typename V>
bool RBTree<K, V>::search ( const K &key ) const {
	
	Node<K, V> *node = root;

	while ( node != NIL ) {

		if( node == NIL ){
			return false;
		}else if( node->key == key ){
			return true;
		}else if( key < node->key ){
			node = node->left;
		}else if( key > node->key )
			node = node->right;
	}
	
	return false;
}

template<typename K, typename V>
Node<K, V>* RBTree<K, V>::minimum( Node<K, V> *node ){
	
	while( node->left != NIL ){
		node = node->left;
	}

	return node;

}

template<typename K, typename V>
void RBTree<K, V>::clear(Node<K, V> *r) {

	Node<K, V> *node = r;
    stack<Node<K, V>*> stack;

    if( node != NIL ) {
        stack.push( node );
    }
    while( !stack.empty() ) {

        Node<K, V> *node = stack.top();
        if(node->right != NIL) {
            stack.push(node->right);
        }
        if(node->left != NIL) {
            stack.push(node->left);
        }
        if( node->right == NIL && node->left == NIL ) {
            RBTree::RBdelete( stack.top() );
            stack.pop();
        }
    }
}

template<typename K, typename V>
bool RBTree<K, V>::empty () const {
	
	if( root != NIL )
		return false;
	return true;

}

template<typename K, typename V>
void RBTree<K, V>::removeAll () {
	clear(root);
}

template<typename K, typename V>
int RBTree<K, V>::blackheight() {

	int value = 0;

	if ( root == NIL) {
		value = 0;
	}else {
		Node<K, V> *node = root;
		value = 1;

		while ( node != NIL ) {
			if ( node->color != RED && node != root ){
				value++;
			}
			node = node->left;
		}	
	}

	return value;
}

/*----------------------------- Rotação ------------------------------------- */

template<typename K, typename V>
void RBTree<K, V>::leftRotate ( Node<K, V> * x ) {

	Node<K, V>* y = x->right;
	x->right = y->left;

	if (y->left != NIL ){
		y->left->parent = x ;
	}
	y->parent = x->parent ;
	if (x->parent == NIL ) {
		root = y ;
	} else if ( x == x->parent->left ) {
		x->parent->left = y ;
	} else {
		x->parent->right = y ;
	}
	y->left = x ;
	x->parent = y ;
}

template<typename K, typename V>
void RBTree<K, V>::rightRotate ( Node<K, V> * x ) {

	Node<K, V>* y = x->left; 
	x->left = y->right;

	if (y->right != NIL ){
		y->right->parent = x;
	}
	y->parent = x->parent ;
	if (x->parent == NIL ) {
		root = y ;
	}else if( x == x->parent->right ) {
		x->parent->right = y ;
	} else {
		x->parent->left = y ;
	}

	y->right = x ;
	x->parent = y ;
}

/* Insert Public */
template<typename K, typename V>
void RBTree<K, V>::insert ( const K &key , const V &v ) {

	// Allocate a new Node
	Node<K, V> *newNode = new Node<K, V> {};
	newNode->key = key ;
	newNode-> value = v ;
	newNode->left = newNode-> right = NIL;
	newNode->parent = NIL;

	// Do a normal BST insert
	RBinsert( newNode );

}

/* Insert Internal */
template<typename K, typename V>
void RBTree<K, V>::RBinsert ( Node<K, V> *z ) {
	
	Node<K, V> *father = NIL ;
	Node<K, V> *son = root ;

	/* Descida */
	while ( son != NIL ) {
		father = son ;
		if (z->key == son->key ) {
			delete z;
			return;
		}
		son = (z->key < son->key ) ? son->left : son->right ;
	}

	z->parent = father;
	if ( father == NIL )
		root = z;
	else if ( z->key < father->key ){
		father->left = z;
	}
	else{ 
		father->right = z;
	}

	z->left = z->right = NIL;
	z->color = RED;

	// Fix Red Black Tree violations
	RBinsert_fixUp( z );

}

/* Ajuste */
template<typename K, typename V>
void RBTree<K, V>::RBinsert_fixUp ( Node<K, V> *z ) {

	while ( z->parent->color == RED ) {
		/* Lado esquerdo */ 
		if ( z->parent == z->parent->parent->left ) {
			Node<K, V> *uncle = z->parent->parent->right;
			 /* Case 1 */
			if ( uncle->color == RED ) {
				cout << "Caso 1 a" << endl;
				z->parent->color = BLACK ;
				uncle->color = BLACK ;
				z->parent->parent->color = RED;
				z = z->parent->parent ;
			} else {
			/* Case 2 a */
				if ( z == z->parent->right ) {
					cout << "Caso 2 a" << endl; 
					z = z->parent;
					leftRotate( z );
				}
			/* Case 3 a */
				cout << "Caso 3 a" << endl;
				z->parent->color = BLACK ;
				z-> parent->parent->color = RED ;
				rightRotate( z->parent->parent ) ;
			}
		}
		/* Lado esquerdo */
		else { 
			Node<K, V> *uncle = z->parent->parent->left;
			/* Caso 1 b */
			if ( uncle->color == RED ){
				cout << "Caso 1 b" << endl;
				z->parent->color = BLACK;
				z->parent->parent->color = RED;
				uncle->color = BLACK;
				z = z->parent->parent;
			}else{
				/* Case 2 b */ 
				if ( z == z->parent->left ) {
					cout << "Caso 2 b" << endl;
					z = z->parent;
					rightRotate( z );
				}
				/* Case 3 a */
				cout << "Caso 3 b" << endl;
				z->parent->color = BLACK;
				z->parent->parent->color = RED;
				leftRotate( z->parent->parent );
			}
		}
	}

	root->color = BLACK ; // Guarantee Property 2

}

/*----------------------------- Remoção -------------------------------------*/
template<typename K, typename V>
void RBTree<K, V>::remove ( const K &key ) {

	Node<K, V> *p = root;

	/* Buscando o node para remover s */
	while ( p != NIL && p->key != key ) {
		
		p = ( key < p->key ) ? p->left : p->right;
	}

	if ( p != NIL ) RBdelete( p );

}

template<typename K, typename V>
void RBTree<K, V>::RBdelete (Node<K, V> *z) {

	Node<K, V> *y; // node que será removido
	Node<K, V> *x; // que ficará no lugar de y

	/* Descobrir se z tem ou não 2 filhos */
	if( z->left == NIL || z->right == NIL ){
		y = z;
	}else{
		y = minimum( z->right ); // sucessor de z
	}

	/* Atribuindo a x, o filho que é diferente de NIL */ 
	if ( y->left != NIL ) {
		x = y->left;
	}else{ 
		x = y->right;
	}

	if ( x != NIL ) x->parent = y->parent;

	if ( y->parent == NIL ) {
		root = x;
	}else{
		if ( y == y->parent->left ){
			y->parent->left = x;
		}
		else{ 
			y->parent->right = x;
		}
	}

	if ( y != z ) {
		z->key = y->key;
		z->value = y->value;
	}
	if ( y->color == BLACK ){
		RBTree::RBdelete_fixUp(x);
	}
	delete y;
}

template<typename K, typename V>
void RBTree<K, V>::RBdelete_fixUp ( Node<K, V> *x ) {

	while ( x != root && x->color == BLACK ) {

		/* Caso esquerdo */
		if ( x == x->parent->left ) {

			Node<K, V> *w = x->parent->right;
			/* Caso 1 a */
			if ( w->color == RED ) {
				w->color = BLACK;
				x->parent->color = RED;
				leftRotate ( x->parent );
				w = x->parent->right;
			}
			/* Caso 2 a */
			if ( w->left->color == BLACK &&
				w->right->color == BLACK ) {
				w->color = RED;
				x = x->parent;
			}
			else {
				/* Case 3 a */
				if (w->right->color == BLACK ) {
					w->left->color = BLACK;
					w->color = RED;
					rightRotate( w );
					w = x->parent->right ;
				}
				/* Case 4 a */
				w->color = x->parent->color;
				x->parent->color = BLACK;
				w->right->color = BLACK;
				leftRotate ( x->parent );
				x = root ;
			}
		}
		/* Caso direito */
		else {
			Node<K, V> *w = x->parent->left;
			/* Caso 1 b */
			if ( w->color == RED) {
				w->color == BLACK;
				x->color = RED;
				rightRotate( x->parent );
				w = x->parent->left;
			}
			/* Caso 2 b */
			if ( w->left->color == BLACK &&
				w->right->color == BLACK ) {
				w->color = RED;
				x = x->parent;
			}
			else {
				/* Caso 3 b */
				if ( w->left->color == BLACK ) {
					w->right->color = BLACK;
					w->color = RED;
					leftRotate( w );
					w = x->parent->left;
				}
				/* Caso 4 b */
				w->color = x->parent->color;
				x->parent->color = BLACK;
				w->left->color = BLACK;
				rightRotate( x->parent );
				x = root;
			}
		}
	}

	x->color = BLACK;

}
