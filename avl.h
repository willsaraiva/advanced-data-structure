#ifndef AVL_H
#define AVL_H
#include "node.h"
#include <bits/stdc++.h>

using std::cout;
using std::string;
using std::endl;
using std::max;

template<typename K>
class AVLTree {
	private:
		Node<K> *root;

	protected:
		Node<K> *avl_rightRotation(Node<K> *node) {
			Node<K> *u = node->left;
			node->left = u->right;
			u->right = node;

			node->height = 1 + max(avl_height(node->left), avl_height(node->right));
			u->height = 1 + max(avl_height(u->left), avl_height(u->right));

			return u;
		}

		Node<K> *avl_leftRotation(Node<K> *node) {
			Node<K> *u = node->right;
			node->right = u->left;
			u->left = node;

			node->height = 1 + max(avl_height(node->left), avl_height(node->right));
			u->height = 1 + max(avl_height(u->left), avl_height(u->right));

			return u;
		}

		Node<K> *avl_fixup_node(Node<K> *node, K key) {
			int bal = avl_balance(node);

			if(bal < -1 and key < node->left->key) return avl_rightRotation(node);
			else if(bal < -1 and key > node->left->key) {
				node->left = avl_leftRotation(node->left);
				return avl_rightRotation(node);
			}else if(bal > 1 and key > node->right->key) return avl_leftRotation(node);
			else if(bal > 1 and key < node->right->key) {
				node->right = avl_rightRotation(node->right);
				return avl_leftRotation(node);
			}
			return node;
		}

		Node<K> *avl_fixup_node_deletion(Node<K> *node) {
			node->height = 1 + max(avl_height(node->right), avl_height(node->left));
			
			int bal = avl_balance(node);
			
			if(bal > 1 && avl_balance(node->right) >= 0) {
				node = avl_leftRotation(node);
			}else if(bal > 1 && avl_balance(node->right) < 0) {
				node->right = avl_rightRotation(node->right);
				node = avl_leftRotation(node);
			}else if(bal < -1 && avl_balance(node->left) <= 0) {
				node = avl_rightRotation(node);
			}else if(bal < -1 && avl_balance(node->left) > 0) {
				node->left = avl_leftRotation(node->left);
				node = avl_rightRotation(node);
			}
			return node;
		}

		Node<K> *avl_delete_pred(Node<K> *root , Node<K> *node) {
			if(node->right != nullptr) {
				node->right = avl_delete_pred(root, node->right);
			}else {
				root->key = node->key;
				Node<K> *aux = node->left;
				delete node;
				return aux;
			}
			node = avl_fixup_node_deletion(node);
			return node;
		}

		int avl_height(Node<K> *node) {
			if(node == nullptr) return 0;
			else return node->height;
		}

		int avl_balance(Node<K> *node) {
			if(node == nullptr) return 0;
			return avl_height(node->right) - avl_height(node->left);
		}

		Node<K> *avl_clear(Node<K> *node) {
			if(node != nullptr) {
				node ->left = avl_clear(node ->left);
				node ->right = avl_clear(node ->right);
				cout << "Erasing the key: " << node ->key << endl;
				delete node;
			}
			return nullptr;
		}

		Node<K> *avl_search(Node<K> *node, K key) {
			if(node == nullptr) {
				return nullptr;
			}
			if(key < node->key) {
				return avl_search(node->left, key);
			}else if(key > node->key) {
				return avl_search(node->right, key);
			}else 	
				return node;
		}

		Node<K> *avl_insert(Node<K> *node, K key, string V1, string V2, string V3, string V4, string V5, bool &ans) {
			if(node == nullptr) {
				node = new Node<K>();
				node->key = key;
				node->V1 = V1;
				node->V2 = V2;
				node->V3 = V3;
				node->V4 = V4;
				node->V5 = V5;
				node->left = nullptr;
				node->right = nullptr;
				node->height = 1;
				ans = true;
				return node;
			}
			if(key < node->key) {
				node->left = avl_insert(node->left, key, V1, V2, V3, V4, V5, ans);
			}else if(key > node->key) {
				node->right = avl_insert(node->right, key, V1, V2, V3, V4, V5, ans);
			}else {
				ans = false;
				return node;
			}

			node->height = 1 + max(avl_height(node->left), avl_height(node->right));

			node = avl_fixup_node(node, key);

			return node;
		}

		Node<K> *avl_delete(Node<K> *node, K key, bool &ans) {
			if(node == nullptr) {
				ans = false;
				return nullptr;
			}
			if(key < node->key) {
				node->left = avl_delete(node->left, key, ans);
			}else if(key > node->key) {
				node->right = avl_delete(node->right, key, ans);
			}else if(node->left == nullptr and node->right == nullptr) {
				ans = true;
				delete node;
				return nullptr;
			}else if(node->left == nullptr || node->right == nullptr) {
				Node<K> *child = node->left ? node->left : node->right;
				ans = true;
				delete node;
				return child;
			}else {
				ans = true;
				node->left = avl_delete_pred(node, node->left);
			}
			node = avl_fixup_node_deletion(node);
			return node;
		}

		void avl_inorder(Node<K> *node) {
			if(node != nullptr) {
				avl_inorder(node->left);
				cout << "(" << node->key << ")" << endl;
				avl_inorder(node->right);
			}
		}

	public:

		AVLTree(void) {
			root = nullptr;
		}

		~AVLTree(void) {
			avl_clear(root);
			root = nullptr;
		}

		Node<K> *search(K key) {
			return avl_search(root, key);
		}

		bool insert(K key, string V1, string V2, string V3, string V4, string V5) {
			bool ans = false;
			root = avl_insert(root, key, V1, V2, V3, V4, V5, ans);
			return ans;
		}

		bool remove(K key) {
			bool ans = false;
			root = avl_delete(root, key, ans);
			return ans;
		}

		void inorder() {
			avl_inorder(root);
		}

};

#endif 