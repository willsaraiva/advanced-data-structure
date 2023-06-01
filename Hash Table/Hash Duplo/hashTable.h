#ifndef hashtable_H
#define hashtable_H

#include <bits/stdc++.h>

using namespace std;

/* Definição do tipo EntryType */
enum EntryType { ACTIVE, EMPTY};

template <typename Tkey, typename Tvalue>
class HashTable {
public:
    explicit HashTable( int size = 1000 );
    bool contains( const Tkey &x ) const;
    void makeEmpty();
    bool insert( const Tkey &x, const Tvalue &v );
    bool remove( const Tkey &x );
    int size() const;
    bool search( const Tkey &x, Tvalue &result );
    void print() const;

private:
    struct HashEntry { 
        std::pair<Tkey,Tvalue> element;
        EntryType status;

        HashEntry( const Tkey &x = Tkey{ }, const Tvalue &v = Tvalue{ }, EntryType i = EMPTY )
            : element( make_pair(x,v) ), status( i ) { }
    };

    std::vector<HashEntry> table;
    /* número de elementos da tabela */
    int currentSize;

    /* Função de Hash */
    size_t hashFunction( const Tkey &x, int i ) const;
};

/* Constructor */
template <typename Tkey, typename Tvalue>
HashTable< Tkey, Tvalue >::HashTable( int tableSize ) 
    : currentSize( 0 )
{
    table.resize(tableSize);
}

/* Retorna o tamanho da tabela */
template <typename Tkey, typename Tvalue>
int HashTable< Tkey, Tvalue >::size() const {
    return currentSize;
} 

/* Mostra os elementos da tabela */
template <typename Tkey, typename Tvalue>
void HashTable< Tkey, Tvalue >::print() const {
	for ( int i = 0 ; i < table.size() ; i++ ) {
		if (table[i].status == ACTIVE) {
			cout << i << " : " << table[i].element.first << " : " << table[i].element.second << endl;
		}
	}
}

/* Remove todos os elementos */
template <typename Tkey, typename Tvalue>
void HashTable< Tkey, Tvalue >::makeEmpty() {
	table.clear();
	currentSize = 0;
}

/* Função de Hash */ 
template <typename Tkey, typename Tvalue>
size_t HashTable< Tkey, Tvalue >::hashFunction( const Tkey &x, int i ) const {
    std::hash<Tkey> hf;
    // hashFunction(x, i) = (hs1(x) + i * hs2(x)) % table.size()
    return (hf(x) % table.size() + i * (1 + (hf(x) % (table.size() - 1 )))) % table.size();
} 

/* Verifica se a chave x está na tabela */
template <typename Tkey, typename Tvalue >
bool HashTable< Tkey, Tvalue>::contains( const Tkey &x ) const {
    int i = 0;
    while ( i < table.size() ) {
        size_t elemento = hashFunction( x, i);
        if ( table[elemento].element.first == x && table[elemento].status == ACTIVE ) {
            return true;
        }
        i++;
    }
    return false;
}

/* Busca uma chave x na tabela e retorna o valor associado a ela */
template <typename Tkey, typename Tvalue >
bool HashTable< Tkey, Tvalue>::search( const Tkey &x, Tvalue &result ) {
	int i = 0;
    while ( i < table.size() ) {
        size_t elemento = hashFunction( x, i);
        if ( table[elemento].element.first == x && table[elemento].status == ACTIVE ) {
        	result = table[elemento].element.second;
            return true;
        }
        i++;
    }
    return false;
}

/* Função que remove um elemento na tabela */
template <typename Tkey, typename Tvalue >
bool HashTable< Tkey, Tvalue>::remove( const Tkey &x ) {
	int i = 0;
    while ( i < table.size() ) {
        size_t elemento = hashFunction( x, i);
        if ( table[elemento].element.first == x && table[elemento].status == ACTIVE ) {
        	table[elemento].status = EMPTY;
            return true;
        }
        i++;
    }
    return false;
}

/* Função que insere um elemento na tabela */
template <typename Tkey, typename Tvalue>
bool HashTable< Tkey, Tvalue >::insert( const Tkey &x, const Tvalue &v ) {
    
    int i = 0;

    if ( contains(x) ) {
        return false;
    }
    while ( i < table.size() ) {
        size_t elemento = hashFunction(x, i);
        if ( table[elemento].status == EMPTY ) {
            table[elemento].element.first = x;
            table[elemento].element.second = v;
            table[elemento].status = ACTIVE;
            currentSize++;
            return true;
        }
    	i++;
    }
}

#endif