# ifndef NODE_H
# define NODE_H

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

# endif
